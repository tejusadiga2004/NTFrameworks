//
//  NTDictionary.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 16/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTString.h"
#include "NTArray.h"
#include "NTMutableArray.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTDictionary.h"
#undef NT_LIBRARY_USAGE

#include "NTDictionaryInternal.h"

NTDictionary::NTDictionary (NTString* inKey1, NTObject* inObject1,...)
: NTObject(), _internal(nullptr)
{
    va_list list;
    va_start(list, inObject1);
    _internal = new NTDictionaryInternal(inKey1, inObject1, list);
}

NTDictionary::NTDictionary (NTDictionary* inDictionary)
: NTObject(), _internal(new NTDictionaryInternal(inDictionary))
{
    
}

NTDictionary::~NTDictionary ()
{
    SafeRelease(_internal);
}

NTObject* NTDictionary::ObjectForKey (NTString* inKey1)
{
    return _internal->ObjectForKey(inKey1);
}

NTArray* NTDictionary::AllKeys ()
{
    NTMutableArray* keysArray = new NTMutableArray();
    
    for (int cnt = 0; cnt < _internal->_list->Size(); cnt++) {
        NTDictionaryPair* pair = (NTDictionaryPair*)_internal->_list->ObjectAtIndex(cnt);
        keysArray->InsertElementAtIndex(pair->_key, cnt);
    }
    
    return keysArray;
}

bool NTDictionary::IsKeyPresent (NTString* inKey)
{
    for (int cnt = 0; cnt < _internal->_list->Size(); cnt++) {
        NTDictionaryPair* pair = (NTDictionaryPair*)_internal->_list->ObjectAtIndex(cnt);
        if (pair->_key->IsEqualToString(inKey)) {
            return true;
        }
    }
    return false;
}