#include "ui.h"

int main()
{
	std::cout << std::setiosflags(std::ios::fixed); 
	UI::StartProcedure(); 
	UI ui; 
	while (true) if (!ui.Run()) break;		//Ñ­»·ÔËĞĞ
	UI::EndProcedure(); 
	return 0; 
}

