//
//  NTNotificationCenter.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 18/08/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#ifndef __NTFoundationFramework__NTNotificationCenter__
#define __NTFoundationFramework__NTNotificationCenter__

#include <iostream>

class NTString;
class NTObject;

class NT_LIBRARY_USAGE NTNotification : public NTObject {
public:
    
    NTNotification (NTString* inProperty, const void* inContext);
    
    ~NTNotification ();
    
    const NTString* QueryProperty () const;
    
    const void* QueryContext () const;
    
private:
    
    NTString* notifierProperty;
    void* context;
};

typedef std::function<void(NTNotification*)> NotificationBlock;

class NT_LIBRARY_USAGE NTNotificationCenter : public NTObject {
public:
    
    static NTNotificationCenter* DefaultNotificationCenter ();

    virtual void AddObserver (NTString*         inProperty,
                              NTObject*         inObserver,
                              void*             inContext,
                              NotificationBlock inMethod) = 0;
    
    virtual void RemoveObserver (NTString* inProperty, NTObject* inObserver) = 0;
    
    virtual void InvokeObserversForProperty (NTString* inProperty) = 0;
    
    virtual bool HasObservers (NTString* inProperty, NTObject* inObserver) = 0;
    
    virtual void RemoveAllObserverForAllProperties (NTObject* inObserver) = 0;
    
    virtual ~NTNotificationCenter () {}
};

#endif /* defined(__NTFoundationFramework__NTNotificationCenter__) */
