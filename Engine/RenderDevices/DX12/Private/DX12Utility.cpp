#include "..\Public\DX12Utility.h"
#include <comdef.h>

DX12Exception::DX12Exception()
{

}

DX12Exception::DX12Exception(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber):
	ErrorCode(hr),
	FunctionName(functionName),
	Filename(filename),
	LineNumber(lineNumber)
{
}

std::wstring DX12Exception::ToString() const
{
	_com_error err(ErrorCode);
	std::wstring msg = ANSIToWString(err.ErrorMessage());

	return FunctionName + L" failed in " + Filename + L"; line " + std::to_wstring(LineNumber) + L"; error: " + msg;
}
