//
//  NTNotificationCenterInternal.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 18/08/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTString.h"
#include "NTArray.h"
#include "NTMutableArray.h"
#include "NTNotificationCenter.h"
#undef NT_LIBRARY_USAGE

#include "NTNotificationCenterInternal.h"

class NTNotificationObject : public NTNotification {
public:
    
    NTNotificationObject (NTString*         inProperty,
                          NTObject*         inObserver,
                          void*             inContext,
                          NotificationBlock inMethod)
    : NTNotification(inProperty, inContext), notificationBlock(inMethod), observer(inObserver)
    {
        NTRetain(observer);
    }
    
    ~NTNotificationObject()
    {
        NTSafeRelease(observer);
    }

    NTObject*           observer;
    NotificationBlock   notificationBlock;
};

NTNotificationCenterInternal::NTNotificationCenterInternal ()
:NTNotificationCenter()
{
    
}

NTNotificationCenterInternal::~NTNotificationCenterInternal ()
{
    std::lock_guard<std::mutex> lock(mutex);
    
    notificationMap.clear();
}

void NTNotificationCenterInternal::AddObserver (NTString*         inProperty,
                                                NTObject*         inObserver,
                                                void*             inContext,
                                                NotificationBlock inMethod)
{
    std::lock_guard<std::mutex> lock(mutex);
    
    NTMutableArray* newNotifierArray = nullptr;
    NTNotificationObject* aNotification = nullptr;
    
    NotificationMap::iterator oldObserver = notificationMap.find(inProperty->UTF8String());

    if (oldObserver == notificationMap.end()) {
        aNotification = new NTNotificationObject(inProperty, inObserver, inContext, inMethod);
        newNotifierArray = new NTMutableArray();
        
    } else {
        newNotifierArray = (NTMutableArray*)oldObserver->second;
        
        for (int cnt = 0; cnt < newNotifierArray->Size(); cnt++) {
            NTNotificationObject* theObject = (NTNotificationObject*)newNotifierArray->ObjectAtIndex(cnt);
            
            if (theObject->observer == inObserver) {
                aNotification = theObject;
                break;
            }
        }
        
        if (aNotification == nullptr) {
            aNotification = new NTNotificationObject(inProperty, inObserver, inContext, inMethod);
        }
    }
    
    newNotifierArray->AppendElement(aNotification);
    
    notificationMap[inProperty->UTF8String()] = (NTArray*)newNotifierArray;

}

void NTNotificationCenterInternal::RemoveObserver (NTString* inProperty, NTObject* inObserver)
{
    std::lock_guard<std::mutex> lock(mutex);
    
    NotificationMap::iterator oldObserver = notificationMap.find(inProperty->UTF8String());
    
    if (oldObserver != notificationMap.end()) {
        NTMutableArray* notifierArray = (NTMutableArray*)oldObserver->second;

        NTNotificationObject* theNotifier = nullptr;
        
        for (int cnt = 0; cnt < notifierArray->Size(); cnt++) {
            NTNotificationObject* theObject = (NTNotificationObject*)notifierArray->ObjectAtIndex(cnt);
            
            if (theObject->observer == inObserver) {
                theNotifier = theObject;
                break;
            }
        }
        
        if (theNotifier) {
            notifierArray->RemoveElement(theNotifier);
            
            if (notifierArray->Size() <= 0) {
                notificationMap.erase(oldObserver);
            }
        }
    }
}

void NTNotificationCenterInternal::InvokeObserversForProperty (NTString* inProperty)
{
    std::lock_guard<std::mutex> lock(mutex);
    
    NotificationMap::iterator oldObserver = notificationMap.find(inProperty->UTF8String());
    
    if (oldObserver != notificationMap.end()) {
        NTArray* notifierArray = oldObserver->second;
        
        for (int cnt = 0; cnt < notifierArray->Size(); cnt++) {
            NTNotificationObject* theNotifier = (NTNotificationObject*)notifierArray->ObjectAtIndex(cnt);
            theNotifier->notificationBlock(theNotifier);
        }
    }
}

bool NTNotificationCenterInternal::HasObservers (NTString* inProperty, NTObject* inObserver)
{
    std::lock_guard<std::mutex> lock(mutex);
    
    bool hasObservers = false;
    
    NotificationMap::iterator oldObserver = notificationMap.find(inProperty->UTF8String());
    
    if (oldObserver != notificationMap.end()) {
        NTArray* notifierArray = oldObserver->second;
        
        for (int cnt = 0; cnt < notifierArray->Size(); cnt++) {
            NTNotificationObject* theNotifier = (NTNotificationObject*)notifierArray->ObjectAtIndex(cnt);
            
            if (theNotifier->observer == inObserver) {
                hasObservers = true;
            }
        }
    }
    
    return hasObservers;
}

void NTNotificationCenterInternal::RemoveAllObserverForAllProperties (NTObject* inObserver)
{
    std::lock_guard<std::mutex> lock(mutex);
    
    NotificationMap::iterator it = notificationMap.begin();
    for (it = notificationMap.begin(); it != notificationMap.end(); it++) {
        NTMutableArray* notifierArray = (NTMutableArray*)it->second;
        
        for (int cnt = 0; cnt < notifierArray->Size(); cnt++) {
            NTNotificationObject* theNotifier = (NTNotificationObject*)notifierArray->ObjectAtIndex(cnt);
            
            if (theNotifier->observer == inObserver) {
                notifierArray->RemoveElement(theNotifier);
            }
        }
    }
}

