//
//  NTSourceFilter.h
//  NTMediaFoundation
//
//  Created by Tejus on 11/02/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTSourceFilter__
#define __NTMediaFoundation__NTSourceFilter__

class NTFilter;
class NTString;
class NTTimer;

class NT_LIBRARY_USAGE NTSourceFilter : public NTFilter, public NTConnectable {
public:
    
    NTSourceFilter (NTString* inFilterName);
    
    ~NTSourceFilter ();
    
    virtual bool Start ();
    
    virtual bool Stop ();
    
    virtual NTFormatDescription* QueryFormat () = 0;
    
protected:
    
    NTTimer* _sourceTimer;
};

#endif /* defined(__NTMediaFoundation__NTSourceFilter__) */
