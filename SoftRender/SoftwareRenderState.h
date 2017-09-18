#ifndef __SOFTWARE_RENDER_STATE_H__
#define __SOFTWARE_RENDER_STATE_H__

namespace SoftRenderer
{
	enum AntiAliasingType
	{
		AAT_2X2 = 0,
		AAT_3X3,
		AAT_4X4,
	};

	enum CullFaceType
	{
		CFT_FRONT = 0,
		CFF_BACK,
	};

	class Texture;

	class SoftwareRenderState
	{
	public:
		SoftwareRenderState();
		~SoftwareRenderState();

		//设置启动剔除
		void SetCullFaceEnable(bool cullFace);
		bool GetCullFaceEnable();

		//设置剔除类型
		void SetCullFaceType(CullFaceType type);
		CullFaceType GetCullFaceType();

		//设置抗锯齿
		void SetAnitiAliasingType(AntiAliasingType type);
		AntiAliasingType GetAnitiAliasingType();

		//设置深度测试开关
		void SetDepthTestEnable(bool depthTest);
		bool GetDepthTestEnable();

		//设置双线性过滤
		void SetBilinearTextureFilteringEnable(bool bilinearTextureFiltering);
		bool GetBilinearTextureFilteringEnable();

		//设置纹理
		void SetTexture(Texture *texture);
		Texture * GetTexture();

	private:
		CullFaceType m_cullFaceType;
		AntiAliasingType m_antiAliasingType;

		bool m_depthTest;		//深度测试
		bool m_bilinearTextureFiltering; //	纹理双线性过滤
		bool m_cullFace;		//启动剔除

		Texture *m_texture;		//纹理
	};
}

#endif