/*!
 @file      NTAllocator.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */


#ifndef __NTFoundationFramework__NTAllocator__
#define __NTFoundationFramework__NTAllocator__

class NTObject;

/*!
 @enum NTAllocatorType
 @abstract  Customized allocator types.
 @field kNTAllocatorTypeNew, memory is allocated with new operator and deleted using delete operator.
 @field kNTAllocatorTypeMalloc, memory is allocated with malloc() and deleted using free.
 @field kNTAllocatorTypeCalloc, memory is allocated with calloc() and deleted using free.
 */
typedef enum NTAllocatorType {
    kNTAllocatorTypeNew,
    kNTAllocatorTypeMalloc,
    kNTAllocatorTypeCalloc,
} NTAllocatorType;

/*!
 @class     INTAllocator
 @abstract  Interface for allocator. use NTAllocatorFactory::GetAllocator() to get a reference to INTAllocator. After using relase the handle with NTAllocatorFactory::Release() method. Core implementations of new/delete, malloc/free and calloc/free handle memory allocation and deallocation process.
 */
class NT_LIBRARY_USAGE INTAllocator {
public:
    
    /*!
     @function  AllocateMemory
     @param     inLength, Length of the buffer to allocate.
     @abstract  Allocates memory and returns the base pointer to allocated memory.
     @return    char*, base pointer to allocated memory. nullptr if memory could not be allocated.
     */
    virtual char* AllocateMemory (int inLength) = 0;
    
    /*!
     @function  ReleaseMemory
     @param     char* , base pointer to the memory.
     @abstract  Releases the memory.
     */
    virtual void ReleaseMemory (char* inMemory) = 0;
    
    /*!
     @function  ReallocateMemory
     @param     char*, base pointer to the memory block.
     @param     int, inOldLength length of the old memory block
     @param     int, inNewLength, length of hte new memory block.
     @abstract  Extends or shrinks the memory block while the contents of memory are retained. WHile shrinking data is lost.
     */
    virtual void ReallocateMemory (char** inMemoryBlock, int inOldLength, int inNewLength) = 0;
    
    virtual ~INTAllocator () {}
};

/*!
 @class     NTAllocatorFactory
 @abstract  Factory class to get the handle for allocator object. Use GetAllocator() to get the allocator and Release() to release the allocator.
 */
class NT_LIBRARY_USAGE NTAllocatorFactory {
public:
    
    /*!
     @function  GetAllocator
     @param     NTAllocatorType, Type of the allocator.
     @abstract  Returns the pointer to INTAllocator interface. However it is not gurented that internal allocator data structure will be of type inAllocator if GetAllocator() and Release() are called unevenly. however basic allocation process is not affected.
     @return    INTAllocator*, base pointer to allocated memory. nullptr if memory could not be allocated.
     */
    static INTAllocator* GetAllocator (NTAllocatorType inAllocator = kNTAllocatorTypeNew);
    
    /*!
     @function  Release
     @param     INTAllocator*, base pointer to the allocator interface.
     @abstract  Release the Allocator object represented by INTAllocator*.
     */
    static void Release (INTAllocator* inAllocator);
    
    virtual ~NTAllocatorFactory () {}
};

class NT_LIBRARY_USAGE NTAllocator : public NTObject, public INTAllocator {
public:
    
    NTAllocator ();
    
    ~NTAllocator ();
    
    virtual char* AllocateMemory (int inLength) = 0;
    
    virtual void ReleaseMemory (char* inMemory) = 0;
    
    void ReallocateMemory (char** inMemoryBlock, int inOldLength, int inNewLength);
    
};

class NT_LIBRARY_USAGE NTAllocatorNew :public NTAllocator {
public:
    
    NTAllocatorNew ();
    
    ~NTAllocatorNew ();
    
    char* AllocateMemory (int inLength);
    
    void ReleaseMemory (char* inMemory);
};

class NT_LIBRARY_USAGE NTAllocatorMalloc :public NTAllocator {
public:
    
    NTAllocatorMalloc ();
    
    ~NTAllocatorMalloc ();
    
    char* AllocateMemory (int inLength);
    
    void ReleaseMemory (char* inMemory);
};

class NT_LIBRARY_USAGE NTAllocatorCalloc :public NTAllocator {
public:
    
    NTAllocatorCalloc ();
    
    ~NTAllocatorCalloc ();
    
    char* AllocateMemory (int inLength);
    
    void ReleaseMemory (char* inMemory);
};

#endif /* defined(__NTFoundationFramework__NTAllocator__) */
