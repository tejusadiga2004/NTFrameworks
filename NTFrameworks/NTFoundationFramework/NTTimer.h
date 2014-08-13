/*!
 @file      NTTimer.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTTimer__
#define __NTFoundationFramework__NTTimer__

class NTObject;
class NTTimer;

/*!
 @class     NTTimerProc
 @param     NTObject*, User information to pass.
 @abstract  Static callback method to be called by timer on timer fire.
 */
typedef void (*NTTimerProc)(NTObject* inUserInfo);

/*!
 @class     NTTimer
 @abstract  NTTimer represents the timer object. Clients can schedule timer periodically until the object is destroyed.
 NTTimer can also be used fire only once.
 */
class NT_LIBRARY_USAGE NTTimer : public NTObject {
public:
    
    /*!
     @function  NTTimer
     @param     NTTimerProc, Pointer to function callback method on timer fire.
     @param     int, time interval between successive timer fire.
     @param     bool, yes if timer has to fire periodically. no if timer has to fire only once.
     @param     NTObject, user info to pass timer proc.
     @abstract  Default constructor.
     */
    NTTimer (NTTimerProc inTimerProc, int inTimeInterval, bool isShouldRepeat, NTObject* inUserInfo);
    
    /*!
     @function  ~NTTimer
     @abstract  Default destructor.
     */
    ~NTTimer ();
    
    /*!
     @function  Start
     @abstract  Starts the timer.
     */
    void Start ();
    
private:
    
    typedef struct NTTImerInternal NTTImerInternal;
    NTTImerInternal* _internal;
};

#endif /* defined(__NTFoundationFramework__NTTimer__) */
