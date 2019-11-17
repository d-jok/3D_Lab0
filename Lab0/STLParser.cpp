#include "STLParser.h"

void STLParser::write(const TriangleSoup& triangleSoup, const std::string& filename)
{
	int count = 0;
	std::string name = filename;

	std::cout << std::endl;

	//std::cout << filename;
	std::fstream file;
	file.open(filename);

	if (file.fail()) 
	{
		std::cout << std::endl << "File does not exist. Program had created it. Please restart program";
		std::ofstream outfile(filename);
	}
	else
		std::cout << std::endl << "File exist";

	//file.write("", 0);

	std::ofstream ofs(filename, std::ios::out | std::ios::trunc); // clear contents

	//WRITING INFO IN STL FILE
	file << "solid sphere corner";

	for (int i = 0; i < triangleSoup.size() / 3; i++)
	{
		file << "\n\t" << "facet normal " << triangleSoup[count].normal.x << " " << triangleSoup[count].normal.y << " " << triangleSoup[count].normal.z;
		file << "\n\t\t" << "outer loop";

		for (int j = count; j < count + 3; j++)
		{
			file << "\n\t\t\t" << "vertex " << triangleSoup[j].pos.x << " " << triangleSoup[j].pos.y << " " << triangleSoup[j].pos.z;
		}

		file << "\n\t\t" << "endloop";
		file << "\n\t" << "endfacet";
		count += 3;
	}

	file << "\n" << "endsolid cube corner";

	file.close();
}

TriangleSoup STLParser::read(const std::string& filename)
{
	std::string temp;

	std::fstream file(filename);
	if (file.is_open())
	{
		while (getline(file, temp))
		{
			LineParse(temp);	//NoSpace
		}
	}

	for (int i = 0; i < points.size(); i++)
	{
		params.push_back(Vertex(points[i], normals[i]));
	}
	//std::cout << params[4].pos.x;
	return params;
}

void STLParser::LineParse(std::string input)	//NoSpace
{
	std::string temp;
	std::string point = "vertex";
	std::string normal = "facetnormal";
	std::vector<double> xyz;
	int Check = 0;

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != ' ' && input[i] != '\t' && Check == 0)
		{
			temp += input[i];
		}

		if (temp == normal)
		{
			std::string buf;
			Check = 1;
			i+=2;

			for (int j = i; j <= input.length(); j++)
			{
				if (input[j] != ' ' && j != input.size())
					buf += input[j];
				else
				{
					//std::cout << buf << " ";
					xyz.push_back(std::atof(buf.c_str()));
					buf.clear();
				}
			}
			//std::cout << std::endl;

			normals.push_back(Vec(xyz[0], xyz[1], xyz[2]));
			normals.push_back(Vec(xyz[0], xyz[1], xyz[2]));
			normals.push_back(Vec(xyz[0], xyz[1], xyz[2]));

			//xyz.clear();
			break;
		}

		if (temp == point)
		{
			std::string buf;
			Check = 1;
			i += 2;

			for (int j = i; j <= input.length(); j++)
			{
				if (input[j] != ' ' && j != input.size())
					buf += input[j];
				else
				{
					//std::cout << buf << " ";
					xyz.push_back(std::atof(buf.c_str()));
					buf.clear();
				}
			}
			//std::cout << std::endl;

			points.push_back(Vec(xyz[0], xyz[1], xyz[2]));

			//xyz.clear();
			break;
		}
	}

	//temp.clear();
}