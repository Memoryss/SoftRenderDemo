#include "SoftwareRenderContext.h"

namespace SoftRenderer
{

    SoftwareRenderContext::SoftwareRenderContext(HWND hwnd, int w, int h)
        : m_hwnd(hwnd)
        , m_width(w)
        , m_height(h)
    {
        init(w, h);
    }

    SoftwareRenderContext::~SoftwareRenderContext()
    {
        DeleteObject(m_offscreenBitmap);
        DeleteDC(m_offscreenDC);
    }

    void SoftwareRenderContext::Resize(int w, int h)
    {
        m_width = w;
        m_height = h;
        init(w, h);
    }

    void SoftwareRenderContext::Present(const vec3 *buffer)
    {
        BYTE *pixels = (BYTE *)m_backBuffer;
        for (int i = 0; i < m_height; ++i)
        {
            for (int j = 0; j < m_width; ++j)
            {
                BYTE r = (BYTE)(buffer[j].r * 255);
                BYTE g = (BYTE)(buffer[j].g * 255);
                BYTE b = (BYTE)(buffer[j].b * 255);

                pixels[j * 3 + 0] = b;
                pixels[j * 3 + 1] = g;
                pixels[j * 3 + 2] = r;
            }

            

            pixels += m_linePatch;
            buffer += m_width;
        }
        
        HDC hdc = GetDC(m_hwnd);
        BitBlt(hdc, 0, 0, m_width, m_height, m_offscreenDC, 0, 0, SRCCOPY);

        ReleaseDC(m_hwnd, hdc);
    }

    void SoftwareRenderContext::init(int w, int h)
    {
        HDC hdc = GetDC(m_hwnd);
        m_offscreenDC = CreateCompatibleDC(hdc);

        BITMAPINFO bi;
        memset(&bi, 0, sizeof(BITMAPINFO));
        bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bi.bmiHeader.biWidth = w;
        bi.bmiHeader.biHeight = -h;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 24;
        bi.bmiHeader.biCompression = BI_RGB;
        m_offscreenBitmap = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (void **)&m_backBuffer, NULL, 0);

        SelectObject(m_offscreenDC, m_offscreenBitmap);

        ReleaseDC(m_hwnd, hdc);

        //32Î»¶ÔÆë
        m_linePatch = m_width * 24 / 8;
        m_linePatch = ((m_linePatch + 3) / 4) * 4;
    }

}