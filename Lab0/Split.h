#pragma once
#include "Command.h";
#include "Parser.h";
#include "STLParser.h";
#include <vector>;
#include <iostream>;

class Split : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;

	Split();
	~Split();

private:
	int checkAB = 0;
	int countZERO = 0;
	int zero = 0, up = 0, down = 0;
	double m, n, p;
	double x, y, z;
	double t, D;

	Vertex PerPoint1;
	Vertex PerPoint2;

	std::string _name;

	std::string filepath;
	std::string output1;
	std::string output2;

	std::vector<double> origin;
	std::vector<double> direction;
	std::vector<Vertex> AB;
	std::vector<Vertex> triangleSoup, A, B;
	std::vector<Vertex> PointsOnPlane;


	void Calculating();
	void Case1(Vertex, Vertex, Vertex);
	void Case2(Vertex, Vertex, Vertex);
	void NoHole();
	void VertexOnPlane(Vertex);

	int CheckPositionPoint(Vertex);
	double Plane(Vec);	//Plane Equation
	Vec Intersection(Vec, Vec);

	void Normals();
	void vectorNormalize(Vec&);
	Vec crossProduct(Vec, Vec);
	double vectorLength(Vec);
};