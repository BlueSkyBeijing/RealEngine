#pragma once
#include <Eigen/Dense>

class IBuffer
{
public:
};

class UniformBuffer : public IBuffer
{
public:

	UniformBuffer()
	{}

private:
};

class IndexBuffer : public IBuffer
{
public:

	IndexBuffer(unsigned int inStride, unsigned int inSize, unsigned int inUsage)
		: Stride(inStride)
		, Size(inSize)
		, Usage(inUsage)
	{}

private:
	unsigned int Stride;
	unsigned int Size;
	unsigned int Usage;
};

class VertexBuffer : public IBuffer
{
public:

	VertexBuffer(unsigned int InSize, unsigned int InUsage)
		: Size(InSize)
		, Usage(InUsage)
	{}

private:
	unsigned int Size;
	unsigned int Usage;
};

