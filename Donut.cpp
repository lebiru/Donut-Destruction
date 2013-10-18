#include "Donut.h"

void Donut::setX (float a)
{
	x = a;
}

void Donut::setY (float a)
{
	y = a;
}

void Donut::setIndex (int a)
{
	index = a;
}

void Donut::setSpeed (float a)
{
	speed = a;
}

void Donut::turnLeft ( )
{
	angle -= angle_dx;
}