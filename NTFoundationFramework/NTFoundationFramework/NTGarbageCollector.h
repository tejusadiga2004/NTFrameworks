


#ifndef __NTFoundationFramework__NTAllocator__
#define __NTFoundationFramework__NTAllocator__

class NTGarbageCollector
{
    public:

    static NTGarbageCollector* GetGarbageCollector();

    static void* operator new(size_t insize);

    static void operator delete (void* inPtr);

private:

    NTGarbageCollector();

    ~NTGarbageCollector();
};

#endif