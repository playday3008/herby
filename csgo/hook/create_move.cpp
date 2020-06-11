#include "csgo/hook/procedure.hpp"
#include "csgo/engine.hpp"
namespace csgo::hook
{
	auto m_send_packet = false;

	std::uintptr_t m_create_move = 0u;
	std::uintptr_t m_create_move_ret = 0u;

	VOID create_move_call(int sequence_number, float input_sample_frametime, bool active)
	{

		auto cmd = m_input->GetUserCmd(sequence_number);
		auto verified = m_input->GetVerifiedUserCmd(sequence_number);

		if (!cmd || !cmd->command_number || !verified)
			return;

		verified->m_cmd = *cmd;
		verified->m_crc = cmd->GetChecksum();
	}

	VOID API_FASTCALL CreateMove(int sequence_number, float input_sample_frametime, bool active)
	{
		m_create_move = m_base_client_hook->Get< std::uintptr_t >(22);

		__asm
		{
			push eax
			mov eax, [esp + 4]
			mov m_create_move_ret, eax
			pop eax
			add esp, 4
			call m_create_move
			mov m_send_packet, bl
			pushad
		}

		create_move_call(sequence_number, input_sample_frametime, active);

		__asm
		{
			popad
			mov bl, m_send_packet
			jmp m_create_move_ret
		}
	}
}