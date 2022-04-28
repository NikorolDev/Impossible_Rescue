#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include <cocos2d.h>

class CBoxCollider
{
private:
	std::string			m_cTag;
	cocos2d::Rect		m_pcCollider;
	cocos2d::Sprite*	m_pcColliderOutline;

public:
	CBoxCollider();
	void Initialise(float fWidth, float fHeight, cocos2d::Vec2 v2Position, std::string cTag, bool bShowCollider);

	~CBoxCollider();

	std::string GetTag();
	void SetTag( std::string cTag );

	cocos2d::Sprite* GetColliderSprite();

	cocos2d::Rect GetRect();

};

#endif //!BOX_COLLIDER_H