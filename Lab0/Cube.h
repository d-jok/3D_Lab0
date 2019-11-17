#pragma once
#include "Command.h";
#include "Parser.h";
#include "STLParser.h"
#include <Vector>;
#include <iostream>;

/*struct Vec 
{ 
	double x, y, z; 

	Vec(double x1, double y1, double z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
};*/

class Cube : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;

	Cube();
	~Cube();

private:
	std::string _name;
	std::vector<double> origin;
	std::string filepath;
	double L;

	std::vector<Vec> points;
	std::vector<Vec> triangles;
	std::vector<Vertex> triangleSoup;

	void Calculating();
	void vectorNormalize(Vec&);
	Vec crossProduct(Vec, Vec);
	double vectorLength(Vec);
};