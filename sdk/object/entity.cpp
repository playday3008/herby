#include "entity.hpp"
#include "csgo/engine.hpp"

C_BaseEntity* C_BaseEntity::GetBaseEntity(int index)
{
	auto client_entity = csgo::m_client_entity_list->GetClientEntity(index);
	return (client_entity ? client_entity->GetBaseEntity() : nullptr);
}

int C_BaseEntity::GetMoveType()
{
	auto& netvar = csgo::engine::NetPropSystem::Instance();
	return netvar.GetDataMap(this->GetPredDescMap(), "m_MoveType");
}

C_AnimationLayer& C_BaseAnimatingOverlay::GetAnimOverlay(int i)
{
	static auto field = csgo::engine::NetPropSystem::Instance().GetDataMap(this->GetPredDescMap(), "m_AnimOverlay");
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

C_CSPlayer* C_CSPlayer::GetCSPlayer(int index)
{
	auto base_entity = C_BaseEntity::GetBaseEntity(index);
	return ToCSPlayer(base_entity);
}
C_CSPlayer* C_CSPlayer::GetLocalPlayer()
{
	auto index = csgo::m_engine_client->GetLocalPlayer();
	return GetCSPlayer(index);
}

C_World* C_World::GetWorld()
{
	return reinterpret_cast<C_World*>(C_BaseEntity::GetBaseEntity(0));
}

