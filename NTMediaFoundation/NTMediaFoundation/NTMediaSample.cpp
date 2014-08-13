//
//  NTMediaSample.cpp
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 22/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTMediaBuffer.h"
#include "NTFormatDescription.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTMediaSample.h"
#undef NT_LIBRARY_USAGE

NTMediaSample::NTMediaSample (NTMediaBuffer* inBuffer, TimeStamp inTime, NTFormatDescription* inFormat)
: NTMutableArray((NTObject*)inBuffer), _timestamp(inTime), _format(inFormat)
{
    _format->Retain();
}

NTMediaSample::NTMediaSample (NTMediaSample* inMediaSample)
: NTMutableArray(inMediaSample), _timestamp(inMediaSample->Timestamp())
{
    
}

NTMediaSample::~NTMediaSample ()
{
    NTSafeRelease(_format);
}

TimeStamp NTMediaSample::Timestamp ()
{
    return _timestamp;
}

NTFormatDescription* NTMediaSample::FormatDescription ()
{
    return _format;
}

void NTMediaSample::SetTimestamp (TimeStamp inTime)
{
    _timestamp = inTime;
}