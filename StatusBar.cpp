#include "StatusBar.h"
#include "template.h"



void StatusBar::initializeStatusBar()
{

	double time = 0;
	int health = 5; //Donut hit points
	int score = 0; //Player score
}

void StatusBar::startTime()
{
	time = agk::GetRunTime();
}

void StatusBar::resetTime()
{
	time = 0;
}

void StatusBar::decrementHealth()
{
	health--;
}

void StatusBar::resetHealth()
{
	health = 5;
}

bool StatusBar::isDead()
{
	(health <= 0) ? true : false;
}


