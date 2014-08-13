//
//  NTMutableArray.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 20/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTArray.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTMutableArray.h"
#undef NT_LIBRARY_USAGE

#include "NTArrayInternal.h"
#include "NTLinkedList.h"

NTMutableArray::NTMutableArray ()
: NTArray(nullptr, nullptr)
{
    
}

NTMutableArray::NTMutableArray (NTObject* inObject1,...)
: NTArray(inObject1)
{
    
}

NTMutableArray::NTMutableArray (NTArray* inArray)
: NTArray(inArray)
{
    
}

NTMutableArray::~NTMutableArray ()
{
    
}

void NTMutableArray::AppendElement (NTObject* inObject)
{
    _internal->_list->InsertBack(inObject);
}

void NTMutableArray::InsertElementAtIndex (NTObject* inObject, int inIndex)
{
    _internal->_list->InsertElement(inObject, inIndex);
}

void NTMutableArray::AppendArray (NTArray* inArray)
{
    for (int cnt = 0; cnt < inArray->Size(); cnt++) {
        _internal->_list->InsertBack(inArray->ObjectAtIndex(cnt));
    }
}

void NTMutableArray::RemoveElement (NTObject* inObject)
{
    _internal->_list->RemoveElement(inObject);
}

void NTMutableArray::RemoveElementAtIndex (int inIndex)
{
    _internal->_list->RemoveElement(inIndex);
}