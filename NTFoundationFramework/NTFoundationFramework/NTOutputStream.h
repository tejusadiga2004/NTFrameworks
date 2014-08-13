//
//  NTOutputStream.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 29/01/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#ifndef __NTFoundationFramework__NTOutputStream__
#define __NTFoundationFramework__NTOutputStream__

#include <stdint.h>

class NTtream;

class NT_LIBRARY_USAGE NTOutputStream : public NTStream {
public:

    virtual NTUInteger Write (uint8_t* inBuffer, NTUInteger inBufferLength) = 0;
    
    virtual bool HasSpaceAwailable () = 0;
    
    virtual ~NTOutputStream () {}
    
protected:
    
    NTOutputStream () {}
};

#endif /* defined(__NTFoundationFramework__NTOutputStream__) */
