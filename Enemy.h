#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{

private:
	float x, y, speed;
	float dgx, dgy, dgspeed; //dropguy variables
	int index, dgindex, explosionIndex; //dgindex is DropGuy Index
	bool goingRight; //determines if enemy is going right or left across screen

public:

	float getX()
	{return x;}

	float getY()
	{return y;}

	int getIndex()
	{return index;}

	float getSpeed()
	{return speed;}

	float getdgX()
	{return dgx;}

	float getdgY()
	{return dgy;}

	int getDropGuyIndex()
	{return dgindex;}

	float getdgspeed()
	{return dgspeed;}

	bool getGoingRight()
	{ return goingRight;}

	int getExplosionIndex()
	{ return explosionIndex;}


	void setX(float a);
	void setY(float a);
	void setIndex(int a);
	void setSpeed(float a);

	void setDropGuyX(float a);
	void setDropGuyY(float a);
	void setDropGuyIndex(int a);
	void setDropGuySpeed(float a);

	void setGoingRight(bool a);

	void setExplosionIndex(int a);





};

#endif //ENEMY_H