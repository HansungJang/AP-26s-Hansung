#pragma once

const int MAX_HEALTH = 100;
const int MAX_OXYGEN = 100; // test for 100, initial 5; 
const int INIT_LIVES = 3;

class Player
{
	private:
		int health;
		int oxygen;
		// int lives; 
		int initialLightCount;
		int lightcount; 
		int positionX;
		int positionY;
		int lighPositionX;
		int lightPositionY;
		bool isAlive; // player state alive or dead

	public:
		Player(int hp, int oxy, int live, int lightcount, int x=-1, int y=-1);
		
		
		void oxyzenCalculator(int oxy = -1); // calculate oxygen level
		void healthCalculator(int hp); // calculate health level (time based)
		void takeDamage(int damage); // calculate player health when attacked
		void useItem(int point, char type); // use Item 
		void playerStateChange(); // check player state; isAlive & health & oxygen
		void playerReset();

		// setter / getter functions: health, oxygen, lives, positionX, positionY, isAlive	
		int getHealth();
		int getOxygen();
        int getLightCount();  
 		int getPositionX();
		int getPositionY();
 		int getLightPositionX();
		int getLightPositionY();
		bool getIsAlive();
		
		void setLightCount(int light);
		void setPositionX(int x);
		void setPositionY(int y);
		void setLightPositionX(int x);
		void setLightPositionY(int y); 

	};