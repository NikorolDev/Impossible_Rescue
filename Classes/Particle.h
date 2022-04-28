#ifndef PARTICLE_H
#define PARTICLE_H

#include "SpriteObject.h"

class CTextureManager;

class CParticle : public CSpriteObject
{
private:
	bool					m_bIsActive;
	int						m_iSpeed;
	cocos2d::Vec2			m_v2Direction;
		
public:
	CParticle();
	~CParticle();

	virtual void VUpdate(float fDeltaTime) override;

	void SetParticleProperties(cocos2d::Vec2 v2SpawnPos, float pcSize, cocos2d::Color3B pcColor, int iSpeed, cocos2d::Vec2 v2Direction);
};

#endif // PARTICLE_H