#pragma once

#pragma warning(push)
#pragma warning(disable: 4005)

#include <string_view>
#include <functional>
#include <exception>
#include <memory>
#include <map>

#include <Windows.h>
#include <wrl/client.h>

#include <d3d11.h>
#include <D3DX11.h>
#include <D3Dcompiler.h>
#include <directxmath/DirectXMath.h>
#include <directxmath/DirectXColors.h>

#include <boost/signals2.hpp>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <implot.h>

#include <luajit/lua.hpp>
#include <sol/sol.hpp>

#pragma warning(pop)

#include "Window.hpp"
#include "Graphics.hpp"
#include "Coords.hpp"
#include "Sampling.hpp"

