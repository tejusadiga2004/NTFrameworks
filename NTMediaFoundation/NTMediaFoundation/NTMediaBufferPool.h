//
//  NTMediaBufferPool.h
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 18/08/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef NTMediaFoundation_NTMediaBufferPool_h
#define NTMediaFoundation_NTMediaBufferPool_h

class NTObject;
class NTMediaBuffer;

class NT_LIBRARY_USAGE NTMediaBufferPool : public NTObject {
public:
    
    NTMediaBufferPool (int inBufferSize, int inPoolSize = 30);
    
    ~NTMediaBufferPool ();
    
    NTMediaBuffer* RequestBuffer ();
    
    void SurrenderBuffer (NTMediaBuffer* inBuffer);

    int QueryBufferSize () const;
    
private:
    NTMutableArray* bufferList;
    
    int bufferSize;
};

#endif
