/*!
 @file      NTData.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTData__
#define __NTFoundationFramework__NTData__

class NTObject;

/*!
 @class     NTData
 @abstract  NTTimer represents the bare data object. It encapsulates a buffer.
 */
class NT_LIBRARY_USAGE NTData : public NTObject {
public:
    
    /*!
     @function  NTData
     @abstract  Default constructor.
     */
    NTData ();
    
    /*!
     @function  NTTimer
     @param     const char*, base pointer to the buffer.
     @param     int, length of the buffer.
     @abstract  Default constructor.
     */
    NTData (const char* inData, int inLength);
    
    /*!
     @function  NTTimer
     @param     NTData, another data object.
     @abstract  Copy constructor.
     */
    NTData (NTData* inData);
    
    /*!
     @function  ~NTTimer
     @abstract  Destructor.
     */
    ~NTData ();
    
    /*!
     @function  AppendData
     @param     NTData, data object to append.
     @abstract  Appends the data to the current buffer object as contigious memory.
     */
    void AppendData (NTData* inData);
    
    /*!
     @function  GetData
     @param     const char*, outside buffer into which data will be copied.
     @param     int, length of the data to be coppied.
     @abstract  Copies the data to the buffer of specified length.
     */
    void GetData (const char* inBuffer, int inDataLength);
    
    /*!
    @function  GetDataBase
    @param     const char*, outside buffer into which data will be copied.
    @param     int, length of the data to be coppied.
    @abstract  Copies the data to the buffer of specified length.
    */
    const char* GetDataBase ();

    /*!
     @function  Length
     @param     const char*, outside buffer into which data will be copied.
     @param     int, length of the data to be coppied.
     @abstract  Copies the data to the buffer of specified length.
     @return    int, Length of the buffer.
     */
    int Length () const;
    
private:
    
    typedef struct NTDataInternal NTDataInternal;
    NTDataInternal* _internal;
};

#endif /* defined(__NTFoundationFramework__NTData__) */
