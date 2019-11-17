#include "Cube.h"

Cube::Cube()
{
	_name = "Cube";
}

Cube::~Cube()
{

}

const std::string& Cube::getName() const
{
	return _name;
}

int Cube::execute(const std::map<std::string, std::string>& args)
{
	Parser P;

	std::map<std::string, std::string> params = args;

	//L
	if (P.L_or_R(std::stof(params["L"])) == 1)
		return 1;
	else
		L = std::stof(params["L"]);

	//Origin
	origin = P.Points(params["origin"]);

	//FilePath
	if (P.FilePath(params["filepath"]) == 0)
	{
		filepath = P.AddSlash(params["filepath"]);
	}
	else
		return 2;

	Calculating();

	return 0;
}

void Cube::Calculating()
{
	std::vector<Vec> normal;

	//QUADS
	points.push_back(Vec(origin[0], origin[1], origin[2]));				//0
	points.push_back(Vec(points[0].x + L, points[0].y, points[0].z));	//1
	points.push_back(Vec(points[1].x, points[1].y + L, points[1].z));	//2
	points.push_back(Vec(points[2].x - L, points[2].y, points[2].z));	//3

	points.push_back(Vec(points[1].x, points[1].y, points[1].z - L));	//4
	points.push_back(Vec(points[4].x, points[4].y + L, points[4].z));	//5
	points.push_back(Vec(points[5].x - L, points[5].y, points[5].z));	//6
	points.push_back(Vec(points[6].x, points[6].y - L, points[6].z));	//7
	//----------------------------------------------------------------------

	//FRONT
	triangles.push_back(Vec(points[0].x, points[0].y, points[0].z));	//0
	triangles.push_back(Vec(points[1].x, points[1].y, points[1].z));	//1
	triangles.push_back(Vec(points[2].x, points[2].y, points[2].z));	//2

	triangles.push_back(Vec(points[2].x, points[2].y, points[2].z));	//3
	triangles.push_back(Vec(points[3].x, points[3].y, points[3].z));	//4
	triangles.push_back(Vec(points[0].x, points[0].y, points[0].z));	//5

	//RIGHT
	triangles.push_back(Vec(points[1].x, points[1].y, points[1].z));	//6
	triangles.push_back(Vec(points[4].x, points[4].y, points[4].z));	//7
	triangles.push_back(Vec(points[5].x, points[5].y, points[5].z));	//8

	triangles.push_back(Vec(points[5].x, points[5].y, points[5].z));	//9
	triangles.push_back(Vec(points[2].x, points[2].y, points[2].z));	//10
	triangles.push_back(Vec(points[1].x, points[1].y, points[1].z));	//11

	//BACK
	triangles.push_back(Vec(points[4].x, points[4].y, points[4].z));	//12
	triangles.push_back(Vec(points[7].x, points[7].y, points[7].z));	//13
	triangles.push_back(Vec(points[6].x, points[6].y, points[6].z));	//14

	triangles.push_back(Vec(points[6].x, points[6].y, points[6].z));	//15
	triangles.push_back(Vec(points[5].x, points[5].y, points[5].z));	//16
	triangles.push_back(Vec(points[4].x, points[4].y, points[4].z));	//17

	//LEFT
	triangles.push_back(Vec(points[7].x, points[7].y, points[7].z));	//18
	triangles.push_back(Vec(points[0].x, points[0].y, points[0].z));	//19
	triangles.push_back(Vec(points[3].x, points[3].y, points[3].z));	//20

	triangles.push_back(Vec(points[3].x, points[3].y, points[3].z));	//21
	triangles.push_back(Vec(points[6].x, points[6].y, points[6].z));	//22
	triangles.push_back(Vec(points[7].x, points[7].y, points[7].z));	//23

	//UP
	triangles.push_back(Vec(points[3].x, points[3].y, points[3].z));	//24
	triangles.push_back(Vec(points[2].x, points[2].y, points[2].z));	//25
	triangles.push_back(Vec(points[5].x, points[5].y, points[5].z));	//26

	triangles.push_back(Vec(points[5].x, points[5].y, points[5].z));	//27
	triangles.push_back(Vec(points[6].x, points[6].y, points[6].z));	//28
	triangles.push_back(Vec(points[3].x, points[3].y, points[3].z));	//29

	//DOWN
	triangles.push_back(Vec(points[7].x, points[7].y, points[7].z));	//30
	triangles.push_back(Vec(points[4].x, points[4].y, points[4].z));	//31
	triangles.push_back(Vec(points[1].x, points[1].y, points[1].z));	//32

	triangles.push_back(Vec(points[1].x, points[1].y, points[1].z));	//33
	triangles.push_back(Vec(points[0].x, points[0].y, points[0].z));	//34
	triangles.push_back(Vec(points[7].x, points[7].y, points[7].z));	//35

	for (int i = 0; i < triangles.size(); i += 3)
	{
		Vec A = Vec(triangles[i + 1].x - triangles[i].x, triangles[i + 1].y - triangles[i].y, triangles[i + 1].z - triangles[i].z);
		Vec B = Vec(triangles[i + 2].x - triangles[i + 2].x, triangles[i + 2].y - triangles[i + 2].y, triangles[i + 2].z - triangles[i + 2].z);

		Vec N = crossProduct(A, B);

		normal.push_back(Vec(N));
		normal.push_back(Vec(N));
		normal.push_back(Vec(N));
	}

	for (int i = 0; i < triangles.size(); i++)
	{
		triangleSoup.push_back(Vertex(triangles[i], normal[i]));
	}

	STLParser obj;
	obj.write(triangleSoup, filepath);
}

Vec Cube::crossProduct(Vec A, Vec B)
{
	Vec n;
	n.x = A.y * B.z - A.z * B.y;
	n.y = A.z * B.x - A.x * B.z;
	n.z = A.x * B.y - A.y * B.x;

	double eps = 0.000001;
	vectorNormalize(n);
	/*if(vectorLength(n) < eps)
		n = */

	return n;
}

void Cube::vectorNormalize(Vec &v)
{
	double length;
	length = vectorLength(v);
	double eps = 0.000000001;

	if (length > eps)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
}

double Cube::vectorLength(Vec v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}