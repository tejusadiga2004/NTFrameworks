//
//  NTFile.h
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 29/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTFoundationFramework__NTFile__
#define __NTFoundationFramework__NTFile__

#include "stdint.h"

class NTString;
class NTStream;
class NTInoutStream;
class NTOutputStream;

typedef NTInputStream NTInputFile;
typedef NTOutputStream NTOutputFile;

class NT_LIBRARY_USAGE  NTFile : public NTObject{
public:

    static NTOutputFile* CreateFileAtPathForWriting(NTString* inFilePath);

    static NTInputFile* CreateFileAtPathForReading(NTString* inFilePath);

    static NTOutputFile* CreateFileAtPathForDataWriting(NTString* inFilePath);

    static NTInputFile* CreateFileAtPathForDataReading(NTString* inFilePath);

    ~NTFile() {}
};

#endif /* defined(__NTFoundationFramework__NTFile__) */
