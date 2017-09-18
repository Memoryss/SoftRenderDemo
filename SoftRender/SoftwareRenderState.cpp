#include "SoftwareRenderState.h"

namespace SoftRenderer
{

	SoftwareRenderState::SoftwareRenderState()
		: m_cullFace(false)
		, m_cullFaceType(CFF_BACK)
		, m_antiAliasingType(AAT_2X2)
		, m_bilinearTextureFiltering(true)
		, m_depthTest(true)
		, m_texture(0)
	{

	}

	SoftwareRenderState::~SoftwareRenderState()
	{

	}

	void SoftwareRenderState::SetCullFaceEnable(bool cullFace)
	{
		m_cullFace = cullFace;
	}

	bool SoftwareRenderState::GetCullFaceEnable()
	{
		return m_cullFace;
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

	void SoftwareRenderState::SetDepthTestEnable(bool depthTest)
	{
		m_depthTest = depthTest;
	}

	bool SoftwareRenderState::GetDepthTestEnable()
	{
		return m_depthTest;
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