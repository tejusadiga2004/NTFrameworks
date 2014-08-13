/*!
 @file      NTArray.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */


#ifndef __NTFoundationFramework__NTArray__
#define __NTFoundationFramework__NTArray__

#include <iostream>

class NTObject;

/*!
 @class     NTArray
 @abstract  NTArray represents a data structure to hold array of NTObjects.
 */
class NT_LIBRARY_USAGE NTArray : public NTObject {
public:
    
    /*!
     @function  NTArray
     @param     NTObject*, Variable argument list of NTObject* objects.
     @abstract  Default constructor for NTArray. Argument initilizes the array with NTObjects.
     */
    NTArray (NTObject* inObject1,...);
    
    /*!
     @function  NTArray
     @param     NTArray, Array to initilize with.
     @abstract  Default constructor for NTArray. Argument initilizes the array with NTObjects.
     */
    NTArray (NTArray* inArray);
    
    /*!
     @function  ~NTArray
     @abstract  Default destructor.
     */
    ~NTArray ();
    
    /*!
     @function  Size
     @abstract  Returns the number of elements contained in the array.
     @return    int, number of elements in the array.
     */
    int Size () const;
    
    /*!
     @function  ObjectAtIndex
     @param     int, index of the object intrested.
     @abstract  Returns the object at indes location.
     @return    NTObject*, object at location inIndex.
     */
    NTObject* ObjectAtIndex (int inIndex);
    
    /*!
     @function  IndexOfObject
     @param     NTObject, object whoose index is enwuired.
     @abstract  Returns the index of the object.
     @return    int, index of the object.
     */
    int IndexOfObject (NTObject* inElement);

    std::string Description();
    
protected:
    
    typedef struct NTArrayInternal NTArrayInternal;
    NTArrayInternal* _internal;
};

#endif /* defined(__NTFoundationFramework__NTArray__) */
