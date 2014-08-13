//
//  NTBackgrounndTask.cpp
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
#include "NTBackgroundTask.h"
#undef NT_LIBRARY_USAGE

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

typedef struct NTBackgroundTaskInternal {
    std::thread _thread;
    std::mutex _mutex;
    std::condition_variable _condition;
    std::atomic_bool _isRunning;
    
    INTBackgroundTaskDelegate* _delegate;
    
    NTBackgroundTaskInternal (INTBackgroundTaskDelegate* inDelegate) : _delegate(inDelegate) {
        _isRunning = false;
    }
    
    ~NTBackgroundTaskInternal () {
        
    }
    
    bool IsRunning () {
        return _isRunning.load();
    }
    
    void Run () {
        
        if (nullptr != _delegate) {
            bool shouldContinue = _delegate->OnStartTask();
            _isRunning.store(shouldContinue);
        }
        
        _condition.notify_one();

        while (_isRunning.load()) {
            std::unique_lock<std::mutex> lock(_mutex);
            if (std::cv_status::no_timeout == _condition.wait_for(lock, std::chrono::milliseconds(10))) {
                if (nullptr != _delegate) {
                    _delegate->OnPerformTask();
                }
            }
        }
        
        if (nullptr != _delegate) {
            _delegate->OnFinishTask();
        }
    }
    
} NTBackgroundTaskInternal;

static void ThreadProc (NTBackgroundTaskInternal* context) {
    context->Run();
}

NTBackgroundTask::NTBackgroundTask (INTBackgroundTaskDelegate* inDelegate)
: NTObject(), _internal(new NTBackgroundTaskInternal(inDelegate))
{
    
}

NTBackgroundTask::~NTBackgroundTask ()
{

}

bool NTBackgroundTask::StartTask ()
{
    bool status = false;
    if (!_internal->IsRunning()) {
        _internal->_thread = std::thread(ThreadProc, _internal);

        std::unique_lock<std::mutex> lock(_internal->_mutex);
        if (std::cv_status::no_timeout == _internal->_condition.wait_for(lock, std::chrono::microseconds(100))) {
            status = true;
        }
    }
    
    return status;
}

void NTBackgroundTask::PerformTask ()
{
    _internal->_condition.notify_one();
}

void NTBackgroundTask::FinishTask ()
{
    if (_internal->IsRunning()) {
        _internal->_isRunning.store(false);
        _internal->_condition.notify_one();
        _internal->_thread.join();
    }
}

bool NTBackgroundTask::IsRunning () const
{
    return _internal->_isRunning;
}