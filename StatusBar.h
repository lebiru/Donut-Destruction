#ifndef STATUSBAR_H
#define STATUSBAR_H

class StatusBar
{

private:
	
	double startTime, health, score;

public:

	void initializeStatusBar();

	int getTime();

	int getHealth()
	{ return health;}

	int getScore()
	{ return score;}

	//void updateTime();
	void resetTime();
	void decrementHealth();
	void resetHealth();
	bool isDead();
	void setScore(int a);


};

#endif //STATUSBAR_H