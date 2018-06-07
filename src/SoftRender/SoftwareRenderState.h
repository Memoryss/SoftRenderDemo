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
        CFT_None = 0,
		CFT_FRONT,
		CFT_BACK,
	};

    enum DepthTestType
    {
        DTT_Always = 0,
        DTT_Less,
        DTT_LessEqual,
        DTT_Greater,
        DTT_GreaterEqual,
        DTT_Equal,
        DTT_NotEqual,
    };

    enum BlendType
    {
        BT_Opacity = 0,
        BT_Add,
        BT_AlphaBlend,
    };

	class Texture;

	class SoftwareRenderState
	{
	public:
		SoftwareRenderState();
		~SoftwareRenderState();

		//设置剔除类型
		void SetCullFaceType(CullFaceType type);
		CullFaceType GetCullFaceType();

		//设置抗锯齿
		void SetAnitiAliasingType(AntiAliasingType type);
		AntiAliasingType GetAnitiAliasingType();

		//设置深度测试类型
		void SetDepthTestType(DepthTestType type);
        DepthTestType GetDepthTestType();

        //深度遮罩
        void EnableDepthMask(bool enable);
        bool IsDepthMask();

        //设置混合方式
        void SetBlendType(BlendType type);
        BlendType GetBlendType();

		//设置双线性过滤
		void SetBilinearTextureFilteringEnable(bool bilinearTextureFiltering);
		bool GetBilinearTextureFilteringEnable();

	private:
        CullFaceType m_cullFaceType{ CFT_BACK };
        AntiAliasingType m_antiAliasingType{ AAT_2X2 };
        DepthTestType m_depthTestType{ DTT_LessEqual };
        BlendType m_blendType{ BT_Opacity };

        bool m_bilinearTextureFiltering{ true }; //	纹理双线性过滤

        bool m_depthMask{ false };  //深度遮罩 TODO透明物体？
	};
}

#endif