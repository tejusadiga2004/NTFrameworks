/*!
 @file      NTDictionary.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTDictionary__
#define __NTFoundationFramework__NTDictionary__

class NTObject;
class NTString;
class NTArray;

/*!
 @class     NTDictionary
 @abstract  NTDictionary is an object store for Key Value pairs. NTDictionary is not mutable.
 */
class NT_LIBRARY_USAGE NTDictionary : public NTObject {
public:
    
    /*!
     @function  NTDictionary
     @param     NTString*, Key for the first object.
     @param     NTObject*, First object.
     @abstract  Default constructor for NTDictionary. Dictionary arguments are in pairs of Key1, Value1, Key2, Value2 and so on.
     */
    NTDictionary (NTString* inKey1, NTObject* inObject1,...);
    
    /*!
     @function  NTDictionary
     @param     NTDictionary*, Other dictionary to initilize with.
     @abstract  Copy constructor for NTDictionary. 
     */
    NTDictionary (NTDictionary* inDictionary);
    
    /*!
     @function  ~NTDictionary
     @abstract  Destructor for NTDictionary.
     */
    ~NTDictionary ();
    
    /*!
     @function  IsKeyPresent
     @param     NTString*, Key for the object enquired.
     @abstract  Returns the Object for corresponding inKey.
     @return    bool, true if key is present.
     */
    bool IsKeyPresent (NTString* inKey);
    
    /*!
     @function  ObjectForKey
     @param     NTString*, Key for the object enquired.
     @abstract  Returns the Object for corresponding inKey.
     @return    NTObject*, Object representing inKey.
     */
    NTObject* ObjectForKey (NTString* inKey);
    
    /*!
     @function  AllKeys
     @abstract  Returns the Object for corresponding inKey.
     @return    NTArray*, Array of Keys in Dictionary.
     */
    NTArray* AllKeys ();
    
protected:
    
    typedef struct NTDictionaryInternal NTDictionaryInternal;
    NTDictionaryInternal* _internal;
};

#endif /* defined(__NTFoundationFramework__NTDictionary__) */
