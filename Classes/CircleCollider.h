#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "cocos2d.h"
#include "SpriteObject.h"

class CCircleCollider : CSpriteObject
{
private:
	
public:
	CCircleCollider();
	CCircleCollider(float fRadius, cocos2d::Vec2 v2Position);

	~CCircleCollider();
};

#endif //!CIRCLE_COLLIDER_H