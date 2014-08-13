/*!
 @file      NTQueue.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */
#ifndef __NTFoundationFramework__NTQueue__
#define __NTFoundationFramework__NTQueue__

class NTObject;

/*!
 @class     NTQueue
 @abstract  NTMutableArray represents a queue object which is thread safe.
 */
class NT_LIBRARY_USAGE NTQueue : public NTObject {
public:
    
    /*!
     @function  NTQueue
     @param     int, capacity of the queue.
     @abstract  Default constructor for NTQueue. Initilizes with inCapacity buffers.
     */
    NTQueue (int inCapacity);
    
    /*!
     @function  ~NTQueue
     @abstract  Default destructor.
     */
    ~NTQueue ();
    
    /*!
     @function  IsQueueFull
     @abstract  Returns true if queue is full.
     @return    bool, true if queue is full.
     */
    bool IsQueueFull ();
    
    /*!
     @function  IsQueueEmpty
     @abstract  Returns true if queue is empty.
     @return    bool, true if queue is empty.
     */
    bool IsQueueEmpty ();
    
    /*!
     @function  GetBufferFullness
     @param     NTArray, Array to initilize with.
     @abstract  Returns the fullness of the queue within range 0.0 and 1.0. For instance 0.25 value indicates queue is 25% full.
     @return    float, 0.0 indicates queue empty. 1.0 indicates queue full. other fractional values indicates the fullness of the queue.
     */
    float GetBufferFullness ();
    
    /*!
     @function  EnqueueObject
     @param     NTObject*, Object to enqueue.
     @abstract  inserts the object at the end of the queue. If the buffer is full EnqueueObject returns false.
     @return    bool, status of enqueuing object. flase if queue is full. Object is retained.
     */
    bool EnqueueObject (NTObject* inObject);
    
    /*!
     @function  DequeueObject
     @abstract  retrives the object at the begining of the queue. If the buffer is empty DequeueObject returns nullptr.
     @return    NTObject*, Object at the front end of the queue. Ownership is transfered to the caller.
     */
    NTObject* DequeueObject ();
    
private:
    
    typedef struct NTQueueInternal NTQueueInternal;
    NTQueueInternal* _internal;
};

#endif /* defined(__NTFoundationFramework__NTQueue__) */
