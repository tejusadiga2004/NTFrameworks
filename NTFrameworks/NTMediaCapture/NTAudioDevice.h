

#ifndef NTMediaCapture_NTAudioDevice_H
#define NTMediaCapture_NTAudioDevice_H

#include "NTDeviceManager.h"
#include "NTDevice.h"

class NTAudioDevice : public NTDevice {
public: 

    static NTAudioDevice* CreateAudioDevice(NTDeviceInfo* inDeviceInfo);

    ~NTAudioDevice();

    virtual int Open() = 0;

    virtual void Close() = 0;

    virtual int StartStreaming() = 0;

    virtual int StopStreaming() = 0;

    virtual int State() = 0;

    virtual  NTArray* EnumarateFormats() = 0;

    virtual int SetFormat(NTFormatDescription* inFormat) = 0;

    virtual NTFormatDescription* QueryFormat() = 0;

protected:

    NTAudioDevice(NTDeviceInfo* inDeviceInfo);
};

#endif