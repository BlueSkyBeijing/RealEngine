#pragma once

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
