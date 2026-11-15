#include "Item.hpp"

    Item::Item()
		{
			point = 0;
			positionX = 0; 
			positionY = 0;
			isCollectible = false; 
			isUsed = false; 
			type = 'i'; 
		}; 
		 char Item::getType(){return type;}
		 int Item::getPoint(){return point;};
		 int Item::getPositionX(){return positionX;};
		 int Item::getPositionY(){return positionY;};
		 bool Item::getCollectible(){return isCollectible;};
		 bool Item::getIsused(){return isUsed;};
		 void Item::setPositionX(int x) {positionX = x;};
		 void Item::setPositionY(int y) {positionY = y;};
		 void Item::setPoint(int pt) {point = pt;}; 
		 void Item::setCollectible(bool state){isCollectible = state;}; 
		 void Item::setIsused(bool state){isUsed = state;}; 

		 Item::~Item() = default;

	Battery::Battery(int x, int y)
	{
		type = 'l';
		setPositionX(x); 
		setPositionY(y); 
		setCollectible(true); 
		setPoint(MaxBattery); 
	}

	Oxygen::Oxygen(int x, int y)
	{
		type = 'a';
		setPositionX(x); 
		setPositionY(y); 
		setCollectible(true); 
		setPoint(MaxOxygen); 
	}