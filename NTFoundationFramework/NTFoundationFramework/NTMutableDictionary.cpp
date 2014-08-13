//
//  NTMutableDictionary.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 20/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTString.h"
#include "NTArray.h"
#include "NTDictionary.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTMutableDictionary.h"
#undef NT_LIBRARY_USAGE

#include "NTDictionaryInternal.h"

NTMutableDictionary::NTMutableDictionary (NTString* inKey1, NTObject* inObject1,...)
: NTDictionary(inKey1, inObject1)
{
    
}

NTMutableDictionary::NTMutableDictionary (NTDictionary* inDictionary)
: NTDictionary(inDictionary)
{
    
}

NTMutableDictionary::~NTMutableDictionary ()
{
    
}

void NTMutableDictionary::AppendObjectForKey (NTObject* inobject, NTString* inKey)
{
    if (inKey != nullptr && inobject != nullptr) {
        NTDictionaryPair* pair = new NTDictionaryPair(inKey, inobject);
        _internal->_list->InsertBack(pair);
        NTSafeRelease(pair);
    }
}

void NTMutableDictionary::RemoveObjectForKey (NTString* inKey)
{
    for (int cnt = 0; cnt <  _internal->_list->Size(); cnt++) {
        NTDictionaryPair* pair = (NTDictionaryPair*) _internal->_list->ObjectAtIndex(cnt);
        if ((NTString*)pair->_key == inKey) {
            _internal->_list->RemoveElement(pair);
            break;
        }
    }
}