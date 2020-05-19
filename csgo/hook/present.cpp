#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

namespace csgo::hook
{
HRESULT API_D3D Present( IDirect3DDevice9* device, const RECT* source_rect, const RECT* dest_rect, HWND dest_window_override, const RGNDATA* dirty_region )
{
	static auto result = m_direct_device_hook->Get<decltype(&Present)>(17);
	auto& renderer = engine::Renderer::Instance();
	auto& gui = feature::Gui::Instance();
	auto& esp = feature::Esp::Instance();

	if( renderer.Begin() )
	{
		esp.Present();
		renderer.DrawText( { 20.f, 10.f }, engine::TextLeft, { 1.f, 1.f, 1.f }, "overlay" );	
		renderer.End();
	}
	gui.Present();
	renderer.Present();

	return result(device, source_rect, dest_rect,dest_window_override,dirty_region);
}

}