#pragma once

enum ShaderType
{
VertexShader,
PixelShader,
GeometryShader,
HullShader,
DomainShader,
}

class IShader
{
public:
	virtual int Load() = 0;
	virtual int Combline() = 0;
	virtual const int GetName() = 0;
	virtual const ShaderType GetType() = 0;
};

class Shader : public IShader
{
public:
	virtual int Load() override;	
	virtual int Combline() override;
	virtual const int GetName() override;
	virtual const ShaderType GetType() override;
};

