#include "NTVideoYUVFileOutputStream.h"


NTVideoYUVFileOutputStream::NTVideoYUVFileOutputStream (NTString* inFileName, NTSize inVideoSize)
: NTFileOutputStream(inFileName), _size(inVideoSize)
{
}


NTVideoYUVFileOutputStream::~NTVideoYUVFileOutputStream ()
{
}
