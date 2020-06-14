#include "csgo/engine.hpp"

#include "csgo/engine/factory.hpp"
#include "csgo/engine/net_prop_system.hpp"

namespace csgo
{

IBaseClientDLL* m_base_client = nullptr;
IClientEntityList* m_client_entity_list = nullptr;
IVEngineClient* m_engine_client = nullptr;
IVModelInfo* m_model_info = nullptr;
IVDebugOverlay* m_debug_overlay = nullptr;

CInput* m_input = nullptr;
CGlobalVarsBase* m_globals = nullptr;

IDirect3DDevice9* m_direct_device = nullptr;

memory::ObjectHook::Shared m_direct_device_hook = { };
memory::ObjectHook::Shared m_base_client_hook = { };

bool Create()
{
	auto& input = win32::Input::Instance();
	auto& system = win32::System::Instance();

	auto& gui = feature::Gui::Instance();

	auto& renderer = engine::Renderer::Instance();
	auto& net_prop_system = engine::NetPropSystem::Instance();

	engine::Factory factory_client( "client.dll" );
	engine::Factory factory_engine( "engine.dll" );

	if( !input.Create() )
		return false;
	
	if( !system.Create() )
		return false;

	m_base_client = factory_client.Get< IBaseClientDLL* >( "VClient" );

	if( !m_base_client )
		return false;

	m_client_entity_list = factory_client.Get< IClientEntityList* >( "VClientEntityList" );

	if( !m_client_entity_list )
		return false;

	m_engine_client = factory_engine.Get< IVEngineClient* >( "VEngineClient" );

	if( !m_engine_client )
		return false;

	m_model_info = factory_engine.Get< IVModelInfo* >("VModelInfoClient");

	if (!m_model_info)
		return false;

	m_debug_overlay = factory_engine.Get< IVDebugOverlay* >("VDebugOverlay");

	if (!m_debug_overlay)
		return false;

	m_input = memory::scan< CInput* >(L"client.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10", 1, 1u);

	if (!m_input)
		return false;

	m_globals = memory::scan< CGlobalVarsBase* >( L"client.dll", "A1 ? ? ? ? 0F 57 ED", 1, 2 );

	if( !m_globals )
		return false;

	m_direct_device = memory::scan< IDirect3DDevice9* >( L"shaderapidx9.dll", "B9 ? ? ? ? 8B 47", 1, 2 );

	if( !m_direct_device )
		return false;

	if( !renderer.Create( m_direct_device ) )
		return false;

	if( !net_prop_system.Create() )
		return false;

	if( !gui.Create() )
		return false;

	m_direct_device_hook = std::make_shared< memory::ObjectHook >(m_direct_device);
	m_base_client_hook = std::make_shared< memory::ObjectHook >(m_base_client);

	m_direct_device_hook->Hook(&hook::Reset,16);
	m_direct_device_hook->Hook(&hook::Present, 17);

	m_base_client_hook->Hook(&hook::CreateMove, 22);

	return true;
}

void Destroy()
{
	auto& input = win32::Input::Instance();
	auto& system = win32::System::Instance();

	auto& gui = feature::Gui::Instance();

	auto& renderer = engine::Renderer::Instance();
	auto& net_prop_system = engine::NetPropSystem::Instance();
	
	input.Destroy();
	system.Destroy();
	
	gui.Destroy();

	renderer.Destroy();
	net_prop_system.Destroy();

	m_direct_device_hook->Destroy();
	m_base_client_hook->Destroy();
}

}