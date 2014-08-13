//
//  NTTimer.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 21/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTBackgroundTask.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTTimer.h"
#undef NT_LIBRARY_USAGE

#include <thread>

typedef struct NTTImerInternal : public NTBackgroundTask, public INTBackgroundTaskDelegate {
    
    NTTimerProc _proc;
    int         _timeInterval;
    bool        _shouldRepeat;
    bool        _firstTimeFired;
    NTObject*   _context;
    NTTimer*    _timer;
    
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    
    NTTImerInternal (NTTimerProc   inTimerProc,
                     int            inTimeInterval,
                     bool           inShouldRepeat,
                     NTObject*      inContext,
                     NTTimer*       inTimer)
    : NTBackgroundTask(this),
     _proc(inTimerProc),
     _timeInterval(inTimeInterval),
     _shouldRepeat(inShouldRepeat),
     _firstTimeFired(false),
     _context(inContext),
     _timer(inTimer)
    {
        _context->Retain();
    }
    
    ~NTTImerInternal () {
        this->FinishTask();
        _proc = nullptr;
        NTSafeRelease(_context);
    }
    
    bool OnStartTask () {
        _start = std::chrono::high_resolution_clock::now();
        return true;
    }
    
    bool OnPerformTask () {

        std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
        
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count() >= _timeInterval) {
            if (nullptr != _proc) {
                _proc(_context);
            }
            
            if (!_shouldRepeat) {
                this->FinishTask();
            }
        }
    
        return true;
    }
    
    void OnFinishTask () {
        
    }
    
} NTTImerInternal;




NTTimer::NTTimer (NTTimerProc inTimerProc, int inTimeInterval, bool inShouldRepeat, NTObject* inUserInfo)
: NTObject(), _internal(new NTTImerInternal(inTimerProc, inTimeInterval, inShouldRepeat, inUserInfo, this))
{
    
}

NTTimer::~NTTimer ()
{
    NTSafeRelease(_internal);
}

void NTTimer::Start ()
{
    _internal->StartTask();
}

