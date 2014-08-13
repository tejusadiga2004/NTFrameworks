


#ifndef __NTMediaFoundation__NTWaveFileInputStream__
#define __NTMediaFoundation__NTWaveFileInputStream__

#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTFormatDescription.h"

class NTWaveFileInputStream : public NTFileInputStream {
public:
    
    NTWaveFileInputStream (NTString* inWaveFileName);
    
    ~NTWaveFileInputStream ();
    
    NTAudioFormatDescription* QueryFormat ();
    
    NTUInteger Read (uint8_t* inoutBuffer, uint64_t inTimeIntervalInMs);
    
private:
    
    typedef struct NTWaveFileInputStreamInternal NTWaveFileInputStreamInternal;
    NTWaveFileInputStreamInternal* _internal;
};

#endif /* defined(__NTMediaFoundation__NTWaveFileInputStream__) */