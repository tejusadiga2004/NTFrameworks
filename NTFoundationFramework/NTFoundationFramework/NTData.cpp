//
//  NTData.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 22/01/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTAllocator.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTData.h"
#undef NT_LIBRARY_USAGE

#include <memory.h>

typedef struct NTDataInternal {
    char* _data;
    int _length;
    
    NTDataInternal () : _data(nullptr), _length(0) {
    }
    
    NTDataInternal (const char* inData, int inLength) : _data(nullptr), _length(0) {
        _data = NTAllocatorFactory::GetAllocator()->AllocateMemory(inLength);
        if (_data != nullptr) {
            memcpy(_data, inData, inLength);
            _length = inLength;
        }
    }
    
    NTDataInternal (NTData* inData) : _data(nullptr), _length(0) {
        _data = NTAllocatorFactory::GetAllocator()->AllocateMemory(inData->Length());
        if (_data != nullptr) {
            inData->GetData(_data, inData->Length());
            _length = inData->Length();
        }
    }
    
    ~NTDataInternal () {
        SafeRelease(_data);
    }
    
} NTDataInternal;

NTData::NTData ()
: _internal(new NTDataInternal())
{
    
}

NTData::NTData (const char* inData, int inLength)
: _internal(new NTDataInternal(inData, inLength))
{
    
}

NTData::NTData (NTData* inData)
: _internal(new NTDataInternal(inData))
{
    
}

NTData::~NTData ()
{
    SafeRelease(_internal);
}

void NTData::AppendData (NTData* inData)
{
    NTAllocatorFactory::GetAllocator()->ReallocateMemory(&_internal->_data, _internal->_length, inData->Length());
    inData->GetData(_internal->_data + _internal->_length, inData->Length());
}

void NTData::GetData (const char* inBuffer, int inDataLength)
{
    if (inBuffer != nullptr) {
        memcpy((char*)inBuffer, _internal->_data, (inDataLength > _internal->_length)? _internal->_length : inDataLength);
    }
}

const char* NTData::GetDataBase()
{
    return _internal->_data;
}

int NTData::Length () const
{
    return _internal->_length;
}
