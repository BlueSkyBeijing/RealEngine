#pragma once

class IEngine
{
public:
	virtual int Init() = 0;

	virtual int Tick() = 0;

	virtual int Exit() = 0;
};


class RealEngine : public IEngine
{
public:
	RealEngine();
	~RealEngine();

	virtual int Init() override;

	virtual int Tick() override;

	virtual int Exit() override;
};
