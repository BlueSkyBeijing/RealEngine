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

inline UINT CalcConstantBufferByteSize(UINT byteSize)
{
	return (byteSize + 255) & ~255;
}