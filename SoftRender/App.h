#ifndef __APP_H__
#define __APP_H__

#include <windows.h>

class App
{
public:
    App();
    virtual ~App();

    virtual void Init(HWND hwnd, int w, int h);

    virtual void Update();

    virtual void Stop();

    virtual void Resize(int w, int h);

    virtual void OnInit(int w, int h) = 0;

    virtual void OnUpdate() = 0;

    virtual void OnStop() = 0;

    virtual void OnResize(int w, int h) = 0;

    virtual void OnMouseDown(int btn) {}

    virtual void OnMouseUp(int btn) {}

    virtual void OnMouseMove(int x, int y) {}

    virtual void OnKeyDown(int key) {}

    virtual void OnKeyUp(int key) {}

protected:
    HWND m_hwnd;
    int m_width{ 0 };
    int m_height{ 0 };

    float m_time;
    float m_framTime;
};

#endif