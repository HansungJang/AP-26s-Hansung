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

		void useItem(int x, int y); 
		void eraseUsedItem(); 
	 
		bool checkCollideEnemy(int playerX, int playerY, int enemyX, int enemyY);
		void updateCurrentState(); 
		int getMapSize(); 
		bool getPlayerCurrentState();  

		// Item 호출 l: light, a : air(=oxygen)



};