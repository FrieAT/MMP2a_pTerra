#include "CircleCollision.h"
#include "CollisionManager.h"

CircleCollision::CircleCollision(float radius,PixelPosition pos)
{
	CollisionManager::GetInstance().RegisterCollisionbody(this);
	this->radius = radius;
	this->pos = pos;
}

CircleCollision::~CircleCollision()
{
	CollisionManager::GetInstance().UnregisterCollisionbody(this);
}

bool CircleCollision::colliding(ICollision* Collidingbody)
{
	CircleCollision* other = static_cast<CircleCollision*> (Collidingbody);

}