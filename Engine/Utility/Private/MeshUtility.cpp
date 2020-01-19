#pragma once
#include "../Public/MeshUtility.h"

bool MeshUtility::CreateCube(ManualMesh& outMesh, float SideSize)
{
	std::vector<Vertex> VertexData;
	std::vector <VertexIndex> IndexData;

	outMesh.FillData();

	return true;
}

bool MeshUtility::CreateSphere(ManualMesh& outMesh, float radius)
{
	return true;
}

bool MeshUtility::CreatePlane(ManualMesh& outMesh, float sideSize)
{
	return true;
}
