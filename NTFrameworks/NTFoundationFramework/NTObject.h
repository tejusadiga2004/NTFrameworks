/*!
 @file      NTObject.h
            NTFoundationFramework

 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTObject__
#define __NTFoundationFramework__NTObject__

#include <iostream>
#include <sstream> 

/*!
 @field     SafeRelease
 @abstract  Convinence macro for releasing a general pointer allocated with new. This dereferences the pointer to null after releasing. Must not be used with NTObject types.
 */
#define SafeRelease(ptr) \
    if (ptr) { \
        delete ptr; \
        ptr = nullptr; \
    }

/*!
 @field     NTSafeRelease
 @abstract  Convinence macro for releasing a NTObject and its derivatives. SafeRelease must not be used to release NTObject type.
 */
#define NTSafeRelease(ptr) \
    if (ptr) { \
        ptr->Release(); \
        ptr = nullptr; \
    }

#define NTRetain(ptr) \
    if (ptr) { \
        ptr->Retain(); \
    }

/*!
 @class NTObject
 @abstract NTObject represents a base object for all objects. It also provides machanism for Reference Counting objects. Other objects may extend NTObject in order to get Reference counting feature.
 */
class NT_LIBRARY_USAGE NTObject {
public:
    
    /*!
     @function NTObject
     @abstract  Default constructor for NTObject. Any class extending NTObject must initilize NTObject in their constructors.
     */
    NTObject ();
    
    /*!
     @function Retain
     @abstract  Increments the objects reference count by 1. When the object is just created reference count will be 1. Reference count will be incremented on every call to NTObject::Retain().
     */
    void Retain ();
    
    /*!
     @function Release
     @abstract  Decrements the objects reference count by 1. When reference count reaches 0 the object is destroyed. Do not use this method to release the object. Insted use NTSafeRelease macro. NTSafeRelease avoids dangling pointers.
     */
    void Release ();

    virtual std::string Description();
    
protected:
    
    ~NTObject ();
    
private:
    
    int mRef;
};

#endif /* defined(__NTFoundationFramework__NTObject__) */
