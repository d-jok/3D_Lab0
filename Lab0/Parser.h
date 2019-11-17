#pragma once
#include "Cube.h"
#include "Sphere.h"
#include "Split.h"
#include "Application.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Windows.h"

class Parser
{
public:
	std::string AddSlash(std::string);
	int L_or_R(double);
	double VectorLength(std::vector<double>);
	std::map<std::string, std::string> makeMap(int argc, char *argv[]);

	static int Distributor(int argc, char *argv[]);
	static int Cube(int argc, char *argv[]);
	static int Sphere(int argc, char *argv[]);
	static int Split(int argc, char *argv[]);
	static int FilePath(std::string);
	static std::string NoFile(std::string);
	static std::vector<double> Points(std::string);

	std::map<std::string, std::string> args;
};