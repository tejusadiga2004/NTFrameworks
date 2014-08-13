

#ifndef NTMediaCapture_NTDeviceManager_H
#define NTMediaCapture_NTDeviceManager_H

#include <NTFoundationFramework/NTLibraryDefines.h>

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include <NTFoundationFramework/NTFoundationFramework.h>
#include <NTMediaFoundation/NTMediaFoundation.h>
#undef NT_LIBRARY_USAGE

class NTDevice;

typedef struct NTDeviceInfo : public NTObject {
    NTString*           deviceID;
    NTString*           friendlyName;
    NTMediaType         mediaType;
    void*               internalContext;

    NTDeviceInfo(NTString* inDeviceID, NTString* inFriendlyName, NTMediaType inDeviceType, void* inContext = nullptr);

    NTDeviceInfo(NTDeviceInfo* inDeviceInfo);

    ~NTDeviceInfo();
} NTDeviceInfo;

class NTDeviceManagerDelegate : public NTObject {
public:

    void OnDeviceArrived(NTDeviceInfo* inDevice);

    void OnDeviceRemoved(NTDeviceInfo* inDevice);
};

class NTDeviceManager : public NTObject {
public:

    static NTDeviceManager* SystemDeviceManager();
    
    static void ReleaseDeviceManager(NTDeviceManager* inDeviceManager);

    virtual NTArray* EnumarateDevicesWithMediaType(NTMediaType inMediaType) = 0;

    virtual NTDevice* CreateDevice(NTDeviceInfo* inDeviceInfo) = 0;

    void SubscribePlugAndPlayObserver(NTDeviceManagerDelegate* inObserver);

    void UnSubscribePlugAndPlayObserver(NTDeviceManagerDelegate* inObserver);

    void UnSubscribeAllPlugAndPlayObservers();


protected:

    NTDeviceManager();

    NTArray* deviceObservers;
};

#endif