//
//  NTWaveFileInputStream.cpp
//  NTMediaFoundation
//
//  Created by Tejus on 14/03/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#include "NTWaveFileInputStream.h"

typedef struct NTWaveHeader : public NTObject {
    uint32_t chunkId;
    uint32_t chunkSize;
    uint32_t fomrat;
    uint32_t subchunkId;
    uint32_t subchunkSize;
    uint16_t audioFormat;
    uint16_t channels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAllign;
    uint16_t bitsPerSample;
    uint32_t subchunk2Id;
    uint32_t subchunk2Size;
} NTWaveHeader;

typedef struct NTWaveFileInputStreamInternal : public NTObject {
    
    NTWaveHeader* _waveHeader;
    NTAudioFormatDescription* _format;
    
    NTWaveFileInputStreamInternal ()
    : NTObject(), _waveHeader(nullptr), _format(nullptr) {
        _waveHeader = new NTWaveHeader();
        memset(_waveHeader, 0, sizeof(NTWaveHeader));
    }
    
    ~NTWaveFileInputStreamInternal () {
        NTSafeRelease(_waveHeader);
        NTSafeRelease(_format);
    }
    
} NTWaveFileInputStreamInternal;

NTWaveFileInputStream::NTWaveFileInputStream (NTString* inWaveFileName)
: NTFileInputStream(inWaveFileName), _internal(new NTWaveFileInputStreamInternal())
{
    NTUInteger bytesRead = NTFileInputStream::Read((uint8_t*)_internal->_waveHeader, sizeof(NTWaveHeader));
    
    if (bytesRead == sizeof(NTWaveHeader)) {
        _internal->_format = new NTAudioFormatDescription(kNTAudioCodec_LPCM,
                                                          _internal->_waveHeader->sampleRate,
                                                          _internal->_waveHeader->channels,
                                                          _internal->_waveHeader->channels);
    }
}

NTWaveFileInputStream::~NTWaveFileInputStream ()
{
    NTSafeRelease(_internal);
}

NTAudioFormatDescription* NTWaveFileInputStream::QueryFormat ()
{
    NTAudioFormatDescription* theFormat = nullptr;
    if (_internal->_format != nullptr) {
        theFormat = _internal->_format;
    }
    
    return theFormat;
}

NTUInteger NTWaveFileInputStream::Read (uint8_t* inoutBuffer, uint64_t inTimeIntervalInMs)
{
    NTWaveHeader* hdr = _internal->_waveHeader;
    int bufferSize = hdr->byteRate * inTimeIntervalInMs / 1000.0f;

    return NTFileInputStream::Read(inoutBuffer, bufferSize);
}

