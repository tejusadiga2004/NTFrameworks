//
//  NTNumber.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 24/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTFoundationFramework__NTNumber__
#define __NTFoundationFramework__NTNumber__

typedef long NTInteger;
typedef unsigned long NTUInteger;

class NT_LIBRARY_USAGE NTNumber : public NTObject {
public:
    
    NTNumber (int inNumber);
    
    NTNumber (NTInteger inNumber);

    NTNumber (float inNumber);
    
    NTNumber (double inNumber);
    
    ~NTNumber ();
    
    int IntValue ();
    
    NTInteger IntegerValue ();
    
    float FloatValue ();
    
    double DoubleValue ();
    
    bool IsEqualToNumber (NTNumber* inNumber);
    
private:
    
    typedef struct NTNumberInternal NTNumberInternal;
    NTNumberInternal* internal;
};

#endif /* defined(__NTFoundationFramework__NTNumber__) */
