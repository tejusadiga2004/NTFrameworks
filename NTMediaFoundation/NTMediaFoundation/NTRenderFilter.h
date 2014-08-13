//
//  NTRenderFilter.h
//  NTMediaFoundation
//
//  Created by Tejus on 11/02/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTRenderFilter__
#define __NTMediaFoundation__NTRenderFilter__

#include <iostream>
#include <mutex>

class NTFilter;
class NTMediaSample;
class NTFormatDescription;

class NT_LIBRARY_USAGE NTRenderFilter : public NTFilter {
public:
    
    NTRenderFilter (NTString* inFilterName, NTFilterType inFilterType = kNTFilterType_Render);
    
    ~NTRenderFilter ();
    
    void PushSample (NTMediaSample* inSample);
    
    virtual bool Start ();
    
    virtual bool Stop ();
    
    virtual NTFormatDescription* QueryFormat () = 0;
    
protected:
    
    NTQueue* _sampleQueue;
    
private:
    
    friend class NTTransformMediaControl;
    friend class NTRenderMediaControl;
    NTMediaSample* GetSampleFromQueue ();
    
    std::mutex _mutex;
};

#endif /* defined(__NTMediaFoundation__NTRenderFilter__) */
