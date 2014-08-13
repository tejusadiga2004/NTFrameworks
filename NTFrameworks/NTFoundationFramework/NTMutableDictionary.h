/*!
 @file      NTDictionary.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTMutableDictionary__
#define __NTFoundationFramework__NTMutableDictionary__

#include <iostream>

class NTObject;
class NTString;
class NTDictionary;

/*!
 @class     NTMutableDictionary
 @abstract  NTMutableDictionary is an object store for Key Value pairs. NTDictionary is mutable and can modify the contents of dictionary.
 */
class NT_LIBRARY_USAGE NTMutableDictionary : public NTDictionary {
public:
    
    /*!
     @function  NTMutableDictionary
     @param     NTString*, Key for the first object.
     @param     NTObject*, First object.
     @abstract  Default constructor for NTDictionary. Dictionary arguments are in pairs of Key1, Value1, Key2, Value2 and so on.
     */
    NTMutableDictionary (NTString* inKey1, NTObject* inObject1,...);
    
    /*!
     @function  ~NTMutableDictionary
     @param     NTDictionary*, Other dictionary to initilize with.
     @abstract  Copy constructor for NTDictionary.
     */
    NTMutableDictionary (NTDictionary* inDictionary);
    
    /*!
     @function  ~~NTMutableDictionary
     @abstract  Destructor for NTDictionary.
     */
    ~NTMutableDictionary ();
    
    /*!
     @function  AppendObjectForKey
     @param     NTObject*, Object to store.
     @param     NTString*, key to store.
     @abstract  Appends a key value pair to the dictionary.
     */
    void AppendObjectForKey (NTObject* inobject, NTString* inKey);
    
    /*!
     @function  AppendObjectForKey
     @param     NTString*, key of the object to remove.
     @abstract  Removes the object corresponding to inKey
     */
    void RemoveObjectForKey (NTString* inKey);
    
    
};

#endif /* defined(__NTFoundationFramework__NTMutableDictionary__) */
