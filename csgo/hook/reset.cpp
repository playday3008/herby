#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

namespace csgo::hook
{

HRESULT API_D3D Reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters )
{
	static auto result = m_direct_device_hook->Get<decltype(&Reset)>(16);

	auto& renderer = engine::Renderer::Instance();

	renderer.Lost();

	auto hr = result(device, presentation_parameters);

	renderer.Reset(hr);

	return hr;
}

}