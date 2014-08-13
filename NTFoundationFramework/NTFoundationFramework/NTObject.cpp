//
//  NTObject.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 16/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include <iostream>
#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTObject.h"
#undef NT_LIBRARY_USAGE

NTObject::NTObject ()
: mRef(1)
{
    
}

NTObject::~NTObject ()
{
    
}

void NTObject::Retain ()
{
    mRef++;
}

void NTObject::Release ()
{
    if (mRef-- <= 0) {
        delete this;
    }
}

std::string NTObject::Description()
{
    char desc[100];
    char* thisPtr = (char*)this;
    sprintf(desc, "{NTObject: 0x%x}", thisPtr);
    return desc;
}