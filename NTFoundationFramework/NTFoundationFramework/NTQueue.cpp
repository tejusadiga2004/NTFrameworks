//
//  NTQueue.cpp
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
#include "NTQueue.h"
#undef NT_LIBRARY_USAGE

#include "NTLinkedList.h"

typedef struct NTQueueInternal {
    NTLinkedList* _list;
    int _capasity;
    
    NTQueueInternal (int inCapasity) : _list(new NTLinkedList(inCapasity)), _capasity(inCapasity) {
        
    }
    
    ~NTQueueInternal () {
        NTSafeRelease(_list);
    }
    
} NTQueueInternal;

NTQueue::NTQueue (int inCapacity)
: _internal(new NTQueueInternal(inCapacity))
{
    
}

NTQueue::~NTQueue ()
{
    SafeRelease(_internal);
}

bool NTQueue::IsQueueFull ()
{
    return (_internal->_list->Size() == _internal->_capasity);
}

bool NTQueue::IsQueueEmpty ()
{
    return (_internal->_list->Size() == 0);
}

float NTQueue::GetBufferFullness ()
{
    return (float)(_internal->_list->Size() / _internal->_capasity);
}

bool NTQueue::EnqueueObject (NTObject* inObject)
{
    bool status = false;
    if (inObject != nullptr && !IsQueueFull()) {
        inObject->Retain();
        _internal->_list->InsertBack(inObject);
    }
    return status;
}

NTObject* NTQueue::DequeueObject ()
{
    NTObject* theObject = nullptr;
    if (!IsQueueEmpty()) {
        theObject = _internal->_list->FirstElement();
    }
    return theObject;
}
