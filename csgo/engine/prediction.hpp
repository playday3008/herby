#pragma once
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::engine
{

	class Prediction : public detail::Singleton< Prediction >
	{
	public:
		bool Begin(bool* send_packet);
		void End();

		C_CSPlayer* GetPlayer() const;
		C_WeaponCSBase* GetWeapon() const;

	private:
		bool* m_send_packet = nullptr;
		C_CSPlayer* m_player = nullptr;
		C_WeaponCSBase* m_weapon = nullptr;
	};
}