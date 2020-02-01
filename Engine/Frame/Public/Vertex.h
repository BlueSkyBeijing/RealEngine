#pragma once
#include <Eigen/Dense>

class IVertexLayout
{
public:
};

class VertexLayout : public IVertexLayout
{
public:
};

class IVertex
{
public:
};

class Vertex : public IVertex
{
public:
	Vertex(Eigen::Vector3f inPos);
protected:
	Eigen::Vector3f Pos;
	VertexLayout Layout;
};



class IVertexIndex
{
};

class VertexIndex : public IVertexLayout
{
public:
	int Index;
};
