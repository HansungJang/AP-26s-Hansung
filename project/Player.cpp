
#include<iostream>
#include "Player.hpp"


		Player::Player(int hp, int oxy, int live, int lightcount, int x, int y) // constructor : initialize player data
		: health(hp), oxygen(oxy), initialLightCount(lightcount), lightcount(lightcount), positionX(x), positionY(y), lighPositionX(x), lightPositionY(y), isAlive(true){}
		

		void Player::oxyzenCalculator(int oxy) // calculate oxygen level
		{
			int nextOxygen = oxygen + oxy; 
			if(nextOxygen >= MAX_OXYGEN) 
			{
				nextOxygen = MAX_OXYGEN;
			}
			if(nextOxygen <= 0)
			{
				nextOxygen = 0; // reset oxygen to max after losing a life
			} 
				
			oxygen = nextOxygen; 
	
			playerStateChange(); 
			return; 
		}

		void Player::healthCalculator(int hp) // calculate health level (time based)
		{
			int nextHealth = health + hp;
			if(nextHealth >= MAX_HEALTH) nextHealth = MAX_HEALTH;
			if(nextHealth <= 0)
			{
				nextHealth = 0; // reset health to max after losing a life
			} 	

			health = nextHealth; 
			playerStateChange(); 
			return; 
		}
 

		void Player::takeDamage(int damage) // calculate player health when attacked
		{
			healthCalculator(-damage);
		}

		void Player::useItem(int point, char type)
		{
			if(type == 'l' || type == 'L') lightcount = point; 
			if(type == 'a' || type == 'A') oxygen = point; 
		}

		void Player::playerStateChange() // check player state; isAlive & health & oxygen
		{
			isAlive = !(health <= 0 || oxygen <= 0);
		}

		void Player::playerReset()
		{
			health = MAX_HEALTH; 
			oxygen = MAX_OXYGEN; 
			lightcount = initialLightCount;
			setPositionX(0); 
			setPositionY(0); 
			playerStateChange(); 
		}

		// setter / getter functions: health, oxygen, lives, positionX, positionY, isAlive	
		int Player::getHealth(){ return health; }
		int Player::getOxygen() {return oxygen; }
		int Player::getLightCount() {return lightcount;}
 		int Player::getPositionX() { return positionX; }
		int Player::getPositionY() { return positionY; }
 		int Player::getLightPositionX() { return lighPositionX; }
		int Player::getLightPositionY() { return lightPositionY; }
		bool Player::getIsAlive() { return isAlive; }
		
		void Player::setLightCount(int light) {lightcount = light;}
		void Player::setPositionX(int x) { positionX = x; }
		void Player::setPositionY(int y) { positionY = y; }		
		void Player::setLightPositionX(int x) { lighPositionX = x; }
		void Player::setLightPositionY(int y) { lightPositionY = y; }		


        
