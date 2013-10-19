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

void StatusBar::resetHealth()
{
	health = 5;
}

void StatusBar::resetScore()
{
	score = 0;
}

int StatusBar::getTime()
{
	return agk::GetRunTime() - startTime;
}

void StatusBar::setHealth(int a)
{
	health += a;
}



bool StatusBar::isDead()
{
	(health <= 0) ? true : false;
}

void StatusBar::setScore(int a)
{
	score += a;
}

