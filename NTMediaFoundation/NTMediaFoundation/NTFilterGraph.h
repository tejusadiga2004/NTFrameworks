//
//  NTFilterGraph.h
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 23/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTFilterGraph__
#define __NTMediaFoundation__NTFilterGraph__

extern NTString* const kNTFilterOption_Format; // Expected Filter Video or Audio Format.

class NT_LIBRARY_USAGE NTFilterGraph : public NTObject {
public:
    
    NTFilterGraph ();
    
    ~NTFilterGraph ();
    
    bool AppendFilter (NTFilter* inFilter);
    
    bool StartFilterGraph ();
    
    bool StopFilterGraph ();
    
    bool IsFilterFraphComplete ();
    
private:
    
    typedef struct NTFilterGraphInternal NTFilterGraphInternal;
    NTFilterGraphInternal* _internal;
};

#endif /* defined(__NTMediaFoundation__NTFilterGraph__) */
