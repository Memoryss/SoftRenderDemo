#include "App.h"

#include <sstream>

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
    //ʹ�þ�̬���� ����
    static DWORD lastTick = GetTickCount();
    DWORD curTick = GetTickCount();

    OnUpdate();

    m_framTime = (curTick - lastTick) / 1000.f;
    m_time += m_framTime;
    lastTick = curTick;

	float frameRate = 0;
	if (m_framTime > 0.000001)
	{
		frameRate = 1.f / m_framTime;
	}

	std::stringstream wss;
	wss << "frame rate:" << frameRate;
	SetWindowText(m_hwnd, wss.str().c_str());
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
