//
//  NTArray.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 20/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTArray.h"
#undef NT_LIBRARY_USAGE

#include "NTLinkedList.h"
#include "NTArrayInternal.h"

#include <stdarg.h>

NTArray::NTArray (NTObject* inObject1,...)
: _internal(nullptr)
{
    va_list list = nullptr;
    if (inObject1 != nullptr) {
        va_start(list, inObject1);
    }

    _internal = new NTArrayInternal(list);
}

NTArray::NTArray (NTArray* inArray)
: _internal(new NTArrayInternal(inArray))
{
    
}

NTArray::~NTArray ()
{
    SafeRelease(_internal);
}

int NTArray::Size () const
{
    return _internal->_list->Size();
}

NTObject* NTArray::ObjectAtIndex (int inIndex)
{
    return _internal->_list->ObjectAtIndex(inIndex);
}

int NTArray::IndexOfObject (NTObject* inElement)
{
    return _internal->_list->GetPositionOfElement(inElement);
}

std::string NTArray::Description()
{
    std::ostringstream stringDec;
	stringDec << "{\n" << NTObject::Description() << std::endl;
	stringDec << "NTArray: "<<this->Size()<<" Objects\n" << std::endl;

	for (int cnt = 0; cnt < this->Size(); cnt++) {
		stringDec << this->ObjectAtIndex(cnt)->Description() << std::endl;
	}

	stringDec << "\n}" << std::endl;
    return stringDec.str();
}