//
//  NTMediaControl.cpp
//  NTMediaFoundation
//
//  Created by Tejus on 11/02/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTFilter.h"
#include "NTRenderFilter.h"
#include "NTMediaSample.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTMediaControl.h"
#undef NT_LIBRARY_USAGE

NTMediaControl::NTMediaControl (NTRenderFilter* inParentFilter)
: NTObject(), _nextFilter(nullptr), _parentFilter(inParentFilter)
{
    _parentFilter->Retain();
}

NTMediaControl::~NTMediaControl ()
{
    NTSafeRelease(_nextFilter);
    NTSafeRelease(_parentFilter);
}

void NTMediaControl::SetRenderFilter (NTRenderFilter* inFilter)
{
    NTSafeRelease(_nextFilter);
    _nextFilter = inFilter;
    _nextFilter->Retain();
}


NTSourceMediaControl::NTSourceMediaControl (NTRenderFilter* inParentFilter)
: NTMediaControl(inParentFilter)
{
    
}

bool NTSourceMediaControl::OnStartTask ()
{
    return (_nextFilter != nullptr);
}

bool NTSourceMediaControl::OnPerformTask ()
{
    bool status = false;
    
    if (_nextFilter != nullptr) {
        NTMediaSample* aSample = this->GenerateSample();
        if (aSample != nullptr) {
            aSample->Retain();
            _nextFilter->PushSample(aSample);
            aSample->Release();
            status = true;
        } else {
            status = false;
        }
    }
    
    return status;
}

void NTSourceMediaControl::OnFinishTask ()
{
    
}


NTTransformMediaControl::NTTransformMediaControl (NTRenderFilter* inParentFilter)
: NTMediaControl(inParentFilter)
{
    
}

bool NTTransformMediaControl::OnStartTask ()
{
    return (_nextFilter != nullptr);
}

bool NTTransformMediaControl::OnPerformTask ()
{
    bool status = false;
    
    if (_nextFilter != nullptr) {
        NTMediaSample* aSample = nullptr;
        while ((aSample = _parentFilter->GetSampleFromQueue()) != nullptr) {
            NTMediaSample* aSample = _parentFilter->GetSampleFromQueue();
            if (aSample != nullptr) {
                aSample->Retain();
                status = this->ProcessSample(aSample);
                aSample->Release();
            } else {
                status = false;
            }
        }
    }
    
    return status;
}

void NTTransformMediaControl::OnFinishTask ()
{
    
}

void NTTransformMediaControl::DeliverProcessedSample (NTMediaSample* inMediaSample)
{
    if (_nextFilter != nullptr) {
        if (inMediaSample != nullptr) {
            inMediaSample->Retain();
            _nextFilter->PushSample(inMediaSample);
            inMediaSample->Release();
        }
    }
}


NTRenderMediaControl::NTRenderMediaControl (NTRenderFilter* inParentFilter)
: NTMediaControl(inParentFilter)
{
    
}

bool NTRenderMediaControl::OnStartTask ()
{
    return true;
}

bool NTRenderMediaControl::OnPerformTask ()
{
    bool status = false;
    
    if (_nextFilter != nullptr) {
        NTMediaSample* aSample = nullptr;
        while ((aSample = _parentFilter->GetSampleFromQueue()) != nullptr) {
            NTMediaSample* aSample = _parentFilter->GetSampleFromQueue();
            if (aSample != nullptr) {
                status = this->RenderSample(aSample);
                aSample->Release();
            } else {
                status = false;
            }
        }
    }
    
    return status;
}

void NTRenderMediaControl::OnFinishTask ()
{
    
}