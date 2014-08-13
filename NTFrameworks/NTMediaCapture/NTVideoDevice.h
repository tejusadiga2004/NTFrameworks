


#ifndef NTMediaCapture_NTVideoDevice_H
#define NTMediaCapture_NTVideoDevice_H

#include "NTDeviceManager.h"
#include "NTDevice.h"

typedef struct NTFrameRateRatio {
    int numarator;
    int denominator;

    NTFrameRateRatio()
        : numarator(0), denominator(0) {}

    NTFrameRateRatio(const NTFrameRateRatio& inRatio)
        : numarator(inRatio.numarator), denominator(inRatio.denominator) {}

    NTFrameRateRatio(int inNumarator, int inDenominator)
        : numarator(inNumarator), denominator(inDenominator) {}

    double FrameRate() {
        return numarator / ((double)denominator + 0.0000001);
    }

    bool operator ==(const NTFrameRateRatio& inRatio) {
        return (inRatio.numarator == numarator && inRatio.denominator == denominator);
    }
} NTFrameRateRatio;

class NTVideoCaptureFormatDescription : public NTVideoFormatDescription {
public:

    NTVideoCaptureFormatDescription(const FourCharCode inCodec, const NTSize& inSize, const NTFrameRateRatio& inRatio)
        : NTVideoFormatDescription(inCodec, inSize), frameRateRatio(inRatio) {}

    ~NTVideoCaptureFormatDescription() {}

    double FrameRate() {
        return frameRateRatio.FrameRate();
    }

    NTFrameRateRatio FrameRateRatio() {
        return frameRateRatio;
    }

    bool IsEqualToFormat(NTFormatDescription* inFormat) {
        bool result = (((NTVideoCaptureFormatDescription*) inFormat)->FrameRateRatio() == frameRateRatio);
        return result && NTVideoFormatDescription::IsEqualToFormat(inFormat);
    }

private:

    NTFrameRateRatio frameRateRatio;
};

class NTVideoDevice : public NTDevice {
public:

    static NTVideoDevice* CreateVideoDevice(NTDeviceInfo* inDeviceInfo);

    ~NTVideoDevice();

    virtual int Open() = 0;

    virtual void Close() = 0;

    virtual int StartStreaming() = 0;

    virtual int StopStreaming() = 0;

    virtual int State() = 0;

    virtual  NTArray* EnumarateFormats() = 0;

    virtual int SetFormat(NTFormatDescription* inFormat) = 0;

    virtual NTFormatDescription* QueryFormat() = 0;

protected:

    NTVideoDevice(NTDeviceInfo* inDeviceInfo);
};

#endif