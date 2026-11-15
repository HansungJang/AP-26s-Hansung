#pragma once

class Item 
{
	private : 
		int point; 
		int positionX; 
		int positionY; 
		bool isCollectible;
		bool isUsed; 
	protected :  
		virtual void setPoint(int pt);   
	public :
		Item(); 
		virtual int getPoint();
		virtual int getPositionX(); 
        virtual int getPositionY();
		virtual bool getCollectible();
		virtual bool getIsused();
		virtual void setPositionX(int x);
		virtual void setPositionY(int y);
		virtual void setCollectible(bool state); 
		virtual void setIsused(bool state); 

		virtual ~Item();
};


// collectible item 
class Battery : public Item  
{
	private : 
		int MaxBattery = 5; 
	public : Battery(int x, int y); 
};

class Oxygen : public Item  
{
	private : 
		int MaxOxygen = 100; 
	public : Oxygen(int x, int y); 
};

// un-collectible item (제한 시간동안 enemy 공격할 수 있음)
class PowerPill : public Item 
{
	public : PowerPill(); 
}; 