#include "main.hpp"

namespace core {
    Window::Window(HINSTANCE hInstance, const str& windowName, const str& className, int width, int height, int cmdShow, 
        LRESULT(*wnd_proc)(HWND, UINT, WPARAM, LPARAM))
        : m_nCmdShow(cmdShow), m_szClassName(className), m_hInstance(hInstance) {
        WNDCLASSEX wc{};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
        wc.hInstance = hInstance;
        wc.lpfnWndProc = wnd_proc;
        wc.lpszClassName = className.data();
        wc.style = CS_VREDRAW | CS_HREDRAW;

        if (!RegisterClassEx(&wc))
            throw std::exception("RegisterClassEx return pizdec");

        m_hWnd = CreateWindow(wc.lpszClassName, windowName.data(), WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, wc.hInstance, nullptr);
        if (m_hWnd == INVALID_HANDLE_VALUE)
            throw std::exception("hWnd == trash");
    }

    Window::~Window()
    {
        UnregisterClass(m_szClassName.data(), m_hInstance);
    }

    int Window::run() const {
        ShowWindow(m_hWnd, m_nCmdShow);
        UpdateWindow(m_hWnd);

        MSG msg{};
        while (GetMessage(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return static_cast<int>(msg.wParam);
    }
}