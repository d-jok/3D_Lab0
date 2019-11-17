#pragma once
#include "Command.h";
#include "Parser.h";
#include "STLParser.h";
#include <vector>;
#include <cmath>;


class Sphere : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;

	Sphere();
	~Sphere();

private:
	std::string _name;
	std::string filepath;
	std::vector<double> origin;
	double R;

	std::vector<Vec> vertices;
	std::vector<Vec> normals;
	std::vector<Vertex> triangleSoup;

	void Calculating();
	void vectorNormalize(Vec&);
	double vectorLength(Vec&);
	Vec crossProduct(Vec a, Vec b);
};