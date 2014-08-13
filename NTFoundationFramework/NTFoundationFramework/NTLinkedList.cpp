//
//  NTLinkedList.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 16/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#undef NT_LIBRARY_USAGE

#include "NTLinkedList.h"


typedef struct NTLinkedListInternal {
    
    typedef struct NTLinkedListElement {
        NTObject* _element;
        int _position;
        NTLinkedListElement* _next;
        NTLinkedListElement* _previous;
        
        NTLinkedListElement(NTObject* inElement = nullptr)
            : _element(inElement), _next(nullptr), _previous(nullptr), _position(0) {
            NTRetain(_element);
        }
        
        NTLinkedListElement (NTObject* inElement, NTLinkedListElement* inNext, NTLinkedListElement* inPrevious)
        : _element(inElement), _next(inNext), _previous(inPrevious), _position(inPrevious->_position + 1) {
            _element->Retain();
            if (inPrevious) {
                inPrevious->_next = this;
            }
            
            if (inNext) {
                inNext->_previous = this;
                inNext->_position = _position + 1;
            
                while (nullptr != (inNext = inNext->_next)) {
                    inNext->_position++;
                }
            }
        }

        ~NTLinkedListElement () {
            NTLinkedListElement* next = _next;
            while (nullptr != next) {
                next->_position--;
                next = next->_next;
            }
            NTSafeRelease(_element);
            _previous = _next = nullptr;
        }
        
    } NTLinkedListElement;
    
    NTLinkedListElement* _front;
    NTLinkedListElement* _rear;
    int _listSize;
    
    NTLinkedListInternal() : _front(nullptr), _rear(nullptr), _listSize(0) {}
    
    ~NTLinkedListInternal () {
        NTLinkedListElement* element = _front;
        while (element != nullptr) {
            element = element->_next;
            SafeRelease(element->_previous);
        }
    }
    
    void PutElement(NTObject* inElement, int inPosition) {

        if (inPosition == 0 && _front == nullptr) {
            NTLinkedListElement* newElement = new NTLinkedListElement(inElement);
            _front = newElement;
            _listSize++;
        }
        else {

            NTLinkedListElement* prevElement = GetElement(inPosition - 1);
            NTLinkedListElement* newElement = new NTLinkedListElement(inElement, prevElement->_next, prevElement);
            _listSize++;
        }
#pragma unused(newElement)
    }
    
    int FindElement (void* inElement) {
        NTLinkedListElement* element = _front;
        while (element->_element != inElement) {
            element = element->_next;
        }
        return element->_position;
    }
    
    NTLinkedListElement* GetElement (int inPosition) {
        if (inPosition > 0 && inPosition >= _listSize) {
            return nullptr;
        }
        
        NTLinkedListElement* element = _front;
        while (element != nullptr && element->_position != inPosition) {
            element = element->_next;
        }
        return element;
    }
    
    int RemoveElement (int inPosition) {
        
        NTLinkedListElement* element = GetElement(inPosition);
        SafeRelease(element);
        return 0;
    }

} NTLinkedListInternal;

NTLinkedList::NTLinkedList (int inCapacity)
: data(new NTLinkedListInternal)
{

}

NTLinkedList::~NTLinkedList ()
{
    SafeRelease(data)
}

void NTLinkedList::InsertElement (NTObject* inElement, int inPosition)
{
    data->PutElement(inElement, inPosition);
}

void NTLinkedList::InsertFront (NTObject* inElement)
{
    this->InsertElement(inElement, 0);
}

void NTLinkedList::InsertBack (NTObject* inElement)
{
    this->InsertElement(inElement, data->_listSize);
}

void NTLinkedList::RemoveElement (int inPosition)
{
    data->RemoveElement(inPosition);
}

void NTLinkedList::RemoveElement (NTObject* inElement)
{
    this->RemoveElement(data->FindElement(inElement));
}

void NTLinkedList::RemoveFront ()
{
    this->RemoveElement(0);
}

void NTLinkedList::RemoveBack ()
{
    this->RemoveElement(data->_listSize);
}

NTObject* NTLinkedList::FirstElement ()
{
    NTLinkedListInternal::NTLinkedListElement* element = data->GetElement(0);
    return element->_element;
}

NTObject* NTLinkedList::LastElement ()
{
    NTLinkedListInternal::NTLinkedListElement* element = data->GetElement(data->_listSize);
    return element->_element;
}

NTObject* NTLinkedList::ObjectAtIndex (int inPosition)
{
    NTLinkedListInternal::NTLinkedListElement* element = data->GetElement(inPosition);
    return element->_element;
}

int NTLinkedList::GetPositionOfElement (NTObject* inElement)
{
    return data->FindElement(inElement);
}

int NTLinkedList::Size () const
{
    return data->_listSize;
}
