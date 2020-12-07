#include "..\Public\Device.h"

void CommandListExecutor::ExecuteList(ICommandList& CmdList)
{

}

int Device::Init()
{
	return 0;
}

int Device::UnInit()
{
	return 0;
}

int Device::Draw()
{
	return 0;
}

void Device::DrawPrimitive(unsigned int baseVertexIndex, unsigned int numPrimitives, unsigned int numInstances)
{

}

void Device::DrawPrimitiveIndirect(void* buffer, unsigned int  offset)
{

}

void Device::DrawIndexedIndirect(void* indexBuffer, void* buffer, int drawIndex, unsigned int numInstances)
{

}

void Device::DrawIndexedPrimitive(void* indexBuffer, int baseVertexIndex, unsigned int firstInstance, unsigned int numVertices, unsigned int startIndex, unsigned int numPrimitives, unsigned int numInstances)
{

}

void Device::DrawIndexedPrimitiveIndirect(void* indexBuffer, void* buffer, unsigned int offset)
{

}

int Device::Clear()
{
	return 0;
}

IRenderTarget*  Device::CreateRenderTarget()
{
	return 0;
}

int Device::SetRenderTarget(IRenderTarget* rt)
{
	return 0;
}

int Device::SetViewPort()
{
	return 0;
}

int Device:: SetPipelineState()
{
	return 0;
}

int Device::Present()
{
	return 0;
}

int Device::CreateObjectConstants()
{
	return 0;
}

int Device::CreateMaterialConstants()
{
	return 0;
}

int Device::CreatePassConstants()
{
	return 0;
}


