

#ifndef __NTMediaFoundation__NTVideoYUVFileOutputStream__
#define __NTMediaFoundation__NTVideoYUVFileOutputStream__

#include <NTFoundationFramework\NTFoundationFramework.h>
#include "NTFormatDescription.h"

class NTVideoYUVFileOutputStream : public NTFileOutputStream {
public:

    NTVideoYUVFileOutputStream (NTString* inFileName, NTSize inVideoSize);

    ~NTVideoYUVFileOutputStream ();

private:
    
    NTSize _size;
};

#endif