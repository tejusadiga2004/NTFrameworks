
#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#include "NTNumber.h"
#include "NTString.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE
#include "NTStream.h"
#include "NTInputStream.h"
#include "NTOutputStream.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTFile.h"
#undef NT_LIBRARY_USAGE

#include <iostream>
#include <fstream>

class NTFileStream : public NTObject {
public:

    NTFileStream(NTString* inFilename, std::ios::openmode inOpenmode)
        : _filename(inFilename), _status(kNTStreamStatus_NoError), _openMode(inOpenmode)
    {

    }

    ~NTFileStream()
    {
        this->Close();
        NTSafeRelease(_filename);
    }

    NTInteger Open(std::fstream* inStream)
    {
        NTInteger status = -1;
        _status = kNTStreamStatus_Error;

        _file = inStream;

        if (_file) {
            status = 0;
            _status = kNTStreamStatus_NoError;
        }

        return status;
    }

    bool IsOpen()
    {
        if (_file && _file->is_open()) {
            return true;
        }
        return false;
    }

    void Close()
    {
        if (_file->is_open()) {
            _file->close();
            delete _file;
            _file = nullptr;
        }
    }

    NTUInteger Status()
    {
        return _status;
    }

    bool IsSeekable()
    {
        return true;
    }

    NTInteger Seek(NTInteger inOffset, NTFileSeekOrigin inSeekOrigin)
    {
		int initial = (int)_file->tellg();
        _file->seekg(inOffset, (std::basic_fstream<char, std::char_traits<char> >::seek_dir)inSeekOrigin);
		int final = (int)_file->tellg();
        return final - initial;
    }

    bool HasBytesAwailable()
    {
        return !_file->eof();
    }

    NTUInteger Read(uint8_t* inoutBuffer, int inBufferSize)
    {
        NTInteger readBytes = -1;
        _status = kNTStreamStatus_Error;

        if (inoutBuffer) {
            if (_file->is_open()) {
                _file->read((char*) inoutBuffer, inBufferSize);
				readBytes = (NTUInteger)_file->gcount();
                _status = (_file->eof()) ? kNTStreamStatu_EndOfStream : kNTStreamStatus_NoError;
            }
        }

        return readBytes;
    }

    NTUInteger Write(uint8_t* inBuffer, NTUInteger inBufferLength)
    {
        NTInteger writtenBytes = -1;
        _status = kNTStreamStatus_Error;

        if (inBuffer) {
            if (_file->is_open()) {
                _file->write((char*)inBuffer, inBufferLength);
				writtenBytes = (NTUInteger)_file->gcount();
                _status = kNTStreamStatus_NoError;
            }
        }

        return writtenBytes;
    }

    NTUInteger AwailableStreamSize()
    {
        NTUInteger remainingSize = 0;
		NTUInteger currentpos = (NTUInteger)_file->tellg();
        _file->seekg(0, std::ios::end);
		remainingSize = (NTUInteger)_file->tellg();
        _file->seekg(currentpos, std::ios::beg);
        return remainingSize;
    }

    NTString* Filename() { return _filename; }

private:

    NTString*           _filename;
    std::fstream*       _file;
    std::ios::openmode  _openMode;
    NTUInteger          _status;
};

class NTInputFileImpl : public NTInputStream {
public:

    NTInputFileImpl(NTString* inFileName) : fileStream(new NTFileStream(inFileName, std::ifstream::beg)), NTInputStream()
    {

    }

    ~NTInputFileImpl()
    {
        this->Close();
        NTSafeRelease(fileStream);
    }

    bool HasBytesAwailable()
    {
        return fileStream->HasBytesAwailable();
    }

    NTUInteger Read(uint8_t* inoutBuffer, int inBufferSize)
    {
        return fileStream->Read(inoutBuffer, inBufferSize);
    }

    NTUInteger AwailableStreamSize()
    {
        return fileStream->AwailableStreamSize();
    }

    NTInteger Open()
    {
        return this->Open(true);
    }

    NTInteger Open(bool shouldOpenInBinaryMode)
    {
        if (fileStream->Filename()) {
            std::ios::openmode openMode = std::ios::in;
            openMode |= (shouldOpenInBinaryMode) ? std::ios::binary : 0;
            std::ifstream* inputStream = new std::ifstream(fileStream->Filename()->UTF8String(), openMode);
            return fileStream->Open((std::fstream*)inputStream);
        }
        return -1;
    }

    bool IsOpen()
    {
        return fileStream->IsOpen();
    }

    void Close()
    {
        return fileStream->Close();
    }

    NTUInteger Status()
    {
        return fileStream->Status();
    }

    bool IsSeekable()
    {
        return true;
    }

    NTInteger Seek(NTInteger inOffset, NTFileSeekOrigin inSeekOrigin)
    {
        return fileStream->Seek(inOffset, inSeekOrigin);
    }

private:

    NTFileStream* fileStream;
};

class NTOutputFileImpl : public NTOutputStream {
public:

    NTOutputFileImpl(NTString* inFileName) : fileStream(new NTFileStream(inFileName, std::ifstream::beg)), NTOutputStream()
    {

    }

    ~NTOutputFileImpl()
    {
        this->Close();
        NTSafeRelease(fileStream);
    }

    NTUInteger Write(uint8_t* inBuffer, NTUInteger inBufferLength)
    {
        return fileStream->Write(inBuffer, inBufferLength);
    }

    bool HasSpaceAwailable()
    {
        return true;
    }

    NTInteger Open()
    {
        return this->Open(true);
    }

    NTInteger Open(bool shouldOpenInBinaryMode)
    {
        if (fileStream->Filename()) {
            std::ios::openmode openMode = std::ios::out | ((shouldOpenInBinaryMode) ? std::ios::binary : 0);
            std::ofstream* outStream = new std::ofstream(fileStream->Filename()->UTF8String(), openMode);
            return fileStream->Open((std::fstream*)outStream);
        }
        return -1;
    }

    bool IsOpen()
    {
        return fileStream->IsOpen();
    }

    void Close()
    {
        return fileStream->Close();
    }

    NTUInteger Status()
    {
        return fileStream->Status();
    }

    bool IsSeekable()
    {
        return true;
    }

    NTInteger Seek(NTInteger inOffset, NTFileSeekOrigin inSeekOrigin)
    {
        return fileStream->Seek(inOffset, inSeekOrigin);
    }

private:

    NTFileStream* fileStream;
};

NTOutputFile* CreateFileAtPathForWriting(NTString* inFilePath)
{
    NTOutputFileImpl* outFile = new NTOutputFileImpl(inFilePath);
    outFile->Open(false);
    return outFile;
}

NTInputFile* CreateFileAtPathForReading(NTString* inFilePath)
{
    NTInputFileImpl* outFile = new NTInputFileImpl(inFilePath);
    outFile->Open(false);
    return outFile;
}

NTOutputFile* CreateFileAtPathForDataWriting(NTString* inFilePath)
{
    NTOutputFileImpl* outFile = new NTOutputFileImpl(inFilePath);
    outFile->Open(false);
    return outFile;
}

NTInputFile* CreateFileAtPathForDataReading(NTString* inFilePath)
{
    NTInputFileImpl* outFile = new NTInputFileImpl(inFilePath);
    outFile->Open(false);
    return outFile;
}