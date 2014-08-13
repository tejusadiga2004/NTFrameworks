//
//  NTWaveFileOutputStream.h
//  NTMediaFoundation
//
//  Created by Tejus on 14/03/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#ifndef __NTMediaFoundation__NTWaveFileOutputStream__
#define __NTMediaFoundation__NTWaveFileOutputStream__

#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTFormatDescription.h"

class NTWaveFileOutputStream : public NTFileOutputStream {
public:
    
    NTWaveFileOutputStream (NTString* inWaveFileName, NTAudioFormatDescription* inFormat);
    
    ~NTWaveFileOutputStream ();
    
    NTAudioFormatDescription* QueryFormat ();

    NTUInteger Write(uint8_t* inBuffer, NTUInteger inBufferLength);
    
    void Close ();
    
private:
    
    typedef struct NTWaveFileOutputStreamInternal NTWaveFileOutputStreamInternal;
    NTWaveFileOutputStreamInternal* _internal;
};

#endif /* defined(__NTMediaFoundation__NTWaveFileOutputStream__) */
