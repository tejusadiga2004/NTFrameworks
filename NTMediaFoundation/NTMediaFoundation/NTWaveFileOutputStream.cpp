//
//  NTWaveFileOutputStream.cpp
//  NTMediaFoundation
//
//  Created by Tejus on 14/03/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#include "NTWaveFileOutputStream.h"

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

typedef struct NTWaveFileOutputStreamInternal {
    NTAudioFormatDescription* _format;
    NTUInteger _streamSize;
    NTWaveFileOutputStreamInternal (NTAudioFormatDescription* inFormat)
        : _format(inFormat), _streamSize(0)
    {
        _format->Retain();
    }
    
    ~NTWaveFileOutputStreamInternal () {
        NTSafeRelease(_format);
    }
    
} NTWaveFileOutputStreamInternal;


NTWaveFileOutputStream::NTWaveFileOutputStream (NTString*                   inWaveFileName,
                                                NTAudioFormatDescription*   inFormat)
: NTFileOutputStream(inWaveFileName), _internal(new NTWaveFileOutputStreamInternal(inFormat))
{
    NTWaveHeader wavHeader;
    memset(&wavHeader, 0, sizeof(NTWaveHeader));
    this->Write((uint8_t*)&wavHeader, sizeof(NTWaveHeader));
}

NTWaveFileOutputStream::~NTWaveFileOutputStream ()
{
    SafeRelease(_internal);
}

NTAudioFormatDescription* NTWaveFileOutputStream::QueryFormat ()
{
    return _internal->_format;
}

void NTWaveFileOutputStream::Close ()
{
    NTWaveHeader wavHeader;
    memcpy(&wavHeader.chunkId, "RIFF", 4);
    memcpy(&wavHeader.fomrat, "WAVE", 4);
    memcpy(&wavHeader.subchunkId, "fmt ", 4);
    memcpy(&wavHeader.subchunk2Id, "data", 4);

    wavHeader.sampleRate = _internal->_format->SampleRate();
    wavHeader.channels = _internal->_format->Channels();
    wavHeader.bitsPerSample = _internal->_format->BitsperSample();

    wavHeader.subchunkSize = 16;
    wavHeader.audioFormat = 1;
    wavHeader.byteRate = wavHeader.sampleRate * wavHeader.channels * wavHeader.bitsPerSample / 8.0f;
    wavHeader.blockAllign = wavHeader.channels * wavHeader.bitsPerSample / 8.0f;
    wavHeader.subchunk2Size = _internal->_streamSize;
    wavHeader.subchunkSize = _internal->_streamSize + 36;

    this->Seek(0, NTFileSeekOrigin::kNTFileSeekOrigin_Begining);
    NTWaveFileOutputStream::Write((uint8_t*)&wavHeader, sizeof(NTWaveHeader));
    NTFileOutputStream::Close();
}

NTUInteger NTWaveFileOutputStream::Write (uint8_t* inBuffer, NTUInteger inBufferLength)
{
    NTUInteger bytesWritten = 0;
    bytesWritten = NTFileOutputStream::Write(inBuffer, inBufferLength);
    _internal->_streamSize += bytesWritten;
    return bytesWritten;
}