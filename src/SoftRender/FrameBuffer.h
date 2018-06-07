#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

namespace SoftRenderer
{
	class Texture;

	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		Texture * GetColorTexture();
		Texture * GetDepthTexture();
		void SetColorTexture(Texture *texture);
		void SetDepthTexture(Texture *texture);


	private:
		Texture *m_colorTexture{ 0 };
		Texture *m_depthTexture{ 0 };
	};

}

#endif
