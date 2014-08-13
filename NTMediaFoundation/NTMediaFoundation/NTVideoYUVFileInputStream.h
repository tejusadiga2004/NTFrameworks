//
//  NTVideoYUVFIleInputStream.h
//  NTMediaFoundation
//
//  Created by Tejus on 14/03/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#ifndef __NTMediaFoundation__NTVideoYUVFIleInputStream__
#define __NTMediaFoundation__NTVideoYUVFIleInputStream__

#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTFormatDescription.h"

class NTVideoYUVFileInputStream : public NTFileInputStream {
public:
    
    NTVideoYUVFileInputStream (NTString* inWaveFileName, NTSize inSize, FourCharCode inCodec);
    
    ~NTVideoYUVFileInputStream ();
    
    NTVideoFormatDescription* QueryFormat ();
    
    NTUInteger Read (uint8_t* inoutBuffer);
    
private:
    
    typedef struct NTVideoYUVFileInputStreamInternal NTVideoYUVFileInputStreamInternal;
    NTVideoYUVFileInputStreamInternal* _internal;
};

#endif /* defined(__NTMediaFoundation__NTVideoYUVFIleInputStream__) */
