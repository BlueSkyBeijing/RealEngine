#pragma once

class ITexture
{
public:
	virtual int Load() = 0;
	virtual const int GetWidth() = 0;
	virtual const int GetHeight() = 0;
	virtual const int GetFormat() = 0;
};

class Texture : public ITexture
{
public:
	virtual int Load() override;
	virtual const int GetWidth() override;
	virtual const int GetHeight() override;
	virtual const int GetFormat() override;
protected:
int Width;
int Hight;
int Format;
};
