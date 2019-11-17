#include "Application.h"
//#include "STLParser.h"
#include "Cube.h"
#include "Sphere.h"
#include "Split.h"
#include <iostream>
#include "conio.h"

int main(int argc, char* argv[])
{
	Application app;

	//std::cout << argv[2];

	app.registerCommand(std::make_unique<Cube>());
	app.registerCommand(std::make_unique<Sphere>());
	app.registerCommand(std::make_unique<Split>());

	//Check instruction!!!!!!
	app.execute(argc, argv);
	_getch();
	return 0;
}