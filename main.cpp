#include "ui.h"

int main()
{
	std::cout << std::setiosflags(std::ios::fixed); 
	UI::StartProcedure(); 
	while (true)
	{
		if (!UI::ChooseMode()) break;		//Ñ¡ÔñÄ£Ê½
		switch (mode)
		{
		case modeType::compulsory: 
			//UI::CompulsorySystem(); 
			break; 
		case modeType::optional: 
			UI::OptionalSystem(); 
			break; 
		}
		system("cls"); 
	}
	UI::EndProcedure(); 
	return 0; 
}

