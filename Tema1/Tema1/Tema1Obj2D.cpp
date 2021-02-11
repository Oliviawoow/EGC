#include "Tema1Obj2D.h"

#include <Core/Engine.h>
#include <vector>

// dreptunghi creat din 2 triunghiuri
Mesh* Tema1Obj2D::CreateDreptunghi(std::string name, glm::vec3 leftBottomCorner, float lungime, float latime, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(lungime, 0, 0), color),
		VertexFormat(corner + glm::vec3(lungime, latime, 0), color),
		VertexFormat(corner + glm::vec3(0, latime, 0), color)
	};

	Mesh* dreptunghi = new Mesh(name);
	std::vector<unsigned short> indices = {0, 1, 2, 3};

	if (!fill) {
		dreptunghi->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	dreptunghi->InitFromData(vertices, indices);
	return dreptunghi;
}

// triunghi
Mesh* Tema1Obj2D::CreateTriunghi(std::string name, glm::vec3 leftBottomCorner, float latura, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, latura, 0), color),
		VertexFormat(corner + glm::vec3(latura/2, latura/2, 0), color)
	};

	Mesh* triunghi = new Mesh(name);
	std::vector<unsigned short> indices = {0, 1, 2};

	if (!fill) {
		triunghi->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(1);
	}

	triunghi->InitFromData(vertices, indices);
	return triunghi;
}

// steaua care este creata din 2 triunghiuri urmand mai apoi sa fac in oglinda un obiect asemanator
// ca sa creez steaua propriuzisa
Mesh* Tema1Obj2D::CreateSteluta(std::string name, glm::vec3 center1, float latura, glm::vec3 color, bool fill)
{
	glm::vec3 center = center1;
	float x = 34.64f;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(-x, -latura / 2 - 5, 0), color),
		VertexFormat(center + glm::vec3(-x, latura / 2, 0), color),

		VertexFormat(center + glm::vec3(-latura / 2 - 5, x, 0), color),
		VertexFormat(center + glm::vec3(latura / 2, x, 0), color),
	};

	Mesh* steluta = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

	if (!fill) {
		steluta->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(3);
	}

	steluta->InitFromData(vertices, indices);
	return steluta;
}

// arcul care este creat dintr-un semi-cerc
Mesh* Tema1Obj2D::CreateArc(std::string name, float nr_tring)
{
	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	GLfloat arg;

	vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	for (GLushort i = 0; i < nr_tring; i++)
	{
		arg = 3.2f * i / nr_tring;

		vertices.emplace_back(glm::vec3(cos(arg) * 100, sin(arg) * 50, 0), glm::vec3(0, 0, 0));
		indices.push_back(i);
	}
	indices.push_back(nr_tring);

	Mesh* arc = new Mesh(name);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(5.f);

	arc->SetDrawMode(GL_LINE_LOOP);

	arc->InitFromData(vertices, indices);
	return arc;
}

// balon format dintr-un cerc scalat pe OY ca sa arate a oval
Mesh* Tema1Obj2D::CreateBalon(std::string name, float nr_tring, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	GLfloat arg;

	vertices.emplace_back(color, color);
	for (GLushort i = 0; i < nr_tring; i++)
	{
		arg = 2 * 3.2f * i / nr_tring;

		vertices.emplace_back(glm::vec3(cos(arg) * 50, sin(arg) * 30, 0), color);
		indices.push_back(i);
	}
	indices.push_back(nr_tring);

	Mesh* balon = new Mesh(name);

	balon->SetDrawMode(GL_TRIANGLE_FAN);

	balon->InitFromData(vertices, indices);
	return balon;
}

// cerc
Mesh* Tema1Obj2D::CreateCerc(std::string name, float nr_tring, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	GLfloat arg;

	vertices.emplace_back(color, color);
	for (GLushort i = 0; i < nr_tring; i++)
	{
		arg = 2 * 3.2f * i / nr_tring;

		vertices.emplace_back(glm::vec3(cos(arg) * 20, sin(arg) * 20, 0), color);
		indices.push_back(i);
	}
	indices.push_back(nr_tring);

	Mesh* cerc = new Mesh(name);

	cerc->SetDrawMode(GL_TRIANGLE_FAN);

	cerc->InitFromData(vertices, indices);
	return cerc;
}

// linie
Mesh* Tema1Obj2D::CreateLinie(std::string name, glm::vec3 stanga, glm::vec3 lungime, glm::vec3 color)
{
	glm::vec3 corner = stanga;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + lungime, color),
	};

	Mesh* linie = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1};

	linie->SetDrawMode(GL_LINE_LOOP);

	linie->InitFromData(vertices, indices);
	return linie;
}

