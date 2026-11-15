#pragma once

#include "World.hpp"

class ControlManager
{
	private : 
		World game; 
		string file;
		bool playingState; 

	public : 
		ControlManager(string filename = "Map2.txt"); 

		void ControlManager::read_input();
 		
		void ControlManager::playerMove(int x, int y); 
		void ControlManager::LightMove(int x, int y);
		void ControlManager::setFilePath();
		void ControlManager::stateUpdate();
		void ControlManager::run();
		 
		void ControlManager::restart();
		void ControlManager::end(); 
		bool ControlManager::getPlayingState();

}; 

// 게임 stage clear , 업데이트 기능 
// 아이템 산소, light 기능 활용 
