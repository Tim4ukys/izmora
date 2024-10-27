#include "main.hpp"

std::unique_ptr<core::Window> g_Window;
std::unique_ptr<core::Graphics::GraphicsEngine> g_pGE;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return 1;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        if (g_pGE) g_pGE->resizeWindow(LOWORD(lParam), HIWORD(lParam));
        return 0;
    case WM_ERASEBKGND:
        return 0;
    case WM_PAINT:
        g_pGE->render();
        return 0;
    case WM_DESTROY:
        PostQuitMessage(EXIT_SUCCESS);
        return 0;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    g_Window = std::make_unique<core::Window>(hInst, L"IzMora", L"iz_mora", 512, 512, cmdshow, wndProc);
    g_pGE = std::make_unique<core::Graphics::GraphicsEngine>();

    Sampling sampl{"example.lua"};
    auto render = [&sampl](ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext) {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();

        namespace im = ImGui;
        im::NewFrame();

        im::SetNextWindowPos(ImVec2(0.0, 0.0));
        im::SetNextWindowSize(im::GetIO().DisplaySize);
        if (im::Begin("##fuck_izmora", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground)) {
            sampl.draw();
            im::End();
        }

        im::EndFrame();
        im::Render();
        ImGui_ImplDX11_RenderDrawData(im::GetDrawData());
        };
    auto initDevice = [](ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImPlot::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        //ImGui::StyleColorsDark();
        
        io.FontGlobalScale = 0.75f;
        ImGui::StyleColorsLight();
        ImGui_ImplWin32_Init(g_Window->getHWND());
        ImGui_ImplDX11_Init(pDevice, pDeviceContext);
        io.Fonts->AddFontFromFileTTF("test.ttf", 18.f*2, nullptr, io.Fonts->GetGlyphRangesCyrillic());
        };
    auto destroyDevice = [](ID3D11Device*, ID3D11DeviceContext*) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        };
    g_pGE->onInitDevice.connect(initDevice);
    g_pGE->onRender.connect(render);
    g_pGE->init(*g_Window.get());
    auto&& exit_code = g_Window->run();
    destroyDevice(0, 0);
    g_pGE.reset();
    g_Window.reset();
    return exit_code;
}
