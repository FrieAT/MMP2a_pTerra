#include "CircleCollision.h"
#include "CollisionManager.h"

#include <iostream>

CircleCollision::CircleCollision(float radius_,IPosition* pos_)
	:pos(pos_)
	,radius(radius_)
{
	CollisionManager::GetInstance().RegisterCollisionbody(this);
	FrameManager::GetInstance().RegisterEventObserver(this);
}

CircleCollision::~CircleCollision()
{
	CollisionManager::GetInstance().UnregisterCollisionbody(this);
	FrameManager::GetInstance().UnregisterEventObserver(this);

}

bool CircleCollision::colliding(ICollision* Collidingbody)
{
	CircleCollision* other = static_cast<CircleCollision*> (Collidingbody);

	sf::Vector2f lenght_vec = other->pos->GetPosition() - pos->GetPosition();
	
	float lenght = lenght_vec.x*lenght_vec.x + lenght_vec.y*lenght_vec.y;
	float dis = radius + other->radius;
	dis = dis*dis;

	if (lenght < dis)
	{
		restitution = lenght_vec;
		hit = true;
		return true;
	}
	else
	{
		hit = false;
		return false;
	}
}

void CircleCollision::OnFrameDraw(sf::RenderWindow * pWindow)
{
	sf::CircleShape test(radius);
	if(hit) test.setFillColor(sf::Color::Magenta);
	else test.setFillColor(sf::Color::Blue);
	test.setPosition(pos->GetPosition()- sf::Vector2f(radius, radius));
	
	// pWindow->draw(test);

}
