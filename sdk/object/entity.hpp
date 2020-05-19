#pragma once

#include "csgo/engine/net_prop_system.hpp"


class C_BaseEntity : public IClientEntity
{
public:
	NET_PROP( int, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum" );

	NET_PROP( float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime" );

	NET_PROP( Vector, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin" );

	NET_PROP( QAngle, m_angRotation, "DT_BaseEntity", "m_angRotation" );

public:
	NET_PROP_EX( const matrix3x4_t, m_rgflCoordinateFrame, "DT_BaseEntity", "m_CollisionGroup", -0x0030 );
};
