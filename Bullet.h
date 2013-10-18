#ifndef BULLET_H
#define BULLET_H

class Bullet
{

private:
	float x, y, player_x, player_y, angle, yVelocity, bulletSpeed, bulletYSpeed;
	bool alive;
	int index;

public:
	float getX()
	{return x;}

	float getY()
	{return y;}

	float getPlayerX()
	{return player_x;}

	float getPlayerY()
	{return player_y;}

	float getAngle()
	{return angle;}

	float getYVelocity()
	{return yVelocity;}

	int getIndex()
	{return index;}

	bool getAlive()
	{return alive;}

	float getBulletSpeed()
	{return bulletSpeed;}

	float getBulletYSpeed()
	{return bulletYSpeed;}

	void setX(float a);
	void setY(float a);
	void setPlayerX(float a);
	void setPlayerY(float a);
	void setAngle(float a);
	void setYVelocity(float a);
	void setIndex(int a);
	void setAlive(bool a);
	void setBulletSpeed(float a);
	void turnOn();
	void setBulletYSpeed(float a);

};

#endif //BULLET_H