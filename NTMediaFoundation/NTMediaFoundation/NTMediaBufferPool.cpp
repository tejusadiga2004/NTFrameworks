//
//  NTMediaBufferPool.cpp
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 18/08/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//


#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTMediaBuffer.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTMediaBufferPool.h"
#undef NT_LIBRARY_USAGE

class NTMediaBufferObject : public NTMediaBuffer {
public:
    
    NTMediaBufferObject(const char* inBuffer, int inBufferSize)
    : NTMediaBuffer(inBuffer, inBufferSize), isFree(true) { }
    
    ~NTMediaBufferObject () { }
    
    void SetIsFree (bool inIsFree)
    {
        isFree = inIsFree;
    }
    
    bool GetIsFree() const
    {
        return isFree;
    }
    
private:
    
    bool isFree;
};


NTMediaBufferPool::NTMediaBufferPool (int inBufferSize, int inPoolSize)
: NTObject(), bufferList(nullptr), bufferSize(inBufferSize)
{
    bufferList = new NTMutableArray();
    
    for (int cnt = 0; cnt < inPoolSize; cnt++) {
        NTMediaBufferObject* buffer = new NTMediaBufferObject(nullptr, inBufferSize);
        
        if (buffer) {
            bufferList->AppendElement(buffer);
        }
    }
}

NTMediaBufferPool::~NTMediaBufferPool ()
{
    NTSafeRelease(bufferList);
}

NTMediaBuffer* NTMediaBufferPool::RequestBuffer ()
{
    NTMediaBufferObject* bufferObject = nullptr;
    
    int cnt = 0;
    
    do {
        NTMediaBufferObject* aBufferObject = (NTMediaBufferObject*) bufferList->ObjectAtIndex(cnt);
        
        if (aBufferObject->GetIsFree()) {
            bufferObject = aBufferObject;
            bufferObject->SetIsFree(true);
            break;
        }
        
    } while (cnt < bufferList->Size());
    
    
    if (bufferObject == nullptr) {
        NTMediaBufferObject* buffer = new NTMediaBufferObject(nullptr, bufferSize);
        
        if (buffer) {
            bufferList->AppendElement(buffer);
            bufferObject = buffer;
        }
    }
    
    return bufferObject;
}

void NTMediaBufferPool::SurrenderBuffer (NTMediaBuffer* inBuffer)
{
    NTMediaBufferObject* objectInList = reinterpret_cast<NTMediaBufferObject*>(inBuffer);
    
    if (objectInList != nullptr) {
        objectInList->SetIsFree(false);
    }
}

int NTMediaBufferPool::QueryBufferSize () const
{
    return bufferSize;
}


