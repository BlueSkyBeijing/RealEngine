#pragma once
#include "d3dx12.h"
#include <windows.h>
#include <string>
#include <cassert>
#include <wrl.h>

#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>

class DX12Exception
{
public:
	DX12Exception();

	DX12Exception(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

	std::wstring ToString()const;

	HRESULT ErrorCode = S_OK;
	std::wstring FunctionName;
	std::wstring Filename;
	int LineNumber = -1;
};

inline std::wstring ANSIToWString(const std::string& str)
{
	WCHAR buffer[512];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);

	return std::wstring(buffer);
}

inline UINT CalcConstantBufferByteSize(UINT byteSize)
{
	return (byteSize + 255) & ~255;
}

#define THROW_IF_FAILED(Res)												       \
{																				   \
    HRESULT Result = (Res);														   \
    std::wstring FileName = ANSIToWString(__FILE__);						 	   \
    if(FAILED(Result)) { throw DX12Exception(Result, L#Res, FileName, __LINE__); } \
}

