#include "Sphere.h";

Sphere::Sphere()
{
	_name = "Sphere";
}

Sphere::~Sphere()
{

}

const std::string& Sphere::getName() const
{
	return _name;
}

int Sphere::execute(const std::map<std::string, std::string>& args)
{
	Parser P;

	std::map<std::string, std::string> params = args;

	//R
	if (P.L_or_R(std::stof(params["R"])) == 1)
		return 1;
	else
		R = std::stof(params["R"]);

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

void Sphere::Calculating()
{
	const double PI = 3.14159265;
	
	int sectorCount = 40;
	int stackCount = 40;

	double x, y, z, xy;                         // vertex position
	double nx, ny, nz, lengthInv = 1.0f / R;    // vertex normal

	double sectorStep = 2 * PI / sectorCount;
	double stackStep = PI / stackCount;
	double sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = R * cosf(stackAngle);             // r * cos(u)          

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = (xy * cosf(sectorAngle)) + origin[0];             // r * cos(u) * cos(v)
			y = (xy * sinf(sectorAngle)) + origin[1];             // r * cos(u) * sin(v)
			z = (R * sinf(stackAngle)) + origin[2];				// r * sin(u)
			vertices.push_back(Vec(y, z, x));	

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back(Vec(ny, nz, nx));
		}
	}

	std::vector<int> indices;
	int k1, k2;

	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	//TriangleSoup
	for (int i = 0; i < indices.size(); i++)
		triangleSoup.push_back(Vertex(vertices[indices[i]], normals[indices[i]]));

	STLParser obj;
	obj.write(triangleSoup, filepath);
}