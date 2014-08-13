//
//  NTFilter.h
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 22/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTFilter__
#define __NTMediaFoundation__NTFilter__

typedef enum NTFilterType {
    kNTFilterType_Source,
    kNTFilterType_Transform,
    kNTFilterType_Render
} NTFilterType;

extern NTString* const kNTFilterDescription_FilterType;

class NTFilter;
class NTMediaControl;
class NTFormatDescription;

class NTConnectable : public NTObject {
public:
    
    NTConnectable (NTFilter* inParentFilter);
    
    virtual ~NTConnectable ();
    
    virtual bool ConnectDownstreamFilter (NTFilter* inFilter);
    
protected:
    
    NTFilter* _downstreamFilter;
    NTFilter* _parentFilter;
};

class NT_LIBRARY_USAGE NTFilter : public NTObject {
public:
    
    NTFilter (NTString* inFilterName, NTFilterType inFilterType);
    
    virtual ~NTFilter ();
    
    virtual void SetMediaControl (NTMediaControl* inMediaControl);
    
    virtual bool Start ();
    
    virtual bool Stop ();
    
    virtual NTFormatDescription* QueryFormat () = 0;
    
    bool IsRunning ();
    
protected:
    
    NTBackgroundTask*   _backgroundTask;
    NTString*           _filterName;
    NTFilterType        _filterType;
    NTMediaControl*     _mediaControl;
    
private:
    
    bool _IsRunning;
};

#endif /* defined(__NTMediaFoundation__NTFilter__) */
