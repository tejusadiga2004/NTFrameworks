//
//  NTTransformFilter.h
//  NTMediaFoundation
//
//  Created by Tejus on 11/02/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTTransformFilter__
#define __NTMediaFoundation__NTTransformFilter__

class NT_LIBRARY_USAGE NTTransformFilter : public NTRenderFilter, public NTConnectable {
public:
    
    NTTransformFilter (NTString* inFilterName);
    
    ~NTTransformFilter ();
    
    virtual bool Start ();
    
    virtual bool Stop ();
    
    virtual NTFormatDescription* QueryFormat () = 0;
};

#endif /* defined(__NTMediaFoundation__NTTransformFilter__) */
