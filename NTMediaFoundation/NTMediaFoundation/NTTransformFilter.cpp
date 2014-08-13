//
//  NTTransformFilter.cpp
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
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTTransformFilter.h"
#undef NT_LIBRARY_USAGE

NTTransformFilter::NTTransformFilter (NTString* inFilterName)
: NTRenderFilter(inFilterName, kNTFilterType_Transform), NTConnectable(this)
{
    
}

NTTransformFilter::~NTTransformFilter ()
{
    
}

bool NTTransformFilter::Start ()
{
    return NTRenderFilter::Start();
}

bool NTTransformFilter::Stop ()
{
    return NTRenderFilter::Stop();
}