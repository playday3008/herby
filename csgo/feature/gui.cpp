#include "csgo/feature/gui.hpp"
#include "csgo/engine.hpp"

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}
}

namespace csgo::feature
{

bool Gui::Create()
{
	auto& input = win32::Input::Instance();

	if( !input.AddEvent( &Gui::MessageProcedure ) )
		return false;

	auto& style = ImGui::GetStyle();

	ImGui::StyleColorsDark();

	style.WindowPadding = { 8.f, 8.f };
	style.WindowRounding = 0.f;
	style.WindowBorderSize = 0.f;
	style.ChildRounding = 0.f;
	style.ChildBorderSize = 1.f;
	style.PopupRounding = 0.f;
	style.PopupBorderSize = 0.f;
	style.FramePadding = { 4.f, 2.f };
	style.FrameRounding = 0.f;
	style.FrameBorderSize = 0.f;
	style.IndentSpacing = 20.f;
	style.ScrollbarSize = 14.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 10.f;
	style.GrabRounding = 0.f;

	CreateTab("aimbot", false);
	CreateTab("triggerbot", false);
	CreateTab("esp", false);
	CreateTab("removal", false);
	CreateTab("misc", false);
	CreateTab("config", false);

	return true;
}

void Gui::Destroy()
{

}

auto get_extension(const std::string& data)
{
	auto dot = data.find_last_of('.');

	std::string extension = { };

	if (dot != std::string::npos)
		extension = data.substr(dot + 1u, data.size());

	return extension;
}

void Gui::Present()
{
	auto& system = win32::System::Instance();

	if( !system.Gui() )
		return;

	auto render_style = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

	auto frame_height = 0.f;

	D3DVIEWPORT9 viewport = { };
	if (SUCCEEDED(m_direct_device->GetViewport(&viewport)))
		frame_height = static_cast<float>(viewport.Height);

	auto frame_pos = ImVec2{ 0.f, 0.f };
	auto frame_size = ImVec2{ 156.f, frame_height };

	ImGui::SetNextWindowPos(frame_pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(frame_size, ImGuiCond_Always);

	auto frame_render_style = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

	if (ImGui::Begin("frame", nullptr, frame_render_style))
	{
		auto& gui_style = ImGui::GetStyle();

		auto tab_size = ImVec2{ 140.f, 30.f };
		auto tab_array_size = ((30.f * (static_cast<float>(m_tab_array.size()) + gui_style.ItemSpacing.y)) - gui_style.ItemSpacing.y) * 0.5f;

		auto frame_tab_center_y = frame_height * 0.5f;
		auto frame_tab_start_y = (frame_tab_center_y - tab_array_size) * 0.5f;

		ImGui::Dummy({ 0.f, frame_tab_start_y });
		ImGui::Dummy({ 0.f, 0.f });

		auto frame_name = "herby"s;
		auto frame_name_size = ImGui::CalcTextSize(frame_name.c_str(), nullptr, true);

		ImGui::SameLine(0.f, (frame_size.x * 0.5f) - (frame_name_size.x * 0.5f) - gui_style.ItemSpacing.x);
		ImGui::Text(frame_name.c_str());
		ImGui::Dummy({ 0.f, frame_tab_start_y });

		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.f, 0.5f });
		ImGui::PushStyleColor(ImGuiCol_Text, { 1.f, 1.f, 1.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.1f, 0.1f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.12f, 0.12f, 0.12f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.15f, 0.15f, 0.15f, 1.f });

		for (auto& tab : m_tab_array)
		{
			if (ImGui::Button(tab.m_name.c_str(), tab_size))
				tab.m_render = !tab.m_render;
		}

		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar(1);
	}
	ImGui::End();

	if (m_tab_array.at(tab_esp).m_render)
	{
		if (ImGui::Begin("esp", nullptr, render_style))
		{
			auto& style = ImGui::GetStyle();
			auto& esp = option::m_visual;

			ImGui::Dummy({ 140.f, 0.f });
			ImGui::PushItemWidth(160.f);
			if (ImGui::CollapsingHeader("core"))
			{
				ImGui::Checkbox("enabled", &esp.m_enabled);
				ImGui::Checkbox("box", &esp.m_box);
			}
			ImGui::PopItemWidth();
		}
		ImGui::End();
	}

	if (m_tab_array.at(tab_misc).m_render)
	{
		if (ImGui::Begin("misc", nullptr, render_style))
		{
			auto& misc = option::m_misc;


			ImGui::Dummy({ 140.f, 0.f });

			ImGui::PushItemWidth(160.f);
			if (ImGui::CollapsingHeader("core"))
			{
				ImGui::Checkbox("auto pistol", &misc.m_auto_pistol);
			}
			ImGui::PopItemWidth();
		}
	}
}

void Gui::CreateTab(const std::string& name, bool selected /*= false*/)
{
	auto index = static_cast<int>(m_tab_array.size());
	m_tab_array.emplace_back(selected, index, name);
}

bool Gui::MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	auto& system = win32::System::Instance();

	switch( message )
	{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if( wparam == VK_INSERT )
			{
				system.Gui( !system.Gui() );
				return true;
			}

			break;
		}
	}

	if( system.Gui() )
	{
		if( ImGui_ImplWin32_WndProcHandler( window, message, wparam, lparam ) )
			return true;
	}

	return false;
}

}