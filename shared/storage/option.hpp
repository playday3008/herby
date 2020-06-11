#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include "shared/imgui/imgui.hpp"

namespace shared::option
{
	struct VisualData
	{
		bool dormant;

		struct {
			bool e_money;
			bool e_armour;
			bool e_zoom;
			bool e_flashed;
			bool e_reloading;
			bool e_bomb;

			bool f_money;
			bool f_armour;
			bool f_zoom;
			bool f_flashed;
			bool f_reloading;
			bool f_bomb;

		} flags;

		struct {
			bool friendly;
			bool enemy;

			ImColor f_box_clr = ImColor(250, 200, 0);
			ImColor e_box_clr = ImColor(150, 200, 60);
		} boxes;

		struct {
			bool friendly;
			bool enemy;

			ImColor name_clr;
		} name;

		struct {
			bool friendly;
			bool enemy;
			bool ammo;

			ImColor ammo_clr = ImColor(180, 10, 40);
		} weapon;

		struct {
			bool friendly;
			bool enemy;
		} health;
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