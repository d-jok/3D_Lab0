#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Vec 
{ 
	double x, y, z; 

	Vec() {}

	Vec(double x1, double y1, double z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
};

struct Vertex
{
	Vec pos;
	Vec normal;

	Vertex() {}

	Vertex(Vec p, Vec n)
	{
		pos = p;
		normal = n;
	}
};

using TriangleSoup = std::vector<Vertex>;

class STLParser
{
public:
	TriangleSoup read(const std::string& filename);
	void write(const TriangleSoup& triangleSoup, const std::string& filename);

private:
	std::vector<Vertex> params;
	std::vector<Vec> points;
	std::vector<Vec> normals;

	void LineParse(std::string);	//NoSpace
};