#include "Application.h"
#include <iostream>

void Application::registerCommand(std::unique_ptr<Command> command)
{
	_commands.insert(std::make_pair(command->getName(), std::move(command)));
}

int Application::execute(int argc, char *argv[])
{
	std::string temp;

	if (argc == 1) { // если в аргументах только имя программы
		std::cout << "no arguments!" << std::endl; // выводим, что нет аргументов
	}
	else 
	{
		// иначе выводим все аргументы, которые переданы
		for (int i = 0; i < argc; i++) 
		{
			std::cout << "argv[" << i << "] - " << argv[i] << std::endl;
		}
	}

	if (_commands.find(argv[1]) == _commands.end())
		std::cout << "Command not found";
	else
	{
		std::cout << "Command was found";

		Parser::Distributor(argc, argv);

		//std::cout << params["origin"];

		for (int i = 1; i < argc; i++)
		{
			temp += argv[i];
			temp += " ";
		}
	}
	//std::cout << std::endl << _commands["Cube"]->getName();

	return 0;
}


std::map<std::string, std::string> Application::getMap()
{
	return params;
}

void Application::setMap(std::string before, std::string after)
{
	params.insert(std::make_pair(before, after));
}