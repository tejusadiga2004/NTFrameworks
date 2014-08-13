//
//  NTAllocator.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 20/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTAllocator.h"
#undef NT_LIBRARY_USAGE

#include <mutex>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>

static std::atomic<INTAllocator*> _allocator(nullptr);

INTAllocator* NTAllocatorFactory::GetAllocator (NTAllocatorType inAllocator)
{
    if (_allocator.load() == nullptr) {
        switch (inAllocator) {
                
            case kNTAllocatorTypeNew: {
                _allocator= new NTAllocatorNew();
                break;
            }
                
            case kNTAllocatorTypeMalloc: {
                _allocator = new NTAllocatorMalloc();
                break;
            }
                
            case kNTAllocatorTypeCalloc: {
                _allocator = new NTAllocatorCalloc();
                break;
            }
        }
    }
    
    return _allocator.load();
}

void NTAllocatorFactory::Release (INTAllocator* inAllocator)
{
    if (inAllocator) {
        delete inAllocator;
        inAllocator = nullptr;
    }
}


NTAllocator::NTAllocator ()
: NTObject()
{
}

NTAllocator::~NTAllocator () {
}

void NTAllocator::ReallocateMemory (char** inMemoryBlock, int inOldLength, int inNewLength)
{
    char* newBase = _allocator.load()->AllocateMemory(inNewLength);
    if (newBase != nullptr) {
        memset(newBase, 0, inNewLength);
        if (inMemoryBlock != nullptr) {
            memcpy(newBase, inMemoryBlock, (inOldLength > inNewLength)? inNewLength : inOldLength);
            _allocator.load()->ReleaseMemory(*inMemoryBlock);
            *inMemoryBlock = newBase;
        }
    }
}


NTAllocatorNew::NTAllocatorNew ()
: NTAllocator()
{
}

NTAllocatorNew::~NTAllocatorNew () {
}

char* NTAllocatorNew::AllocateMemory (int inLength)
{
    return new char[inLength];
}

void NTAllocatorNew::ReleaseMemory (char* inMemory)
{
    SafeRelease(inMemory);
}


NTAllocatorMalloc::NTAllocatorMalloc ()
: NTAllocator()
{
}

NTAllocatorMalloc::~NTAllocatorMalloc () {
}

char* NTAllocatorMalloc::AllocateMemory (int inLength)
{
    return (char*)malloc(inLength);
}

void NTAllocatorMalloc::ReleaseMemory (char* inMemory)
{
    if (inMemory) {
        free(inMemory);
        inMemory = nullptr;
    }
}


NTAllocatorCalloc::NTAllocatorCalloc ()
: NTAllocator()
{
}

NTAllocatorCalloc::~NTAllocatorCalloc () {
}

char* NTAllocatorCalloc::AllocateMemory (int inLength)
{
    return (char*)calloc(1, inLength);
}

void NTAllocatorCalloc::ReleaseMemory (char* inMemory)
{
    if (inMemory) {
        free(inMemory);
        inMemory = nullptr;
    }
}


