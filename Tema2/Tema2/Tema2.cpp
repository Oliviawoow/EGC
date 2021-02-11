#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

#include <Core/Engine.h>
#include "Tema2_Transform3D.h"
#include "Tema2_Camera.h"
#include "Tema2_Platforma.h"

using namespace std;

Tema2::Tema2()
{
	jump = false;
	power = false;
	time = 0;
	timeVerde = 0;
	inc = 5;
	picatVerde = false;
	changeCamera = false;
	picat = false;
	timp = 0;
	timeJump = 0;
	culoareViteza = glm::vec3(0.8, 0.6, 0.5);
	culoareViata = glm::vec3(0.8, 0.2, 0.4);
	viata = 3;
	scale_nolife = 0;

	// sfera
	translateX_sphere = 0;
	translateY_sphere = 0;
	translateZ_sphere = 0;
	scaleX_sphere = 1;
	scaleY_sphere = 1;
	scaleZ_sphere = 1;

	// platforma
	x1 = 0;
	y = -0.45;
	z1 = -7;
	x2 = 2;
	z2 = -5;
	x3 = -2;
	z3 = -9;
	scaleX_box = 0.7;
	scaleY_box = 0.1;
	scaleZ_box = 5;
	culoare_box = 1;

	// bara combustibil
	translateX_bara = -3.5;
	translateY_bara = 3.5;
	translateZ_bara = 0;
	scaleX_bara = 3;
	scaleY_bara = 0.5;
	scaleZ_bara = 0;

	translateX_combustibil = translateX_bara + 0.05 - 1.40;
	translateY_combustibil = translateY_bara - 0.05 + 0.2;
	translateZ_combustibil = translateZ_bara + 0.1;
	scaleX_combustibil = scaleX_bara - 0.15;
	scaleY_combustibil = scaleY_bara - 0.1;
	scaleZ_combustibil = scaleZ_bara;
	scaleX_viteza = scaleX_bara - 2.5;
	scaleY_viteza = scaleY_bara - 0.1;
	scaleZ_viteza = scaleZ_bara;
	scaleX_viata1 = 0.5;
	scaleY_viata1 = 0.5;
	scaleZ_viata1 = 0;
	scaleX_viata2 = 0.5;
	scaleY_viata2 = 0.5;
	scaleZ_viata2 = 0;
	scaleX_viata3 = 0.5;
	scaleY_viata3 = 0.5;
	scaleZ_viata3 = 0;
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	// camera
	camera = new Tema::Camera();
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	polygonMode = GL_FILL;

	Mesh* mesh1 = new Mesh("sphere");
	mesh1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[mesh1->GetMeshID()] = mesh1;

	Mesh* mesh2 = new Mesh("box");
	mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh2->GetMeshID()] = mesh2;

	// linia initiala de platforme
	Platforma platforma0;
	platforma0.setCoordonate(x1, y, z1, scaleX_box, scaleY_box, scaleZ_box, culoare_box);
	platforme.push_back(platforma0);

	culoare_box = myRandomColor();
	Platforma platforma1;
	platforma1.setCoordonate(x2, y, z2, scaleX_box, scaleY_box, scaleZ_box, culoare_box);
	platforme.push_back(platforma1);

	culoare_box = myRandomColor();
	Platforma platforma2;
	platforma2.setCoordonate(x3, y, z3, scaleX_box, scaleY_box, scaleZ_box, culoare_box);
	platforme.push_back(platforma2);

	float min = z1;
	if (min > z2) {
		min = z2;
	}
	if (min > z3) {
		min = z3;
	}
	next_poz = min;

	// shader
	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Tema2_VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Tema2_FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader1 = new Shader("ShaderTema2Placute");
		shader1->AddShader("Source/Laboratoare/Tema2/Shaders/Tema2_VertexShaderPlacute.glsl", GL_VERTEX_SHADER);
		shader1->AddShader("Source/Laboratoare/Tema2/Shaders/Tema2_FragmentShaderPlacute.glsl", GL_FRAGMENT_SHADER);
		shader1->CreateAndLink();
		shaders[shader1->GetName()] = shader1;
	}

	// camera change
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();

	GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glUniform3fv(glGetUniformLocation(shader->program, "Color"), 1, glm::value_ptr(color));

	mesh->Render();
}

void Tema2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// camera move speed
	camera->TranslateForward(deltaTimeSeconds * inc);

	// sfera
	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_Transform3D::Translate(0, 0, -2);
	modelMatrix *= Tema2_Transform3D::Translate(translateX_sphere, translateY_sphere, translateZ_sphere);
	if (picatVerde == true) {
		modelMatrix *= Tema2_Transform3D::Scale(0.2, 0.2, 0.2);
		RenderMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix);
	}
	else {
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}

	// platforma
	if (platforme.size() < 20) {
		addPlatforme(platforme, next_poz);
	}
	for (int i = 0; i < platforme.size(); i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Tema2_Transform3D::Translate(platforme[i].getX(), platforme[i].getY(), platforme[i].getZ());
		modelMatrix *= Tema2_Transform3D::Scale(platforme[i].getScale_x(), platforme[i].getScale_y(), platforme[i].getScale_z());
		// rosu = 2
		if (platforme[i].getCuloare() == 2) {
			culoare = glm::vec3(0.8, 0, 0.1);
		}
		// albastru = 1
		if (platforme[i].getCuloare() == 1) {
			culoare = glm::vec3(0.1, 0, 1);
		}
		// galben = 3
		if (platforme[i].getCuloare() == 3) {
			culoare = glm::vec3(1, 1, 0.2);
		}
		// portocaliu = 4
		if (platforme[i].getCuloare() == 4) {
			culoare = glm::vec3(0.9, 0.5, 0);
		}
		// verde = 5
		if (platforme[i].getCuloare() == 5) {
			culoare = glm::vec3(0, 0.9, 0.5);
		}
		// mov = 6
		if (platforme[i].getCuloare() == 6) {
			culoare = glm::vec3(0.7, 0.3, 0.7);
		}
		// turcoaz = 7
		if (platforme[i].getCuloare() == 7) {
			culoare = glm::vec3(0.7, 1, 0.9);
		}
		// gri = 8
		if (platforme[i].getCuloare() == 8) {
			culoare = glm::vec3(0.8, 0.8, 0.8);
		}
		RenderSimpleMesh(meshes["box"], shaders["ShaderTema2Placute"], modelMatrix, culoare);
	}

	// scot platformele care nu se mai vad si le adaug mai in fata in scena
	int last3pos = 0;
	for (int i = 0; i < platforme.size(); i++) {
		if (platforme[i].getZ() > camera->position.z) {
			platforme[i].setZ(next_poz - 6.f);
			platforme[i].setCuloare(myRandomColor());
			if (platforme[i].getZ() < next_poz) {
				last3pos = platforme[i].getZ();
			}
			if ((i + 1) % 3 == 0) {
				next_poz = last3pos;
			}
		}
	}
	
	// coliziuni + avantaje/dezavantaje
	for (int i = 0; i < platforme.size(); i++) {
		coliziuneX = max(platforme[i].getX(), min(translateX_sphere, platforme[i].getX() + scaleX_box));
		coliziuneY = max(platforme[i].getY(), min(translateY_sphere, platforme[i].getY() + scaleY_box));
		coliziuneZ = max(platforme[i].getZ(), min(translateZ_sphere, platforme[i].getZ() + scaleZ_box));

		distance = sqrt(((coliziuneX - translateX_sphere) * (coliziuneX - translateX_sphere)) +
						((coliziuneY - translateY_sphere) * (coliziuneY - translateY_sphere)) +
						((coliziuneZ - translateZ_sphere) * (coliziuneZ - translateZ_sphere)));

		if (distance < scaleX_sphere / 2) {
			int culoarePlaca = platforme[i].getCuloare();
			// albastru
			if (culoarePlaca == 1) {
				cout << "coliziune albastru" << '\n';
				cout << endl;
			}
			// rosu
			if (culoarePlaca == 2) {
				cout << "coliziune rosu" << '\n';
				cout << "GAME OVER" << '\n';
				cout << endl;
				exit(1);
			}
			// galben
			if (culoarePlaca == 3) {
				cout << "coliziune galben" << '\n';
				cout << "scade combustibil" << '\n';
				cout << endl;
				scaleX_combustibil -= 0.3;
			}
			// portocaliu
			if (culoarePlaca == 4) {
				cout << "coliziune portocaliu" << '\n';
				cout << "esti blocat haha" << '\n';
				cout << endl;
				power = true;
			}
			// verde
			if (culoarePlaca == 5) {
				cout << "coliziune verde" << '\n';
				cout << "creste combustibil" << '\n';
				cout << endl;
				scaleX_combustibil += 0.3;
				picatVerde = true;
			}
			if (culoarePlaca == 7) {
				cout << "coliziune turcoaz" << '\n';
				cout << "creste viata" << '\n';
				cout << endl;
				if (viata != 3) {
					viata++;
					if (viata == 2) {
						scaleX_viata2 = 0.5;
						scaleY_viata2 = 0.5;
					}
					if (viata == 3) {
						scaleX_viata3 = 0.5;
						scaleY_viata3 = 0.5;
					}
				}
			}
			if (culoarePlaca == 8) {
				cout << "coliziune gri" << '\n';
				cout << "scade viata" << '\n';
				cout << endl;
				viata--;
				if (viata == 2) {
					scaleX_viata3 = 0;
					scaleY_viata3 = 0;
				}
				if (viata == 1) {
					scaleX_viata2 = 0;
					scaleY_viata2 = 0;
				}
				if (viata == 0) {
					cout << "nu mai ai viata" << '\n';
					exit(1);
				}
			}
			// coliziune si seteaza culoarea la mov
			platforme[i].setCuloare(6);
		}
	}

	// combustibil
	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_Transform3D::Translate(translateX_bara, translateY_bara, translateZ_bara);
	modelMatrix *= Tema2_Transform3D::Scale(scaleX_bara, scaleY_bara, scaleZ_bara);
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2Placute"], modelMatrix, glm::vec3(1, 1, 1));

	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_Transform3D::Translate(translateX_combustibil, translateY_combustibil, translateZ_combustibil);
	modelMatrix *= Tema2_Transform3D::Translate(+scaleX_combustibil / 2, -scaleY_combustibil / 2, -scaleZ_combustibil / 2);
	modelMatrix *= Tema2_Transform3D::Scale(scaleX_combustibil, scaleY_combustibil, scaleZ_combustibil);
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2Placute"], modelMatrix, glm::vec3(0.8, 0.6, 0.5));

	// fundal pentru cand s-a atins platforma portocalie
	// idee de la o colega :)
	if (power == true) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Tema2_Transform3D::Translate(0, 0, -2);
		modelMatrix *= Tema2_Transform3D::Translate(translateX_sphere, translateY_sphere, translateZ_sphere);
		modelMatrix *= Tema2_Transform3D::Scale(30, 30, 30);
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}

	// viteza
	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_Transform3D::Translate(translateX_bara, translateY_bara - 1, translateZ_bara);
	modelMatrix *= Tema2_Transform3D::Scale(scaleX_bara, scaleY_bara, scaleZ_bara);
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2Placute"], modelMatrix, glm::vec3(1, 1, 1));

	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_Transform3D::Translate(translateX_combustibil, translateY_combustibil - 1, translateZ_combustibil);
	modelMatrix *= Tema2_Transform3D::Translate(+scaleX_viteza / 2, -scaleY_viteza / 2, -scaleZ_viteza / 2);
	modelMatrix *= Tema2_Transform3D::Scale(scaleX_viteza, scaleY_viteza, scaleZ_viteza);
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2Placute"], modelMatrix, culoareViteza);

	// viata
	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_Transform3D::Translate(translateX_combustibil + 0.25, translateY_combustibil - 2, translateZ_combustibil);
	modelMatrix *= Tema2_Transform3D::Scale(scaleX_viata1, scaleY_viata1, scaleZ_viata1);
	RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2Placute"], modelMatrix, culoareViata);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_Transform3D::Translate(translateX_combustibil + 1, translateY_combustibil - 2, translateZ_combustibil);
	modelMatrix *= Tema2_Transform3D::Scale(scaleX_viata2, scaleY_viata2, scaleZ_viata2);
	RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2Placute"], modelMatrix, culoareViata);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_Transform3D::Translate(translateX_combustibil + 1.75, translateY_combustibil - 2, translateZ_combustibil);
	modelMatrix *= Tema2_Transform3D::Scale(scaleX_viata3, scaleY_viata3, scaleZ_viata3);
	RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2Placute"], modelMatrix, culoareViata);
}

void Tema2::FrameEnd()
{
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (inc > 20 && power == false) {
		inc = 20;
	}
	if (inc < 5 && power == false) {
		inc = 5;
	}

	// creste timpu pt platforma portoclaie
	if (power == true) {
		inc = 50;
		time += deltaTime;
		scaleX_viteza = scaleX_bara - 0.15;
		culoareViteza = glm::vec3(0.8, 0, 0.1);
	}
	if (time > 5) {
		time = 0;
		inc = 5;
		power = false;
	}

	// timpul pentru deformarea pe verde
	if (picatVerde == true) {
		timeVerde += deltaTime;
	}
	if (timeVerde > 1) {
		timeVerde = 0;
		picatVerde = false;
	}
	if (timeVerde > 0.5 && inc == 10) {
		timeVerde = 0;
		picatVerde = false;
	}
	if (timeVerde > 0.15 && inc == 15) {
		timeVerde = 0;
		picatVerde = false;
	}
	// timp pt deformarea lui verde cand placuta portocalie a fost atinsa
	if (picatVerde == true && power == true) {
		timeVerde += deltaTime;
	}
	if (timeVerde > 0.30 && power == true) {
		timeVerde = 0;
		picatVerde = false;
	}

	// sfera se deplaseaza cu o viteza initiala mica pana o sa o crestem
	translateZ_sphere -= deltaTime * inc;
	translateZ_bara -= deltaTime * inc;
	translateZ_combustibil -= deltaTime * inc;
	scaleX_combustibil -= deltaTime / 10;

	// verifica combustibilul si viata
	if (scaleX_combustibil < 0 && viata == 1) {
		cout << "GAME OVER" << '\n';
		cout << "no more fuel or life" << '\n';
		exit(1);
	}
	if (scaleX_combustibil > 2.8) {
		scaleX_combustibil = 2.8;
	}
	if (scaleX_combustibil < 0 && viata == 3) {
		cout << "no more fuel I take a life" << '\n';
		viata = 2;
		scaleX_viata3 = 0;
		scaleY_viata3 = 0;
		scaleX_combustibil = scaleX_bara - 0.15;
	}
	if (scaleX_combustibil < 0 && viata == 2) {
		cout << "no more fuel I take a life" << '\n';
		viata = 1;
		scaleX_viata2 = 0;
		scaleY_viata2 = 0;
		scaleX_combustibil = scaleX_bara - 0.15;
	}

	// verificare daca sunt pe placa sau nu
	if (translateX_sphere > 2 || translateX_sphere < -2) {
		cout << "ai cazut" << '\n';
		translateY_sphere -= 6 * deltaTime;
		picat = true;
		timp += deltaTime;
	}
	if (picat == true && timp > 0.5) {
		exit(1);
	}

	// bara viteza
	if (inc == 5) {
		scaleX_viteza = scaleX_bara - 2.5;
		culoareViteza = glm::vec3(0.9, 0.7, 1);
	}
	if (inc == 10) {
		scaleX_viteza = scaleX_bara - 2;
	}
	if (inc == 15) {
		scaleX_viteza = scaleX_bara - 1.5;
	}
	if (inc == 20) {
		scaleX_viteza = scaleX_bara - 1;
	}

	// jump
	if (jump == true) {
		translateY_sphere += deltaTime * 6;
		timeJump += deltaTime;
	}
	if (timeJump > 0.3) {
		jump = false;
		translateY_sphere -= deltaTime * 5;
		if (translateY_sphere < 0) {
			translateY_sphere = 0;
			timeJump = 0;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// A si D = schimba coloana
	if (key == GLFW_KEY_A) {
		translateX_sphere -= 2;
	}
	if (key == GLFW_KEY_D) {
		translateX_sphere += 2;
	}

	// SPACE = sare
	if (key == GLFW_KEY_SPACE) {
 		jump = true;
	}

	// W = creste viteza
	if (key == GLFW_KEY_W) {
		inc += 5;
	}

	// S = scade viteza
	if (key == GLFW_KEY_S) {
		inc -= 5;
	}

	// C = schimba perspectiva
	if (key == GLFW_KEY_C)
	{
		changeCamera = !changeCamera;

		if (changeCamera) {
			projectionMatrix = glm::perspective(RADIANS(15), window->props.aspectRatio, 0.01f, 200.0f);
		}
		else {
			projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
		}
	}
}

// functie care imi genereaza random o culoare pentru platformele mele
int Tema2::myRandomColor() {
	int x;
	x = rand() % 350;
	if (x <= 50) {
		x = 1;
	}
	else if (x > 50 && x <= 100) {
		x = 2;
	}
	else if (x > 100 && x <= 150) {
		x = 3;
	}
	else if (x > 150 && x <= 200) {
		x = 4;
	}
	else if (x > 200 && x <= 250) {
		x = 5;
	}
	else if (x > 250 && x <= 300) {
		x = 7;
	}
	else if (x > 300) {
		x = 8;
	}
	return x;
}

// functie care imi adauga cate 3 platforme in scena
void Tema2::addPlatforme(std::vector<Platforma>& platforme, int& next_poz) {
	float x, y, z1, culoare, z2, z3;
	float scaleX, scaleY, scaleZ;
	y = -0.45;
	scaleX = 0.7;
	scaleY = 0.1;
	scaleZ = 5;

	Platforma platformaNew1;
	x = 2;
	z1 = next_poz - scaleZ - rand() % 3;
	culoare = myRandomColor();
	platformaNew1.setCoordonate(x, y, z1, scaleX, scaleY, scaleZ, culoare);
	platforme.push_back(platformaNew1);

	Platforma platformaNew2;
	x = -2;
	z2 = next_poz - scaleZ - rand() % 3;
	culoare = myRandomColor();
	platformaNew2.setCoordonate(x, y, z2, scaleX, scaleY, scaleZ, culoare);
	platforme.push_back(platformaNew2);

	Platforma platformaNew3;
	x = 0;
	z3 = next_poz - scaleZ - rand() % 3;
	culoare = myRandomColor();
	platformaNew3.setCoordonate(x, y, z3, scaleX, scaleY, scaleZ, culoare);
	platforme.push_back(platformaNew3);

	float min = z1;
	if (min > z2) {
		min = z2;
	}
	if (min > z3) {
		min = z3;
	}
	next_poz = min;
}