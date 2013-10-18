#ifndef DONUT_H
#define DONUT_H

class Donut
{

private:
	float x, y, speed, angle, angle_dx;
	int index;

public:

	float getX()
	{return x;}

	float getY()
	{return y;}

	int getIndex()
	{return index;}

	float getSpeed()
	{return speed;}

	void setX(float a);
	void setY(float a);
	void setIndex(int a);
	void setSpeed(float a);
	void turnLeft();


};

#endif //DONUT_H