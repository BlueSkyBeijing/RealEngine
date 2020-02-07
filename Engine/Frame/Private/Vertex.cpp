#include "..\Public\Vertex.h"


Vertex::Vertex()
{
}

Vertex::Vertex(Eigen::Vector3f inPos, Eigen::Vector3f inNormal, Eigen::Vector2f inTexCoord)
	:Pos(inPos),
	Normal(inNormal),
	TexCoord(inTexCoord)
{
}

Vertex::Vertex(
	float px, float py, float pz,
	float nx, float ny, float nz,
	float u, float v) :
	Pos(px, py, pz),
	Normal(nx, ny, nz),
	TexCoord(u, v)
{
}

