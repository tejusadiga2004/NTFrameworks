//
//  NTInputStream.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 29/01/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#ifndef __NTFoundationFramework__NTInputStream__
#define __NTFoundationFramework__NTInputStream__

#include <stdint.h>

class NTStream;

class NT_LIBRARY_USAGE NTInputStream : public NTStream {
public:

    virtual bool HasBytesAwailable () = 0;

    virtual NTUInteger Read (uint8_t* inoutBuffer, int inBufferSize) = 0;

    virtual NTUInteger AwailableStreamSize () = 0;
    
    virtual ~NTInputStream () {}
    
protected:
    
    NTInputStream () {}
};

#endif /* defined(__NTFoundationFramework__NTInputStream__) */
