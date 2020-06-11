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

		if (!input.AddEvent(&Gui::MessageProcedure))
			return false;

		auto& style = ImGui::GetStyle();

		ImGui::StyleColorsDark();

		style.ScrollbarSize = 13.0f;
		style.WindowTitleAlign = { 0.5f, 0.5f };

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
		io.Fonts->Flags |= ImFontAtlasFlags_NoPowerOfTwoHeight;

		return true;
	}

	void Gui::Destroy()
	{

	}

	void Gui::Present()
	{
		auto& system = win32::System::Instance();

		if (!system.Gui())
			return;

		ImGui::Begin("herby", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse);

		if (!ImGui::BeginTabBar("##tabbar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_NoTooltip)) {
			ImGui::End();
			return;
		}

		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 350.0f);

		ImGui::TextUnformatted("Build date: " __DATE__ " " __TIME__);
		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 55.0f);

		if (ImGui::BeginTabItem("ESP"))
		{
			auto& esp = option::m_visual;

			ImGui::PushItemWidth(160.f);
			if (ImGui::CollapsingHeader("box"))
			{
				ImGui::Checkbox("enemy", &esp.boxes.enemy);
				ImGui::SameLine();
				ImGui::ColorEdit3("enemy clr", &esp.boxes.e_box_clr.Value.x);
				ImGui::Checkbox("friendly", &esp.boxes.friendly);
				ImGui::SameLine();
				ImGui::ColorEdit3("friendly clr", &esp.boxes.f_box_clr.Value.x);
			}
			ImGui::PopItemWidth();
		}
		ImGui::EndTabItem();

		if (ImGui::BeginTabItem("Misc"))
		{
			auto& misc = option::m_misc;

			ImGui::PushItemWidth(160.f);
			if (ImGui::CollapsingHeader("core"))
			{
				ImGui::Checkbox("auto pistol", &misc.m_auto_pistol);
			}
			ImGui::PopItemWidth();
		}
		ImGui::EndTabItem();
		ImGui::EndTabBar();
		ImGui::End();
	}

	bool Gui::MessageProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
	{
		auto& system = win32::System::Instance();

		switch (message)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if (wparam == VK_INSERT)
			{
				system.Gui(!system.Gui());
				return true;
			}

			break;
		}
		}

		if (system.Gui())
		{
			if (ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam))
				return true;
		}

		return false;
	}

}