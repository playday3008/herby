#include "csgo/hook/procedure.hpp"
#include "csgo/engine.hpp"

namespace csgo::hook
{
	auto m_send_packet = false;

	VOID API_WIN32 create_move_call(int sequence_number, float input_sample_frametime, bool active)
	{
		m_create_move_hook->Restore();
		m_create_move_hook->Win32Call< VOID >(sequence_number, input_sample_frametime, active);
		m_create_move_hook->Replace();

		auto& prediction = engine::Prediction::Instance();

		if (prediction.Begin(&m_send_packet))
		{

		}
		prediction.End();
	}

	__declspec(naked) VOID API_FASTCALL CreateMove(int sequence_number, float input_sample_frametime, bool active)
	{
		__asm
		{
			mov m_send_packet, bl
			push ebp
			mov ebp, esp
			sub esp, 8
			pushad
			push active
			push input_sample_frametime
			push sequence_number
			call create_move_call
		}
		create_move_call(sequence_number, input_sample_frametime, active);
		__asm
		{
			popad
			mov bl, m_send_packet
			mov esp, ebp
			pop ebp
			retn 0x0C
		}
	}
}