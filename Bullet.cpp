#include "Bullet.h"

void Bullet::setX (float a)
{
	x = a;
}

void Bullet::setY (float a)
{
	y = a;
}

void Bullet::setPlayerX(float a)
{
	player_x = a;
}

void Bullet::setPlayerY(float a)
{
	player_y = a;
}

void Bullet::setAngle(float a)
{
	angle = a;
}

void Bullet::setYVelocity(float a)
{
	yVelocity = a;
}

void Bullet::setAlive (bool a)
{
	alive = a;
}
void Bullet::setIndex (int a)
{
	index = a;
}
void Bullet::setBulletSpeed(float a)
{
	bulletSpeed = a;
}

void Bullet::turnOn()
{
	alive = true;

}

void Bullet::setBulletYSpeed(float a)
{
	bulletYSpeed = a;
}