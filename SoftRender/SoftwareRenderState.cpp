#include "SoftwareRenderState.h"

namespace SoftRenderer
{

	SoftwareRenderState::SoftwareRenderState()
	{

	}

	SoftwareRenderState::~SoftwareRenderState()
	{

	}

	void SoftwareRenderState::SetCullFaceType(CullFaceType type)
	{
		m_cullFaceType = type;
	}

	CullFaceType SoftwareRenderState::GetCullFaceType()
	{
		return m_cullFaceType;
	}

	void SoftwareRenderState::SetAnitiAliasingType(AntiAliasingType type)
	{
		m_antiAliasingType = type;
	}

	AntiAliasingType SoftwareRenderState::GetAnitiAliasingType()
	{
		return m_antiAliasingType;
	}

	void SoftwareRenderState::SetDepthTestType(DepthTestType type)
	{
		m_depthTestType = type;
	}

    DepthTestType SoftwareRenderState::GetDepthTestType()
	{
		return m_depthTestType;
	}

    void SoftwareRenderState::EnableDepthMask(bool enable)
    {
        m_depthMask = enable;
    }

    bool SoftwareRenderState::IsDepthMask()
    {
        return m_depthMask;
    }

    void SoftwareRenderState::SetBlendType(BlendType type)
    {
        m_blendType = type;
    }

    BlendType SoftwareRenderState::GetBlendType()
    {
        return m_blendType;
    }

    void SoftwareRenderState::SetBilinearTextureFilteringEnable(bool bilinearTextureFiltering)
	{
		m_bilinearTextureFiltering = bilinearTextureFiltering;
	}

	bool SoftwareRenderState::GetBilinearTextureFilteringEnable()
	{
		return m_bilinearTextureFiltering;
	}

	void SoftwareRenderState::SetTexture(Texture *texture)
	{
		if (0 == texture)
		{
			return;
		}

		m_texture = texture;
	}

	Texture * SoftwareRenderState::GetTexture()
	{
		return m_texture;
	}

}