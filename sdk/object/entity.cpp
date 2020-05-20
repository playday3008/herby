#include "entity.hpp"
#include "csgo/engine.hpp"

C_AnimationLayer& C_BaseAnimatingOverlay::GetAnimOverlay(int i)
{
	static auto field = csgo::engine::NetPropSystem::Instance().Get(this->GetPredDescMap(), "m_AnimOverlay");
	return (*reinterpret_cast<C_AnimationLayer**>(reinterpret_cast<int>(this) + 0x2980))[i];
}

Activity C_BaseAnimatingOverlay::GetSequenceActivity(int sequence)
{
	model_t* mdl = this->GetModel();
	if (mdl)
	{
		studiohdr_t* hdr = csgo::m_model_info->GetStudioModel(mdl);
		if (hdr)
		{
			static int offset = memory::scan<int>(L"client_panorama.dll","55 8B EC 53 8B 5D 08 56 8B F1 83");
			static auto get_sequence_activity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(offset);
			return static_cast<Activity>(get_sequence_activity(this, hdr, sequence));
		}
	}
	return Activity::ACT_RESET;
}

