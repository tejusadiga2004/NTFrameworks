//
//  NTVideoYUVFIleInputStream.cpp
//  NTMediaFoundation
//
//  Created by Tejus on 14/03/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#include "NTVideoYUVFIleInputStream.h"

typedef struct NTVideoYUVFileInputStreamInternal {
    
    NTSize _size;
    FourCharCode _codec;
    NTVideoFormatDescription* _format;
    
    NTVideoYUVFileInputStreamInternal(NTSize inSize, FourCharCode  inCodec)
    : _size(inSize), _codec(inCodec) {
        _format = new NTVideoFormatDescription(inCodec, inSize);
    }
    
    ~NTVideoYUVFileInputStreamInternal() {
        NTSafeRelease(_format);
    }
    
} NTVideoYUVFileInputStreamInternal;

NTVideoYUVFileInputStream::NTVideoYUVFIleInputStream (NTString*     inWaveFileName,
                                                      NTSize        inSize,
                                                      FourCharCode  inCodec)
: NTFileInputStream(inWaveFileName), _internal(new NTVideoYUVFIleInputStreamInternal(inSize, inCodec))
{
    
}

NTVideoYUVFileInputStream::~NTVideoYUVFIleInputStream()
{
    SafeRelease(_internal);
}

NTVideoFormatDescription* NTVideoYUVFileInputStream::QueryFormat()
{
    _internal->_format->Retain();
    return _internal->_format;
}

NTUInteger NTVideoYUVFileInputStream::Read(uint8_t* inoutBuffer)
{
    return NTFileInputStream::Read(inoutBuffer, _internal->_size.length);
}