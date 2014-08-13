//
//  NTMediaControl.h
//  NTMediaFoundation
//
//  Created by Tejus on 11/02/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#ifndef __NTMediaFoundation__NTMediaControl__
#define __NTMediaFoundation__NTMediaControl__

class NTRenderFilter;
class NTMediaSample;

class NT_LIBRARY_USAGE NTMediaControl : public NTObject, public INTBackgroundTaskDelegate {
public:
    
    NTMediaControl (NTRenderFilter* inParentFilter);
    
    virtual ~NTMediaControl ();
    
    void SetRenderFilter (NTRenderFilter* inFilter);
    
    virtual bool OnStartTask () = 0;
    
    virtual bool OnPerformTask () = 0;
    
    virtual void OnFinishTask () = 0;
    
protected:
    
    NTRenderFilter* _nextFilter;
    NTRenderFilter* _parentFilter;
};

class NTSourceMediaControl : public NTMediaControl {
public:
    
    NTSourceMediaControl (NTRenderFilter* inParentFilter);
    
    virtual ~NTSourceMediaControl () {}
    
    virtual NTMediaSample* GenerateSample () = 0;
    
    bool OnStartTask ();
    
    bool OnPerformTask ();
    
    void OnFinishTask ();
};

class NTTransformMediaControl : public NTMediaControl {
public:
    
    NTTransformMediaControl (NTRenderFilter* inParentFilter);
    
    virtual ~NTTransformMediaControl () {}
    
    virtual bool ProcessSample (NTMediaSample* inMediaSample) = 0;
    
    bool OnStartTask ();
    
    bool OnPerformTask ();
    
    void OnFinishTask ();
    
protected:
    
    void DeliverProcessedSample (NTMediaSample* inMediaSample);
};

class NTRenderMediaControl : public NTMediaControl {
public:
    
    NTRenderMediaControl (NTRenderFilter* inParentFilter);
    
    virtual ~NTRenderMediaControl () {}
    
    virtual bool RenderSample (NTMediaSample* inMediaSample) = 0;
    
    bool OnStartTask ();
    
    bool OnPerformTask ();
    
    void OnFinishTask ();
};


#endif /* defined(__NTMediaFoundation__NTMediaControl__) */
