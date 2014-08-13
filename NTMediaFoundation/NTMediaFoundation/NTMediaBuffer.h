//
//  NTMediaBuffer.h
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 22/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTMediaBuffer__
#define __NTMediaFoundation__NTMediaBuffer__


class NT_LIBRARY_USAGE NTMediaBuffer : public NTObject {
public:
    
    NTMediaBuffer (const char* inBuffer, int inLength);
    
    ~NTMediaBuffer ();
    
    bool AquireOwnership (NTObject* inContext);
    
    bool RelinqueshOwnership (NTObject* inContext);
    
    const char* Buffer ();

    int QueryLength ();
    
private:
    
    typedef struct NTMediaBufferInternal NTMediaBufferInternal;
    NTMediaBufferInternal* _internal;
};

#endif /* defined(__NTMediaFoundation__NTMediaBuffer__) */
