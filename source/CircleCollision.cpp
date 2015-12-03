#include "CircleCollision.h"
#include "CollisionManager.h"

#include <iostream>

CircleCollision::CircleCollision(float radius_,PixelPosition* pos_)
	:pos(pos_)
	,radius(radius_)
{
	CollisionManager::GetInstance().RegisterCollisionbody(this);
}

CircleCollision::~CircleCollision()
{
	CollisionManager::GetInstance().UnregisterCollisionbody(this);
		
}

bool CircleCollision::colliding(ICollision* Collidingbody)
{
	CircleCollision* other = static_cast<CircleCollision*> (Collidingbody);
	std::cout << "called" << std::endl;
	return true;
}