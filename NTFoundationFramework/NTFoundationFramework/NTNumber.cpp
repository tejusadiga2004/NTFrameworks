
#include "NTLibraryDefines.h"

#define NT_LIBRARY_USAGE NT_LIBRARY_IMPORT
#include "NTObject.h"
#undef NT_LIBRARY_USAGE

#define NT_LIBRARY_USAGE NT_LIBRARY_EXPORT
#include "NTNumber.h"
#undef NT_LIBRARY_USAGE

typedef struct NTNumberInternal {
	double data;
} NTNumberInternal;

NTNumber::NTNumber(int inNumber) : internal(new NTNumberInternal)
{
	internal->data = (double)inNumber;
}

NTNumber::NTNumber(NTInteger inNumber) : internal(new NTNumberInternal)
{
	internal->data = (double)inNumber;
}

NTNumber::NTNumber(float inNumber) : internal(new NTNumberInternal)
{
	internal->data = (double)inNumber;
}

NTNumber::NTNumber(double inNumber) : internal(new NTNumberInternal)
{
	internal->data = (double)inNumber;
}

NTNumber::~NTNumber()
{
	SafeRelease(internal);
}

int NTNumber::IntValue()
{
	return (int)internal->data;
}

NTInteger NTNumber::IntegerValue()
{
	return (NTInteger)internal->data;
}

float NTNumber::FloatValue()
{
	return (float)internal->data;
}

double NTNumber::DoubleValue()
{
	return (double)internal->data;
}

bool NTNumber::IsEqualToNumber(NTNumber* inNumber)
{
	return (internal->data == inNumber->DoubleValue());
}