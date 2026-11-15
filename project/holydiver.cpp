#include "GameManager.hpp"

int main (void)
{
    srand(time(0)); // for random move generate seed value; 

	ControlManager controller; 
	controller.run();

	return 0; 

}