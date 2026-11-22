#include "GameManager.hpp"



		ControlManager::ControlManager(string filename) : game(filename), file(filename), playingState(true)
		{
			setFilePath(); 
			game.flagRandomPlace(); 
			game.itemRandomPlace(itemNumbers); 
			game.render_screen(); 
		};

		void ControlManager::read_input()
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

				// item use : 'U' / 'u' 
				if(input == 'u' || input == 'U') game.chooseItem(); 

			}


		} 
		
		void ControlManager::playerMove(int x, int y)
		{
			game.playerMove(x, y); 
		} 

		void ControlManager::LightMove(int x, int y)
		{
			game.LightMove(x, y); 
		} 

		void ControlManager::setFilePath()
		{
			string filepath; 
			cout << "Insert File path (defalut : Map0.txt): "; 

			if (!getline(cin, filepath) || filepath == "Map/Map0.txt" || filepath == "map2.txt" || filepath.empty()) return;
			file = filepath;
			game.filePathChange(file);
		}

		void ControlManager::stateUpdate()
		{
			game.enemyMove(); 
			game.updateCurrentState(); 
			game.render_screen(); 
			checkStageClear(); 
		} 

		void ControlManager::run()
		{
			while(true)
			{
				read_input(); 
				if(!playingState) break; 
				stateUpdate(); 
			}
		}

		void ControlManager::restart()
		{
			cout << "Game Restart" << endl; 
			cout << endl; 

			game.gameReset(); 
		}

		void ControlManager::checkStageClear()
		{
			if(!game.getStageClear()) return; 
			

			int input;
			int currlevel = game.getCurrStagelevel();
			
			cout << endl << endl; 
			cout << "\t Congrats You Complete Stage #" << currlevel << " \t" << endl << endl; 

			cout << "\t Do You Want To Play Next Stage ? [0 : Yes, 1 : No] :";
			cin >> input; 
			cin.ignore();
			
			if(currlevel >= MaxstageLevel || input >= 1) 
			{
				if(currlevel >= MaxstageLevel) cout << "You complete All Stages!!" << endl; 
				cout << "Thank You For Playing!" << endl; 
				end(); 
				return ; 
			}

			if(input == 0)
			{ 
				game.checkstageClear();
				game.stageUpgrade(); 
			}
			
		}

		void ControlManager::end()
		{ 
			playingState = false; 
			game.mapDelete(); 
			cout <<endl<< "BYE! Welcome back soon."<<endl;

			return; 
		}

		bool ControlManager::getPlayingState()
		{
			return playingState; 
		}



