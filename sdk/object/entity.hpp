#pragma once

#include "csgo/engine/net_prop_system.hpp"


class C_BaseEntity : public IClientEntity
{
public:
	datamap_t* GetPredDescMap()
	{
		return memory::Call<17, datamap_t*>(this);
	}

	bool IsPlayer()
	{
		return memory::Call<156, bool>(this);
	}
public:
	static C_BaseEntity* GetBaseEntity(int index);
public:
	NET_PROP( int, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum" );
	NET_PROP( float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime" );
	NET_PROP( Vector, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin" );
	NET_PROP( QAngle, m_angRotation, "DT_BaseEntity", "m_angRotation" );
public:
	NET_PROP_EX( const matrix3x4_t, m_rgflCoordinateFrame, "DT_BaseEntity", "m_CollisionGroup", -0x0030 );
public:
	int GetMoveType();
};


class C_BaseAnimating : public C_BaseEntity
{
public:
	NET_PROP(int, m_nHitboxSet, "DT_BaseAnimating", "m_nHitboxSet");
	NET_PROP(int, m_nSequence, "DT_BaseAnimating", "m_nSequence");
	NET_PROP(float, m_flCycle, "DT_BaseAnimating", "m_flCycle");
};

class C_AnimationLayer
{
public:
	char  pad_0000[20];
	uint32_t m_nOrder;					//0x0014
	uint32_t m_nSequence;				//0x0018
	float m_flPrevCycle;				//0x001C
	float m_flWeight;					//0x0020
	float m_flWeightDeltaRate;			//0x0024
	float m_flPlaybackRate;				//0x0028
	float m_flCycle;					//0x002C
	C_BaseAnimating* m_pOwner;			//0x0030
	char  pad_0038[4]; //0x0034
}; //Size: 0x0038

class C_BaseAnimatingOverlay : public C_BaseAnimating
{
public:
	C_AnimationLayer& GetAnimOverlay(int i);
	Activity GetSequenceActivity(int sequence);
};

class C_BaseFlex : public C_BaseAnimatingOverlay
{
public:
	NET_PROP(bool, m_blinktoggle, "DT_BaseFlex", "m_blinktoggle");
	NET_PROP(Vector, m_viewtarget, "DT_BaseFlex", "m_viewtarget");
};

class C_BaseCombatCharacter : public C_BaseFlex
{
public:
	NET_PROP(CBaseHandle, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	NET_PROP(float, m_flNextAttack, "DT_BaseCombatCharacter", "m_flNextAttack");
};

class C_BasePlayer : public C_BaseCombatCharacter
{
public:
	NET_PROP(char, m_lifeState, "DT_BasePlayer", "m_lifeState");
	NET_PROP(int, m_fFlags, "DT_BasePlayer", "m_fFlags");
	NET_PROP(int, m_iHealth, "DT_BasePlayer", "m_iHealth");
	NET_PROP(int, m_nTickBase, "DT_BasePlayer", "m_nTickBase");
	NET_PROP(Vector, m_vecVelocity, "DT_BasePlayer", "m_vecVelocity[0]");
	NET_PROP(Vector, m_vecViewOffset, "DT_BasePlayer", "m_vecViewOffset[0]");
	NET_PROP(QAngle, m_aimPunchAngle, "DT_BasePlayer", "m_aimPunchAngle");
	NET_PROP(QAngle, m_viewPunchAngle, "DT_BasePlayer", "m_viewPunchAngle");
	NET_PROP_EX(QAngle, v_angle, "DT_BasePlayer", "deadflag", 0x04);
};

class C_CSPlayer : public C_BasePlayer
{
public:
	static C_CSPlayer* GetCSPlayer(int index);
	static C_CSPlayer* GetLocalPlayer();
public:
	NET_PROP(bool, m_bIsDefusing, "DT_CSPlayer", "m_bIsDefusing");
	NET_PROP(bool, m_bHasHelmet, "DT_CSPlayer", "m_bHasHelmet");
	NET_PROP(bool, m_bHasHeavyArmor, "DT_CSPlayer", "m_bHasHeavyArmor");
	NET_PROP(int, m_ArmorValue, "DT_CSPlayer", "m_ArmorValue");
	NET_PROP(int, m_iShotsFired, "DT_CSPlayer", "m_iShotsFired");
	NET_PROP(float, m_flFlashMaxAlpha, "DT_CSPlayer", "m_flFlashMaxAlpha");
	NET_PROP(float, m_flLowerBodyYawTarget, "DT_CSPlayer", "m_flLowerBodyYawTarget");
	NET_PROP(QAngle, m_angEyeAngles, "DT_CSPlayer", "m_angEyeAngles[0]");
};

class C_World : public C_BaseEntity
{
public:
	static C_World* GetWorld();
public:
	NET_PROP(bool, m_flWaveHeight, "DT_World", "m_flWaveHeight");
	NET_PROP(Vector, m_WorldMins, "DT_World", "m_WorldMins");
	NET_PROP(Vector, m_WorldMaxs, "DT_World", "m_WorldMaxs");
	NET_PROP(bool, m_bStartDark, "DT_World", "m_bStartDark");
	NET_PROP(char, m_iszDetailSpriteMaterial, "DT_World", "m_iszDetailSpriteMaterial");
};



inline C_BasePlayer* ToBasePlayer(C_BaseEntity* base_entity)
{
	if (!base_entity || !base_entity->IsPlayer())
		return nullptr;

	return reinterpret_cast<C_BasePlayer*>(base_entity);
}

inline C_CSPlayer* ToCSPlayer(C_BaseEntity* base_entity)
{
	return reinterpret_cast<C_CSPlayer*>(ToBasePlayer(base_entity));
}

	

