#ifndef __SOFTWARE_RENDER_CONTEXT_H__
#define __SOFTWARE_RENDER_CONTEXT_H__

#include <windows.h>
#include "type.h"

namespace SoftRenderer
{
    class SoftwareRenderContext
    {
    public:
        SoftwareRenderContext(HWND hwnd, int w, int h);
        ~SoftwareRenderContext();

        void Resize(int w, int h);

        void Present(const vec3 *buffer);

    protected:
        void init(int w, int h);

    protected:
        HWND m_hwnd;
        int m_width{ 0 };
        int m_height{ 0 };
        int m_linePatch{ 0 };
        HDC m_offscreenDC;
        HBITMAP m_offscreenBitmap;
        void *m_backBuffer;
    };
}

#endif