//
//  NTNotificationCenter.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 18/08/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTString.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTNotificationCenter.h"
#undef NT_LIBRARY_USAGE

#include "NTNotificationCenterInternal.h"

static NTNotificationCenter* defaultCenter = nullptr;

NTNotification::NTNotification (NTString* inProperty, const void* inContext)
: notifierProperty(inProperty), context((void*)inContext)
{
    NTRetain(notifierProperty);
}

NTNotification::~NTNotification ()
{
    NTSafeRelease(notifierProperty);
}

const NTString* NTNotification::QueryProperty () const
{
    NTRetain(notifierProperty);
    return notifierProperty;
}

const void* NTNotification::QueryContext () const
{
    return context;
}


NTNotificationCenter* NTNotificationCenter::DefaultNotificationCenter ()
{
    if (defaultCenter == nullptr) {
        defaultCenter = new NTNotificationCenterInternal();
    }
    
    return defaultCenter;
}