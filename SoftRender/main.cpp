#include "App.h"
#include "SoftwareRender.h"
#include "SoftwareRenderState.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "RenderBuffer.h"
#include "Camera.h"
#include "Shader.h"

#pragma comment(lib, "FreeImage.lib")

using namespace SoftRenderer;

void fillVertex(vec3 pos, vec3 normal, vec2 uv, vec4 color, Vertex *vertex)
{
    vertex->position = pos;
    vertex->normal = normal;
    vertex->texcoord = uv;
    vertex->color = color;
}

void createBox(RenderBuffer *buffer, float width, float height, float depth)
{
    const float half_w = width * 0.5f;
    const float half_h = height * 0.5f;
    const float half_d = depth * 0.5f;

    vec3 box_pos[8] = {
        vec3(-half_w, half_h, -half_d),
        vec3(half_w, half_h, -half_d),
        vec3(-half_w, -half_h, -half_d),
        vec3(half_w, -half_h, -half_d),

        vec3(-half_w, half_h, half_d),
        vec3(half_w, half_h, half_d),
        vec3(-half_w, -half_h, half_d),
        vec3(half_w, -half_h, half_d),
    };

    vec3 box_normals[6] = {
        vec3(0, 0, -1),
        vec3(0, 0, 1),
        vec3(-1, 0, 0),
        vec3(1, 0, 0),
        vec3(0, 1, 0),
        vec3(0, -1, 0)
    };

    vec4 box_colors[6] = {
        vec4(1, 1, 1, 1),
        vec4(1, 1, 1, 1),
        vec4(1, 1, 1, 1),
        vec4(1, 1, 1, 1),
        vec4(1, 1, 1, 1),
        vec4(1, 1, 1, 1)
    };

    vec2 box_uv[4] = {
        vec2(0, 0),
        vec2(1, 0),
        vec2(0, 1),
        vec2(1, 1)
    };

    buffer->vbuffer.resize(4 * 6);
    Vertex *vertex = &buffer->vbuffer[0];

    //前面
    fillVertex(box_pos[0], box_normals[0], box_uv[0], box_colors[0], vertex);
    ++vertex;
    fillVertex(box_pos[1], box_normals[0], box_uv[1], box_colors[0], vertex);
    ++vertex;
    fillVertex(box_pos[2], box_normals[0], box_uv[2], box_colors[0], vertex);
    ++vertex;
    fillVertex(box_pos[3], box_normals[0], box_uv[3], box_colors[0], vertex);
    ++vertex;

    //后面
    fillVertex(box_pos[5], box_normals[1], box_uv[0], box_colors[1], vertex);
    ++vertex;
    fillVertex(box_pos[4], box_normals[1], box_uv[1], box_colors[1], vertex);
    ++vertex;
    fillVertex(box_pos[7], box_normals[1], box_uv[2], box_colors[1], vertex);
    ++vertex;
    fillVertex(box_pos[6], box_normals[1], box_uv[3], box_colors[1], vertex);
    ++vertex;

    // 左边
    fillVertex(box_pos[4], box_normals[2], box_uv[0], box_colors[2], vertex);
    ++vertex;
    fillVertex(box_pos[0], box_normals[2], box_uv[1], box_colors[2], vertex);
    ++vertex;
    fillVertex(box_pos[6], box_normals[2], box_uv[2], box_colors[2], vertex);
    ++vertex;
    fillVertex(box_pos[2], box_normals[2], box_uv[3], box_colors[2], vertex);
    ++vertex;

    // 右边
    fillVertex(box_pos[1], box_normals[3], box_uv[0], box_colors[3], vertex);
    ++vertex;
    fillVertex(box_pos[5], box_normals[3], box_uv[1], box_colors[3], vertex);
    ++vertex;
    fillVertex(box_pos[3], box_normals[3], box_uv[2], box_colors[3], vertex);
    ++vertex;
    fillVertex(box_pos[7], box_normals[3], box_uv[3], box_colors[3], vertex);
    ++vertex;

    // 顶部
    fillVertex(box_pos[4], box_normals[4], box_uv[0], box_colors[4], vertex);
    ++vertex;
    fillVertex(box_pos[5], box_normals[4], box_uv[1], box_colors[4], vertex);
    ++vertex;
    fillVertex(box_pos[0], box_normals[4], box_uv[2], box_colors[4], vertex);
    ++vertex;
    fillVertex(box_pos[1], box_normals[4], box_uv[3], box_colors[4], vertex);
    ++vertex;

    //底部
    fillVertex(box_pos[2], box_normals[5], box_uv[0], box_colors[5], vertex);
    ++vertex;
    fillVertex(box_pos[3], box_normals[5], box_uv[1], box_colors[5], vertex);
    ++vertex;
    fillVertex(box_pos[6], box_normals[5], box_uv[2], box_colors[5], vertex);
    ++vertex;
    fillVertex(box_pos[7], box_normals[5], box_uv[3], box_colors[5], vertex);
    ++vertex;

    //索引
    buffer->ibuffer.resize(6 * 6);
    auto *ib = &buffer->ibuffer[0];
    for (short i = 0; i < 6; ++i)
    {
        short idx = i * 4;

        *ib++ = idx + 0;
        *ib++ = idx + 1;
        *ib++ = idx + 2;

        *ib++ = idx + 2;
        *ib++ = idx + 1;
        *ib++ = idx + 3;
    }

    buffer->primCount = 12;
    buffer->primType = PT_TriangleList;
}

void createSphere(RenderBuffer *buffer, float radius, int rings, int segments)
{
    int vertexCount = (rings + 1) * (segments + 1);
    int indexCount = rings * segments * 6;

    //顶点数据
    buffer->vbuffer.resize(vertexCount);
    Vertex *vertex = &buffer->vbuffer[0];
    
    float anglePreRings = M_PI / rings;
    float anglePreSeg = M_PI * 2 / segments;

    float r;
    vec3 pos, nor;

    //纬线
    for (int i = 0; i < rings; ++i)
    {
        //纬线圈的半径
        r = radius * sin(i * anglePreRings);
        pos.y = radius * cos(i * anglePreRings);

        //经线
        for (int j = 0; j < segments; ++j)
        {
            pos.x = r * cos(j * anglePreSeg);
            pos.y = r * sin(j * anglePreSeg);
            nor = pos;
            normalize(nor);

            vertex->position = pos;
            vertex->normal = nor;
            vertex->color = (nor + vec3(1.f, 1.f, 1.f)) / 2;
            ++vertex;
        }
    }

    //索引数据
    buffer->ibuffer.resize(indexCount);
    short *indices = &buffer->ibuffer[0];

    short row = 0, row_n = 0;

    for (int i = 0; i < rings; ++i)
    {
        row_n = row + segments + 1;

        for (int j = 0; j < segments; ++j)
        {
            *indices++ = row + j;
            *indices++ = row + j + 1;
            *indices++ = row_n + j;

            *indices++ = row_n + j;
            *indices++ = row + j + 1;
            *indices++ = row_n + j + 1;
        }

        row += segments + 1;
    }

    buffer->primCount = indexCount / 3;
    buffer->primType = PT_TriangleList;
}

class TestShader : public Shader
{
public:
    virtual void VertexShader(RasterizerVertex *v_out, const Vertex *v_in)
    {
        v_out->normal = v_in->normal;
        v_out->color = v_in->color;
        v_out->texcoord = v_in->texcoord;
        v_out->position = v_in->position;

        v_out->position = m_worldMatrix * v_out->position;
        v_out->position = m_viewMatrix * v_out->position;
        v_out->position = m_projMatrix * v_out->position;
    }

    virtual bool FragmentShader(RasterizerVertex *v_io)
    {
        if (m_texture != NULL)
        {
            vec4 tex_color;
            m_texture->Sample2D(v_io->texcoord.x, v_io->texcoord.y, m_state, tex_color);
            v_io->color *= tex_color;
        }

        return true;
    }
};

class TestApp : public App
{
public:
    TestApp()
    {

    }

    virtual ~TestApp()
    {

    }

    virtual void OnInit(int w, int h)
    {
        m_render = new SoftwareRender(m_hwnd, w, h);
        m_texture = new Texture;
        m_renderBuffer = new RenderBuffer;
        m_camera = new Camera;

        ResourceManager::Instance()->AddPath("../Media");
        //createBox(m_renderBuffer, 1, 1, 1);
        createSphere(m_renderBuffer, 1, 30, 30);
        //m_texture->LoadTexture("../Media/X1.png");
    }

    virtual void OnUpdate()
    {
        //重置状态
        m_render->Begin();

        //清空buffer
        m_render->Clear();

        m_worldMatrix = rotate(M_PI * m_time * 0.3f , vec3(0.f, 1.f, 0.f));

        m_camera->SetPerspective(M_PI / 3, m_width / (float)m_height, 0.1f, 1000.f);
        m_camera->Look(vec3(0, 3, -3), vec3(0, 0, 0), vec3(0, 1, 0));

        //设置采样
        SamplerState state;
        state.m_filter = NEAREST;
        state.m_wrapMode = WRAP;
        m_shader.SetSampleState(state);
        m_shader.SetWorldMatrix(m_worldMatrix);
        m_shader.SetViewMatrix(m_camera->m_viewMatrix);
        m_shader.SetProjMatrix(m_camera->m_projectMatrix);
        m_shader.SetTexture(m_texture);

        //设置渲染状态
        SoftwareRenderState rState;
        rState.SetCullFaceType(CFT_BACK);
        rState.SetBlendType(BT_Opacity);
        rState.SetDepthTestType(DTT_LessEqual);
        rState.EnableDepthMask(true);
        m_render->SetRenderState(rState);

        m_render->SetShader(&m_shader);

        m_render->Render(m_renderBuffer);

        m_render->End();

        m_render->Present();
    }


    virtual void OnStop() override
    {
        delete m_camera;
        delete m_texture;
        delete m_render;
        delete m_renderBuffer;
    }


    virtual void OnResize(int w, int h) override
    {
        m_render->Resize(w, h);
    }

private:
    SoftwareRender *m_render{ NULL };
    Texture *m_texture{ NULL };
    RenderBuffer *m_renderBuffer{ NULL };
    Camera *m_camera{ NULL };
    TestShader m_shader;

    mat4x4 m_worldMatrix;
    mat4x4 m_viewMatrix;
    mat4x4 m_projMatrix;
};

App *gApp = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (NULL == gApp)
    {
        return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }

    switch (uiMsg)
    {
    case WM_CREATE:
        break;
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
        {
            RECT rc;
            GetClientRect(hWnd, &rc);

            int w = rc.right - rc.left;
            int h = rc.bottom - rc.top;

            gApp->Resize(w, h);
        }
        break;
    case WM_LBUTTONDBLCLK:
        gApp->OnMouseDown(0);
        break;
    case WM_LBUTTONUP:
        gApp->OnKeyUp(0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

static const WCHAR * WIN32_CLASS_NAME = L"Myway3D";
const int S_WIDTH = 666, S_HEIGHT = 400;
INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // 创建窗口
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor = NULL;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = WIN32_CLASS_NAME;
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);

    DWORD style = WS_OVERLAPPEDWINDOW;//WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX;
    RECT rc = { 0, 0, S_WIDTH, S_HEIGHT };

    AdjustWindowRect(&rc, style, FALSE);

    int width = rc.right - rc.left;
    int	height = rc.bottom - rc.top;
    int xpos = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int ypos = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    HWND hWnd = CreateWindow(WIN32_CLASS_NAME, L"SoftRender", style,
        xpos, ypos, width, height,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    GetClientRect(hWnd, &rc);
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;

    // 创建离屏DC
    BYTE * pBackBuffer = NULL;
    HDC hdc = GetDC(hWnd);
    HDC hOffscreenDC = CreateCompatibleDC(hdc);

    gApp = new TestApp();
    gApp->Init(hWnd, width, height);

    /*
    if (AllocConsole())
    {
        freopen("CONOUT$", "w", stdout);
        printf("hello, world!");
    }*/

    //循环
    MSG msg;
    memset(&msg, 0, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            gApp->Update();
        }
    }

    gApp->Stop();
    delete gApp;

    UnregisterClass(WIN32_CLASS_NAME, hInstance);

    return 0;
}