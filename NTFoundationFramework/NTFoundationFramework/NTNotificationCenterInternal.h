//
//  NTNotificationCenterInternal.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 18/08/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTFoundationFramework__NTNotificationCenterInternal__
#define __NTFoundationFramework__NTNotificationCenterInternal__

#include <iostream>
#include <map>

#include <mutex>

class NTObject;
class NTString;
class NTNotificationCenter;
class NTNotification;
class NTArray;

typedef std::map<std::string, NTArray*> NotificationMap;

class NTNotificationCenterInternal : public NTNotificationCenter {
public:
    
    NTNotificationCenterInternal ();
    
    ~NTNotificationCenterInternal ();
    
    void AddObserver (NTString*         inProperty,
                      NTObject*         inObserver,
                      void*             inContext,
                      NotificationBlock inMethod);
    
    void RemoveObserver (NTString* inProperty, NTObject* inObserver);
    
    void InvokeObserversForProperty (NTString* inProperty);
    
    bool HasObservers (NTString* inProperty, NTObject* inObserver);
    
    void RemoveAllObserverForAllProperties (NTObject* inObserver);
    
private:
    
    NotificationMap notificationMap;
    
    std::mutex mutex;

};

#endif /* defined(__NTFoundationFramework__NTNotificationCenterInternal__) */
