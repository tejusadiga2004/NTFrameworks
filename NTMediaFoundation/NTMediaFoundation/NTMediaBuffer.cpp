//
//  NTMediaBuffer.cpp
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 22/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTMediaBuffer.h"
#undef NT_LIBRARY_USAGE

typedef struct NTMediaBufferInternal {
    char* _buffer;
    int         _length;
    
    NTObject* _context;
    
    NTMediaBufferInternal (const char* inBuffer, int inLength) : _buffer((char*)inBuffer), _context(nullptr), _length(0) {
        
        INTAllocator* allocator = NTAllocatorFactory::GetAllocator();
        _buffer = allocator->AllocateMemory(inLength);
        if (_buffer) {
            memset(_buffer, 0, inLength);
            if (inBuffer) {
                memcpy(_buffer, inBuffer, inLength);
                _length = inLength;
            }
        }
    }
    
    ~NTMediaBufferInternal () {
        SafeRelease(_buffer);
        _context = nullptr;
    }
    
} NTMediaBufferInternal;

NTMediaBuffer::NTMediaBuffer (const char* inBuffer, int inLength)
: NTObject(), _internal(new NTMediaBufferInternal(inBuffer, inLength))
{
    
}

NTMediaBuffer::~NTMediaBuffer ()
{
    std::cout << __FUNCTION__ << std::endl;
    SafeRelease(_internal);
}

bool NTMediaBuffer::AquireOwnership (NTObject* inContext)
{
    bool status = (_internal->_context == nullptr);
    if (_internal->_context == nullptr) {
        _internal->_context = inContext;
    }
    return status;
}

bool NTMediaBuffer::RelinqueshOwnership (NTObject* inContext)
{
    bool status = (_internal->_context == inContext);
    if (_internal->_context == inContext) {
        _internal->_context = nullptr;
    }
    return status;
}

const char* NTMediaBuffer::Buffer ()
{
    const char* theData = nullptr;
    if (_internal->_context != nullptr) {
        theData = _internal->_buffer;
    }
    return theData;
}

int NTMediaBuffer::QueryLength ()
{
    return _internal->_length;
}