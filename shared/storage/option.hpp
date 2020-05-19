#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include "shared/imgui/imgui.hpp"

namespace shared::option
{
	struct VisualData
	{
		bool m_enabled = false;
		bool m_box = false;
		bool m_corner = false;
		bool m_health = false;

		///Colors
		ImColor box_color = ImColor();
		ImColor name_color = ImColor();
	};

	struct MiscData
	{
		bool m_auto_pistol = false;
	};

	extern VisualData m_visual;
	extern MiscData m_misc;

	bool Create();
	void Destroy();

	void Load(const std::string& name);
	void Save(const std::string& name);
	void Delete(const std::string& name);
}