#include "Enemy.hpp"

    Enemy::Enemy()
		{
			damage = 0;
			positionX = 0; 
			positionY = 0;
		}; 
		 int Enemy::givedamage(){return damage;};
		 int Enemy::getPositionX(){return positionX;};
		 int Enemy::getPositionY(){return positionY;};
		 void Enemy::setPositionX(int x) {positionX = x;};
		 void Enemy::setPositionY(int y) {positionY = y;};
		 void Enemy::setDamage(int dg) {damage = dg;}; 

		 Enemy::~Enemy() = default;

	MoveableEnemy::MoveableEnemy (int dg, int x, int y) : moveActive(false) 
	{
		this->setDamage(dg); 
		this->setPositionX(x); 
		this->setPositionY(y); 
		nextPosX= x; 
		nextPosY= y; 
	}; 

	bool MoveableEnemy::getMoveActive() {return moveActive;};
	void MoveableEnemy::setMoveActive(bool active) {moveActive = active;};

	int MoveableEnemy::randomDirection(){return rand() %4; }; 
	void MoveableEnemy::nextPos(int nextDir)
	{
		nextPosX = this->getPositionX();
		nextPosY = this->getPositionY();

		switch (nextDir)
		{
			case 0: --nextPosY; break; // up
			case 1: --nextPosX; break; // leaft
			case 2: ++nextPosY; break; // down
			case 3: ++nextPosX; break; // right
			default: break;
		}
	};  // randomDirection()  
	void MoveableEnemy::move()
	{
		this->setPositionX(nextPosX); 
		this->setPositionY(nextPosY);
	}; // update position positionX = nextposX, positionY = nextposY

	int MoveableEnemy::getNextPosX(){return nextPosX;};
	int MoveableEnemy::getNextPosY(){return nextPosY;};
 
	FixedEnemy::FixedEnemy (int dg, int x, int y) 
	{
		this->setDamage(dg); 
		this->setPositionX(x); 
		this->setPositionY(y); 
	}; 
