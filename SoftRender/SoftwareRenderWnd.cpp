#include "SoftwareRenderWnd.h"

#include "log.h"
#include "type.h"

namespace SoftRenderer
{

    SoftwareRenderWnd::SoftwareRenderWnd()
    {
        char *module_dir = new char[256];
        wchar_t *wstr = new wchar_t[256];
        GetModuleFileName(GetModuleHandle(NULL), wstr, 256);
        WideCharToMultiByte(CP_ACP, 0, wstr, 256, module_dir, 256, NULL, NULL);
        *(strrchr(module_dir, '\\') + 1) = 0;
        m_directory = module_dir;
        delete[] module_dir;
        delete[] wstr;
    }

    SoftwareRenderWnd::~SoftwareRenderWnd()
    {

    }

    bool SoftwareRenderWnd::Init(HINSTANCE hInstance, const char *title, int width, int height)
    {
        WNDCLASSEX wndClassEx;

        memset(&wndClassEx, 0, sizeof(WNDCLASSEX));

        wndClassEx.cbSize = sizeof(WNDCLASSEX);
        wndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        wndClassEx.lpfnWndProc = WndProc;
        wndClassEx.hInstance = hInstance;
        wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        wndClassEx.hCursor = LoadIcon(NULL, IDC_ARROW);
        wndClassEx.lpszClassName = L"SoftwareRenderWnd";

        if (RegisterClassEx(&wndClassEx) == 0)
        {
            SLOG("RegisterClassEx Error");
            return false;
        }

        m_title = title;
        m_width = width;
        m_height = height;

        std::wstring wtitle;
        StrToWstr(m_title, wtitle);

        DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
        m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, wndClassEx.lpszClassName, wtitle.c_str(), style, 0, 0, width, height, NULL, NULL, hInstance, NULL);
        if (NULL == m_hwnd)
        {
            SLOG("CreateWindowEx Error");
            return false;
        }

        m_hdc = GetDC(m_hwnd);
        if (NULL == m_hdc)
        {
            SLOG("GetDC Error");
            return false;
        }

        //TODO
    }

    void SoftwareRenderWnd::ShowWnd(bool fullscreen /*= false*/)
    {
        RECT wndRect, clientRect, desktopRect;
        GetWindowRect(GetDesktopWindow(), &desktopRect);
        GetWindowRect(m_hwnd, &wndRect);
        GetClientRect(m_hwnd, &clientRect);

        wndRect.right += m_width - clientRect.right;
        wndRect.bottom += m_height - clientRect.bottom;

        wndRect.right -= wndRect.left;
        wndRect.bottom -= wndRect.top;

        wndRect.left = desktopRect.right / 2 - wndRect.right / 2;
        wndRect.top = desktopRect.bottom / 2 - wndRect.bottom / 2;

        MoveWindow(m_hwnd, wndRect.right, wndRect.top, wndRect.right, wndRect.bottom, false);
        ShowWindow(m_hwnd, fullscreen ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
    }

    void SoftwareRenderWnd::MsgHandle()
    {
        MSG msg;
        while (GetMessage(&msg, m_hwnd, 0, 0) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void SoftwareRenderWnd::Clear()
    {
        //TODO
        DestroyWindow(m_hwnd);
    }

    void SoftwareRenderWnd::OnKeyDown(UINT key)
    {
        //TODO
    }

    void SoftwareRenderWnd::OnMouseMove(int x, int y)
    {
        //TODO
    }

}