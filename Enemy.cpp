#include "Enemy.h"

void Enemy::setX (float a)
{
	x = a;
}

void Enemy::setY (float a)
{
	y = a;
}

void Enemy::setIndex (int a)
{
	index = a;
}

void Enemy::setSpeed (float a)
{
	speed = a;
}

void Enemy::setDropGuyX (float a)
{
	
	dgx = a;
	
}

void Enemy::setDropGuyY (float a)
{

	dgy = a;

}

void Enemy::setDropGuyIndex(int a)
{

	dgindex = a;

}

void Enemy::setDropGuySpeed(float a)
{

	dgspeed = a;

}

void Enemy::setDropGuyIsSafe(bool a)
{
	dropGuyIsSafe = a;
}

void Enemy::setGoingRight(bool a)
{
	goingRight = a;
}

void Enemy::setExplosionIndex(int a)
{
	explosionIndex = a;
}