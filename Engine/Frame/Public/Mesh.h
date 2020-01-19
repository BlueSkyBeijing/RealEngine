#pragma once
#include "Vertex.h"
#include <vector>

class IMesh
{
public:
	virtual int Load() = 0;
};

class Mesh : public IMesh
{
public:
	virtual int Load() override;
	inline const std::vector<Vertex>& GetVertexData() const
	{
		return VertexData;
	}
	inline const std::vector<VertexIndex>& GetIndexData() const
	{
		return IndexData;
	}

protected:
	std::vector<Vertex> VertexData;
	std::vector <VertexIndex> IndexData;
};


class ManualMesh : public Mesh
{
public:
	void FillData(std::vector<Vertex>&inVertexData, std::vector<VertexIndex>&inIndexData);

};
