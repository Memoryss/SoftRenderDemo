#include "App.h"

App::App()
{

}

App::~App()
{

}

void App::Init(HWND hwnd, int w, int h)
{
    m_hwnd = hwnd;
    m_width = w;
    m_height = h;

    OnInit(w, h);

    m_time = 0;
    m_framTime = 1.f / 60.f;
}

void App::Update()
{
    //使用静态变量 保存
    static DWORD lastTick = GetTickCount();
    DWORD curTick = GetTickCount();

    OnUpdate();

    m_framTime = (curTick - lastTick) / 1000.f;
    m_time += m_framTime;
    lastTick = curTick;
}

void App::Stop()
{
    OnStop();
}

void App::Resize(int w, int h)
{
    m_width = w;
    m_height = h;
    OnResize(w, h);
}
