//
//  NTFilterGraph.cpp
//  NTMediaFoundation
//
//  Created by Tejus Adiga on 23/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#include "NTFilter.h"
#include "NTFormatDescription.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTFilterGraph.h"
#undef NT_LIBRARY_USAGE

NTString* const kNTFilterOption_Format = new NTString("NTFilterOption_Format");

typedef struct NTFilterGraphInternal {
    
    NTMutableArray* _filterList;
    
    NTFilterGraphInternal () : _filterList(new NTMutableArray()) {
        
    }
    
    ~NTFilterGraphInternal () {
        NTSafeRelease(_filterList);
    }
    
    bool ConnectFilter (NTFilter* inFilter);
    
} NTFilterGraphInternal;


NTFilterGraph::NTFilterGraph ()
: _internal(new NTFilterGraphInternal())
{
    
}

NTFilterGraph::~NTFilterGraph ()
{
    SafeRelease(_internal->_filterList);
}

bool NTFilterGraph::AppendFilter (NTFilter* inFilter)
{
    bool status = false;
    
    if (inFilter == nullptr) {
        return false;
    }
    
    status = _internal->ConnectFilter(inFilter);

    if (status) {
        _internal->_filterList->AppendElement(inFilter);
    }
    
    return status;
}

bool NTFilterGraph::StartFilterGraph ()
{
    bool status = false;
    for (int cnt = _internal->_filterList->Size(); cnt > 0; cnt--) {
        NTFilter* aFilter = (NTFilter*)_internal->_filterList->ObjectAtIndex(cnt);
        status = aFilter->Start();
        if (!status) {
            break;
        }
    }
    
    if (!status) {
        for (int cnt = _internal->_filterList->Size(); cnt > 0; cnt--) {
            NTFilter* aFilter = (NTFilter*)_internal->_filterList->ObjectAtIndex(cnt);
            aFilter->Stop();
        }
    }
    
    return status;
}

bool NTFilterGraph::StopFilterGraph ()
{
    bool status = false;
    for (int cnt = 0; cnt < _internal->_filterList->Size(); cnt--) {
        NTFilter* aFilter = (NTFilter*)_internal->_filterList->ObjectAtIndex(cnt);
        aFilter->Stop();
    }
    return status;
}

bool NTFilterGraphInternal::ConnectFilter (NTFilter* inFilter)
{
    NTFilter* upstreamFilter = (NTFilter*) _filterList->ObjectAtIndex(_filterList->Size());
    
    NTConnectable* connectableFilter = dynamic_cast<NTConnectable*>(upstreamFilter);

    if (connectableFilter != nullptr) {
        if (upstreamFilter->QueryFormat()->MediaType() == inFilter->QueryFormat()->MediaType()) {
            if (connectableFilter)
            return connectableFilter->ConnectDownstreamFilter(inFilter);
        }
    }
    
    return false;
}
