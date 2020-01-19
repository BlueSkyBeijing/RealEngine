#include "..\Public\Mesh.h"

int Mesh::Load()
{
	return 0;
}

void ManualMesh::FillData(std::vector<Vertex>&inVertexData, std::vector<VertexIndex>&inIndexData)
{
	VertexData = inVertexData;
	IndexData = inIndexData;
}
