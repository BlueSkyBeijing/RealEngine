#pragma once

#include "Vertex.h"
#include <vector>
#include <Eigen/Dense>

enum PassInputId
{
	PII_Input0,
	PII_Input1,
	PII_Input2,
	PII_Input3,
	PII_Input4,
	PII_Input5,
	PII_Input6,
	PII_Input7,
	PII_Input8,
	PII_Input9,
	PII_Input10,
	PII_Input_MAX
};

enum PassOutputId
{
	POI_Output0,
	POI_Output1,
	POI_Output2,
	POI_Output3,
	POI_Output4,
	POI_Output5,
	POI_Output6,
	POI_Output7
};

struct PostProcessingInputs
{

};

class CompositePass;
class CompositionGraph;


class CompositePassContext
{
	CompositePassContext();

	~CompositePassContext();

	void Process(CompositePass* root)
	{
	}

	CompositePass* mPass;
	CompositionGraph* mGraph;

private:
	bool mProcessed;
};

class CompositePass
{
	CompositePass()
		: mProcessed(false)
	{
	}

	virtual ~CompositePass() {}

	virtual CompositePass* GetInput(PassInputId inPassInputId) = 0;

	virtual const CompositePass* GetInput(PassInputId inPassInputId) const = 0;

	virtual void SetInput(PassInputId inPassInputId, const CompositePass& inOutputRef) = 0;

	virtual void AddDependency(const CompositePass& inOutputRef) = 0;

	virtual void Process(CompositePassContext& Context) = 0;

	virtual CompositePass* GetOutput(PassOutputId inPassOutputId) = 0;

	virtual CompositePass* GetDependency(unsigned int Index) = 0;


protected:

	bool mProcessed;
	friend class CompositionGraph;
};

class CompositionGraph
{
public:
	CompositionGraph();
	~CompositionGraph();

	template<class T>
	T* AddPass(T* InPass)
	{
		mNodes.push_back(InPass);

		return InPass;
	}

	friend class CompositePassContext;

private:

	std::vector<CompositePass*> mNodes;
};

class PostprocessContext
{
public:
	PostprocessContext(CompositionGraph& InGraph);

	CompositionGraph& Graph;

	CompositePass* mSceneColor;
	CompositePass* mSceneDepth;
	CompositePass* mFinalOutput;
};


struct ScreenRectangleVertex
{
public:
	Eigen::Vector4f mPosition;
	Eigen::Vector2f mUV;
};

class ScreenRectangleVertexDeclaration
{
public:
    virtual void Init()
    {
		std::vector<VertexElement> Elements;
        unsigned int Stride = sizeof(ScreenRectangleVertex);
    }
};

class ScreenRectangleVertexBuffer
{
public:
	void Init()
	{
        std::vector<ScreenRectangleVertex> Vertices;

        Vertices.resize(6);

        Vertices[0].mPosition = Eigen::Vector4f(1, 1, 0, 1);
        Vertices[0].mUV = Eigen::Vector2f(1, 1);

        Vertices[1].mPosition = Eigen::Vector4f(0, 1, 0, 1);
        Vertices[1].mUV = Eigen::Vector2f(0, 1);

        Vertices[2].mPosition = Eigen::Vector4f(1, 0, 0, 1);
        Vertices[2].mUV = Eigen::Vector2f(1, 0);

        Vertices[3].mPosition = Eigen::Vector4f(0, 0, 0, 1);
        Vertices[3].mUV = Eigen::Vector2f(0, 0);

        Vertices[4].mPosition = Eigen::Vector4f(-1, 1, 0, 1);
        Vertices[4].mUV = Eigen::Vector2f(-1, 1);

        Vertices[5].mPosition = Eigen::Vector4f(1, -1, 0, 1);
        Vertices[5].mUV = Eigen::Vector2f(1, -1);

	}

public:
    VertexBuffer mVertexBuffer;
};

class ScreenRectangleIndexBuffer
{
public:
	void Init()
	{
        const unsigned int Indices[] = { 0, 1, 2, 2, 1, 3, 0, 4, 5 };

        std::vector<unsigned int> IndexBuffer;
		unsigned int NumIndices = 9;
        IndexBuffer.resize(NumIndices);
        memcpy(IndexBuffer.data(), Indices, NumIndices * sizeof(unsigned int));

	}
public:
	VertexIndexBuffer mVertexIndexBuffer;
};

class PostProcessVS
{
public:
	PostProcessVS()
	{}

	void SetParameters(const CompositePassContext&) {}
};

class IPostProcessing
{
public:
	virtual int Process() = 0;
    virtual void DrawRectangle(float x, float y, float sizeX, float sizeY, float u, float v, float sizeU, float sizeV, Eigen::Vector2i targetSize, Eigen::Vector2i textureSize) = 0;

};

class PostProcessing : public IPostProcessing
{
public:
	int Process() override;
    virtual void DrawRectangle(float x, float y, float sizeX, float sizeY, float u, float v, float sizeU, float sizeV, Eigen::Vector2i targetSize, Eigen::Vector2i textureSize) override;

protected:
	ScreenRectangleVertexBuffer mScreenRectangleVertexBuffer;
	ScreenRectangleIndexBuffer mScreenRectangleIndexBuffer;
};
