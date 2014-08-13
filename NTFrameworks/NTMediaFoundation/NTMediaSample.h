//
//  NTMediaSample.h
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 22/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTMediaSample__
#define __NTMediaFoundation__NTMediaSample__

typedef unsigned long long TimeStamp;

class NTMutableArray;
class NTMediaBuffer;

class NT_LIBRARY_USAGE NTMediaSample : public NTMutableArray {
public:
    
    NTMediaSample (NTMediaBuffer* inBuffer, TimeStamp inTime, NTFormatDescription* inFormat);
    
    NTMediaSample (NTMediaSample* inMediaSample);
    
    ~NTMediaSample ();

    void SetTimestamp (TimeStamp inTime);
    
    TimeStamp Timestamp ();
    
    NTFormatDescription* FormatDescription ();
    
private:
    TimeStamp            _timestamp;
    NTFormatDescription* _format;
};

#endif /* defined(__NTMediaFoundation__NTMediaSample__) */
