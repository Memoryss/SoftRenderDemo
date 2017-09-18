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

		//���������޳�
		void SetCullFaceEnable(bool cullFace);
		bool GetCullFaceEnable();

		//�����޳�����
		void SetCullFaceType(CullFaceType type);
		CullFaceType GetCullFaceType();

		//���ÿ����
		void SetAnitiAliasingType(AntiAliasingType type);
		AntiAliasingType GetAnitiAliasingType();

		//������Ȳ��Կ���
		void SetDepthTestEnable(bool depthTest);
		bool GetDepthTestEnable();

		//����˫���Թ���
		void SetBilinearTextureFilteringEnable(bool bilinearTextureFiltering);
		bool GetBilinearTextureFilteringEnable();

		//��������
		void SetTexture(Texture *texture);
		Texture * GetTexture();

	private:
		CullFaceType m_cullFaceType;
		AntiAliasingType m_antiAliasingType;

		bool m_depthTest;		//��Ȳ���
		bool m_bilinearTextureFiltering; //	����˫���Թ���
		bool m_cullFace;		//�����޳�

		Texture *m_texture;		//����
	};
}

#endif