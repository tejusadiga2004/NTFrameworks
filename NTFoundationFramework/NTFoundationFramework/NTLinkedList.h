/*!
 @file      NTLinkedList.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTLinkedList__
#define __NTFoundationFramework__NTLinkedList__

class NTObject;

/*!
 @class NTLinkedList
 @abstract NTLinkedList represents the internal data structure for various container classes like NTArray, NTDictionary,NTQueue etc. This is not exposed to the user.
 */
class NTLinkedList : public NTObject {
public:
    
    /*!
     @function  NTLinkedList
     @param     int, Initial capacity of the linked list.
     @abstract  Default constructor for NTLinkedList
     */
    NTLinkedList (int inCapacity);
    
    /*!
     @function  ~NTLinkedList
     @param     int, Initial capacity of the linked list.
     @abstract  Destructor for NTLinkedList
     */
    ~NTLinkedList ();
    
    /*!
     @function  InsertElement
     @param     NTObject*, Object to insert.
     @param     int, position of the object in the list.
     @abstract  Insert the given object at given position in the linked list. A new node is created for new object. No duplicate check is performed. Object is retained.
     */
    void InsertElement (NTObject* inElement, int inPosition);
    
    /*!
     @function  InsertFront
     @param     NTObject*, Object to insert.
     @abstract  Insert the given object at front end of the list. All other elements preceds this front element. Object is retained.
     */
    void InsertFront (NTObject* inElement);
    
    /*!
     @function  InsertBack
     @param     NTObject*, Object to insert.
     @abstract  Insert the given object at rear end of the list. All other elements are precedded by this front element. Object is retained.
     */
    void InsertBack (NTObject* inElement);
    
    /*!
     @function  RemoveElement
     @param     int, position of the object in the list.
     @abstract  Remove the element at given position. Releasses the object ownership.
     */
    void RemoveElement (int inPosition);
    
    /*!
     @function  RemoveElement
     @param     NTObject*, Object to insert.
     @abstract  Remove the element given from the list. Releasses the object ownership.
     */
    void RemoveElement (NTObject* inElement);
    
    /*!
     @function  RemoveFront
     @abstract  Remove the front element from the list. Releasses the object ownership.
     */
    void RemoveFront ();
    
    /*!
     @function  RemoveBack
     @abstract  Remove the rear element from the list. Releasses the object ownership.
     */
    void RemoveBack ();
    
    /*!
     @function  FirstElement
     @abstract  Retreve the front most element from the list. List retains the object ownership.
     @return    NTObject* Front most object in the list.
     */
    NTObject* FirstElement ();
    
    /*!
     @function  LastElement
     @abstract  Retreve the rear most element from the list. List retains the object ownership.
     @return    NTObject* Last most object in the list.
     */
    NTObject* LastElement ();
    
    /*!
     @function  ObjectAtIndex
     @param     int, position of the object in the list.
     @abstract  Retreve the object at inPosition. List retains the object ownership.
     @return    NTObject* Object at index inPosition.
     */
    NTObject* ObjectAtIndex (int inPosition);
    
    /*!
     @function  GetPositionOfElement
     @param     NTObject*, Object whoose position is enquired in the list.
     @abstract  Retreve the index of the object. TODO: Handle other Error casses.
     @return    int, Index of the object inElement.
     */
    int GetPositionOfElement (NTObject* inElement);
    
    /*!
     @function  Size
     @abstract  Retrives the size of the list.
     @return    int, Index of the object inElement.
     */
    int Size () const;
    
private:
    
    typedef struct NTLinkedListInternal NTLinkedListInternal;
    NTLinkedListInternal* data;
};

#endif /* defined(__NTFoundationFramework__NTLinkedList__) */
