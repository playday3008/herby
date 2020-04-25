#include "csgo/engine/prediction.hpp"

namespace csgo::engine
{
	bool Prediction::Begin(bool* send_packet)
	{
		m_send_packet = send_packet;

		m_player = C_CSPlayer::GetLocalCSPlayer();

		if (!m_player)
			return false;

		if (m_player->m_lifeState() != 0)
			return false;

		m_weapon = reinterpret_cast<C_WeaponCSBase*>(m_player->GetActiveWeapon());

		if (!m_weapon)
			return false;
	}

	void Prediction::End()
	{

	}

	C_CSPlayer* Prediction::GetPlayer() const
	{
		return m_player;
	}

	C_WeaponCSBase* Prediction::GetWeapon() const
	{
		return m_weapon;
	}
}