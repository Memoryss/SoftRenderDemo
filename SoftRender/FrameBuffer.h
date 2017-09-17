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
		Texture *m_colorTexture{ NULL };
		Texture *m_depthTexture{ NULL };
	};

}

#endif
