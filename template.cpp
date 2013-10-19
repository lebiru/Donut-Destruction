// Includes, namespace and prototypes
#include "template.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Donut.h"
#include "StatusBar.h"
#include <math.h>
#include <iostream>

using namespace std;
using namespace AGK;

app App;

//GAME LOGIC CONSTANTS
int gState = 1; //We start the game in the TITLE SCREEN
const int TITLE_STATE = 1;
const int GAME_STATE = 2;
const int OVER_STATE = 3;
const int ABOUT_STATE = 4;
const int HOW_STATE = 5;
const float gravity = 9.81;
int score = 0;

float d_blt_yspd = -110.0;


//SYSTEM PROPERTIES
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 720;

//SPRITES
const int TITLE_SCREEN = 1;
const int GAME_SCREEN = 2;
const int GAMEOVER_SCREEN = 3;
const int ABOUT_SCREEN = 4;
const int DONUT_SPRITE = 5;
const int DONUT_HEALTH_SPRITE = 99;
const int HOW_SCREEN = 7;
const int DONUT_START = 30; //30 - 33 donut bullets
const int ENEMY_START = 105; //105 - 110


const int dgStart = 125; //111 - 116
int EXPLOSION_START = 130; // # of explosion sprites = num of enemies * # of explosions for each sprite


//IMAGES
int TITLE_IMAGE = 1;
int GAME_IMAGE = 2;
int GAMEOVER_IMAGE = 3;
int ABOUT_IMAGE = 4;
int DONUT_IMAGE = 5;
int DONUT_HEALTH_IMAGE = 200;
int HOW_IMAGE = 7;
int EXPLOSION_IMAGE = 80; //6 - 10 for explosions
int BULLET_IMAGE = 30; //30 - 33 donut bullets
int ENEMY_IMAGE = 40; //105 - 110
int dgIMAGE = 50; //111 - 116

//bullets
const int DONUT_MAX = 3;
Bullet donutBlt[DONUT_MAX];

const int ENEMY_MAX = 10; 
Enemy enemy[ENEMY_MAX];

int dgSpeed = 10;


// MUSIC & SOUND EFFECTS
const int bgMusic = 1;
const int coin = 2;
const int explosion = 3;
const int explosion2 = 4;
const int hit = 5;
const int hit2 = 6;
const int jump = 7;
const int shoot = 8;
const int shoot2 = 9; 

//TEXT INDEXES
const int CLOCK_INDEX = 1;
const int SCORE_INDEX = 2;
const int HEALTH_INDEX = 3;

// GAME VARIABLES
bool gameOver = false;
int numOfDropGuys = 0;

int donutAngle = 0; //The rotation of the Donut Turret
const float donutAngle_dx = 5; //How fast the Donut Turret rotates.



//Function Declarations
void titleToHow();
void howToGame();
void gameToOver();
void overToTitle();
void overToGame();
void titleToAbout();
void aboutToTitle();

StatusBar statusBar;

void manageEnemies(Enemy enemy[], int size, int start);

void handlePlayerMovement();
void testCode();

void initializeBullets(Bullet b[], int size, int start);
void initializeEnemies(Enemy enemy[], int size, int start, int dgstart, int dropguySpeed, int EXPLOSION_START);
void initializeHealth(int DONUT_HEALTH_SPRITE, int DONUT_HEALTH_IMAGE);

void moveBulletPlayer(Bullet b[], int size, float gravity);
int moveEnemy(Enemy enemy[], int size, int numOfDropGuys);

void clearEnemies(Enemy b[], int size);

float projectileRange(float velocity, float angle, double gravity);
float projectileHeight(float velocity, float angle, double gravity);
float toRadians(float degrees);


float xPosition(float velocity, float angle);
float yPosition(float velocity, float angle, float gravity);

void bulletIsOOB(Bullet b[], int size); //turns off bullets that have gone out of bounds.
void objectIsOOB(int spriteIndex); //turns off sprites that have gone out of bounds.
int bulletCollisionEnemy(Bullet b[], int bulletListSize, Enemy enemy[], int enemyListSize, int score, int EXPLOSION_IMAGE);


// Begin app, called once at the start
void app::Begin( void )
{
	agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	


	//LOAD IMAGES
	agk::LoadImage(TITLE_IMAGE, "images/titlescreen.png");
	agk::LoadImage(HOW_IMAGE, "images/howtoplay.png");
	agk::LoadImage(GAME_IMAGE, "images/maingame.png");
	agk::LoadImage(GAMEOVER_IMAGE, "images/gameover.png");
	agk::LoadImage(ABOUT_IMAGE, "images/about.png");
	agk::LoadImage(DONUT_IMAGE, "images/donut.png");
	agk::LoadImage(EXPLOSION_IMAGE, "images/particle.png");
	agk::LoadImage(BULLET_IMAGE, "images/bullet.png");
	agk::LoadImage(ENEMY_IMAGE, "images/enemy.png");
	agk::LoadImage(dgIMAGE, "images/dropguy.png");
	agk::LoadImage(DONUT_HEALTH_IMAGE, "images/health.png");
	
	
	//LOAD SOUNDS
	agk::LoadMusic(bgMusic, "sounds/Ambition.mp3");
	agk::LoadSound(shoot, "sounds/shoot.wav");
	agk::LoadSound(shoot2, "sounds/shoot2.wav");
	agk::LoadSound(coin, "sounds/coin.wav");
	agk::LoadSound(explosion, "sounds/explosion.wav");
	agk::LoadSound(explosion2, "sounds/explosion2.wav");
	agk::LoadSound(hit, "sounds/hit.wav");
	agk::LoadSound(hit2, "sounds/hit2.wav");
	agk::LoadSound(jump, "sounds/jump.wav");

	//LOAD TEXT
	agk::CreateText(CLOCK_INDEX, "");
	agk::CreateText(SCORE_INDEX, "");
	agk::CreateText(HEALTH_INDEX, "");
	
	
	//Initialize the Title Screen
	agk::CreateSprite(TITLE_SCREEN, TITLE_IMAGE);
	agk::SetSpritePosition(TITLE_IMAGE, 0, 0);
	agk::SetSpriteSize(TITLE_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);


	//Initialize Bullets
	initializeBullets(donutBlt, DONUT_MAX, DONUT_START);
	initializeEnemies(enemy, ENEMY_MAX, ENEMY_START, dgStart, dgSpeed, EXPLOSION_START); 
    

	agk::PlayMusic(bgMusic);
	agk::SetMusicSystemVolume(50);

	statusBar.initializeStatusBar();


	agk::SetTextPosition(CLOCK_INDEX, 80, 4);
	agk::SetTextColor(CLOCK_INDEX, 0, 0, 0, 255);
	agk::SetTextSize(CLOCK_INDEX, 30);

	agk::SetTextPosition(SCORE_INDEX, 120, 32);
	agk::SetTextColor(SCORE_INDEX, 0, 0, 0, 255);
	agk::SetTextSize(SCORE_INDEX, 30);

	agk::SetTextPosition(HEALTH_INDEX, 120, 60);
	agk::SetTextColor(HEALTH_INDEX, 0, 0, 0, 255);
	agk::SetTextSize(HEALTH_INDEX, 30);


	

	

	
}

// Main loop, called every frame
void app::Loop ( void )
{
	

	//agk::Print("donut index: " + donutHealthIndex);

	//Title Screen
	if(gState == TITLE_STATE)
	{

		//transition to next state
		if(agk::GetRawKeyPressed(AGK_KEY_SPACE))
		{
			gState = HOW_STATE;
			titleToHow(); //go from Title Screen to How to Play Screen

		}

		if(agk::GetRawKeyPressed(AGK_KEY_LEFT))
		{

			gState = ABOUT_STATE;
			titleToAbout();
		}
		
	}

	//ABOUT SCREEN
	if(gState == ABOUT_STATE)
	{

		if(agk::GetRawKeyPressed(AGK_KEY_RIGHT))
		{

			gState = TITLE_STATE;
			aboutToTitle();
		}
	}

	//HOW TO PLAY SCREEN
	if(gState == HOW_STATE)
	{

		if(agk::GetRawKeyPressed(AGK_KEY_RIGHT))
		{
			gState = GAME_STATE;
			howToGame();
		
		}


	}
	
	//Game Screen
	/*
	Game screen should only be entered into through the Title Screen. Game screen 
	should exit to the Game Over screen upon ending.
	*/
	if(gState == GAME_STATE)
	{

		
		agk::SetTextString(CLOCK_INDEX, agk::Str(statusBar.getTime()));
		agk::SetTextString(HEALTH_INDEX, agk::Str(statusBar.getHealth()));
		
		
		if(gameOver == false)
		{
			
           // agk::Print(numOfDropGuys);
			

			//update model
			
			manageEnemies(enemy, ENEMY_MAX, ENEMY_START);

			//move
			handlePlayerMovement();
			moveBulletPlayer(donutBlt, DONUT_MAX, gravity);
			numOfDropGuys = moveEnemy(enemy, ENEMY_START, numOfDropGuys);

			//collision
			bulletIsOOB(donutBlt, DONUT_MAX);
			statusBar.setScore(bulletCollisionEnemy(donutBlt, DONUT_MAX, enemy, ENEMY_MAX, score, EXPLOSION_IMAGE));
			agk::SetTextString(SCORE_INDEX, agk::Str(statusBar.getScore()));
			
			
			if(numOfDropGuys >= 5)
			{
				gameOver = true;
			}





		}

		//if gameOver is true
		else
		{

			

			gState = OVER_STATE;
			agk::DeleteSprite(DONUT_SPRITE);
			clearEnemies(enemy, ENEMY_MAX);
			gameToOver(); //transition to game Over screen


		}



	}


	//Game Over Screen
	if(gState == OVER_STATE)
	{

		

		//play again?
		if(agk::GetRawKeyState(AGK_KEY_UP))
		{
		
			gState = TITLE_STATE;
			gameOver = false;
			numOfDropGuys = 0;
			initializeEnemies(enemy, ENEMY_MAX, ENEMY_START, dgStart, dgSpeed, EXPLOSION_START);
			overToTitle();
		
		}

		if(agk::GetRawKeyState(AGK_KEY_DOWN))
		{
			gState = GAME_STATE;
			gameOver = false;
			numOfDropGuys = 0;
			
			overToGame();
		}



	}

	//collisions handle


	//move scene



	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{

}


////FUNCTION DEFINITIONS/////////////////////

void handlePlayerMovement()
{

		
	if(agk::GetRawKeyState(AGK_KEY_LEFT))
	{
	
		donutAngle -= donutAngle_dx;
		agk::SetSpriteAngle(DONUT_SPRITE, donutAngle);	
	
	}

	if(agk::GetRawKeyState(AGK_KEY_RIGHT))
	{
		donutAngle += donutAngle_dx;
		agk::SetSpriteAngle(DONUT_SPRITE, donutAngle);
	}

	if(agk::GetRawKeyPressed(AGK_KEY_SPACE))
	{

		int i = 0;
		for(i; i < DONUT_MAX; i++) //for all the bullets
		{

			if(donutBlt[i].getAlive() == false) //if we've found a dead slot
			{
				donutBlt[i].turnOn();
				donutBlt[i].setX(agk::GetSpriteX(DONUT_SPRITE));
				donutBlt[i].setY(agk::GetSpriteY(DONUT_SPRITE) + 100); //100 offset for closer to the "cannon"
				donutBlt[i].setAngle(agk::GetSpriteAngle(DONUT_SPRITE));
				donutBlt[i].setYVelocity(d_blt_yspd);
				agk::CreateSprite(donutBlt[i].getIndex(), BULLET_IMAGE);
				agk::SetSpriteColor(donutBlt[i].getIndex(), agk::Random(0, 255), agk::Random(0, 255), agk::Random(0, 255), 255);
				agk::SetSpritePosition(donutBlt[i].getIndex(), (donutBlt[i].getX() + (agk::GetSpriteWidth(DONUT_SPRITE)/ 2) - 5), donutBlt[i].getY()); 

				//play shoot sound
				int ran = agk::Random(0,1);
				(ran%2 == 0) ? agk::PlaySound(shoot) : agk::PlaySound(shoot2);
				

				return;
			}	

		}
		
	}


}

//Test to see if a piece of code is being accessed
void testCode()
{
	
	//Debug info
	agk::SetPrintColor(0,0,0);

	//Press "t" to test if code is being accessed.
	if(agk::GetRawKeyState(84))
	{
		agk::Print("Code is being accessed");
	}
}

void titleToGame()
{

		//Clean up Title
		agk::DeleteSprite(TITLE_SCREEN);
		agk::DeleteSprite(GAMEOVER_SCREEN);

		//Restart game clock
		statusBar.resetTime();
		statusBar.resetScore();
		statusBar.resetHealth();

		//Set up Game Screen
		agk::CreateSprite(GAME_SCREEN, GAME_IMAGE);
		agk::SetSpritePosition(GAME_SCREEN, 0,0);
		agk::SetSpriteSize(GAME_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);

		//Set up Game Screen
		agk::CreateSprite(DONUT_SPRITE, DONUT_IMAGE);
		agk::SetSpritePosition(DONUT_SPRITE, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - (agk::GetSpriteHeight(DONUT_SPRITE)));

		//Set up health icons
		//agk::CreateSprite(DONUT_HEALTH_SPRITE, DONUT_HEALTH_IMAGE);
		//agk::SetSpritePosition(DONUT_HEALTH_SPRITE, 40, 80);

}

void titleToAbout()
{
	
	agk::DeleteSprite(TITLE_SCREEN);
	agk::CreateSprite(ABOUT_SCREEN, ABOUT_IMAGE);
	agk::SetSpritePosition(ABOUT_SCREEN, 0,0);
	agk::SetSpriteSize(ABOUT_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);
	
}

void aboutToTitle()
{
	
	agk::DeleteSprite(ABOUT_SCREEN);
	agk::CreateSprite(TITLE_SCREEN, TITLE_IMAGE);
	agk::SetSpritePosition(TITLE_SCREEN, 0,0);
	agk::SetSpriteSize(TITLE_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);
	
}


void gameToOver()
{

	//Clean up game
	agk::DeleteSprite(GAME_SCREEN);
	agk::DeleteSprite(TITLE_SCREEN);

	agk::SetTextString(HEALTH_INDEX, "");
	

	//Set up Game Screen
	agk::CreateSprite(GAMEOVER_SCREEN, GAMEOVER_IMAGE);
	agk::SetSpritePosition(GAMEOVER_SCREEN, 0,0);
	agk::SetSpriteSize(GAMEOVER_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);
	
}

void overToTitle()
{
	//Clean up Title
	agk::DeleteSprite(GAMEOVER_SCREEN);

	//Clean up statusBar
	agk::SetTextString(SCORE_INDEX, "");
	agk::SetTextString(CLOCK_INDEX, "");
	
	//Set up Game Screen
	agk::CreateSprite(TITLE_SCREEN, TITLE_IMAGE);
	agk::SetSpritePosition(TITLE_SCREEN, 0,0);
	agk::SetSpriteSize(TITLE_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void overToGame()
{

	//Clean up Title
	agk::DeleteSprite(GAMEOVER_SCREEN);


	//Reset game timer
	statusBar.resetTime();
	statusBar.resetScore();
	statusBar.resetHealth();

	//Set up Game Screen
	agk::CreateSprite(GAME_SCREEN, GAME_IMAGE);
	agk::SetSpritePosition(GAME_SCREEN, 0,0);
	agk::SetSpriteSize(GAME_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Set up Donut
	agk::CreateSprite(DONUT_SPRITE, DONUT_IMAGE);
	agk::SetSpritePosition(DONUT_SPRITE, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - (agk::GetSpriteHeight(DONUT_SPRITE)));

	//Set up Health icons
	initializeHealth(DONUT_HEALTH_SPRITE, DONUT_HEALTH_IMAGE);

}



/*
This function is responsible for maintaining the right number 
of enemies on screen. If there are too few enemies, it instantiates 
another enemy. If there are too many enemies, it does not create 
another enemy.

Should be called every few seconds.
*/
void manageEnemies(Enemy enemy[], int size, int start)
{

	int i = 0;

	int dropGuyChance = agk::Random(1, 1000);

	for(i; i < size; i++)
	{

		

		//for a dead enemy
		if(!agk::GetSpriteExists(enemy[i].getIndex()) && dropGuyChance < 20) 
		{
			
			agk::CreateSprite(enemy[i].getIndex(), ENEMY_IMAGE);
			agk::SetSpriteAnimation(enemy[i].getIndex(), 195, 146, 2);
			agk::PlaySprite(enemy[i].getIndex(), agk::Random(2, 10), 1, 1, 2);
			agk::SetSpriteColor(enemy[i].getIndex(), agk::Random(150, 255), agk::Random(200, 255), agk::Random(200, 255), 255);

			//determines the start location of the enemy if it's going left or right
			if(enemy[i].getGoingRight() == true)
			{
				agk::SetSpritePosition(enemy[i].getIndex(), 0 - agk::GetSpriteWidth(enemy[i].getIndex()), agk::Random(50, 150));
			}
			else
			{
				agk::SetSpritePosition(enemy[i].getIndex(), SCREEN_WIDTH + agk::GetSpriteWidth(enemy[i].getIndex()), agk::Random(50, 150));
			}
			

			enemy[i].setSpeed(agk::Random(5, 15));
			

			if(dropGuyChance <= 5) {enemy[i].setSpeed(50);}
		}	

	    //for an alive enemy who does not have a drop guy, 20% chance
		if(agk::GetSpriteExists(enemy[i].getIndex())
			&& !agk::GetSpriteExists(enemy[i].getDropGuyIndex())
			&& dropGuyChance > 980
			&& (agk::GetSpriteX(enemy[i].getIndex()) > 100 && (agk::GetSpriteX(enemy[i].getIndex()) < SCREEN_WIDTH - 100))
		   )	
			{
				agk::CreateSprite(enemy[i].getDropGuyIndex(), dgIMAGE);
				agk::SetSpriteColor(enemy[i].getDropGuyIndex(), agk::Random(150, 255), agk::Random(100, 200), agk::Random(100, 200), 255);
				agk::SetSpritePosition(enemy[i].getDropGuyIndex(), agk::GetSpriteX(enemy[i].getIndex()), enemy[i].getY() + 100);

				agk::PlaySound(jump);
			}	

		//for an enemy that went off screen
		if(agk::GetSpriteExists(enemy[i].getIndex()))
		{
			if(enemy[i].getGoingRight() == true && agk::GetSpriteX(enemy[i].getIndex()) >= SCREEN_WIDTH) 
			{ agk::DeleteSprite(enemy[i].getIndex());}
			else if(enemy[i].getGoingRight() == false && agk::GetSpriteX(enemy[i].getIndex()) <= 0)
			{ agk::DeleteSprite(enemy[i].getIndex());}

		}

		dropGuyChance = agk::Random(1, 1000);
	}

}

void initializeBullets(Bullet b[], int size, int start)
{
	int i = 0;
	for(i; i < size; i++)
	{
		b[i].setAlive(false);
		b[i].setIndex(start + i); //global sprite index of the bullet, must be unique
		b[i].setX(0);
		b[i].setY(0);
		b[i].setPlayerX(0);
		b[i].setPlayerY(0);
		b[i].setAngle(0);
		b[i].setBulletSpeed(10);
		b[i].setBulletYSpeed(-110.0);
	}

}

void moveBulletPlayer(Bullet b[], int size, float gravity)
{

	int i = 0;
	for(i; i < size; i++) //for all the bullets
	{
		if(b[i].getAlive() == true && agk::GetSpriteExists(b[i].getIndex())) //for an alive bullet
		{
			agk::SetSpritePosition(b[i].getIndex(), 
								   agk::GetSpriteX(b[i].getIndex()) + (xPosition(b[i].getBulletSpeed(), b[i].getAngle())),
								   agk::GetSpriteY(b[i].getIndex()) + yPosition(b[i].getYVelocity(), b[i].getAngle(), gravity)); 
								   b[i].setYVelocity(yPosition(b[i].getYVelocity(), b[i].getAngle(), gravity)); //update the new YVelocity due to the effects of gravity
		
		}	
	}


}

float xPosition( float velocity, float angle)
{
	return ( (float)sin(toRadians(angle)) * velocity * velocity);
}

float yPosition(float velocity, float angle, float gravity)
{
	velocity = velocity + gravity;
	return velocity;
}

float toRadians(float degrees)
{
	float radians = degrees * (3.1415 / 180);
	return radians;
	
}

void bulletIsOOB(Bullet b[], int size)
{
	int i = 0;
	for(i; i < size; i++) //for all the bullets
	{
		//if alive, exists, and is out of bounds
		if(
			b[i].getAlive() == true 
			&& agk::GetSpriteExists(b[i].getIndex()) 
			&& ( agk::GetSpriteInBox(b[i].getIndex(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) == 0 )
		  )
		{
			b[i].setAlive(false);
			agk::DeleteSprite(b[i].getIndex());

			
		}	

		
	}
	
}

int bulletCollisionEnemy(Bullet b[], int bulletListSize, Enemy enemy[], int enemyListSize, int score, int EXPLOSION_IMAGE)
{
	int i = 0;

	

	for(i; i < bulletListSize; i++) //for all the bullets
	{

		//if enemy is alive, exists, and is out of bounds
		int j = 0;
		for(j; j < enemyListSize; j++)
		{
			//check if collided with enemy
			if( agk::GetSpriteExists(b[i].getIndex())
				&& agk::GetSpriteExists(enemy[j].getIndex())
				&& agk::GetSpriteCollision(b[i].getIndex(), enemy[j].getIndex()))
			{
				b[i].setAlive(false);

				//Explosion particles
				agk::CreateParticles(enemy[j].getExplosionIndex(), 
					agk::GetSpriteX(enemy[j].getIndex()) + (agk::GetSpriteWidth(enemy[j].getExplosionIndex())/2), 
					agk::GetSpriteY(enemy[j].getIndex()) + (agk::GetSpriteHeight(enemy[j].getExplosionIndex())/2));
				agk::SetParticlesImage(enemy[j].getExplosionIndex(), EXPLOSION_IMAGE);
				agk::SetParticlesPosition(enemy[j].getIndex(), 
					agk::GetSpriteX(enemy[j].getIndex()) + (agk::GetSpriteWidth(enemy[j].getExplosionIndex())/2),
					agk::GetSpriteY(enemy[j].getIndex()) + (agk::GetSpriteHeight(enemy[j].getExplosionIndex())/2));

				agk::SetParticlesSize(enemy[j].getExplosionIndex(), 50);
				agk::SetParticlesDirection(enemy[j].getExplosionIndex(), 0, 200);
				agk::SetParticlesAngle(enemy[j].getExplosionIndex(), agk::Random(1,359));
				agk::SetParticlesLife(enemy[j].getExplosionIndex(), 3);
				agk::SetParticlesMax(enemy[j].getExplosionIndex(), 10);
				

				
				agk::DeleteSprite(b[i].getIndex());
				agk::DeleteSprite(enemy[j].getIndex());

				agk::PlaySound(explosion);



				
				
				score += 100;
			}	

			//check if collided with dropguy
			if( agk::GetSpriteExists(b[i].getIndex())
				&& agk::GetSpriteExists(enemy[j].getDropGuyIndex())
				&& agk::GetSpriteCollision(b[i].getIndex(), enemy[j].getDropGuyIndex())
				&& enemy[j].getDropGuyIsSafe() == false)
			{
				b[i].setAlive(false);
				agk::DeleteSprite(b[i].getIndex());
				agk::DeleteSprite(enemy[j].getDropGuyIndex());

				agk::PlaySound(explosion2);

				score += 50;
			}	


		}


	}

	return score;

}

void initializeEnemies(Enemy enemy[], int size, int start, int dgstart, int dropguySpeed, int EXPLOSION_START)
{
	int i = 0;
	for(i; i < size; i++)
	{
		enemy[i].setIndex(start + i); //global sprite index of the enemy, must be unique
		enemy[i].setX(0);
		enemy[i].setY(0);
		enemy[i].setSpeed(0);

		(i%2 == 0) ? enemy[i].setGoingRight(true) : enemy[i].setGoingRight(false);

		//dropguy stuff
		enemy[i].setDropGuyIndex(dgstart + i);
		enemy[i].setDropGuyX(0);
		enemy[i].setDropGuyY(0);
		enemy[i].setDropGuySpeed(dropguySpeed);
		enemy[i].setDropGuyIsSafe(false);

		enemy[i].setExplosionIndex(EXPLOSION_START + i);


	

	}

}

int moveEnemy(Enemy enemy[], int size, int numOfDropGuys)
{

	numOfDropGuys = 0;

	int i = 0;
	for(i; i < size; i++) //for all the enemies
	{
		if(agk::GetSpriteExists(enemy[i].getIndex())) //for an existing enemy
		{
			if(enemy[i].getGoingRight() == true)
			{
			agk::SetSpritePosition
				( 
				enemy[i].getIndex(), 
				agk::GetSpriteX(enemy[i].getIndex()) + enemy[i].getSpeed(),
				agk::GetSpriteY(enemy[i].getIndex())
				);
			}

			else
			{
				agk::SetSpritePosition
				( 
				enemy[i].getIndex(), 
				agk::GetSpriteX(enemy[i].getIndex()) - enemy[i].getSpeed(),
				agk::GetSpriteY(enemy[i].getIndex())
				);
			}


		}	

		if(agk::GetSpriteExists(enemy[i].getDropGuyIndex())) //for an existing dropguy
		{
			//agk::Print( agk::GetSpriteX(enemy[i].getDropGuyIndex()));
			

			//if the dropguy has not reached the bottom of the screen.
			if(  (agk::GetSpriteY(enemy[i].getDropGuyIndex()) + agk::GetSpriteHeight(enemy[i].getDropGuyIndex())) <= SCREEN_HEIGHT )
			{ 
				agk::SetSpritePosition
				( 
					enemy[i].getDropGuyIndex(), 
					agk::GetSpriteX(enemy[i].getDropGuyIndex()),
					agk::GetSpriteY(enemy[i].getDropGuyIndex()) + enemy[i].getSpeed()
				);
			}

			//if the dropguy has reached the bottom of the screen
			else
			{
				numOfDropGuys++;

				if(enemy[i].getDropGuyIsSafe() == false)
				{
					enemy[i].setDropGuyIsSafe(true);
					statusBar.setHealth(-1);
				}
		
			}

		

		}	

	}

	return numOfDropGuys;

}

void clearEnemies(Enemy b[], int size)
{

	int i = 0;

	for(i; i < size; i++)
	{
		if(agk::GetSpriteExists(b[i].getIndex()))
		{
			agk::DeleteSprite(b[i].getIndex());
		}

		if(agk::GetSpriteExists(b[i].getDropGuyIndex()))
		{
			agk::DeleteSprite(b[i].getDropGuyIndex());
		}
		

	}

}

//Initializes the health icon
void initializeHealth(int DONUT_HEALTH_INDEX, int DONUT_HEALTH_IMAGE)
{
	
	agk::CreateSprite(DONUT_HEALTH_SPRITE, DONUT_HEALTH_IMAGE);
	agk::SetSpritePosition(DONUT_HEALTH_SPRITE, 70,60);
	

}

void titleToHow()
{
	
		agk::DeleteSprite(TITLE_SCREEN);	
		

		agk::CreateSprite(HOW_SCREEN, HOW_IMAGE);
		agk::SetSpritePosition(HOW_SCREEN, 0,0);
		agk::SetSpriteSize(HOW_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void howToGame()
{

		agk::DeleteSprite(HOW_SCREEN);	

		//Restart game clock
		statusBar.resetTime();
		statusBar.resetScore();
		statusBar.resetHealth();

		//Set up Game Screen
		agk::CreateSprite(GAME_SCREEN, GAME_IMAGE);
		agk::SetSpritePosition(GAME_SCREEN, 0,0);
		agk::SetSpriteSize(GAME_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);

		//Set up Donut Player
		agk::CreateSprite(DONUT_SPRITE, DONUT_IMAGE);
		agk::SetSpritePosition(DONUT_SPRITE, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - (agk::GetSpriteHeight(DONUT_SPRITE)));

		//initialize health icon
		initializeHealth(DONUT_HEALTH_SPRITE, DONUT_HEALTH_IMAGE);


}