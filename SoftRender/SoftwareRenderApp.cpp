#include "SoftwareRenderApp.h"

#include "log.h"
#include "type.h"

namespace SoftRenderer
{

    SoftwareRenderApp::SoftwareRenderApp()
    {
        
    }

    SoftwareRenderApp::~SoftwareRenderApp()
    {

    }

    bool SoftwareRenderApp::Init(HWND hWnd, int w, int h)
    {
        m_hwnd = hWnd;
        m_width = w;
        m_height = h;

        return true;
    }

    void SoftwareRenderApp::Resize(int w, int h)
    {

    }

    void SoftwareRenderApp::ShowWnd(bool fullscreen /*= false*/)
    {
        
    }

    void SoftwareRenderApp::MsgHandle()
    {
        MSG msg;
        while (GetMessage(&msg, m_hwnd, 0, 0) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void SoftwareRenderApp::Clear()
    {
        //TODO
        DestroyWindow(m_hwnd);
    }

    void SoftwareRenderApp::OnKeyDown(UINT key)
    {
        //TODO
    }

    void SoftwareRenderApp::OnMouseMove(int x, int y)
    {
        //TODO
    }

}