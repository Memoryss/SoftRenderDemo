#ifndef __SOFTWARE_RENDER_WND_H__
#define __SOFTWARE_RENDER_WND_H__

#include <string>
#include <windef.h>

namespace SoftRenderer
{
	class SoftwareRenderWnd
	{
	public:

	private:
		std::string m_title;
		int m_width{ 0 };
		int m_height{ 0 };

	};
}

#endif // !__SOFTWARE_RENDER_WND_H__
