#include "FrameBuffer.h"
#include "Texture.h"

namespace SoftRenderer
{

	FrameBuffer::FrameBuffer()
	{

	}

	FrameBuffer::~FrameBuffer()
	{

	}

	Texture * FrameBuffer::GetColorTexture()
	{
		return m_colorTexture;
	}

	Texture * FrameBuffer::GetDepthTexture()
	{
		return m_depthTexture;
	}

	void FrameBuffer::SetColorTexture(Texture *texture)
	{
		m_colorTexture = NULL;
		if (NULL != texture && texture->GetFormat() == TF_BGR24 && texture->GetData() != NULL)
		{
			if (m_depthTexture == NULL 
				|| (texture->GetWidth() == m_depthTexture->GetWidth()
					&& texture->GetHeight() == m_depthTexture->GetHeight()))
			{
				m_colorTexture = texture;
			}
		}
	}

	void FrameBuffer::SetDepthTexture(Texture *texture)
	{
		m_depthTexture = 0;
		if (texture != NULL && texture->GetFormat() == TF_DEPTH16 && texture->GetData() != NULL)
		{
			if (m_colorTexture == NULL
				|| (texture->GetHeight() == m_colorTexture->GetHeight()
					&& texture->GetWidth() == m_colorTexture->GetWidth()))
			{
				m_depthTexture = texture;
			}
		}
	}

}