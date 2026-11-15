#pragma once

#include "Player.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include <iostream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std; 

class World
{
	private:
		char** map;
		char** lightmap; 
		int mapSize;
		int DEFAULTDAMAGE = 10; 
		int DEFAULTLIGHTCOUNT = 5; 
		Player player_data;
		vector<unique_ptr<Enemy>> enemyContainer; 
		// Item container 보관할 수 있어야함 
		vector<unique_ptr<Item>> itemContainer; 
		vector<char> itemType = {'l', 'a'}; 
		int lightitem = 0; 
		int oxygenitem = 0; 
		bool isRestart; 
		string filepath; 

		void checkInitialPosition(char character, int x, int y); 
		bool checkPosition(int next_x, int next_y);
		void calculationLightRange(int x, int y);
		void checkEnemystate();
		void initialLightMap();
		bool inBounds(int x, int y);
		Enemy* findEnemy(int x, int y);
		Item* findItem(int x, int y); 

	public:
		World(string file); 
		void start_splash_screen(void) ;
		bool load_level();
 		void mapDelete(); 
		void gameReset();
		void filePathChange(string newFile);
		void render_screen(void);
		void playerMove(int input_x, int input_y);
		void LightMove(int input_x, int input_y);
 		void enemyMove(); 
		int findDamage(int x, int y);
	 
		bool checkCollideEnemy(int playerX, int playerY, int enemyX, int enemyY);
		void updateCurrentState(); 
		int getMapSize(); 
		bool getPlayerCurrentState();  

		// Item 호출 l: light, a : air(=oxygen)
		void itemRandomPlace(int num); // number of item; item placed random position on the map  
		void storeItem(char item, int posX, int posY); // store player collectible item
		void chooseItem(); 
		void useItem(char type); 
		// void eraseUsedItem(); 

};