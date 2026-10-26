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
#include <algorithm>
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
//   int poitionX;
//   int poitionY;
// } Player; // named as "Player", a struct containing relevant player data is declared

// Player player_data = {MAX_HEALTH, MAX_OXYGEN, INIT_LIVES, 0, 0}; // initialize player data


/****************************************************************
 * 
 * Class 
 * Refactoring to class based implementation
 * 
 ****************************************************/

/*
Task To Do [26.09.30.  ~ 26.10.07.]

- Player class
  - 기존 player struct -> private var  
  - getter / setter 변수 주는 encapsulate 
  - 산소 감소 [새로운 함수] // oxyzenCalculator 함수
  - 죽음 판별 [새로운 함수] // playerState 함수 
  - move, attack, takeDamage, die, state, skill, item 

	[variables]
	int health;
	int oxygen;
	int lives; 
	int poitionX;
	int poitionY;
	bool isAlive; // player state alive or dead
    
	[functions]
	constructor : initialize player data
	void poitionUpdate(int, int) : update player position
	void oxyzenCalculator(int) : calculate oxygen level
	void healthCalculator(int) : calculate health level (time based)
	void takeDamage(int) : calculate player health when attacked
	bool playerState() : check player state; isAlive & health & oxygen

	setter / getter functions: health, oxygen, lives, poitionX, poitionY, isAlive

    //

- Enemy class 
  - move, attack, takeDamage, die, state

	[variables]
	int damage;
	int lives; 
	int poitionX;
	int poitionY;
	bool isAlive; // enemy state alive or dead

	[functions]
	constructor : initialize enemy data
	void poitionUpdate(int, int) : update enemy position
    void takeDamage(int) : calculate enemy health when attacked
	bool enemyState() : check enemy state; isAlive & health & oxygen

	setter / getter functions: health, oxygen, lives, poitionX, poitionY, isAlive

- Item class 
  - item type, item name, item effect, item state
  - useItem, pickUpItem, dropItem

- World class :  player, Enemy, Item
  - map 정보도 받아야함 
  - start/quit routine 
  - load_level, mapsize
  - restart

  - player, world, enemy class받아야함 


  	[variables]
	char** map 
	int mapSize

	class Player player_data
	class Enemy enemies_data[]
	class Item items_data[]

	[functions]
	void start_splash_screen(void);
	void load_level(string); // a routine to load a level map from a file
	void mapDelete();
	int mapSize();

	checkInitialPosition; // check player, enemies, items initial position in map

	player :
	    - playerData
	    - playerPosition
	enemy :
	    - enemyPosition
	item :
	    - itemPosition
	

- ControlManager class : World <- User input 받아서 각 클래스에 전달하는 역할

  - read_input, update_screen, render_screen  
  - takeDamage, attack 

	[variables]
	const int MAX_HEALTH = 100;
	const int MAX_OXYGEN = 100;
	const int INIT_LIVES = 3;
	int positionX;
	int positionY;

	class World world_data

	[functions]
	#load : constructor level 
	world : 
	    - start_splash_screen()
		- startup_routines()
		- load_level(string)

	#controler 
	int read_input(char *);
	
	#update 
	void startup_routines(void);
	void quit_routines(void);
	void mapReset();

	void update_state(char);  // assuming only one input char (key press) at most at a time ("turn-based" execution flow)
	void render_screen(void);

	void move(int, int);
	int checkPosition(int, int);
*/


class Player
{
	private:
		int health;
		int oxygen;
		int lives; // 필요없으면 hp로 
		int poitionX;
		int poitionY;
		bool isAlive; // player state alive or dead
	public:
		Player(int hp, int oxy, int live, int x=0, int y=0) // constructor : initialize player data
		: health(hp), oxygen(oxy), lives(live), poitionX(x), poitionY(y), isAlive(true){}
		
		
		void poitionUpdate(int x, int y) // update player position
		{
			poitionX = x;
			poitionY = y;
		}

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
			setPositionX(0); 
			setPositionY(0); 
			playerStateChange(); 
		}

		// setter / getter functions: health, oxygen, lives, poitionX, poitionY, isAlive	
		int getHealth(){ return health; }
		int getOxygen() {return oxygen; }
 		int getPositionX() { return poitionX; }
		int getPositionY() { return poitionY; }
		bool getIsAlive() { return isAlive; }
		
		void setHealth(int hp) { health = hp; }
		void setOxygen(int oxy) { oxygen = oxy; }
		void setPositionX(int x) { poitionX = x; }
		void setPositionY(int y) { poitionY = y; }		
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
		virtual int getPositiony(){return positionY;};
		virtual void setpositionX(int x) {positionX = x;};
		virtual void setpositiony(int y) {positionY = y;};
		virtual void setDamage(int dg) {damage = dg;}; 

		virtual ~Enemy() = default;

};

class MoveableEnemy : public Enemy
{
	private : 
		int nextPosX; 
		int nextPosY; 
	public :
	MoveableEnemy (int dg, int x, int y) 
	{
		this->setDamage(dg); 
		this->setpositionX(x); 
		this->setpositiony(y); 
		nextPosX= x; 
		nextPosY= y; 
	}; 


	int randomDirection(){return rand() %4; }; // 0~3 시간별 임의값 random [0: u, 1: l, 2: d, 3: r],  time 단위 update 
	void nextPos(int nextDir)
	{
		nextPosX = getPositionX();
		nextPosY = getPositiony();

		switch (nextDir)
		{
			case 0: --nextPosY; break; // 위
			case 1: --nextPosX; break; // 왼쪽
			case 2: ++nextPosY; break; // 아래
			case 3: ++nextPosX; break; // 오른쪽
			default: break;
		}
	};  // randomDirection() 실행 방향 current position에 연산, next좌표 만듬
	void move()
	{
		this->setpositionX(nextPosX); 
		this->setpositiony(nextPosY);
	}; // update position positionX = nextposX, positionY = nextposY

	int getnextPosx(){return nextPosX;};
	int getnextPosy(){return nextPosY;};

}; 



class FixedEnemy : public Enemy 
{
	public :
	FixedEnemy (int dg, int x, int y) 
	{
		this->setDamage(dg); 
		this->setpositionX(x); 
		this->setpositiony(y); 
	}; 
}; 

class World
{
	private:
		char** map;
		int mapSize;
		int DEFAULTDAMAGE = 10; 
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
				if(map[next_y][next_x] == 'x' || map[next_y][next_x] == 'X') canMove = false; 
				// if 장애물 접촉 -> 넘어가는 연산 호출 (좌표 겹침) 

			return canMove; 
		}

	public:
		World(string file) : player_data(MAX_HEALTH, MAX_OXYGEN, INIT_LIVES), mapSize(0), map(nullptr), isRestart(false)
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

		void load_level() // a routine to load a level map from a file
		{
			// Implementation for loading level
			FILE* file = NULL;
			const char* filename = this->filepath.c_str(); 
			int currLength = 0; 
			int character; 

			int curr_charater_size = 0;
			string currString  = ""; 

			file = fopen(filename, "r"); 

			if(file == NULL) 
			{
				cout << "File Path Somthing Wrong ... (Check file path)" << endl; 
				return; 
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
						return;
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

			return; 
		}

		void mapDelete() 
		{
			for(int i =0; i < mapSize; i++) 
			{
				delete[] map[i]; 
			}

			delete[] map; 
			map = nullptr; 
			mapSize = 0; 
		}

		void retrial()
		{
			// if(live <= 0) 게임 오버 

			// lives -= 1; 

			// player_status, map 요소만 다시 reset 
		}

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
			load_level(); 
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

			// 맵 그리기 
			for(int y=0; y < mapSize; y++)
			{
				for(int x =0; x < mapSize; x++)
				{
					cout << map[y][x] << " " ;  
				}
				cout << endl; 
			}
			cout << endl; 
			cout << "*******  PLAYER STATUS *******" << endl;
			cout << "Health : " << player_data.getHealth() << ", " << "Oxygen : " << player_data.getOxygen() << endl; 
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
			if(!checkPlayerState) return; 

			player_data.oxyzenCalculator();
			checkPlayerState = player_data.getIsAlive();

			// if enemy 충돌 -> damage 연산 호출 (player가 이동한 경우)
			if(map[next_y][next_x] == 'm' || map[next_y][next_x] == 'M') 
			{
				player_data.takeDamage(findDamage(next_x, next_y)); 
			}

			if(checkPlayerMove && checkPlayerState) 
			{
				swap(map[curr_y][curr_x], map[next_y][next_x]); 
 
				player_data.setPositionX(next_x); 
				player_data.setPositionY(next_y);
	  
				// player_data.oxygen *= 0.98; Oxygen decrease when player move
			}

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

				int nextdir = movingEnemy->randomDirection(); 
				movingEnemy->nextPos(nextdir); 

				const int oldX = movingEnemy->getPositionX(); 
				const int oldY = movingEnemy->getPositiony(); 
				int nextX = movingEnemy->getnextPosx(); 
				int nextY = movingEnemy->getnextPosy(); 
				int playerX = player_data.getPositionX(); 
				int playerY = player_data.getPositionY();
				
			
				// player와 충돌여부 
				if(checkCollideEnemy(playerX, playerY, nextX, nextY))
				   {
						player_data.takeDamage(movingEnemy->givedamage());
						continue;
				   }

				// 이동가능 여부 
				if(!checkPosition(nextX, nextY)) continue; 

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
				int enemyPosY = enemy->getPositiony();

				if(x == enemyPosX && y == enemyPosY) 
				{
					damage = enemy->givedamage();
				}
				break; 
			}
			return damage;  
		}

		bool checkCollideEnemy(int playerX, int playerY, int enemyX, int enemyY)
		{
			bool collide = false; 

			if(playerX == enemyX && playerY == enemyY) collide = true; 

			// for(const auto& enemy : enemyContainer)
			// {
			// 	auto* movingEnemy = dynamic_cast<MoveableEnemy*>(enemy.get()); // type identify 
			// 	auto* fixedEnemy = dynamic_cast<FixedEnemy*>(enemy.get()); // type identify 				
			// 	if(movingEnemy != nullptr)
			// 	{
			// 		if(player_data.getPositionX() == movingEnemy->getnextPosx() && 
			// 		player_data.getPositionY() == movingEnemy->getnextPosy())
			// 		{
			// 			collide = true; 
			// 			player_data.takeDamage(movingEnemy->givedamage());
			// 		}
			// 	} 

			// 	if(fixedEnemy != nullptr)
			// 	{
			// 		if(player_data.getPositionX() == fixedEnemy->getPositionX() && 
			// 		player_data.getPositionY() == fixedEnemy->getPositiony())
			// 		{
			// 			collide = true; 
			// 			player_data.takeDamage(fixedEnemy->givedamage());
			// 		}					
			// 	}

			// }

			return collide; 
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
		ControlManager(string filename) : game(filename), file(filename), playingState(true)
		{
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

			}


		} 
		
		void playerMove(int x, int y)
		{
			game.playerMove(x, y); 
		} 

		void stateUpdate()
		{
			game.enemyMove(); 
			game.render_screen(); 
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

	string filepath; 
	cout << "Insert File path (defalut : Map2.txt): "; 

	if (!getline(cin, filepath)) return 0;
	if (filepath.empty()) filepath = "Map2.txt";
	ControlManager controller(filepath); 

	while(true)
	{
		controller.read_input();
		if(!controller.getPlayingState()) break; 
		controller.stateUpdate(); 
	}

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
