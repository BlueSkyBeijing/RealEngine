#pragma once
#include <string>

enum ShaderType
{
	ST_Vertex,
	ST_Pixel,
	ST_Geometry,
	ST_Hull,
	ST_Domain,
	ST_Compute,
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
	Shader(ShaderType inType);
	virtual int Load() override;	
	virtual int Combline() override;
	virtual const std::string& GetName() const override;
	virtual const ShaderType GetType() const override;
protected:
	std::string Name;
	ShaderType Type;
};

class GraphicsShader : public Shader
{
public:
	GraphicsShader(ShaderType inType);
protected:
};

class ComputeShader : public Shader
{
public:
	ComputeShader();
protected:
};

class VertexShader : public GraphicsShader
{
public:
    VertexShader() : GraphicsShader(ST_Vertex) {}
};

class HullShader : public GraphicsShader
{
public:
    HullShader() : GraphicsShader(ST_Hull) {}
};

class DomainShader : public GraphicsShader
{
public:
    DomainShader() : GraphicsShader(ST_Domain) {}
};

class PixelShader : public GraphicsShader
{
public:
    PixelShader() : GraphicsShader(ST_Pixel) {}
};

class GeometryShader : public GraphicsShader
{
public:
    GeometryShader() : GraphicsShader(ST_Geometry) {}
};
