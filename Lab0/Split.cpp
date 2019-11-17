#include "Split.h";

Split::Split()
{
	_name = "Split";
}

Split::~Split()
{
}

const std::string& Split::getName() const
{
	return _name;
}

int Split::execute(const std::map<std::string, std::string>& args)
{
	Parser P;
	STLParser STL;
	std::map<std::string, std::string> params = args;

	filepath = P.AddSlash(params["input"]);

	std::fstream file;
	file.open(filepath);

	//Input file exist
	if (file.fail())
	{
		std::cout << std::endl << "Input file does not exist.";
		return 2;
	}
	else
		std::cout << std::endl << "File exist";

	//Origin
	origin = P.Points(params["origin"]);

	//Direction
	if (P.VectorLength(P.Points(params["direction"])) <= 0)
	{
		return 1;
	}
	else
		direction = P.Points(params["direction"]);

	//std::cout << params["output1"];

	//OUTPUT1
	if (P.FilePath(params["output1"]) == 0)
	{
		output1 = P.AddSlash(params["output1"]);
	}
	else
		return 2;

	//OUTPUT2
	if (P.FilePath(params["output2"]) == 0)
	{
		output2 = P.AddSlash(params["output2"]);
	}
	else
		return 2;

	std::cout << std::endl << "Waiting..." << std::endl;

	triangleSoup = STL.read(filepath);

	std::cout << "Ready" << std::endl;
	//std::cout << triangleSoup[120].normal.z;

	Calculating();
	NoHole();
	Normals();

	//Write To STL
	STL.write(A, output1);
	STL.write(B, output2);

	return 0;
}

void Split::Calculating()
{
	std::vector<double> P;
	std::vector<Vec> temp;
	std::vector<Vec> intersectionPoints;

	for (int i = 0; i < triangleSoup.size(); i += 3)
	{
		up = 0; zero = 0; down = 0;

		for (int j = i; j < i + 3; j++)
		{
			CheckPositionPoint(triangleSoup[j]);
		}

		if (zero == 3)
		{
			A.push_back(Vertex(triangleSoup[i].pos, triangleSoup[i].normal));
			A.push_back(Vertex(triangleSoup[i + 1].pos, triangleSoup[i + 1].normal));
			A.push_back(Vertex(triangleSoup[i + 2].pos, triangleSoup[i + 2].normal));

			B.push_back(Vertex(triangleSoup[i].pos, triangleSoup[i].normal));
			B.push_back(Vertex(triangleSoup[i + 1].pos, triangleSoup[i + 1].normal));
			B.push_back(Vertex(triangleSoup[i + 2].pos, triangleSoup[i + 2].normal));
		}

		if ((up == 3) || ((zero == 2) && (up == 1)) || ((zero == 1) && (up == 2)))
		{
			A.push_back(Vertex(triangleSoup[i].pos, triangleSoup[i].normal));
			A.push_back(Vertex(triangleSoup[i + 1].pos, triangleSoup[i + 1].normal));
			A.push_back(Vertex(triangleSoup[i + 2].pos, triangleSoup[i + 2].normal));
		}

		if ((down == 3) || ((zero == 2) && (down == 1)) || ((zero == 1) && (down == 2)))
		{
			B.push_back(Vertex(triangleSoup[i].pos, triangleSoup[i].normal));
			B.push_back(Vertex(triangleSoup[i + 1].pos, triangleSoup[i + 1].normal));
			B.push_back(Vertex(triangleSoup[i + 2].pos, triangleSoup[i + 2].normal));
		}

		if ((zero == 1) && (up == 1) && (down == 1))
		{
			Case1(triangleSoup[i], triangleSoup[i + 1], triangleSoup[i + 2]);
		}

		if (((up == 1) && (down == 2)) || ((up == 2) && (down == 1)))
		{
			Case2(triangleSoup[i], triangleSoup[i + 1], triangleSoup[i + 2]);
		}
	}

	//for(int i = 0; i < )
}

void Split::Case1(Vertex point1, Vertex point2, Vertex point3)
{
	if (CheckPositionPoint(point1) == 0)
	{
		//Intersection(point2.pos, point3.pos);	//point2, point3
		
		PerPoint1 = Vertex(Intersection(point3.pos, point2.pos), point1.normal);
		//PerPoint1.normal = point1.normal;

		if (CheckPositionPoint(point2) == 1)
		{
			A.push_back(Vertex(point2.pos, point2.normal));
			A.push_back(Vertex(point1.pos, point1.normal));
			A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

			B.push_back(Vertex(point3.pos, point3.normal));
			B.push_back(Vertex(point1.pos, point1.normal));
			B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
		}
		else
		{
			A.push_back(Vertex(point3.pos, point3.normal));
			A.push_back(Vertex(point1.pos, point1.normal));
			A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

			B.push_back(Vertex(point2.pos, point2.normal));
			B.push_back(Vertex(point1.pos, point1.normal));
			B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
		}
		VertexOnPlane(PerPoint1);

	}
	else

		if (CheckPositionPoint(point2) == 0)
		{
			//point3, point1
			PerPoint1 = Vertex(Intersection(point1.pos, point3.pos), point1.normal);

			if (CheckPositionPoint(point1) == 1)
			{
				A.push_back(Vertex(point1.pos, point1.normal));
				A.push_back(Vertex(point2.pos, point2.normal));
				A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

				B.push_back(Vertex(point3.pos, point3.normal));
				B.push_back(Vertex(point2.pos, point2.normal));
				B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
			}
			else
			{
				A.push_back(Vertex(point3.pos, point3.normal));
				A.push_back(Vertex(point2.pos, point2.normal));
				A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

				B.push_back(Vertex(point1.pos, point1.normal));
				B.push_back(Vertex(point2.pos, point2.normal));
				B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
			}
			VertexOnPlane(PerPoint1);
		}
		else
			if (CheckPositionPoint(point3) == 0)
			{
				PerPoint1 = Vertex(Intersection(point1.pos, point2.pos), point1.normal);

				if (CheckPositionPoint(point1) == 1)
				{
					A.push_back(Vertex(point1.pos, point1.normal));
					A.push_back(Vertex(point3.pos, point3.normal));
					A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

					B.push_back(Vertex(point2.pos, point2.normal));
					B.push_back(Vertex(point3.pos, point3.normal));
					B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
				}
				else
				{
					A.push_back(Vertex(point2.pos, point2.normal));
					A.push_back(Vertex(point3.pos, point3.normal));
					A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

					B.push_back(Vertex(point1.pos, point1.normal));
					B.push_back(Vertex(point3.pos, point3.normal));
					B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
				}
				//PointsOnPlane.push_back(PerPoint1);
				VertexOnPlane(PerPoint1);
			}
}

void Split::Case2(Vertex point1, Vertex point2, Vertex point3)
{
	if ((CheckPositionPoint(point1) == 1) && (CheckPositionPoint(point2) == -1) && (CheckPositionPoint(point3) == -1))
	{
		PerPoint1 = Vertex(Intersection(point1.pos, point2.pos), point1.normal);		
		PerPoint2 = Vertex(Intersection(point1.pos, point3.pos), point1.normal);

		A.push_back(Vertex(point1.pos, point1.normal));
		A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
		A.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));

		B.push_back(Vertex(point2.pos, point2.normal));
		B.push_back(Vertex(point3.pos, point3.normal));
		B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

		B.push_back(Vertex(point3.pos, point3.normal));
		B.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));
		B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

		/*PointsOnPlane.push_back(PerPoint1);
		PointsOnPlane.push_back(PerPoint2);*/
		VertexOnPlane(PerPoint1);
		VertexOnPlane(PerPoint2);

		if (checkAB == 0)
		{
			AB.push_back(PerPoint1);
			AB.push_back(PerPoint2);

			checkAB = 1;
		}
	}
	else
		if ((CheckPositionPoint(point1) == -1) && (CheckPositionPoint(point2) == 1) && (CheckPositionPoint(point3) == 1))
		{
			PerPoint1 = Vertex(Intersection(point3.pos, point1.pos), point3.normal);
			PerPoint2 = Vertex(Intersection(point2.pos, point1.pos), point2.normal);

			B.push_back(Vertex(point1.pos, point1.normal));
			B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
			B.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));

			A.push_back(Vertex(point3.pos, point3.normal));
			A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
			A.push_back(Vertex(point2.pos, point2.normal));

			A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
			A.push_back(Vertex(point2.pos, point2.normal));
			A.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));

			/*PointsOnPlane.push_back(PerPoint1);
			PointsOnPlane.push_back(PerPoint2);*/
			VertexOnPlane(PerPoint1);
			VertexOnPlane(PerPoint2);

			if (checkAB == 0)
			{
				AB.push_back(PerPoint1);
				AB.push_back(PerPoint2);

				checkAB = 1;
			}
		}
	//Duo

	if ((CheckPositionPoint(point1) == -1) && (CheckPositionPoint(point2) == 1) && (CheckPositionPoint(point3) == -1))
	{
		PerPoint1 = Vertex(Intersection(point2.pos, point1.pos), point2.normal);
		PerPoint2 = Vertex(Intersection(point2.pos, point3.pos), point2.normal);

		A.push_back(Vertex(point2.pos, point2.normal));
		A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
		A.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));

		B.push_back(Vertex(point1.pos, point1.normal));
		B.push_back(Vertex(point3.pos, point3.normal));
		B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

		B.push_back(Vertex(point3.pos, point3.normal));
		B.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));
		B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

		/*PointsOnPlane.push_back(PerPoint1);
		PointsOnPlane.push_back(PerPoint2);*/
		VertexOnPlane(PerPoint1);
		VertexOnPlane(PerPoint2);

		if (checkAB == 0)
		{
			AB.push_back(PerPoint1);
			AB.push_back(PerPoint2);

			checkAB = 1;
		}
	}
	else
		if ((CheckPositionPoint(point1) == 1) && (CheckPositionPoint(point2) == -1) && (CheckPositionPoint(point3) == 1))
		{
			PerPoint1 = Vertex(Intersection(point1.pos, point2.pos), point1.normal);
			PerPoint2 = Vertex(Intersection(point3.pos, point2.pos), point3.normal);

			B.push_back(Vertex(point2.pos, point2.normal));
			B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
			B.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));

			A.push_back(Vertex(point1.pos, point1.normal));
			A.push_back(Vertex(point3.pos, point3.normal));
			A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

			A.push_back(Vertex(point3.pos, point3.normal));
			A.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));
			A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

			/*PointsOnPlane.push_back(PerPoint1);
			PointsOnPlane.push_back(PerPoint2);*/
			VertexOnPlane(PerPoint1);
			VertexOnPlane(PerPoint2);

			if (checkAB == 0)
			{
				AB.push_back(PerPoint1);
				AB.push_back(PerPoint2);

				checkAB = 1;
			}
		}

	//Uno

	if ((CheckPositionPoint(point1) == -1) && (CheckPositionPoint(point2) == -1) && (CheckPositionPoint(point3) == 1))
	{
		PerPoint1 = Vertex(Intersection(point3.pos, point1.pos), point3.normal);
		PerPoint2 = Vertex(Intersection(point3.pos, point2.pos), point3.normal);

		A.push_back(Vertex(point3.pos, point3.normal));
		A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
		A.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));

		B.push_back(Vertex(point1.pos, point1.normal));
		B.push_back(Vertex(point2.pos, point2.normal));
		B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

		B.push_back(Vertex(point2.pos, point2.normal));
		B.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));
		B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

		/*PointsOnPlane.push_back(PerPoint1);
		PointsOnPlane.push_back(PerPoint2);*/
		VertexOnPlane(PerPoint1);
		VertexOnPlane(PerPoint2);

		if (checkAB == 0)
		{
			AB.push_back(PerPoint1);
			AB.push_back(PerPoint2);

			checkAB = 1;
		}
	}
	else
		if ((CheckPositionPoint(point1) == 1) && (CheckPositionPoint(point2) == 1) && (CheckPositionPoint(point3) == -1))
		{
			PerPoint1 = Vertex(Intersection(point1.pos, point3.pos), point1.normal);
			PerPoint2 = Vertex(Intersection(point2.pos, point3.pos), point2.normal);

			B.push_back(Vertex(point3.pos, point3.normal));
			B.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));
			B.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));

			A.push_back(Vertex(point1.pos, point1.normal));
			A.push_back(Vertex(point2.pos, point2.normal));
			A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

			A.push_back(Vertex(point2.pos, point2.normal));
			A.push_back(Vertex(PerPoint2.pos, PerPoint2.normal));
			A.push_back(Vertex(PerPoint1.pos, PerPoint1.normal));

			/*PointsOnPlane.push_back(PerPoint1);
			PointsOnPlane.push_back(PerPoint2);*/
			VertexOnPlane(PerPoint1);
			VertexOnPlane(PerPoint2);

			if (checkAB == 0)
			{
				AB.push_back(PerPoint1);
				AB.push_back(PerPoint2);

				checkAB = 1;
			}
		}
}

void Split::NoHole()
{
	struct SortAngle
	{
		Vec pos;
		Vec normal;
		double angle;

		SortAngle() {}
		SortAngle(Vec a, Vec b, double c)
		{
			pos = a;
			normal = b;
			angle = c;
		}
	};

	bool check;
	std::vector<Vertex> temp;

	std::cout << std::endl << "AB: " << AB.size() << std::endl;
	std::cout << std::endl << "AB: " << AB[0].pos.x << " " << AB[0].pos.y << " " << AB[0].pos.z << std::endl;
	std::cout << std::endl << "AB: " << AB[1].pos.x << " " << AB[1].pos.y << " " << AB[1].pos.z << std::endl;

	temp = PointsOnPlane;

	double x = 0, y = 0, z = 0;
	Vertex center;	
	for (int i = 0; i < temp.size(); i++)
	{
		x += temp[i].pos.x;
		y += temp[i].pos.y;
		z += temp[i].pos.z;
	}

	center = Vertex(Vec(x / temp.size(), y / temp.size(), z / temp.size()), Vec(0, 0, 0));

	//std::vector<Vertex> minL;
	double length = 0;
	double lengthTemp = 0;

	std::vector<SortAngle> S;

	Vec vA = Vec(AB[1].pos.x - AB[0].pos.x, AB[1].pos.y - AB[0].pos.y, AB[1].pos.z - AB[0].pos.z);

	//S.push_back(SortAngle(AB[0].pos, AB[0].normal, 0));
	S.push_back(SortAngle(AB[1].pos, AB[1].normal, 0));

	for (int i = 0; i < temp.size(); i++)
	{
		if ((temp[i].pos.x != AB[1].pos.x || temp[i].pos.y != AB[1].pos.y || temp[i].pos.z != AB[1].pos.z) &&
			(temp[i].pos.x != AB[0].pos.x || temp[i].pos.y != AB[0].pos.y || temp[i].pos.z != AB[0].pos.z))
		{
			Vec vB = Vec(temp[i].pos.x - AB[0].pos.x, temp[i].pos.y - AB[0].pos.y, temp[i].pos.z - AB[0].pos.z);

			double COSangle = ((vA.x * vB.x) + (vA.y * vB.y) + (vA.z * vB.z)) / (sqrt(pow(vA.x, 2) + pow(vA.y, 2) + pow(vA.z, 2)) *
				sqrt(pow(vB.x, 2) + pow(vB.y, 2) + pow(vB.z, 2)));
			S.push_back(SortAngle(temp[i].pos, temp[i].normal, acos(COSangle)));
			//std::cout << COSangle << std::endl;
		}
	}

	

	SortAngle T;
	for (int i = 2; i < S.size() - 1; i++)
	{
		for (int j = 2; j < S.size() - 1; j++)
		{
			if (S[j].angle > S[j + 1].angle)
			{
				T = SortAngle(S[j].pos, S[j].normal, S[j].angle);
				S[j] = S[j + 1];
				S[j + 1] = T;
			}
		}
	}

	S.push_back(SortAngle(AB[0].pos, AB[0].normal, 0));

	/*std::cout << std::endl << "SORT:" << std::endl;
	for (int i = 0; i < S.size(); i++)
	{
		std::cout << S[i].angle << std::endl;
		std::cout << S[i].pos.x << " " << S[i].pos.y << " " << S[i].pos.z << std::endl;
	}*/

	A.push_back(Vertex(AB[1].pos, AB[1].normal));
	A.push_back(Vertex(center.pos, center.normal));
	A.push_back(Vertex(AB[0].pos, AB[0].normal));

	B.push_back(Vertex(AB[0].pos, AB[0].normal));
	B.push_back(Vertex(center.pos, center.normal));
	B.push_back(Vertex(AB[1].pos, AB[1].normal));

	for (int i = 1; i < S.size(); i++)
	{
		A.push_back(Vertex(S[i].pos, S[i].normal));
		A.push_back(Vertex(center.pos, center.normal));
		A.push_back(Vertex(S[i - 1].pos, S[i - 1].normal));

		B.push_back(Vertex(S[i - 1].pos, S[i - 1].normal));
		B.push_back(Vertex(center.pos, center.normal));
		B.push_back(Vertex(S[i].pos, S[i].normal));
	}

	/*A.push_back(Vertex(S[0].pos, S[0].normal));
	A.push_back(Vertex(center.pos, center.normal));
	A.push_back(Vertex(S[S.size() - 1].pos, S[S.size() - 1].normal));

	B.push_back(Vertex(S[S.size() - 1].pos, S[S.size() - 1].normal));
	B.push_back(Vertex(center.pos, center.normal));
	B.push_back(Vertex(S[0].pos, S[0].normal));*/
}

//Plane Equation
double Split::Plane(Vec input)
{
	return direction[0] * (input.x - origin[0]) + direction[1] * (input.y - origin[1]) + direction[2] * (input.z - origin[2]);
}

int Split::CheckPositionPoint(Vertex point)
{
	if (Plane(point.pos) > 0)
	{
		up++;
		return 1;
	}

	if (Plane(point.pos) == 0)
	{
		zero++;
		VertexOnPlane(point);

		if (countZERO < 2)
		{
			AB.push_back(point);
			countZERO++;
		}

		return 0;
	}

	if (Plane(point.pos) < 0)
	{
		down++;
		return -1;
	}	
}

Vec Split::Intersection(Vec a, Vec b)
{
	double t;
	double x, y, z;
	double x0 = origin[0], y0 = origin[1], z0 = origin[2];
	double A = direction[0], B = direction[1], C = direction[2];

	m = b.x - a.x; 
	n = b.y - a.y; 
	p = b.z - a.z;

	D = -((A * x0) + (B * y0) + (C * z0));

	t = -(((A*a.x) + (B*a.y) + (C*a.z) + D) / ((A*m) + (B*n) + (C*p)));

	//std::cout << t << std::endl;

	x = (m * t) + a.x;
	y = (n * t) + a.y;
	z = (p * t) + a.z;

	//Vec point = Vec(x, y, z);

	return Vec(x, y, z);
}

void Split::VertexOnPlane(Vertex point)
{
	int count = 0;

	for (int i = 0; i < PointsOnPlane.size(); i++)
	{
		if ((point.pos.x == PointsOnPlane[i].pos.x) && (point.pos.y == PointsOnPlane[i].pos.y) && (point.pos.z == PointsOnPlane[i].pos.z))
			count++;
	}

	if (count == 0)
		PointsOnPlane.push_back(point);
}

void Split::Normals()
{
	for (int i = 0; i < A.size(); i += 3)
	{
		Vec P = Vec(A[i + 1].pos.x - A[i].pos.x, A[i + 1].pos.y - A[i].pos.y, A[i + 1].pos.z - A[i].pos.z);
		Vec L = Vec(A[i + 2].pos.x - A[i + 2].pos.x, A[i + 2].pos.y - A[i + 2].pos.y, A[i + 2].pos.z - A[i + 2].pos.z);

		Vec N = crossProduct(P, L);

		A[i] = Vertex(A[i].pos, N);
		A[i + 1] = Vertex(A[i + 1].pos, N);
		A[i + 2] = Vertex(A[i + 2].pos, N);
	}
	for (int i = 0; i < B.size(); i += 3)
	{
		Vec P = Vec(B[i + 1].pos.x - B[i].pos.x, B[i + 1].pos.y - B[i].pos.y, B[i + 1].pos.z - B[i].pos.z);
		Vec L = Vec(B[i + 2].pos.x - B[i + 2].pos.x, B[i + 2].pos.y - B[i + 2].pos.y, B[i + 2].pos.z - B[i + 2].pos.z);

		Vec N = crossProduct(P, L);

		B[i] = Vertex(B[i].pos, N);
		B[i + 1] = Vertex(B[i + 1].pos, N);
		B[i + 2] = Vertex(B[i + 2].pos, N);
	}
}

Vec Split::crossProduct(Vec A, Vec B)
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

void Split::vectorNormalize(Vec &v)
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

double Split::vectorLength(Vec v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}