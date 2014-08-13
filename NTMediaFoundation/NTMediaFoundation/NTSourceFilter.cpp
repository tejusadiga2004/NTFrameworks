//
//  NTSourceFilter.cpp
//  NTMediaFoundation
//
//  Created by Tejus on 11/02/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTFilter.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTSourceFilter.h"
#undef NT_LIBRARY_USAGE

static void TimerFired (NTObject* inUserInfo)
{
    NTBackgroundTask* backTask = (NTBackgroundTask*)inUserInfo;
    backTask->PerformTask();
}

NTSourceFilter::NTSourceFilter (NTString* inFilterName)
: NTFilter(inFilterName, kNTFilterType_Source), NTConnectable(this)
{
    
}

NTSourceFilter::~NTSourceFilter ()
{
    
}

bool NTSourceFilter::Start ()
{
    if (!this->IsRunning()) {
        if (NTFilter::Start()) {
            _sourceTimer = new NTTimer(TimerFired, 30, true, (NTBackgroundTask*)this);
            _sourceTimer->Start();
            return true;
        }
    }
    
    return false;
}

bool NTSourceFilter::Stop ()
{
    if (this->IsRunning()) {
        NTSafeRelease(_sourceTimer);
        return NTFilter::Stop();
    }
    
    return false;
}