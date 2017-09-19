#ifndef __SOFTWARE_RENDER_WND_H__
#define __SOFTWARE_RENDER_WND_H__

#include <string>
#include <windows.h>

namespace SoftRenderer
{
	class SoftwareRenderWnd
	{
	public:
        SoftwareRenderWnd();
        ~SoftwareRenderWnd();

        bool Init(HINSTANCE hInstance, const char *title, int width, int height);

        void ShowWnd(bool fullscreen = false);

        void MsgHandle();

        void Clear();

        //键盘和鼠标事件响应
        void OnKeyDown(UINT key);
        void OnMouseMove(int x, int y);

	private:
		std::string m_title;
		int m_width{ 0 };
		int m_height{ 0 };
        HWND m_hwnd;
        HDC m_hdc;

        std::string m_directory;
	};
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

#endif // !__SOFTWARE_RENDER_WND_H__
