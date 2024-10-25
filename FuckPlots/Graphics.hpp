#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__

/**
* @note очень сильно урезанная часть граф. движка
*/
namespace core {
    namespace Graphics {

        class GraphicsEngine {
            Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice;
            Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext;
            Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
            Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;

            void createTargetView();
            inline void destroyTargetView() noexcept { m_pRenderTargetView.Reset(); };

        public:
            GraphicsEngine() = default;
            ~GraphicsEngine();

            void render();
            void init(const Window& window);

            inline void resizeWindow(UINT width, UINT height) noexcept {
                destroyTargetView();
                /*D3D11_VIEWPORT vp{};
                vp.Width = static_cast<float>(width);
                vp.Height = static_cast<float>(height);
                vp.MaxDepth = 1.0f;
                m_pDeviceContext->RSSetViewports(1, &vp);*/
                m_pSwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
                createTargetView();
            }

            boost::signals2::signal<void(ID3D11Device*, ID3D11DeviceContext*)> onInitDevice;
            //boost::signals2::signal<void(ID3D11Device*, ID3D11DeviceContext*)> onLostTargetView;
            boost::signals2::signal<void(ID3D11Device*, ID3D11DeviceContext*)> onRender;
        };

    }
}

#endif