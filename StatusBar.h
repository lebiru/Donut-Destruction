#ifndef STATUSBAR_H
#define STATUSBAR_H

class StatusBar
{

private:
	
	double time;
	int health, score;

public:

	void initializeStatusBar();

	double getTime()
	{ return time;}

	int getHealth()
	{ return health;}

	int getScore()
	{ return score;}

	void startTime();
	void resetTime();
	void decrementHealth();
	void resetHealth();
	bool isDead();


};

#endif //STATUSBAR_H