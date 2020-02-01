#pragma once
#include <string>

enum ShaderType
{
	VertexShader,
	PixelShader,
	GeometryShader,
	HullShader,
	DomainShader,
};

class IShader
{
public:
	virtual int Load() = 0;
	virtual int Combline() = 0;
	virtual const std::string& GetName() const = 0;
	virtual const ShaderType GetType() const = 0;
};

class Shader : public IShader
{
public:
	virtual int Load() override;	
	virtual int Combline() override;
	virtual const std::string& GetName() const override;
	virtual const ShaderType GetType() const override;
protected:
	std::string Name;
	ShaderType Type;
};

