#pragma once

#include "World.hpp"

class ControlManager
{
	private : 
		World game; 
		string file;
		bool playingState; 
		int MaxstageLevel = 3; 
		int currStageLevel = 0; 
		int itemNumbers = 3; // items

		/*
		To Do (~24.11.26.)
		[] 게임 승리 조건 ; 교수님께서 아이템 모두 회수 / [내 아이디어] Flag 찾으면 다음 레벨 이동 
		[] 게임 완료시 Map level 이동 / 단 기존 Item, 체력상태 등 Player 요소는 유지되어야 함 
		*/

	public : 
		ControlManager(string filename = "Map/Map0.txt"); 

		void ControlManager::read_input();
 		
		void ControlManager::playerMove(int x, int y); 
		void ControlManager::LightMove(int x, int y);
		void ControlManager::setFilePath();
		void ControlManager::stateUpdate();
		void ControlManager::run();

		void ControlManager::checkStageClear(); // 새로운 스테이지 [아이템은 유지] / 체력, 베터리 초기화, 맵 초기화 
		                                   // 여유가 된다면 screen 메세지, 다음스테이지 넘어갈 건지 물어보는 것 
										   
	   // void ControlManager::stageCompleteUI(); // Complete stage Message
		 
		void ControlManager::restart();
		void ControlManager::end(); 
		bool ControlManager::getPlayingState();

}; 

