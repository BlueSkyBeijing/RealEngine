#pragma once

enum PixelFormat
{
	R8G8B8,
};

enum TextureFileFormat
{
	TGA,
};

class ITexture
{
public:
	virtual int Load() = 0;
	virtual const int GetWidth() const = 0;
	virtual const int GetHeight() const = 0;
	virtual const PixelFormat GetPixelFormat() const = 0;
	virtual const TextureFileFormat GetTextureFileFormat() const = 0;
};

class Texture : public ITexture
{
public:
	virtual int Load() override;
	virtual const int GetWidth() const override;
	virtual const int GetHeight() const override;
	virtual const PixelFormat GetPixelFormat() const override;
	virtual const TextureFileFormat GetTextureFileFormat() const = 0;
protected:
	int mWidth;
	int mHeight;
	PixelFormat mPixelFormat;
	TextureFileFormat mTextureFileFormat;
};
