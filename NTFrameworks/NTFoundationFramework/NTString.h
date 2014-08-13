/*!
 @file      NTString.h
            NTFoundationFramework
 
 @author    Tejus Adiga M
 @date      16/01/14.
 @copyright Copyright (c) 2014 Entropy. All rights reserved.
 */

#ifndef __NTFoundationFramework__NTString__
#define __NTFoundationFramework__NTString__

class NTObject;

typedef enum NTStringEncoding {
    kNTStringEncoding_UTF8,
    kNTStringEncoding_UTF16
} NTStringEncoding;

/*!
 @struct    NTRange
 @field     location
 @field     length
 @abstract  NTRange wraps the location and range information. location specifies the starting point of the data and length specifies contigious length of the data from location.
 */
typedef struct NTRange {
    int location;
    int length;
    
    NTRange () : location(0), length(0) {}
    NTRange (int inLoc, int inLength) : location(inLoc), length(inLength) {}
} NTRange;

/*!
 @class     NTString
 @abstract  NTString respesents the string object and related operations on strings.
 */
class NT_LIBRARY_USAGE NTString : public NTObject {
public:
    
    /*!
     @function  NTString
     @param     const char*, The buffer containing string. Searches for \0 for termination of string.
     @abstract  Default constructor for NTString. Argument initilizes the string with inString.
     */
    NTString(const char* inString, NTStringEncoding inEncoding = kNTStringEncoding_UTF16);
    
    /*!
     @function  ~NTString
     @abstract  Destructor for NTString.
     */
    ~NTString ();
    
    /*!
     @function  StringByAppendingString
     @param     NTString*, The string to current string and returns appneded string as new object.
     @abstract  Appends current string string with new string and returns appended string as new object.
     @return    NTString*, new string constructed.
     */
    NTString* StringByAppendingString (NTString* inString);
    
    /*!
     @function  AppendString
     @param     NTString*, string to append with.
     @abstract  Appends current string with given string and returns current object. New object is not constructed.
     @return    NTString*, appneded string.
     */
    NTString* AppendString (NTString* inString);
    
    /*!
     @function  IsEqualToString
     @param     NTString*, string to compare with.
     @abstract  Compares current string with inString. This is case sensitive.
     @return    bool, true if current string is same as inString and false otherwise.
     */
    bool IsEqualToString (NTString* inString);
    
    /*!
     @function  SubString
     @param     NTRange, Range specifying start location and length of substring.
     @abstract  Extracts the substring in the current string cheracterized by location and length of substring.
     @return    NTString*, substring as new object.
     */
    NTString* SubString (NTRange inRange);
    
    /*!
     @function  SearchString
     @param     NTString*, string to search.
     @abstract  searches the given string in the current string and returns its location.
     @return    NTRange, Location of given string in current string.
     */
    NTRange SearchString (NTString* inString);
    
    /*!
     @function  UTF8String
     @abstract  returns the internal buffer base pointer. Buffer is still owned by NTString.
     @return    const char*, Base pointer of the string.
     */
    const char* UTF8String () const;

    const char* UTF16String() const;
    
    /*!
     @function  Length
     @abstract  Returns the length of the string.
     @return    int, Length of the string.
     */
    int Length () const;

    NTStringEncoding StringEncoding();

    virtual std::string Description();
    
private:
    
    typedef struct NTStringInternal NTStringInternal;
    mutable NTStringInternal* data;
};

#endif /* defined(__NTFoundationFramework__NTString__) */
