//
//  NTStream.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 29/01/14.
//  Copyright (c) 2014 Robosoft. All rights reserved.
//

#ifndef __NTFoundationFramework__NTStream__
#define __NTFoundationFramework__NTStream__

#include <iostream>

class NTObject;
class NTNumber;

typedef enum {
    kNTStreamStatus_NoError     = 20001,
    kNTStreamStatus_Error       = 20002,
    kNTStreamStatu_EndOfStream  = 20003
} NTStreamStatus;

typedef enum NTFileSeekOrigin {
    kNTFileSeekOrigin_Begining  = std::ios::beg,
    kNTFileSeekOrigin_End       = std::ios::end,
    kNTFileSeekOrigin_Current   = std::ios::cur
} NTFileSeekOrigin;

class NT_LIBRARY_USAGE NTStream : public NTObject {
public:
    
    virtual NTInteger Open () = 0;

    virtual bool IsOpen () = 0;
    
    virtual void Close () = 0;
    
    virtual NTUInteger Status () = 0;

    virtual bool IsSeekable () = 0;

    virtual NTInteger Seek(NTInteger inOffset, NTFileSeekOrigin inSeekOrigin) = 0;
    
    virtual ~NTStream () {}
    
protected:
    
    NTStream () {}
};

#endif /* defined(__NTFoundationFramework__NTStream__) */
