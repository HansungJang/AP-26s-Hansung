/*
*
* Holy diver - an epic adventure at object-oriented world way beneath the surface!
* Template code for implementing the rich features to be specified later on.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

#include <vector>
#include <memory>
#include <ctime>

/****************************************************/
// declaring functions:
/****************************************************/
// void start_splash_screen(void);
// void startup_routines(void);
// void quit_routines(void);
// void load_level(string); // a routine to load a level map from a file
// void mapDelete();
// void mapReset();


// int read_input(char *);
// void update_state(char);  // assuming only one input char (key press) at most at a time ("turn-based" execution flow)
// void render_screen(void);

// // new function [내가 새로 만든 함수]
// void playerMove(int, int);
// int mapSize();
// int checkPosition(int, int);


/****************************************************/
// global variables:
/****************************************************/
// char ** map;// pointer pointer equals to array of arrays = 2-dimensional array of chars
			// above is virtually identical, as a variable, compared to for example:
			//	    char map[MAXSTR][MAXLEN] = {{0}}; // declare a static 2-dim array of chars, initialize to zero
			// However pointer to pointer has not allocated memory yet attached to it, this is done dynamically when actual size known

const int MAX_HEALTH = 100;
const int MAX_OXYGEN = 100; // 5
const int INIT_LIVES = 3;


// typedef struct Player{ 
//   int health;
//   int oxygen;
//   int lives; 
//   int positionX;
//   int positionY;
// } Player; // named as "Player", a struct containing relevant player data is declared

// Player player_data = {MAX_HEALTH, MAX_OXYGEN, INIT_LIVES, 0, 0}; // initialize player data


/****************************************************************
 * 
 * Class 
 * Refactoring to class based implementation
 * 
 ****************************************************/

/*
Task To Do  [~03.11.2026.]

*/


class Player
{
	private:
		int health;
		int oxygen;
		int lives; // 필요없으면 hp로 
		int initialLightCount;
		int lightcount; 
		int positionX;
		int positionY;
		int lighPositionX;
		int lightPositionY;
		bool isAlive; // player state alive or dead

	public:
		Player(int hp, int oxy, int live, int lightcount, int x=-1, int y=-1) // constructor : initialize player data
		: health(hp), oxygen(oxy), lives(live), initialLightCount(lightcount), lightcount(lightcount), positionX(x), positionY(y), lighPositionX(x), lightPositionY(y), isAlive(true){}
		

		void oxyzenCalculator(int oxy = -1) // calculate oxygen level
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

		void healthCalculator(int hp) // calculate health level (time based)
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
 

		void takeDamage(int damage) // calculate player health when attacked
		{
			healthCalculator(-damage);
		}

		void playerStateChange() // check player state; isAlive & health & oxygen
		{
			isAlive = !(health <= 0 || oxygen <= 0);
		}

		void playerReset()
		{
			health = MAX_HEALTH; 
			oxygen = MAX_OXYGEN; 
			lightcount = initialLightCount;
			setPositionX(0); 
			setPositionY(0); 
			playerStateChange(); 
		}

		// setter / getter functions: health, oxygen, lives, positionX, positionY, isAlive	
		int getHealth(){ return health; }
		int getOxygen() {return oxygen; }
		int getLightCount() {return lightcount;}
 		int getPositionX() { return positionX; }
		int getPositionY() { return positionY; }
 		int getLightPositionX() { return lighPositionX; }
		int getLightPositionY() { return lightPositionY; }
		bool getIsAlive() { return isAlive; }
		
		void setLightCount(int light) {lightcount = light;}
		void setPositionX(int x) { positionX = x; }
		void setPositionY(int y) { positionY = y; }		
		void setLightPositionX(int x) { lighPositionX = x; }
		void setLightPositionY(int y) { lightPositionY = y; }		

	};

class Enemy 
{
	private : 
		int damage; 
		int positionX; 
		int positionY; 
	public :
		Enemy()
		{
			damage = 0;
			positionX = 0; 
			positionY = 0;
		}; 
		virtual int givedamage(){return damage;};
		virtual int getPositionX(){return positionX;};
		virtual int getPositionY(){return positionY;};
		virtual void setPositionX(int x) {positionX = x;};
		virtual void setPositionY(int y) {positionY = y;};
		virtual void setDamage(int dg) {damage = dg;}; 

		virtual ~Enemy() = default;

};

class MoveableEnemy : public Enemy
{
	private : 
		int nextPosX; 
		int nextPosY; 
		bool moveActive; 
	public :
	MoveableEnemy (int dg, int x, int y) : moveActive(false) 
	{
		this->setDamage(dg); 
		this->setPositionX(x); 
		this->setPositionY(y); 
		nextPosX= x; 
		nextPosY= y; 
	}; 

	bool getMoveActive() {return moveActive;};
	void setMoveActive(bool active) {moveActive = active;};

	int randomDirection(){return rand() %4; }; // 0~3 시간별 임의값 random [0: u, 1: l, 2: d, 3: r],  time 단위 update 
	void nextPos(int nextDir)
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
	};  // randomDirection() 실행 방향 current position에 연산, next좌표 만듬
	void move()
	{
		this->setPositionX(nextPosX); 
		this->setPositionY(nextPosY);
	}; // update position positionX = nextposX, positionY = nextposY

	int getNextPosX(){return nextPosX;};
	int getNextPosY(){return nextPosY;};

}; 



class FixedEnemy : public Enemy 
{
	public :
	FixedEnemy (int dg, int x, int y) 
	{
		this->setDamage(dg); 
		this->setPositionX(x); 
		this->setPositionY(y); 
	}; 
}; 

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

		bool isRestart; 
		string filepath; 

		// Enemy enemies_data[];  
		// Item items_data[];

		void checkInitialPosition(char character, int x, int y) // check player, enemies, items initial position in map
		{
			if(character == 'p') 
			{
					player_data.setPositionX(x); // 0부터 시작함으로
					player_data.setPositionY(y);
			}

			// enemies 
			if(character == 'M') // movable
			{
					enemyContainer.push_back(make_unique<MoveableEnemy>(DEFAULTDAMAGE, x, y));
			}

			if(character == 'm') // fixed
			{
					enemyContainer.push_back(make_unique<FixedEnemy>(DEFAULTDAMAGE, x, y));
			}


			// item 

		}

		bool checkPosition(int next_x, int next_y)
		{
			if(map == nullptr) // check map
			{
				cout <<  "Current map is not loaded ... " << endl; 
				return false;  
			}
			
			if(next_x < 0 || next_x >= mapSize // check position bound 
				|| next_y < 0 || next_y >= mapSize)
				{
					cout << "Position is Out of Bound ... " << endl;
					return false; 
				} 
  			
			bool canMove = false; 

				if(map[next_y][next_x] == 'o' || map[next_y][next_x] == 'O') canMove = true; 
				if(map[next_y][next_x] == 'm' || map[next_y][next_x] == 'M') canMove = true; 				
				if(map[next_y][next_x] == 'x' || map[next_y][next_x] == 'X') canMove = false; 
				// if 장애물 접촉 -> 넘어가는 연산 호출 (좌표 겹침) 

			return canMove; 
		}




		void calculationLightRange(int x, int y)
		{
			if(x < 0 || x >= mapSize || y < 0 || y >= mapSize) return; 
			
			if(lightmap[y][x] == ' ') lightmap[y][x] = map[y][x]; 
			// clalculate vision range size 
			if(y - 1 < 0 || x - 1 <0) return;
				if(lightmap[y][ x-1 ] == ' ') lightmap[y][x -1 ] = map[y][x-1]; // l
				if(lightmap[y-1][x-1] == ' ') lightmap[y-1][x-1] = map[y-1][x-1]; // lu  
				if(lightmap[y-1][x] == ' ') lightmap[y-1][x] = map[y-1][x]; // u
			if(y+1 >= mapSize || x+1 >= mapSize) return; 
				if(lightmap[y-1][x+1] == ' ') lightmap[y-1][x+1] = map[y-1][x+1]; // ru
				if(lightmap[y][x+1] == ' ') lightmap[y][x+1] = map[y][x+1]; // r  
				if(lightmap[y+1][x+1] == ' ') lightmap[y+1][x+1] = map[y+1][x+1]; // rd
				if(lightmap[y+1][x] == ' ') lightmap[y+1][x] = map[y+1][x]; // d  
				if(lightmap[y+1][x-1] == ' ') lightmap[y+1][x-1] = map[y+1][x-1]; // ld

		}

		void checkEnemystate()
		{
			for(int i = 0 ; i < mapSize; i++)
			{
				for(int j =0; j < mapSize; j++)
				{
					if(lightmap[i][j] == 'M') 
					{
						auto* movingEnemy = dynamic_cast<MoveableEnemy*>(findEnemy(j, i));
						if(movingEnemy) movingEnemy->setMoveActive(true);
					}
				}
			}
		}

		void initialLightMap()
		{
			if(map == nullptr) return; 
			if(mapSize <= 0 ) return; 
			
			int initialX = player_data.getPositionX();
			int initialY = player_data.getPositionY();
			// int range; default는 1이라고 생각
			if(initialX < 0 || initialY < 0) return; 

			for(int i = 0; i < mapSize; i++)
			{
				if(i == 0){lightmap = new char*[mapSize];}
				lightmap[i] = new char[mapSize]; 
				for(int j = 0; j < mapSize; j++)
				{
					lightmap[i][j] = ' '; 
				}
			}

			lightmap[initialY][initialX] = 'p'; 
			player_data.setLightPositionX(initialX); 
			player_data.setLightPositionY(initialY); 
			calculationLightRange(initialX, initialY); 
			checkEnemystate();

		}

		bool inBounds(int x, int y) const
		{
			return x >= 0 && x < mapSize &&
				y >= 0 && y < mapSize;
		}

		Enemy* findEnemy(int x, int y)
		{
			for(const auto& enemy : enemyContainer)
			{
				if(enemy->getPositionX() == x && enemy->getPositionY() == y)
				{
					return enemy.get(); 
				}
			}
			return nullptr; 
		}

	public:
		World(string file) : player_data(MAX_HEALTH, MAX_OXYGEN, INIT_LIVES, DEFAULTLIGHTCOUNT), mapSize(0), map(nullptr), isRestart(false)
		{
			start_splash_screen(); 
			enemyContainer.clear(); 
			this->filepath = file; 
			load_level(); 
		}
		
		void start_splash_screen(void) 
		{
			/* this function to display any title information at startup, may include instructions or fancy ASCII-graphics */
			cout <<endl<< "WELCOME to epic Holy Diver v0.01"<<endl;
			cout << "Enter commands and enjoy! (press q to quit at all times)"<<endl<<endl;
 		}

		bool load_level() // a routine to load a level map from a file
		{

			// Implementation for loading level
			FILE* file = NULL;
			const char* filename = this->filepath.c_str(); 
			int currLength = 0; 
			int character; 

			int curr_charater_size = 0;
			string currString  = ""; 

			file = fopen(filename, "r"); 

			if(file == NULL || file == nullptr) 
			{
				cout << "File Path Somthing Wrong ... (Check file path)" << endl; 
				return false; 
			}


			while((character = fgetc(file)) != EOF)
			{
				if(character == '\r') continue; 
				if(character == '\0' || character == '\n')
				{
					if((currLength == 0 && mapSize == 0) || isRestart)
					{
						mapSize = curr_charater_size; 
						map = new char*[mapSize]; 
						isRestart = false; 
					}
					// 에러 처리 

					if(curr_charater_size != mapSize) 
					{
						cout << "Map data is un-unify ... (check file map)" << endl; 
						return false;
					}
				
					map[currLength]  = new char[mapSize + 1]; 
					copy(currString.begin(), currString.end(), map[currLength]);
					map[currLength][mapSize] = '\0'; 
					curr_charater_size = 0; 
					currLength += 1;
					currString = "";
					continue; 
				}	
				// 읽는 문자 저장하는 변수 
				// 문자열 dynamic 으로 문자열 만들어서 문자하나씩 넣어야함 
				if(character == 'p' || character == 'P')
				{
					checkInitialPosition('p', currString.size(), currLength);
				}

				// enemy, item 초기 위치 확인
				if(character == 'M') // movable
				{
					checkInitialPosition('M', currString.size(), currLength);
				}
				
				if(character == 'm') // fixed
				{
					checkInitialPosition('m', currString.size(), currLength);
				}

				// enemycontainer에 담아야함

				currString.push_back(character);
				curr_charater_size += 1; 
			}

			if(currString != "" )
			{
					map[currLength]  = new char[mapSize + 1]; 
					copy(currString.begin(), currString.end(), map[currLength]);
					map[currLength][mapSize] = '\0'; 
					curr_charater_size = 0; 
					currLength += 1;
					currString = "";
			}

			fclose(file); 
			cout << "Map Load Complete" << endl; 

			initialLightMap(); 

			return true; 
		}

		void mapDelete() 
		{
			for(int i =0; i < mapSize; i++) 
			{
				delete[] map[i]; 
				delete[] lightmap[i]; 
			}

			delete[] map; 
			delete[] lightmap; 
			map = nullptr; 
			lightmap = nullptr; 
			mapSize = 0; 
		}

		// void retrial()
		// {
		// 	// if(live <= 0) 게임 오버 

		// 	// lives -= 1; 

		// 	// player_status, map 요소만 다시 reset 
		// }

		void gameReset()
		{
			char input; 
			cout << "Are You Sure want to Restart ? [y / n] :  "; 
			cin >> input; 
		
			if(input == 'n' || input == 'N') return; 
			isRestart = true; 
			cin.ignore();


			mapDelete();
			enemyContainer.clear(); 
			player_data.playerReset();
			if(!load_level()) 
			{
				cout << "Map Load Fail ... " << endl; 
				exit(1);
			}
		}

		void filePathChange(string newFile)
		{
			this->filepath = newFile; 
			
			mapDelete();
			enemyContainer.clear(); 
			player_data.playerReset();
			if(!load_level()) 
			{
				cout << "Map Load Fail ... " << endl; 
				exit(1);
			}		
		}

		void render_screen(void)
		{
			if(!player_data.getIsAlive()) 
			{
				cout << endl; 
				cout << "*******  GAME OVER *******" << endl;
				cout << "Restart : r" << endl;
				cout << "Quit : q" << endl; 
				cout << endl; 
				return; 
			}

			// 맵 그리기 (다른 맵으로 교체해야 함)
			for(int y=0; y < mapSize; y++)
			{
				for(int x =0; x < mapSize; x++)
				{
					// cout << map[y][x] << " " ;  
					cout << lightmap[y][x] << " "; 
				}
				cout << endl; 
			}
			cout << endl; 
			cout << "*******  PLAYER STATUS *******" << endl;
			cout << "Health : " << player_data.getHealth() << ", " << "Oxygen : " << player_data.getOxygen() <<  ", " << "Light Count : " << player_data.getLightCount() << endl; 
			// player lives 는 나중에 추가 (아마 game over 횟수에 들어가겠지)

		}

		void playerMove(int input_x, int input_y)
		{
			int curr_x = player_data.getPositionX(); 
			int curr_y = player_data.getPositionY(); 
			int next_x = curr_x + input_x; 
			int next_y = curr_y + input_y; 

			bool checkPlayerMove = checkPosition(next_x, next_y); 
			bool checkPlayerState = player_data.getIsAlive(); 

			Enemy* enemy; 
			char target = map[next_y][next_x];


			if(!checkPlayerState) return; 
			if(map == nullptr || lightmap == nullptr) return;

			player_data.oxyzenCalculator(); // 이동 가능 여부 상관없이 이동 시도 많으로 산소 소비 발생해야 함.
			checkPlayerState = player_data.getIsAlive();

			if(!checkPlayerState) return;
			if(!inBounds(next_x, next_y)) return;

			if (target == 'x' || target == 'X') return;
			// if enemy 충돌 -> damage 연산 호출 (player가 이동한 경우)
			if(target == 'm' || target == 'M') 
			{
				player_data.takeDamage(findDamage(next_x, next_y)); 
				enemy = findEnemy(next_x, next_y);
				
				enemy->setPositionX(curr_x);
				enemy->setPositionY(curr_y);
			}

			if(checkPlayerMove && checkPlayerState) 
			{
				swap(map[curr_y][curr_x], map[next_y][next_x]); 
				swap(lightmap[curr_y][curr_x], lightmap[next_y][next_x]); 
				
				player_data.setPositionX(next_x); 
				player_data.setPositionY(next_y);

				// if player move vision position also automatically cange 
				player_data.setLightPositionX(next_x); 
				player_data.setLightPositionY(next_y); 
				calculationLightRange(next_x, next_y); 
				checkEnemystate();
	  
			}

			return; 
		}

		void LightMove(int input_x, int input_y)
		{
			int curr_count = player_data.getLightCount(); 
			if(curr_count <= 0) return; 
			curr_count-= 1; 
			player_data.setLightCount(curr_count);

			// step 1. 현재 light 좌표 가지고 와야함 (player)
			int next_lightX = player_data.getLightPositionX() + input_x; 
			int next_lightY = player_data.getLightPositionY() + input_y; 
			if(next_lightX < 0 || next_lightX >= mapSize) return; 
			if(next_lightY < 0 || next_lightY >= mapSize) return; 

			player_data.setLightPositionX(next_lightX); 
			player_data.setLightPositionY(next_lightY);  
			
			// step 2. 입력만큼 이동 
			calculationLightRange(next_lightX, next_lightY); 
			return; 
		}


		void enemyMove()
		{
			// exception handle 
			if(map == nullptr || !player_data.getIsAlive()) return; 

			for(const auto& enemy : enemyContainer)
			{
				auto* movingEnemy = dynamic_cast<MoveableEnemy*>(enemy.get()); // type identify 
				if(movingEnemy == nullptr) continue; 
				if(!movingEnemy->getMoveActive()) continue; // 발견 안된 enemy는 이동하지 않음

				int nextdir = movingEnemy->randomDirection(); 
				movingEnemy->nextPos(nextdir); 

				const int oldX = movingEnemy->getPositionX(); 
				const int oldY = movingEnemy->getPositionY(); 
				int nextX = movingEnemy->getNextPosX(); 
				int nextY = movingEnemy->getNextPosY(); 
				int playerX = player_data.getPositionX(); 
				int playerY = player_data.getPositionY();
				
				if(!inBounds(nextX, nextY)) continue;
				if(findEnemy(nextX, nextY) != nullptr) continue; // 다른 enemy와 충돌여부
 				if(!checkPosition(nextX, nextY)) continue; // 이동가능 여부 

				// player와 충돌여부 
				if(checkCollideEnemy(playerX, playerY, nextX, nextY))
				   {
						player_data.takeDamage(movingEnemy->givedamage());
						if (!player_data.getIsAlive()) return; 
						continue;
				   }


				swap(map[oldY][oldX], map[nextY][nextX]); 

				movingEnemy->move(); 

			}
		}

		int findDamage(int x, int y)
		{
			int damage = 0;
			for(const auto& enemy : enemyContainer)
			{
				int enemyPosX = enemy->getPositionX();
				int enemyPosY = enemy->getPositionY();

				if(x == enemyPosX && y == enemyPosY) 
				{
					damage = enemy->givedamage();
					break; 
				}
			}
			return damage;  
		}

		bool checkCollideEnemy(int playerX, int playerY, int enemyX, int enemyY)
		{
			bool collide = false; 

			if(playerX == enemyX && playerY == enemyY) collide = true; 

			return collide; 
		}

		void updateCurrentState()
		{
		   for(int i = 0;  i < mapSize; i++)
		   {
				for(int j =0; j < mapSize; j++)
				{
					if(lightmap[i][j] != ' '){lightmap[i][j] = map[i][j];}
				}
		   }
		}

		int getMapSize() { return mapSize; }
		bool getPlayerCurrentState() {return player_data.getIsAlive();}
		

};


class ControlManager
{
	private : 
		World game; 
		string file;
		bool playingState; 

	public : 
		ControlManager(string filename = "Map2.txt") : game(filename), file(filename), playingState(true)
		{
			setFilePath(); 
			game.render_screen(); 
		};

		void read_input()
		{
			char input ='\0'; 
			cout << "your command : "; 
			try{
				cin >> input; 
			}
			catch(...)
			{
				cout << "Somthing went wrong ... " <<endl; 
				return; 
			}
			cout << endl; 
			cin.ignore(); 

			if(input == 'q' || input =='Q') end(); 
			if(input == 'r' || input == 'R') restart(); 

			if(game.getPlayerCurrentState()) // player가 살아있는 상태에서만 입력 받음
			{
				// player move 
				if(input == 'w' || input =='W') playerMove(0, -1); 
				if(input == 'a' || input =='A') playerMove(-1, 0); 
				if(input == 's' || input =='S') playerMove(0, 1); 
				if(input == 'd' || input =='D') playerMove(1, 0); 

				// player light 
				if(input == 'i' || input =='I') LightMove(0, -1); 
				if(input == 'j' || input =='J') LightMove(-1, 0); 
				if(input == 'k' || input =='K') LightMove(0, 1); 
				if(input == 'l' || input =='L') LightMove(1, 0); 

			}


		} 
		
		void playerMove(int x, int y)
		{
			game.playerMove(x, y); 
		} 

		void LightMove(int x, int y)
		{
			game.LightMove(x, y); 
		} 

		void setFilePath()
		{
			string filepath; 
			cout << "Insert File path (defalut : Map2.txt): "; 

			if (!getline(cin, filepath) || filepath == "Map2.txt" || filepath == "map2.txt" || filepath.empty()) return;
			file = filepath;
			game.filePathChange(file);
		}

		void stateUpdate()
		{
			game.enemyMove(); 
			game.updateCurrentState(); 
			game.render_screen(); 

		} 

		void run()
		{
			while(true)
			{
				read_input(); 
				if(!playingState) break; 
				stateUpdate(); 
			}
		}

		void restart()
		{
			cout << "Game Restart" << endl; 
			cout << endl; 

			game.gameReset(); 
		}

		void end()
		{ 
			playingState = false; 
			game.mapDelete(); 
			cout <<endl<< "BYE! Welcome back soon."<<endl;

			return; 
		}

		bool getPlayingState()
		{
			return playingState; 
		}

}; 



/****************************************************************
 * 
 * MAIN
 * main function contains merely function calls to various routines and the main game loop
 * 
 ****************************************************/
int main (void)
{
    srand(time(0)); // for random move generate seed value; 

	ControlManager controller; 
	controller.run();

	return 0; 

}

/****************************************************************
 * 
 * FUNCTION load_level
 * 
 * Open a map file and load level map from it.
 * First weekly home assignment is to be implemented mostly here.
 * 
 * **************************************************************/

// /****************************************************************
//  * 
//  * FUNCTION read_input
//  * 
//  * read input from user
//  * 
//  * **************************************************************/

// /****************************************************************
//  * 
//  * FUNCTION update_state
//  * 
//  * update game state (player, enemies, artefacts, inventories, health, whatnot)
//  * this is a collective entry point to all updates - feel free to divide these many tasks into separate subroutines
//  * 
//  * **************************************************************/


// /****************************************************************
//  * 
//  * FUNCTION render_screen
//  * 
//  * this function prints out all visuals of the game (typically after each time game state updated)
//  * 
//  * **************************************************************/
