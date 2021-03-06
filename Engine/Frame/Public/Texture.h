#pragma once

enum PixelFormat
{
	PF_Unknown,
	PF_A32B32G32R32F,
	/** UNORM (0..1), corresponds to FColor.  Unpacks as rgba in the shader. */
	PF_B8G8R8A8,
	/** UNORM red (0..1) */
	PF_G8,
	PF_G16,
	PF_DXT1,
	PF_DXT3,
	PF_DXT5,
	PF_UYVY,
	/** Same as PF_FloatR11G11B10 */
	PF_FloatRGB,
	/** RGBA 16 bit signed FP format.  Use FFloat16Color on the CPU. */
	PF_FloatRGBA,
	/** A depth+stencil format with platform-specific implementation, for use with render targets. */
	PF_DepthStencil,
	/** A depth format with platform-specific implementation, for use with render targets. */
	PF_ShadowDepth,
	PF_R32_FLOAT,
	PF_G16R16,
	PF_G16R16F,
	PF_G16R16F_FILTER,
	PF_G32R32F,
	PF_A2B10G10R10,
	PF_A16B16G16R16,
	PF_D24,
	PF_R16F,
	PF_R16F_FILTER,
	PF_BC5,
	/** SNORM red, green (-1..1). Not supported on all RHI e.g. Metal */
	PF_V8U8,
	PF_A1,
	/** A low precision floating point format, unsigned.  Use FFloat3Packed on the CPU. */
	PF_FloatR11G11B10,
	PF_A8,
	PF_R32_UINT,
	PF_R32_SINT,
	PF_PVRTC2,
	PF_PVRTC4,
	PF_R16_UINT,
	PF_R16_SINT,
	PF_R16G16B16A16_UINT,
	PF_R16G16B16A16_SINT,
	PF_R5G6B5_UNORM,
	PF_R8G8B8A8,
	/** Only used for legacy loading; do NOT use! */
	PF_A8R8G8B8,
	/** High precision single channel block compressed, equivalent to a single channel BC5, 8 bytes per 4x4 block. */
	PF_BC4,
	/** UNORM red, green (0..1). */
	PF_R8G8,
	/** ATITC format. */
	PF_ATC_RGB,
	/** ATITC format. */
	PF_ATC_RGBA_E,
	/** ATITC format. */
	PF_ATC_RGBA_I,
	/** Used for creating SRVs to alias a DepthStencil buffer to read Stencil.  Don't use for creating textures. */
	PF_X24_G8,
	PF_ETC1,
	PF_ETC2_RGB,
	PF_ETC2_RGBA,
	PF_R32G32B32A32_UINT,
	PF_R16G16_UINT,
	/** 8.00 bpp */
	PF_ASTC_4x4,
	/** 3.56 bpp */
	PF_ASTC_6x6,
	/** 2.00 bpp */
	PF_ASTC_8x8,
	/** 1.28 bpp */
	PF_ASTC_10x10,
	/** 0.89 bpp */
	PF_ASTC_12x12,
	PF_BC6H,
	PF_BC7,
	PF_R8_UINT,
	PF_L8,
	PF_XGXR8,
	PF_R8G8B8A8_UINT,
	/** SNORM (-1..1), corresponds to FFixedRGBASigned8. */
	PF_R8G8B8A8_SNORM,
	PF_R16G16B16A16_UNORM,
	PF_R16G16B16A16_SNORM,
	PF_MAX,
};

enum TextureFileFormat
{
	TGA,
};


enum SamplerFilter
{
    SF_Point,
    SF_Bilinear,
    SF_Trilinear,
    SF_AnisotropicPoint,
    SF_AnisotropicLinear,
};

enum SamplerAddressMode
{
    SAM_Wrap,
    SAM_Clamp,
    SAM_Mirror,
    /** Not supported on all platforms */
    SAM_Border,
};

enum SamplerCompareFunction
{
    SCF_Never,
    SCF_Less
};

class SamplerState
{
public:
	SamplerAddressMode WrapS;
	SamplerAddressMode WrapT;
	SamplerAddressMode WrapR;
    int LODBias;
	SamplerCompareFunction MagFilter;
	SamplerCompareFunction MinFilter;
	int MaxAnisotropy;
	SamplerCompareFunction CompareMode;
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

class Texture2D : public Texture
{
public:
protected:
};

class TextureCube : public Texture
{
public:
protected:
};

class TextureVolume : public Texture
{
public:
protected:
};
