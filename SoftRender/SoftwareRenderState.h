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

		//�����޳�����
		void SetCullFaceType(CullFaceType type);
		CullFaceType GetCullFaceType();

		//���ÿ����
		void SetAnitiAliasingType(AntiAliasingType type);
		AntiAliasingType GetAnitiAliasingType();

		//������Ȳ�������
		void SetDepthTestType(DepthTestType type);
        DepthTestType GetDepthTestType();

        //�������
        void EnableDepthMask(bool enable);
        bool IsDepthMask();

        //���û�Ϸ�ʽ
        void SetBlendType(BlendType type);
        BlendType GetBlendType();

		//����˫���Թ���
		void SetBilinearTextureFilteringEnable(bool bilinearTextureFiltering);
		bool GetBilinearTextureFilteringEnable();

	private:
        CullFaceType m_cullFaceType{ CFT_BACK };
        AntiAliasingType m_antiAliasingType{ AAT_2X2 };
        DepthTestType m_depthTestType{ DTT_LessEqual };
        BlendType m_blendType{ BT_Opacity };

        bool m_bilinearTextureFiltering{ true }; //	����˫���Թ���

        bool m_depthMask{ false };  //������� TODO͸�����壿
	};
}

#endif