//
//  NTFormatDescription.h
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 22/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTFormatDescription__
#define __NTMediaFoundation__NTFormatDescription__

typedef int FourCharCode;

typedef enum NTMediaType {
    kNTMediaTypeNone,
    kNTMediaTypeVideo,
    kNTMediaTypeAudio
} NTMediaType;

typedef enum NTMediaCodec {
    kNTVideoCodec_None         = 0,
    kNTVideoCodec_YUY2         = 'yuy2',
    kNTVideoCodec_PlanarYUV420 = 'y420',
    kNTVideoCodec_PlanarYUV422 = 'y422',
    kNTVideoCodec_MJPG         = 'mjpg',

    kNTAudioCodec_LPCM         = 'lpcm'
} NTMediaCodec;

typedef struct NTSize {
    
    int width;
    int height;
    int length;
    
    NTSize (int inWidth, int inHeight) : width(inWidth), height(inHeight), length(width * height) {}

    bool operator == (const NTSize& inSize) {
        return (inSize.width == width && inSize.height == height);
    }

} NTSize;

const NTSize NTSizeZero = NTSize(0, 0);

class NTObject;

class NTFormatDescription : public NTObject {
public:
    
    NTFormatDescription (FourCharCode inCodec, const NTMediaType inMediaType)
    : _codec(inCodec), _mediaType(inMediaType) {}
    
    virtual ~NTFormatDescription () {}
    
    FourCharCode Codec () {
        return _codec;
    }
    
    NTMediaType MediaType () {
        return _mediaType;
    }

    bool IsEqualToFormat (NTFormatDescription* inFormat) {
        return   (inFormat->MediaType() == this->MediaType()
               && inFormat->Codec() == this->Codec());
    }
    
private:
    FourCharCode _codec;
    NTMediaType  _mediaType;
};

class NTVideoFormatDescription : public NTFormatDescription {
public:
    
    NTVideoFormatDescription (const FourCharCode inCodec, const NTSize& inSize)
    : NTFormatDescription(inCodec, kNTMediaTypeVideo),
      _size(inSize) {}
    
    ~NTVideoFormatDescription () {}
    
    NTSize& Size () {
        return _size;
    }

    bool IsEqualToFormat (NTFormatDescription* inFormat) {
        NTVideoFormatDescription* videoFormat = dynamic_cast<NTVideoFormatDescription*>(inFormat);
        bool result = false;
        if (videoFormat != nullptr) {
            result = NTFormatDescription::IsEqualToFormat(inFormat) && videoFormat != nullptr;
            result |= (videoFormat->Size() == _size);
        }
        return result;
    }
    
private:
    NTSize _size;
};

class NTAudioFormatDescription : public NTFormatDescription {
public:
    
    NTAudioFormatDescription (const FourCharCode inCodec, int inSampleRate, int inChannels, int inBitsPerSample)
    : NTFormatDescription(inCodec, kNTMediaTypeAudio),
     _sampleRate(inSampleRate),
     _channels(inChannels),
     _bitsPerSample(inBitsPerSample) {}
    
    ~NTAudioFormatDescription () {
        
    }
    
    int SampleRate () {
        return _sampleRate;
    }
    
    int Channels () {
        return _channels;
    }
    
    int BitsperSample () {
        return _bitsPerSample;
    }

    bool IsEqualToFormat (NTFormatDescription* inFormat) {
        NTAudioFormatDescription* audioFormat = dynamic_cast<NTAudioFormatDescription*>(inFormat);
        bool result = false;
        if (audioFormat != nullptr) {
            result = NTFormatDescription::IsEqualToFormat(inFormat);
            result |= (audioFormat->SampleRate() == _sampleRate);
            result |= (audioFormat->Channels() == _channels);
            result |= (audioFormat->BitsperSample() == _bitsPerSample);
        }
        return result;
    }
    
private:
    int _sampleRate;
    int _channels;
    int _bitsPerSample;
};

#endif /* defined(__NTMediaFoundation__NTFormatDescription__) */
