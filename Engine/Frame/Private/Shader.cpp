#include "..\Public\Shader.h"

Shader::Shader(ShaderType inType):Type(inType)
{

}

int Shader::Load()
{
	return 0;
}

int Shader::Combline()
{
	return 0;
}

const std::string& Shader::GetName() const
{
	return Name;
}

const ShaderType Shader::GetType() const
{
	return Type;
}


GraphicsShader::GraphicsShader(ShaderType inType):
	Shader(inType)
{

}

ComputeShader::ComputeShader() :
    Shader(ST_Compute)
{

}
