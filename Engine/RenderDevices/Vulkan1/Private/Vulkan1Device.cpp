#include "..\Public\Vulkan1Device.h"
#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Platforms\Windows\Public\EngineWindows.h"
#include "..\..\..\Platforms\Windows\Public\RenderWindowWindows.h"
#include "..\..\..\Platforms\Windows\Public\WindowsUtility.h"
#include <SDL.h>

Vulkan1Device::Vulkan1Device()
{

}

Vulkan1Device::~Vulkan1Device()
{

}

int Vulkan1Device::Init()
{
	const VkApplicationInfo app = {
	VK_STRUCTURE_TYPE_APPLICATION_INFO,
	NULL,
	"Real",
	0,
	"Real",
	0,
	VK_API_VERSION_1_0,
	};

	RenderWindow *Window = dynamic_cast<RenderWindow*>(EngineWindows::GetInstance()->GetRenderTarget());

	// Create instance
	//VkInstanceCreateInfo inst_info = {
	//	VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
	//	NULL,
	//	&app,
	//	1,
	//	nullptr,
	//	1,
	//	"",
	//};

	// Select physics device

	// Create a logical device

	// Create a surface

	// Create queue

	return 0;
}

int Vulkan1Device::UnInit()
{
	return 0;

}

int Vulkan1Device::Draw()
{

	return 0;
}
