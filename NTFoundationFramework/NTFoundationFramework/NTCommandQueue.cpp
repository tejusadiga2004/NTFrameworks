//
//  NTCommandQueue.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 20/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTBackgroundTask.h"
#include "NTQueue.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTCommandQueue.h"
#undef NT_LIBRARY_USAGE

#include <mutex>
#include <atomic>

typedef struct NTCommandQueueInternal : public INTBackgroundTaskDelegate {
    
    std::atomic<NTQueue*> _commandQueue;
    
    NTCommandQueueInternal (int inCapacity)
    : _commandQueue(new NTQueue(inCapacity))
    {
        
    }
    
    ~NTCommandQueueInternal () {
        NTQueue* theQueue = _commandQueue.load();
        NTSafeRelease(theQueue);
    }
    
    bool OnStartTask ()
    {
        return true;
    }
    
    bool OnPerformTask ()
    {
        while (!_commandQueue.load()->IsQueueEmpty()) {
            NTCommand* command = (NTCommand*) _commandQueue.load()->DequeueObject();
            command->OnPerformCommand(command->GetUserData());
            NTSafeRelease(command);
        }
        return true;
    }
    
    void OnFinishTask ()
    {
        OnPerformTask();
    }
    
} NTCommandQueueInternal;


NTCommand::NTCommand (NTObject* inUserData)
: _userData(inUserData)
{
    _userData->Retain();
}

NTCommand::~NTCommand ()
{
    _userData->Release();
}

NTObject* NTCommand::GetUserData ()
{
    return _userData;
}


NTCommandQueue::NTCommandQueue (int inQueueCapacity)
: _internal(new NTCommandQueueInternal(inQueueCapacity)), NTBackgroundTask(_internal)
{
    
}

NTCommandQueue::~NTCommandQueue ()
{
    if (this->IsRunning()) {
        this->FinishTask();
    }
    
    SafeRelease(_internal);
}

bool NTCommandQueue::ScheduleCommand (NTCommand* inCommand)
{
    bool status = false;
    if (this->IsRunning()) {
        this->StartTask();
    }
    
    if (this->IsRunning()) {
        inCommand->Retain();
        _internal->_commandQueue.load()->EnqueueObject(inCommand);
        this->PerformTask();
        status = true;
    }
    
    return status;
}

