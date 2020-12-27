#include "..\Public\PostProcessing.h"
#include "..\Public\Engine.h"

int PostProcessing::Process()
{
    return 0;
}

void PostProcessing::DrawRectangle(float x, float y, float sizeX, float sizeY, float u, float v, float sizeU, float sizeV, Eigen::Vector2i targetSize, Eigen::Vector2i textureSize)
{
    assert(Engine::GetDevice() != nullptr);
    Engine::GetDevice()->DrawIndexedPrimitive(nullptr, 0, 0, 4, 0, 2, 1);

}
