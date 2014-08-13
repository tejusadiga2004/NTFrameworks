/*!
 @file      NTBackgrounndTask.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */


#ifndef __NTFoundationFramework__NTBackgrounndTask__
#define __NTFoundationFramework__NTBackgrounndTask__

class NTObject;

/*!
 @class     INTBackgroundTaskDelegate
 @abstract  Interface for Worker object. WOrker object intended to run on another thread must extend INTBackgroundTaskDelegate and implement all methods. When NTBackgroundTask::StartTask() is called on main thread INTBackgroundTaskDelegate::OnStartTask() is called on sew thread. Here worker class can initilize it needs. INTBackgroundTaskDelegate::OnPerformTask () is called on nwe thread whenever NTBackgroundTask::PerformTask() is called on main thread. This happens asynchronously. When NTBackgroundTask::FinishTask() is called INTBackgroundTaskDelegate::OnFinishTask() is called. Until the worker thread is destoryed NTBackgroundTask::FinishTask() blocks.
 */
class NT_LIBRARY_USAGE INTBackgroundTaskDelegate {
public:
    
    /*!
     @function  OnStartTask
     @abstract  Called by NTBackgroundTask when StartTask() is called.
     @return    bool, true if the thread must continue further. If false the worker thread will be destroyed and OnFinishTask() is called before exit.
     */
    virtual bool OnStartTask () = 0;
    
    /*!
     @function  OnPerformTask
     @abstract  Called by NTBackgroundTask on worker thread when PerformTask() is called.
     @return    bool, true if the thread must continue further. If false the worker thread will be destroyed and OnFinishTask() is called before exit.
     */
    virtual bool OnPerformTask () = 0;
    
    /*!
     @function  OnFinishTask
     @abstract  Called by NTBackgroundTask on worker thread when FinishTask() is called.
     */
    virtual void OnFinishTask () = 0;
    
    virtual ~INTBackgroundTaskDelegate () {}
};

class NT_LIBRARY_USAGE NTBackgroundTask : public NTObject {
public:
    
    /*!
     @function  NTBackgroundTask
     @param     INTBackgroundTaskDelegate*, Delegate class to be called on worker thread.
     @abstract  Default constructor.
     */
    NTBackgroundTask (INTBackgroundTaskDelegate* inDelegate);
    
    /*!
     @function  ~NTBackgroundTask
     @abstract  Default Destructor.
     */
    ~NTBackgroundTask ();
    
    /*!
     @function  StartTask
     @abstract  Initiates the worker thread and its tasks.
     @return    bool, status true indicating that worker thread has started and performing normally. False indicates worker thread encountered error.
     */
    bool StartTask ();
    
    /*!
     @function  PerformTask
     @abstract  Performs a single piece of thask on secondary thread. Calls OnPerformTask on Secondary thread.
     */
    void PerformTask ();
    
    /*!
     @function  FinishTask
     @abstract  Finish operation of secondsry thread. Blocks until secondary thread ends.
     */
    void FinishTask ();
    
    /*!
     @function  IsRunning
     @abstract  boolean indicating whether secondsry thread is running.
     @return    bool, true indicates healthy secondary thread running.
     */
    bool IsRunning () const;
    
private:
    
    typedef struct NTBackgroundTaskInternal NTBackgroundTaskInternal;
    NTBackgroundTaskInternal* _internal;
};

#endif /* defined(__NTFoundationFramework__NTBackgrounndTask__) */
