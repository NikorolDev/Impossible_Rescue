#include "Particle.h"

CParticle::CParticle()
{

}

CParticle::~CParticle()
{

}

void CParticle::VUpdate( float fDeltaTime )
{
	if( m_bIsActive )
	{
		setPositionX( ( getPosition().x + m_v2Direction.x ) * m_iSpeed * fDeltaTime );
		setPositionY( ( getPosition().y + m_v2Direction.y ) * m_iSpeed * fDeltaTime );
	}
}

void CParticle::SetParticleProperties( cocos2d::Vec2 v2SpawnPos, float pcSize, cocos2d::Color3B pcColor, int iSpeed, cocos2d::Vec2 v2Direction )
{
	setPosition( v2SpawnPos );
	setScale( pcSize );
	setColor( pcColor );
	m_v2Direction = v2Direction;
}
