/*!
 @file      NTMutableArray.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTMutableArray__
#define __NTFoundationFramework__NTMutableArray__


class NTArray;

/*!
 @class     NTMutableArray
 @abstract  NTMutableArray represents a data structure to hold array of NTObjects and with added ability to modify the objects.
 */
class NT_LIBRARY_USAGE NTMutableArray : public NTArray {
public:
    
    /*!
     @function  NTMutableArray
     @abstract  Default constructor for NTArray.
     */
    NTMutableArray ();
    
    /*!
     @function  NTMutableArray
     @param     NTObject*, Array to initilize with.
     @abstract  Default constructor for NTArray. Argument initilizes the array with NTObjects.
     */
    NTMutableArray (NTObject* inObject1,...);
    
    /*!
     @function  NTMutableArray
     @param     NTArray, Array to initilize with.
     @abstract  Default constructor for NTArray. Argument initilizes the array with NTObjects.
     */
    NTMutableArray (NTArray* inArray);
    
    /*!
     @function  ~NTMutableArray
     @abstract  Default destructor.
     */
    ~NTMutableArray ();
    
    /*!
     @function  AppendElement
     @param     NTObject*, Object to appned.
     @abstract  Appned the object to the array.
     */
    void AppendElement (NTObject* inObject);
    
    /*!
     @function  InsertElementAtIndex
     @param     NTObject*, Object to appned.
     @param     int, index of the object.
     @abstract  Insert the object at position inIndex.
     */
    void InsertElementAtIndex (NTObject* inObject, int inIndex);
    
    /*!
     @function  AppendArray
     @param     NTArray*, Array to append.
     @abstract  Append the array elements with inArray.
     */
    void AppendArray (NTArray* inArray);
    
    /*!
     @function  RemoveElement
     @param     NTObject*, Element to remove.
     @abstract  Remove the element from the array.
     */
    void RemoveElement (NTObject* inObject);
    
    /*!
     @function  RemoveElementAtIndex
     @param     int, Array to append.
     @abstract  Remove the elemnet at inIndex.
     */
    void RemoveElementAtIndex (int inIndex);
};

#endif /* defined(__NTFoundationFramework__NTMutableArray__) */
