


#ifndef NTMediaCapture_NTDevice_H
#define NTMediaCapture_NTDevice_H

#include "NTDeviceManager.h"

typedef enum NTDeviceState {
    kNTDeviceState_None             = 0,
    kNTDeviceState_Open             = 1,
    kNTDeviceState_Streaming        = (kNTDeviceState_Open << 1),
    kNTDeviceState_Error            = (kNTDeviceState_Streaming << 1),
    kNTDeviceState_InvalidFormat    = (kNTDeviceState_Error << 1)
};

class NTDeviceDelegate : public NTObject {
public:

    virtual void OnFrameCapture(NTMediaSample* outMediaSample) = 0;

    virtual void OnStart() = 0;

    virtual void OnStop() = 0;

    virtual ~NTDeviceDelegate() {}
};

class NTSampleObserver;

class NTDevice : public NTObject {
public:

    NTDeviceInfo* QueryDeviceInfo();

    void SubscribeDelegate(NTDeviceDelegate* inDeviceDelegate);

    void RemoveDelegate(NTDeviceDelegate* inDeviceDelegate);

    void RemoveAllDelegates();

    virtual int Open() = 0;

    virtual void Close() = 0;

    virtual int StartStreaming();

    virtual int StopStreaming();

    virtual NTArray* EnumarateFormats() = 0;

    virtual int SetFormat(NTFormatDescription* inFormat) = 0;

    virtual NTFormatDescription* QueryFormat() = 0;

    virtual int State() = 0;

    bool IsInState(NTDeviceState inState);

    ~NTDevice();

protected:

    NTDevice(NTDeviceInfo* inDeviceInfo);

    NTSampleObserver* GetSampleAcceptor();

    NTDeviceInfo* deviceInfo;

private:

    NTSampleObserver* observer;

    typedef struct NTDeviceInternal NTDeviceInternal;
    NTDeviceInternal* internal;
};

#endif