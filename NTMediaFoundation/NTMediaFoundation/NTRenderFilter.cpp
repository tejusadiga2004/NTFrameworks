//
//  NTRenderFilter.cpp
//  NTMediaFoundation
//
//  Created by Tejus on 11/02/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTFilter.h"
#include "NTMediaSample.h"
#include "NTFormatDescription.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTRenderFilter.h"
#undef NT_LIBRARY_USAGE

#include "NTRenderFilter.h"


NTRenderFilter::NTRenderFilter (NTString* inFilterName, NTFilterType inFilterType)
: NTFilter(inFilterName, inFilterType)
{
    
}

NTRenderFilter::~NTRenderFilter ()
{
    
}

void NTRenderFilter::PushSample (NTMediaSample* inSample)
{
    std::lock_guard<std::mutex> lock(_mutex);
    
    if (!_sampleQueue->IsQueueFull()) {
        inSample->Retain();
        _sampleQueue->EnqueueObject(inSample);
        _backgroundTask->PerformTask();
    }
}

bool NTRenderFilter::Start ()
{
    std::lock_guard<std::mutex> lock(_mutex);
    bool status = false;
    _sampleQueue = new NTQueue(30);
    status = NTFilter::Start();
    return status;
}

bool NTRenderFilter::Stop ()
{
    bool status = NTFilter::Stop();
    NTSafeRelease(_sampleQueue);
    return status;
}

NTMediaSample* NTRenderFilter::GetSampleFromQueue ()
{
    std::lock_guard<std::mutex> lock(_mutex);
    
    if (!_sampleQueue->IsQueueEmpty()) {
        return (NTMediaSample*)_sampleQueue->DequeueObject();
    }
    
    return nullptr;
}


