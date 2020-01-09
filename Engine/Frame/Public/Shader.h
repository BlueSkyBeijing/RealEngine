#pragma once

class IShader
{
public:
	virtual int Load() = 0;
};

class Shader : public IShader
{
public:
	virtual int Load() override;
};

