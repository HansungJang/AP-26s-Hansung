#pragma once

#include <memory>
#include <ctime>

class Enemy 
{
	private : 
		int damage; 
		int positionX; 
		int positionY; 
	public :
		Enemy(); 
		virtual int givedamage();
		virtual int getPositionX(); 
        virtual int getPositionY();
		virtual void setPositionX(int x);
		virtual void setPositionY(int y);
		virtual void setDamage(int dg);   

		virtual ~Enemy();
};

class MoveableEnemy : public Enemy
{
	private : 
		int nextPosX; 
		int nextPosY; 
		bool moveActive; 
	public :
	MoveableEnemy (int dg, int x, int y); 

	bool getMoveActive();
	void setMoveActive(bool active);

	int randomDirection(); // 0~3 random direction value calculate function [0: u, 1: l, 2: d, 3: r] 
	void nextPos(int nextDir); // calculate movable enemy next postion   
 	void move(); // set movable enemy next postion 

	int getNextPosX();
	int getNextPosY();
}; 



class FixedEnemy : public Enemy 
{
	public :
	FixedEnemy (int dg, int x, int y) ;
}; 