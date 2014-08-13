//
//  NTFilter.cpp
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 22/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTMediaControl.h"
#include "NTFormatDescription.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTFilter.h"
#undef NT_LIBRARY_USAGE

NTString* const kNTFilterDescription_FilterType = new NTString("NTFilterDescription_FilterType");

NTConnectable::NTConnectable (NTFilter* inParentFilter)
: NTObject(), _parentFilter(inParentFilter), _downstreamFilter(nullptr)
{
    _parentFilter->Retain();
}

NTConnectable::~NTConnectable ()
{
    NTSafeRelease(_parentFilter);
    NTSafeRelease(_downstreamFilter);
}

bool NTConnectable::ConnectDownstreamFilter (NTFilter* inFilter)
{
    bool status = false;
    
    NTFormatDescription* hostFormat = inFilter->QueryFormat();
    NTFormatDescription* myFormat = _parentFilter->QueryFormat();
    
    if (hostFormat->MediaType() == myFormat->MediaType()) {
        switch (hostFormat->MediaType()) {
            case kNTMediaTypeVideo:
                status = ((NTVideoFormatDescription*)hostFormat)->IsEqualToFormat((NTVideoFormatDescription*)myFormat);
                break;
                
            case kNTMediaTypeAudio:
                status = ((NTAudioFormatDescription*)hostFormat)->IsEqualToFormat((NTAudioFormatDescription*)myFormat);
                break;
        }
        
        if (status) {
            _downstreamFilter = inFilter;
            _downstreamFilter->Retain();
        }
    }
    return status;
}


NTFilter::NTFilter (NTString* inFilterName, NTFilterType inFilterType)
: NTObject(),
  _filterName(inFilterName),
  _filterType(inFilterType),
  _backgroundTask(nullptr),
  _mediaControl(nullptr),
  _IsRunning(false)
{
    _filterName->Retain();
}

NTFilter::~NTFilter ()
{
    NTSafeRelease(_mediaControl);
    NTSafeRelease(_filterName);
    NTSafeRelease(_backgroundTask);
}

void NTFilter::SetMediaControl (NTMediaControl* inMediaControl)
{
    NTSafeRelease(_mediaControl);
    _mediaControl = inMediaControl;
    _mediaControl->Retain();
}



bool NTFilter::Start ()
{
    bool status = false;
    
    if (_mediaControl != nullptr) {
        _backgroundTask = new NTBackgroundTask(_mediaControl);
        status = _backgroundTask->StartTask();
        _IsRunning = _backgroundTask->IsRunning();
    }
    
    return status;
}

bool NTFilter::Stop ()
{
    bool status = false;
    
    if (_backgroundTask && _mediaControl) {
        if (_backgroundTask->IsRunning()) {
            _backgroundTask->FinishTask();
            status = _IsRunning = _backgroundTask->IsRunning();
            NTSafeRelease(_backgroundTask);
        }
    }
    return status;
}

bool NTFilter::IsRunning ()
{
    return _IsRunning;
}

