#pragma once
#include "../Public/MeshUtility.h"

bool MeshUtility::CreateCube(ManualMesh& outMesh, float SideSize)
{
	std::vector<Vertex> VertexData;
	std::vector<VertexIndex> IndexData;

	VertexData.resize(24);
	IndexData.resize(36);

	float w2 = 1.0f;
	float h2 = 1.0f;
	float d2 = 1.0f;

	//
	// Create the vertices.
	//

	// Fill in the front face vertex data.
	VertexData[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	VertexData[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	VertexData[2] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	VertexData[3] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	VertexData[4] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	VertexData[5] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	VertexData[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	VertexData[7] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	VertexData[8] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	VertexData[9] = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	VertexData[10] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	VertexData[11] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	VertexData[12] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	VertexData[13] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	VertexData[14] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	VertexData[15] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	VertexData[16] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	VertexData[17] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	VertexData[18] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	VertexData[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	VertexData[20] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	VertexData[21] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	VertexData[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	VertexData[23] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	//
	// Create the indices.
	//

	// Fill in the front face index data
	IndexData[0] = 0; IndexData[1] = 1; IndexData[2] = 2;
	IndexData[3] = 0; IndexData[4] = 2; IndexData[5] = 3;

	// Fill in the back face index data
	IndexData[6] = 4; IndexData[7] = 5; IndexData[8] = 6;
	IndexData[9] = 4; IndexData[10] = 6; IndexData[11] = 7;

	// Fill in the top face index data
	IndexData[12] = 8; IndexData[13] = 9; IndexData[14] = 10;
	IndexData[15] = 8; IndexData[16] = 10; IndexData[17] = 11;

	// Fill in the bottom face index data
	IndexData[18] = 12; IndexData[19] = 13; IndexData[20] = 14;
	IndexData[21] = 12; IndexData[22] = 14; IndexData[23] = 15;

	// Fill in the left face index data
	IndexData[24] = 16; IndexData[25] = 17; IndexData[26] = 18;
	IndexData[27] = 16; IndexData[28] = 18; IndexData[29] = 19;

	// Fill in the right face index data
	IndexData[30] = 20; IndexData[31] = 21; IndexData[32] = 22;
	IndexData[33] = 20; IndexData[34] = 22; IndexData[35] = 23;

	outMesh.FillData(VertexData, IndexData);

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
