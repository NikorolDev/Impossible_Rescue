#include "BoxCollider.h"

CBoxCollider::CBoxCollider()
{
	m_pcCollider = cocos2d::Rect();
	m_pcColliderOutline = nullptr;
}

void CBoxCollider::Initialise( float fWidth, float fHeight, cocos2d::Vec2 v2Position, std::string cTag, bool bShowCollider )
{
	m_pcCollider.setRect(v2Position.x, v2Position.y, fWidth, fHeight);

	m_cTag = cTag;

	if( bShowCollider )
	{
		m_pcColliderOutline = cocos2d::Sprite::create( "Collider.png" );
		m_pcColliderOutline->setPosition( v2Position );
		m_pcColliderOutline->setContentSize( cocos2d::Size( fWidth, fHeight ) );
	}
}

CBoxCollider::~CBoxCollider()
{
	//CC_SAFE_DELETE( m_pcCollider );
}

std::string CBoxCollider::GetTag()
{
	return m_cTag;
}

void CBoxCollider::SetTag( std::string cTag )
{
	m_cTag = cTag;
}

cocos2d::Sprite* CBoxCollider::GetColliderSprite()
{
	return m_pcColliderOutline;
}

cocos2d::Rect CBoxCollider::GetRect()
{
	return m_pcCollider;
}


