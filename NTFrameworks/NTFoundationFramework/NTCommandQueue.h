/*!
 @file      NTCommandQueue.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTCommandQueue__
#define __NTFoundationFramework__NTCommandQueue__

class NTBackgroundTask;
class NTObject;

/*!
 @class     NTCommand
 @abstract  NTCommand encapsulates the piece of code containing the operations to be performed asynchronously. NTCommandQueue calls OnPerformCommand() asynchronously without blocking. Clients extending NTCommand must implement OnPerformCommand() to receive calls asynchronously.
 */
class NT_LIBRARY_USAGE NTCommand : public NTObject {
public:
    
    /*!
     @function  NTCommand
     @param     NTObject*, User data to encapsulate.
     @abstract  Default constructor.
     */
    NTCommand (NTObject* inUserData);
    
    /*!
     @function  ~NTCommand
     @abstract  Default destructor.
     */
    ~NTCommand ();
    
    /*!
     @function  GetUserData
     @param     NTObject*, User data to encapsulate.
     @abstract  Returns the User data encapsulated.
     @return    NTObject*, User data encapsulated.
     */
    NTObject* GetUserData ();
    
    /*!
     @function  OnPerformCommand
     @param     NTObject*, User data to encapsulate.
     @abstract  Clients must perform the operations intended to do asynchronously.
     */
    virtual void OnPerformCommand (NTObject* inUserData) = 0;
    
private:
    
    NTObject* _userData;
};

/*!
 @class     NTCommandQueue
 @abstract  NTCommandQueue represents the Command pattern implemenation.
 */
class NT_LIBRARY_USAGE NTCommandQueue : public NTBackgroundTask {
public:
    
    /*!
     @function  NTCommandQueue
     @param     int, queue capacity.
     @abstract  Default constructor.
     */
    NTCommandQueue (int inQueueCapacity);
    
    /*!
     @function  ~NTCommandQueue
     @abstract  Default destructor.
     */
    ~NTCommandQueue ();
    
    /*!
     @function  ScheduleCommand
     @abstract     NTCommand*, command object to be performed asynchronously Commands will be performed on secondary thread.
     @return  bool, false if queue is full. true on success.
     */
    bool ScheduleCommand (NTCommand* inCommand);
    
private:
    
    typedef struct NTCommandQueueInternal NTCommandQueueInternal;
    NTCommandQueueInternal* _internal;
};

#endif /* defined(__NTFoundationFramework__NTCommandQueue__) */
