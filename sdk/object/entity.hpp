#pragma once

#include "csgo/engine/net_prop_system.hpp"


class C_BaseEntity : public IClientEntity
{
public:
	datamap_t* GetPredDescMap()
	{
		return memory::Call<17, datamap_t*>(this);
	}
public:
	NET_PROP( int, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum" );
	NET_PROP( float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime" );
	NET_PROP( Vector, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin" );
	NET_PROP( QAngle, m_angRotation, "DT_BaseEntity", "m_angRotation" );
public:
	NET_PROP_EX( const matrix3x4_t, m_rgflCoordinateFrame, "DT_BaseEntity", "m_CollisionGroup", -0x0030 );
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
private:
	char  pad_0038[4]; //0x0034
}; //Size: 0x0038

class C_BaseAnimatingOverlay : public C_BaseAnimating
{
public:
	C_AnimationLayer& GetAnimOverlay(int i);
	Activity GetSequenceActivity(int sequence);
};

