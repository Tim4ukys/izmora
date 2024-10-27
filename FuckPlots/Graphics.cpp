#include "main.hpp"

void core::Graphics::GraphicsEngine::init(const Window& window)
{
    auto [screenWidth, screenHeight] = window.getClientScreenSize();

#ifndef NDEBUG
    constexpr auto deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
    constexpr UINT deviceFlags = 0;
#endif
    DXGI_SWAP_CHAIN_DESC swapChainDesc{};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = screenWidth;
    swapChainDesc.BufferDesc.Height = screenHeight;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = window.getHWND();
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceFlags, NULL, NULL,
        D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext);
   
    onInitDevice(m_pDevice.Get(), m_pDeviceContext.Get());
}

void core::Graphics::GraphicsEngine::createTargetView()
{
    ID3D11Texture2D* pBackBuffer;
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&pBackBuffer);
    m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();
    m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL);
}

core::Graphics::GraphicsEngine::~GraphicsEngine()
{
    m_pDeviceContext->ClearState();
    m_pRenderTargetView.Reset();
    m_pSwapChain.Reset();
    m_pDevice.Reset();
}

void core::Graphics::GraphicsEngine::render()
{
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), DirectX::Colors::White);
    onRender(m_pDevice.Get(), m_pDeviceContext.Get());
    m_pSwapChain->Present(1, 0);
}
