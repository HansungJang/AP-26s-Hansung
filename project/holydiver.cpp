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
const int MAX_OXYGEN = 100;
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
		int lives; 
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
			if(oxygen > MAX_OXYGEN) 
			{
				oxygen = MAX_OXYGEN;
				return; 
			}
			if(oxygen <= 0)
			{
				livesCalculator();
				oxygen = MAX_OXYGEN; // reset oxygen to max after losing a life
				return; 
			} 
			oxygen += oxy; // decrease oxygen by default, if not specified

		}

		void healthCalculator(int hp) // calculate health level (time based)
		{
			health += hp;
			if(health > MAX_HEALTH) health = MAX_HEALTH;
			if(health <= 0)
			{
				livesCalculator(); 
				health = MAX_HEALTH; // reset health to max after losing a life
			} 	
		}

		void livesCalculator(void) // calculate lives
		{
			lives -= 1;
			if(lives <= 0) 
			{
				lives = 0;
				playerStateChange(); 
			}
		}

		void takeDamage(int damage) // calculate player health when attacked
		{
			healthCalculator(-damage);
		}

		void playerStateChange() // check player state; isAlive & health & oxygen
		{
			isAlive = (lives > 0);
		}

		// setter / getter functions: health, oxygen, lives, poitionX, poitionY, isAlive	
		int getHealth(){ return health; }
		int getOxygen() {return oxygen; }
		int getLives() { return lives; }
		int getPositionX() { return poitionX; }
		int getPositionY() { return poitionY; }
		bool getIsAlive() { return isAlive; }
		
		void setHealth(int hp) { health = hp; }
		void setOxygen(int oxy) { oxygen = oxy; }
		void setLives(int live) { lives = live; }
		void setPositionX(int x) { poitionX = x; }
		void setPositionY(int y) { poitionY = y; }		
};


class World
{
	private:
		char** map;
		int mapSize;
		Player player_data;
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
			// item 

		}

		bool checkPosition(int next_x, int next_y)
		{
			bool canMove = false; 
			if(map[next_y][next_x] == 'o' || map[next_y][next_x] == 'O') canMove = true; 
			if(map[next_y][next_x] == 'x' || map[next_y][next_x] == 'X') canMove = false; 
			// if enemy 충돌 -> damage 연산
			return canMove; 
		}

	public:
		World(string file = "Map.txt") : player_data(MAX_HEALTH, MAX_OXYGEN, INIT_LIVES), mapSize(0), map(nullptr)
		{
			start_splash_screen(); 
			load_level(file); 
		}
		
		void start_splash_screen(void) 
		{
			/* this function to display any title information at startup, may include instructions or fancy ASCII-graphics */
			cout <<endl<< "WELCOME to epic Holy Diver v0.01"<<endl;
			cout << "Enter commands and enjoy! (press q to quit at all times)"<<endl<<endl;
			cin.ignore();
		}

		void load_level(string filepath) // a routine to load a level map from a file
		{
			// Implementation for loading level
			FILE* file = NULL;
			const char* filename = filepath.c_str(); 
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
					if(currLength == 0 && mapSize == 0)
					{
						mapSize = curr_charater_size; 
						map = new char*[mapSize]; 
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
		}

		void mapReset(string file)
		{
			char input; 
			cout << "Are You Sure want to Restart ? [y / n] :  "; 
			cin >> input; 
			cin.ignore();
			if(input == 'n' || input == 'N') return; 

			mapDelete();
			load_level(file); 
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
		}



		void playerMove(int input_x, int input_y)
		{
			int curr_x = player_data.getPositionX(); 
			int curr_y = player_data.getPositionY(); 
			int next_x = curr_x + input_x; 
			int next_y = curr_y + input_y; 

			bool checkPlayerMove = checkPosition(next_x, next_y); 

			if(checkPlayerMove) 
			{
				swap(map[curr_y][curr_x], map[next_y][next_x]); 
				player_data.setPositionX(next_x); 
				player_data.setPositionY(next_y);
				player_data.oxyzenCalculator();  
				// player_data.oxygen *= 0.98; Oxygen decrease when player move
			}

			return; 
		}

		int getMapSize() { return mapSize; }
		

};


class ControlManager
{
	private : 
		World game; 
		string file;
		bool playingState; 

	public : 
		ControlManager(string filename) : game(filename), file(filename), playingState(true){};

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
			if(input == 'w' || input =='W') playerMove(0, -1); 
			if(input == 'a' || input =='A') playerMove(-1, 0); 
			if(input == 's' || input =='S') playerMove(0, 1); 
			if(input == 'd' || input =='D') playerMove(1, 0); 

		} 
		
		void playerMove(int x, int y)
		{
			game.playerMove(x, y); 
		} 

		void stateUpdate()
		{
			game.render_screen(); 
		} 

		void restart()
		{
			cout << "Game Restart" << endl; 
			cout << endl; 

			game.mapReset(file); 
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
	// start_splash_screen();
	// startup_routines();
	// char input;

	// // IMPORTANT NOTE: do not exit program without cleanup: freeing allocated dynamic memory etc
	// while (true) // infinite loop, should end with "break" in case of game over or user quitting etc.
	// {
	// 	input = '\0'; // make sure input resetted each cycle
	// 	if(0 > read_input(&input)) break; // exit loop in case input reader returns negative (e.g. user selected "quit")
	// 	update_state(input);
	// 	render_screen();
	// }

	// quit_routines(); // cleanup, bye-bye messages, game save and whatnot
	// return 0;

	string filepath = "Map.txt"; 
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
// void load_level(string filepath) 
// {
// 	// steps in short:
// 	// [Keywords] file I/O, dynamic memory(new keywords), double pointer 
	
// 	// 1) locate, check and open file, if failure, return value indicating error (and check on the calling side)
// 	// 2) read first row, count number of characters. Assuming all maps are rectangular, use this information
// 	//    to memory allocation of global "map" (char ** map) pointer.
// 	//    Assuming first row contains N characters, then you need to allocate 2D table/array of dimensions N x N
// 	//    -> in practice first allocate to "map" an N-long array of (char *) pointers
// 	//        and then within a loop allocate an N-long array of chars to each of the previous entries
// 	//           -> as a result "map" is a pointer to pointer corresponding a 2D-array sized [N][N]
// 	//              and it's each "slot" can be referred to using syntax: map[x][y], each capable of storing a char.
// 	// 3) close file
// 	// 4) return with success value (e.g. zero when OK, negative if error)
// 	// [  5) outside this function, remember to free() allocated memory eventually ]

// 	// player position x, y 좌표 만들기 

// 	FILE* file = NULL;
// 	const char* filename = filepath.c_str(); 
// 	int length = 0; // array size of length 
// 	int currLength = 0; 
// 	int character; 

// 	file = fopen(filename, "r"); 

// 	if(file == NULL) 
// 	{
// 		cout << "File Path Somthing Wrong ... (Check file path)" << endl; 
// 		return; 
// 	}

// 	int curr_charater_size = 0;
// 	string currString  = ""; 

// 	while((character = fgetc(file)) != EOF)
// 	{
// 		if(character == '\r') continue; 
// 		if(character == '\0' || character == '\n')
// 		{
// 			if(currLength == 0 && length == 0)
// 			{
// 				length = curr_charater_size; 
// 				map = new char*[length]; 
// 			}
// 			// 에러 처리 

// 			if(curr_charater_size != length) 
// 			{
// 				cout << "Map data is un-unify ... (check file map)" << endl; 
// 				return;
// 			}
		
// 			map[currLength]  = new char[length + 1]; 
// 			copy(currString.begin(), currString.end(), map[currLength]);
// 			map[currLength][length] = '\0'; 
//  			curr_charater_size = 0; 
// 			currLength += 1;
// 			currString = "";
// 			continue; 
// 		}	
//      	// 읽는 문자 저장하는 변수 
// 		// 문자열 dynamic 으로 문자열 만들어서 문자하나씩 넣어야함 
// 		if(character == 'p' || character == 'P')
// 		{
// 			player_data.poitionX = currString.size(); // 0부터 시작함으로
// 			player_data.poitionY = currLength;
// 		}
// 		currString.push_back(character);
// 		curr_charater_size += 1; 
// 	}

// 	if(currString != "" )
// 	{
// 			map[currLength]  = new char[length + 1]; 
// 			copy(currString.begin(), currString.end(), map[currLength]);
// 			map[currLength][length] = '\0'; 
//  			curr_charater_size = 0; 
// 			currLength += 1;
// 			currString = "";
// 	}

// 	fclose(file); 
// 	cout << "Map Load Complete" << endl; 

// return; 
// }


// /****************************************************************
//  * 
//  * FUNCTION read_input
//  * 
//  * read input from user
//  * 
//  * **************************************************************/
// int read_input(char * input)
// {
// 	cout << ">>>";	// simple prompt
// 	try{
// 		cin >> *input;
// 	}
// 	catch(...){
// 		return -1; // failure
// 	}
// 	cout << endl;  //new line to reset output/input
// 	cin.ignore();  //clear cin to avoid messing up following inputs
// 	if(*input == 'q') return -2; // quitting game...
// 	return 0; // default return, no errors
// }

// /****************************************************************
//  * 
//  * FUNCTION update_state
//  * 
//  * update game state (player, enemies, artefacts, inventories, health, whatnot)
//  * this is a collective entry point to all updates - feel free to divide these many tasks into separate subroutines
//  * 
//  * **************************************************************/
// void update_state(char input)
// {
//   int intend_x = player_data.poitionX;
//   int intend_y = player_data.poitionY;  
//   // input 값이 wasd  중 하나가 입력됨 
//   // w (0, 1), ... Player position 에서 이동 가능 여부 확인 
//   if(input == 'w' || input =='W')
//   { 
// 	intend_x += 0; 
// 	intend_y += (-1);  
//   }

//   if(input == 'a' || input =='A')
//   { 
// 	intend_x += (-1); 
// 	intend_y += 0;  
//   }

//   if(input == 's' || input =='S')
//   { 
// 	intend_x += 0; 
// 	intend_y += 1;  
//   }

//   if(input == 'd' || input =='D')
//   { 
// 	intend_x += 1; 
// 	intend_y += 0;  
//   }

//   playerMove(intend_x, intend_y); 
 
//   //   -> map에서의 위치 해당 위치 저장값 확인 (o -> 해당 위치  o <-> p 교환, x -> 벽으로 이동불가, m -> enemy , 추후 인터렉션 추가 위해 지금 벽처럼 처리)
//   // r , 제시작하는 함수 호출
//   if(input == 'r' ||input == 'R') mapReset(); 
// }


// int mapSize()
// {
// 	int size = 0; 
// 	while(map[0][size] != '\0') size += 1;
// 	return size;  
// }


// int checkPosition(int x_position, int y_position)
// {
// 	// 1: Don't move , 0: Available to move, -1: enemy
// 	int result = -1;
// 	if(map[y_position][x_position] == 'o' || map[y_position][x_position] == 'O') result = 0; 
// 	else if(map[y_position][x_position] == 'x' || map[y_position][x_position] == 'X') result = 1; 
// 	return result; 
// }


// void playerMove(int intend_x, int intend_y)
// {
// 	int checkPlayerMove = checkPosition(intend_x, intend_y); 
// 	int curr_x = player_data.poitionX; 
// 	int curr_y = player_data.poitionY; 

// 	if(checkPlayerMove == 0) 
// 	{
// 		swap(map[curr_y][curr_x], map[intend_y][intend_x]); 
// 		player_data.poitionX = intend_x; 
// 		player_data.poitionY = intend_y; 
// 		// player_data.oxygen *= 0.98; Oxygen decrease when player move
// 	}

// 	if(checkPlayerMove == -1) {} // enemy detect 

// 	return; 
// }


// void mapDelete()
// {
// 	int map_size;
// 	int map_arr_num =0; 
// 	while(map[0][map_arr_num] != '\0')
// 	{
// 		map_arr_num += 1; 
// 	}
// 	map_size = map_arr_num; 

// 	for(int i =0; i <map_size; i++) 
// 	{
// 		delete[] map[i]; 
// 	}

// 	delete[] map; 
// 	map = nullptr; 
// }

// void mapReset()
// {
// 	mapDelete();
// 	startup_routines();
// }

// /****************************************************************
//  * 
//  * FUNCTION render_screen
//  * 
//  * this function prints out all visuals of the game (typically after each time game state updated)
//  * 
//  * **************************************************************/
// void render_screen(void)
// {
// 	// 맵 그리기 
// 	int length = mapSize();

// 	for(int y=0; y < length; y++)
// 	{
// 		for(int x =0; x < length; x++)
// 		{
// 			cout << map[y][x] << " " ;  
// 		}
// 		cout << endl; 
// 	}
// 	cout << endl; 
// }

// /****************************************************************
//  * 
//  * FUNCTION start_splash_screen
//  * 
//  * outputs any data or info at program start
//  * 
//  * **************************************************************/
// void start_splash_screen(void)
// {
// 	/* this function to display any title information at startup, may include instructions or fancy ASCII-graphics */
// 	cout <<endl<< "WELCOME to epic Holy Diver v0.01"<<endl;
// 	cout << "Enter commands and enjoy! (press q to quit at all times)"<<endl<<endl;
// 	cin.ignore();
// }

// /****************************************************************
//  * 
//  * FUNCTION startup_routines
//  * 
//  * Function performs any tasks necessary to set up a game
//  * May contain game load dialogue, new player/game dialogue, level loading, random inits, whatever else
//  * 
//  * At first week, this could be suitable place to load level map.
//  * 
//  * **************************************************************/
// void startup_routines(void)
// {
// 	load_level("Map.txt"); 

// 	// For example if memory allocated here... (*)
// }

// /****************************************************************
//  * 
//  * FUNCTION quit_routines
//  * 
//  * function performs any routines necessary at program shut-down, such as freeing memory or storing data files
//  * 
//  * **************************************************************/
// void quit_routines(void)
// {
	
// 	// (*) ... the memory should be free'ed here at latest.
// 	 mapDelete(); 

// 	cout <<endl<< "BYE! Welcome back soon."<<endl;
// }