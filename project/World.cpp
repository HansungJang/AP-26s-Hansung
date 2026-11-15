#include "World.hpp"

		void World::checkInitialPosition(char character, int x, int y) // check player, enemies, items initial position in map
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
			if(character == 'l' || character == 'L')
			{
				itemContainer.push_back(make_unique<Battery>(x, y));
			}

			if(character == 'a' || character == 'A')
			{
				itemContainer.push_back(make_unique<Oxygen>(x, y));
			}

		}

		bool World::checkPosition(int next_x, int next_y)
		{
			if(map == nullptr) // check map
			{
				std::cout <<  "Current map is not loaded ... " << endl; 
				return false;  
			}
			
			if(next_x < 0 || next_x >= mapSize // check position bound 
				|| next_y < 0 || next_y >= mapSize)
				{
					std::cout << "Position is Out of Bound ... " << endl;
					return false; 
				} 
  			
			bool canMove = false; 

				if(map[next_y][next_x] == 'o' || map[next_y][next_x] == 'O') canMove = true; 
				if(map[next_y][next_x] == 'm' || map[next_y][next_x] == 'M') canMove = true; 				
				if(map[next_y][next_x] == 'l' || map[next_y][next_x] == 'L') canMove = true; 				
				if(map[next_y][next_x] == 'a' || map[next_y][next_x] == 'A') canMove = true; 				
				if(map[next_y][next_x] == 'x' || map[next_y][next_x] == 'X') canMove = false; 

			return canMove; 
		}


		void World::calculationLightRange(int x, int y)
		{
			if(x < 0 || x >= mapSize || y < 0 || y >= mapSize) return; 
			
			if(lightmap[y][x] == ' ') lightmap[y][x] = map[y][x]; 
			// clalculate vision range size 
			if(y - 1 < 0 || x - 1 <0) return;
				if(lightmap[y][ x-1 ] == ' ' && inBounds(y, x-1)) lightmap[y][x -1 ] = map[y][x-1]; // l
				if(lightmap[y-1][x-1] == ' ' && inBounds(y-1, x-1)) lightmap[y-1][x-1] = map[y-1][x-1]; // lu  
				if(lightmap[y-1][x] == ' ' && inBounds(y-1, x)) lightmap[y-1][x] = map[y-1][x]; // u
			if(y+1 >= mapSize || x+1 >= mapSize) return; 
				if(lightmap[y-1][x+1] == ' ' && inBounds(y-1, x+1)) lightmap[y-1][x+1] = map[y-1][x+1]; // ru
				if(lightmap[y][x+1] == ' ' && inBounds(y, x+1)) lightmap[y][x+1] = map[y][x+1]; // r  
				if(lightmap[y+1][x+1] == ' ' && inBounds(y+1, x+1)) lightmap[y+1][x+1] = map[y+1][x+1]; // rd
				if(lightmap[y+1][x] == ' ' && inBounds(y+1, x)) lightmap[y+1][x] = map[y+1][x]; // d  
				if(lightmap[y+1][x-1] == ' ' && inBounds(y+1, x-1)) lightmap[y+1][x-1] = map[y+1][x-1]; // ld

		}

		void World::checkEnemystate()
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

		void World::initialLightMap()
		{
			if(map == nullptr) return; 
			if(mapSize <= 0 ) return; 
			
			int initialX = player_data.getPositionX();
			int initialY = player_data.getPositionY();
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

		bool World::inBounds(int x, int y)
		{
			return x >= 0 && x < mapSize &&
				y >= 0 && y < mapSize;
		}


		Enemy* World::findEnemy(int x, int y)
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

		Item* World::findItem(int x, int y)
		{
			for(const auto& item : itemContainer)
			{
				if(item->getPositionX() == x && item->getPositionY() == y)
				{
					return item.get(); 
				}
			}
			return nullptr; 
		}

		World::World(string file) : player_data(MAX_HEALTH, MAX_OXYGEN, INIT_LIVES, DEFAULTLIGHTCOUNT), mapSize(0), map(nullptr), isRestart(false)
		{
			start_splash_screen(); 
			enemyContainer.clear(); 
			this->filepath = file; 
			load_level(); 
		}
		
		void World::start_splash_screen(void) 
		{
			cout <<endl<< "WELCOME to epic Holy Diver v0.01"<<endl;
			cout << "Enter commands and enjoy! (press q to quit at all times)"<<endl<<endl;
 		}

		bool World::load_level() // a routine to load a level map from a file
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

				// Item 선언 (container)
				if(character == 'l' || character == 'L') // fixed
				{
					checkInitialPosition('l', currString.size(), currLength);
				}

				if(character == 'a' || character == 'A') // fixed
				{
					checkInitialPosition('a', currString.size(), currLength);
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

		void World::mapDelete() 
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

		void World::gameReset()
		{
			char input; 
			cout << "Are You Sure want to Restart ? [y / n] :  "; 
			cin >> input; 
		
			if(input == 'n' || input == 'N') return; 
			isRestart = true; 
			cin.ignore();


			mapDelete();
			enemyContainer.clear(); 
			itemContainer.clear(); 
			player_data.playerReset();
			if(!load_level()) 
			{
				cout << "Map Load Fail ... " << endl; 
				exit(1);
			}
		}

		void World::filePathChange(string newFile)
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

		void World::render_screen(void)
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

		void World::playerMove(int input_x, int input_y)
		{
			int curr_x = player_data.getPositionX(); 
			int curr_y = player_data.getPositionY(); 
			int next_x = curr_x + input_x; 
			int next_y = curr_y + input_y; 

			bool checkPlayerMove = checkPosition(next_x, next_y); 
			bool checkPlayerState = getPlayerCurrentState(); 

			Enemy* enemy; 
			Item* item; 

			if(map == nullptr || lightmap == nullptr || !checkPlayerState) return;

			player_data.oxyzenCalculator(); // 이동 가능 여부 상관없이 이동 시도 많으로 산소 소비 발생해야 함.
			checkPlayerState = player_data.getIsAlive();
			if(!checkPlayerState) return;

			if(!inBounds(next_x, next_y) || !inBounds(curr_x, curr_y)) return;
			if(!checkPosition(next_x, next_y)) return;
			char target = map[next_y][next_x];

			if (target == 'x' || target == 'X') return;
			// if enemy 충돌 -> damage 연산 호출 (player가 이동한 경우)
			if(target == 'm' || target == 'M') 
			{
				enemy = findEnemy(next_x, next_y);
				player_data.takeDamage(findDamage(next_x, next_y)); 

				if(getPlayerCurrentState()) // player가 살아있는 상태에서만 enemy 위치 update
				{
					// enemy 위치 update 
					enemy->setPositionX(curr_x);
					enemy->setPositionY(curr_y);
				}

			}

			if(target == 'l' || target == 'L' || target == 'a' || target == 'A')
			{
				item = findItem(next_x, next_y); 
				if (item == nullptr){cout << "Current Item is null... " << endl;  return; }
				if(target == 'l' || target == 'L') player_data.useItem(item->getPoint(), 'l');
				if(target == 'a' || target == 'A') player_data.useItem(item->getPoint(), 'a');
				useItem(next_x, next_y); 
				eraseUsedItem(); 

				// 저장이 되도록 수정 필요 
			}

			if(checkPlayerMove && getPlayerCurrentState()) 
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

		void World::LightMove(int input_x, int input_y)
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


		void World::enemyMove()
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
				if(findItem(nextX, nextY) != nullptr) continue; // item이 있는 경우 이동 막음
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

		int World::findDamage(int x, int y)
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

		void World::useItem(int x, int y)
		{
			for(const auto& item : itemContainer)
			{
				int itemPosX = item->getPositionX();
				int itemPosY = item->getPositionY();
				if(itemPosX == x && itemPosY == y)
				{			
					item->setIsused(true); 
					break; 
				}
			}
		}

		void World::eraseUsedItem()
		{
			vector<int> eraseList; 
			int itemindex = 0; 
			for(const auto& item : itemContainer)
			{
				if(item->getIsused()) 
				{
					int itemPosX = item->getPositionX();
					int itemPosY = item->getPositionY();	
					map[itemPosY][itemPosX] = 'o'; 
					lightmap[itemPosY][itemPosX] = 'o'; 
					eraseList.push_back(itemindex); 
					itemindex++; 
 					// item pop or erase 되어야함 
				}
			}

			for(int i =0 ; i < eraseList.size(); i++)
			{
				itemContainer.erase(itemContainer.begin() + eraseList[i]); 
			}

			eraseList.clear(); 
		}

		bool World::checkCollideEnemy(int playerX, int playerY, int enemyX, int enemyY)
		{
			bool collide = false; 

			if(playerX == enemyX && playerY == enemyY) collide = true; 

			return collide; 
		}

		void World::updateCurrentState()
		{
		   for(int i = 0;  i < mapSize; i++)
		   {
				for(int j =0; j < mapSize; j++)
				{
					if(lightmap[i][j] != ' '){lightmap[i][j] = map[i][j];}
				}
		   }
		}

		int World::getMapSize() { return mapSize; }
		bool World::getPlayerCurrentState() {return player_data.getIsAlive();}
		