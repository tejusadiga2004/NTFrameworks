//
//  NTDictionaryInternal.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 20/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef NTFoundationFramework_NTDictionaryInternal_h
#define NTFoundationFramework_NTDictionaryInternal_h

#include <stdarg.h>
#include "NTLinkedList.h"
#include "NTString.h"

typedef struct NTDictionaryPair : public NTObject {
    
    NTString* _key;
    NTObject* _value;
    
    NTDictionaryPair (NTString* inKey, NTObject* inObject) : _key(inKey), _value(inObject) {
        _key->Retain();
        _value->Retain();
    }
    
    ~NTDictionaryPair () {
        NTSafeRelease(_key);
        NTSafeRelease(_value);
    }
    
} NTDictionaryPair;

typedef struct NTDictionaryInternal {
    
    NTLinkedList* _list;
    
    NTDictionaryInternal (NTString* inKey1, NTObject* inObject1, va_list inList)
    : _list(new NTLinkedList(0))
    {
        
        NTDictionaryPair* pair = new NTDictionaryPair(inKey1, inObject1);
        _list->InsertBack(pair);
        NTSafeRelease(pair);
          
        NTString* key = nullptr;
        NTObject* object = nullptr;
          
        while ((key = va_arg(inList, NTString*)) != nullptr) {
            object = va_arg(inList, NTObject*);
            if (object != nullptr) {
                NTDictionaryPair* pair = new NTDictionaryPair(key, object);
                _list->InsertBack(pair);
                NTSafeRelease(pair);
            }
        }
        va_end(inList);
    }
    
    NTDictionaryInternal (NTDictionary* inDictionary)
    : _list(new NTLinkedList(0))
    {
        NTArray* inKeys = inDictionary->AllKeys();
        
        if (inKeys != nullptr) {
            for (int cnt = 0; cnt < inKeys->Size(); cnt++) {
                NTString* key = (NTString*)inKeys->ObjectAtIndex(cnt);
                if (key != nullptr) {
                    NTObject* object = inDictionary->ObjectForKey(key);
                    if (object != nullptr) {
                        NTDictionaryPair* pair = new NTDictionaryPair(key, object);
                        _list->InsertBack(pair);
                        NTSafeRelease(pair);
                    }
                }
            }
        }
    }
    
    ~NTDictionaryInternal () {
        NTSafeRelease(_list);
    }
    
    NTObject* ObjectForKey (NTString* inKey) {
        NTObject* anObject = nullptr;
        
        for (int cnt = 0; cnt < _list->Size(); cnt++) {
            NTDictionaryPair* pair = (NTDictionaryPair*)_list->ObjectAtIndex(cnt);
            if ((NTString*)pair->_key == inKey) {
                anObject = pair->_value;
                break;
            }
        }
        
        return anObject;
    }
    
} NTDictionaryInternal;


#endif
