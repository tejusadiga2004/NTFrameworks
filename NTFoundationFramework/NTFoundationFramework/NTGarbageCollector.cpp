

#include "NTGarbageCollector.h"

#include "GarbageCollection/gc.h"

static NTGarbageCollector* collector;

NTGarbageCollector* NTGarbageCollector::GetGarbageCollector()
{
    if (collector == nullptr) {
        GC_INIT();
        collector = (NTGarbageCollector*)GC_MALLOC(sizeof(NTGarbageCollector));

        collector = new (collector) NTGarbageCollector;
    }

    return collector;
}

NTGarbageCollector::NTGarbageCollector()
{
    GC_INIT();
}

NTGarbageCollector::~NTGarbageCollector()
{

}

void* operator new(size_t insize)
{

}

void operator delete (void* inPtr)
{

}