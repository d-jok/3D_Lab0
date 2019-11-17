#include "Parser.h";

int Parser::Distributor(int argc, char *argv[])
{
	::Cube cube;
	::Sphere sphere;
	::Split split;

	if (argv[1] == cube.getName())
		return Cube(argc, argv);
	else if(argv[1] == sphere.getName())
		return Sphere(argc, argv);
	else if(argv[1] == split.getName())
		return Split(argc, argv);
}

int Parser::Cube(int argc, char *argv[])
{
	::Cube obj;
	::Parser P;

	std::map<std::string, std::string> temp;

	std::cout << std::endl << "Kill" << std::endl;

	if (argc < 5 || argc > 5)
	{
		std::cout << std::endl << "Err";
		return 3;
	}
	else
	{
		temp = P.makeMap(argc, argv);

		obj.execute(temp);//----
						//     |
		return 0;		//  <---
	}
}

int Parser::Sphere(int argc, char *argv[])
{
	std::cout << std::endl << "KILL KILL";

	::Sphere obj;
	::Parser P;

	std::map<std::string, std::string> temp;

	if (argc < 5 || argc > 5)
	{
		std::cout << std::endl << "Err";
		return 3;
	}
	else
	{
		temp = P.makeMap(argc, argv);
		obj.execute(temp);//----
						//     |
		return 0;		//  <---
	}
}

int Parser::Split(int argc, char *argv[])
{
	std::cout << std::endl << "KILL EVERYONE";

	::Split obj;
	::Parser P;

	std::map<std::string, std::string> temp;

	if (argc != 7)
	{
		std::cout << std::endl << "Err";
		return 3;
	}
	else
	{
		temp = P.makeMap(argc, argv);
		obj.execute(temp);//----
						//     |
		return 0;		//  <---
	}
}

std::map<std::string, std::string> Parser::makeMap(int argc, char *argv[])
{
	::Application app;

	std::string temp;
	std::string before;
	std::string after;

	bool check;

	for (int i = 2; i < argc; i++)
	{
		check = false;

		temp.clear();
		temp = argv[i];

		before.clear();
		after.clear();

		for (int j = 0; j < temp.length(); j++)
		{
			if (temp[j] == '=')
			{
				check = true;
				j++;
			}

			if (check == false)
			{
				if (temp[j] == ',')
				{
					before += ' ';
					j++;
				}

				before += temp[j];
			}
			if (check == true)
			{
				if (temp[j] == ',')
				{
					after += ' ';
					j++;
				}

				after += temp[j];
			}
		}
		std::cout << std::endl << before << " = " << after;
		app.setMap(before, after);
	}

	return app.getMap();
}

int Parser::FilePath(std::string path)
{
	path = NoFile(path);

	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		std::cout << "Wrong Path";
		return 2;
	}
	else
	{
		std::cout << "Path is OK";
		return 0;
	}
		//return false;  //something is wrong with your path!

	/*if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		std::cout << "this is a directory!";*/
		//return true;   // this is a directory!

	//return false;    // this is not a directory!
}

std::string Parser::NoFile(std::string path)
{
	int n = 0;
	int count = 0;
	std::string temp;

	for (int i = 0; i < path.length(); i++)
	{
		if(path[i] == '\\')
			count++;
	}

	for (int i = 0; i < path.length(); i++)
	{
		/*if (path[i] == '\\')
		{
			//temp += '\\';
			n++;
		}*/

		if (n < count)
		{
			temp += path[i];

			if (path[i] == '\\')
			{
				temp += '\\';
				n++;
			}
		}
	}
	std::cout << std::endl << temp << std::endl;

	return temp;
}

std::string Parser::AddSlash(std::string input)
{
	std::string temp;

	for (int i = 0; i < input.length(); i++)
	{
		temp += input[i];

		if (input[i] == '\\')
			temp += '\\';
	}

	return temp;
}

std::vector<double> Parser::Points(std::string points)
{
	std::vector<double> origin;
	std::string temp;

	for (int i = 0; i < points.length() - 2; i++)
	{
		if (points[i] != '(' && points[i] != ')' && points[i] != ' ')
			temp += points[i];

		if (points[i] == ' ' || points[i] == ')')
		{
			origin.push_back(::atof(temp.c_str()));
			temp.clear();
		}			
	}

	/*for (int i = 0; i < origin.size(); i++)
		std::cout << std::endl << origin[i];*/

	return origin;
}

int Parser::L_or_R(double input)
{
	if (input <= 0)
		return 1;
	else
		return 0;
}

double Parser::VectorLength(std::vector<double> input)
{
	return sqrt(pow(input[0], 2) + pow(input[1], 2) + pow(input[2], 2));
}