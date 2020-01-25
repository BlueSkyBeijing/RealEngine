#include "..\Public\Texture.h"

int Texture::Load()
{
    return 0;
}

const int Texture::GetWidth() const
{
    return mWidth;
}

const int Texture::GetHeight() const
{
    return mHeight;
}

const PixelFormat Texture::GetPixelFormat() const
{
    return mPixelFormat;
}

const TextureFileFormat Texture::GetTextureFileFormat() const
{
    return mTextureFileFormat;
}
