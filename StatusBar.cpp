#include "StatusBar.h"
#include "template.h"



void StatusBar::initializeStatusBar()
{

	startTime = 0;
	health = 5; //Donut hit points
	score = 0; //Player score
}


void StatusBar::resetTime()
{
	startTime = agk::GetRunTime();
}

int StatusBar::getTime()
{
	return agk::GetRunTime() - startTime;
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

void StatusBar::setScore(int a)
{

	score = a;
}

