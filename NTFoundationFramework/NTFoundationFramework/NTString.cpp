//
//  NTString.cpp
//  NTFoundationFramework
//
//  Created by Tejus Adiga on 16/01/14.
//  Copyright (c) 2014 Entropy. All rights reserved.
//

#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTString.h"
#undef NT_LIBRARY_USAGE

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream> 

typedef struct NTStringInternal {
    char* _string;
    int _length;
    std::wstring string;

    NTStringEncoding encoding;
    
    NTStringInternal(const char* inString, NTStringEncoding inEncoding = kNTStringEncoding_UTF16)
        : encoding(inEncoding)
    {
        if (inEncoding == kNTStringEncoding_UTF8) {
            std::string narrowString(inString);
            string = std::wstring(narrowString.begin(), narrowString.end());
        }
        else {
            string = std::wstring((wchar_t*)inString);
        }
        _length = string.length();
    }
    
    ~NTStringInternal() {
        if (_string != nullptr) {
            free(_string);
            _string = nullptr;
        }
    }
    
} NTStringInternal;

NTString::NTString(const char* inString, NTStringEncoding inEncoding)
: data(new NTStringInternal(inString, inEncoding))
{
    
}

NTString::~NTString ()
{
    SafeRelease(data);
}

NTString* NTString::StringByAppendingString (NTString* inString)
{
    std::wstring newString = data->string + (wchar_t*)inString->UTF16String();
    return (new NTString((char*)newString.c_str()));
}

NTString* NTString::AppendString (NTString* inString)
{
    char* catString = strncat(data->_string, inString->UTF8String(), inString->Length());
    SafeRelease(data);
    data = new NTStringInternal(catString);
    return this;
}

bool NTString::IsEqualToString (NTString* inString)
{
    return (strncmp(data->_string, inString->UTF8String(), data->_length) == 0);
}

NTString* NTString::SubString (NTRange inRange)
{
    char* substring = _strdup(data->_string);
    memset(substring, 0, data->_length);
    strncpy(substring, data->_string + inRange.location, inRange.length);
                             
    NTString* string = new NTString(substring);
    free(substring);
    return string;
}

NTRange NTString::SearchString (NTString* inString)
{
    NTRange range;
    
    char* substring = strstr(data->_string, inString->UTF8String());
    if (substring != nullptr) {
        range = NTRange((int)(substring - inString->UTF8String()), inString->Length());
    }
    
    return range;
}

const char* NTString::UTF16String() const
{
	return (const char*)_wcsdup(data->string.c_str());
}

const char* NTString::UTF8String () const
{
    std::wstring::iterator it;
    std::string utf8String;
    for (it = data->string.begin(); it != data->string.end(); it++) {
        wchar_t wideCahr = *it;
        utf8String += (char)wideCahr;
    }

	return _strdup(utf8String.c_str());
}

int NTString::Length () const
{
    return data->string.length();
}

NTStringEncoding NTString::StringEncoding()
{
    return data->encoding;
}

std::string NTString::Description()
{
    std::ostringstream stringDec;
    stringDec << "{\n" << NTObject::Description() << "\nNTString: " << this->UTF8String() << "\n}" << std::endl;
    return stringDec.str();
}