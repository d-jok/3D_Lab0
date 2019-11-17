#pragma once
#include "Command.h"
#include "Parser.h"

class Application
{
public:
	void registerCommand(std::unique_ptr<Command> command);
	int execute(int argc, char *argv[]);

	std::map<std::string, std::string> getMap();
	void setMap(std::string, std::string);

private:
	std::map<std::string, std::unique_ptr<Command>> _commands;
	std::map<std::string, std::string> params;
};