#pragma once

#include <vector>

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

	void Process(CompositePass* Root)
	{
	}

	CompositePass* Pass;
	CompositionGraph* Graph;

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
		Nodes.push_back(InPass);

		return InPass;
	}

	friend struct CompositePassContext;

private:

	std::vector<CompositePass*> Nodes;
};

class PostprocessContext
{
public:
	PostprocessContext(CompositionGraph& InGraph);

	CompositionGraph& Graph;

	CompositePass* SceneColor;
	CompositePass* SceneDepth;
	CompositePass* FinalOutput;
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
};

class PostProcessing : public IPostProcessing
{
public:
	int Process() override;
};
