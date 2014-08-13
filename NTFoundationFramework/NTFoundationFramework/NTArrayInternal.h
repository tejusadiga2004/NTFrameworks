//
//  NTArrayInternal.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 20/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef NTFoundationFramework_NTArrayInternal_h
#define NTFoundationFramework_NTArrayInternal_h

#include <stdarg.h>
#include "NTLinkedList.h"

typedef struct NTArrayInternal {
    NTLinkedList* _list;
    
    NTArrayInternal (va_list inList) : _list(new NTLinkedList(0)) {
        
        NTObject* anObject = nullptr;
        
        if (inList != nullptr) {
            while ((anObject = va_arg(inList, NTObject*)) != nullptr) {
                _list->InsertBack(anObject);
            }
            va_end(inList);
        }
    }
    
    NTArrayInternal (NTArray* inArray) : _list(new NTLinkedList(0)) {
        for (int cnt = 0; cnt < inArray->Size(); cnt++) {
            NTObject* anObject = inArray->ObjectAtIndex(cnt);
            if (anObject != nullptr) {
                _list->InsertBack(anObject);
            }
        }
    }
    
    ~NTArrayInternal () {
        NTSafeRelease(_list);
    }
    
} NTArrayInternal;

#endif
