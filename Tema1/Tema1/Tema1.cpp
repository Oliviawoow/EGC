// Copyright Oprea Olivia Maria-Magdalena 333CA 2020
#include "Tema1.h"

#include <vector>
#include <iostream>
#include <math.h>

#include <Core/Engine.h>
#include "Tema1Obj2D.h"
#include "Tema1Transform2D.h"

using namespace std;

Tema1::Tema1()
{
	glm::ivec2 resolution = window->GetResolution();
	lungime_sageata = 121.65f;
	poz_X_arc = 150;
	poz_Y_arc = resolution.y / 2;
	poz_X_sageata = 150;
	poz_Y_sageata = resolution.y / 2;
	poz_X_balon_galben = rand() % 1000 + 100;
	poz_Y_balon_galben = 0;
	poz_X_balon_rosu = rand() % 1000;
	poz_Y_balon_rosu = 0;
	poz_X_steluta = 1280;
	poz_Y_steluta = rand() % 1000;
	poz_X_cerc = 1280;
	poz_Y_cerc = rand() % 1000;
	poz_X_bar = poz_X_arc - 100;
	poz_Y_bar = poz_Y_arc - 150;
	poz_X_bar_scor = poz_X_arc - 100;
	poz_Y_bar_scor = poz_Y_arc + 300;
	poz_Y_viata = 180;

	scor = 0;
	collision_balon_rosu = false;
	collision_balon_galben = false;
	collision_sageata_steluta = false;
	collision_arc_steluta = false;
	collision_sageata_cerc = false;
	viata = 3;

	scale_x_rosu = 1;
	scale_y_rosu = 1;
	scale_x_galben = 1;
	scale_y_galben = 1;
	scale_x_stea = 1;
	scale_y_stea = 1;
	scale1 = 1;
	scale2 = 1;
	scale3 = 1;

	mouse_press = 1;
	tasta_apasata = false;
	spin = 0;
	game_over = false;
	culoare_fundal = true;

	dx_rosu = 0;
	dy_rosu = 0;
	d_rosu = 0;
	dx_galben = 0;
	dy_galben = 0;
	d_galben = 0;
	dx_stea = 0;
	dy_stea = 0;
	d_stea = 0;
	dx_arc_stea = 0;
	dy_arc_stea = 0;
	d_arc_stea = 0;
	dx_cerc = 0;
	dy_cerc = 0;
	d_cerc = 0;

	rotatie = 0;
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner1 = glm::vec3(0, 0, 0);
	glm::vec3 corner2 = glm::vec3(0, 0, 0);
	glm::vec3 corner3 = glm::vec3(0, 0, 0);
	glm::vec3 linie_lungime1 = glm::vec3(25, 0, 0);
	glm::vec3 linie_lungime2 = glm::vec3(125, 0, 0);
	glm::vec3 linie_lungime3 = glm::vec3(100, 0, 0);
	glm::vec3 linie_lungime4 = glm::vec3(75, 0, 0);
	float lungime = 5;
	float latime = 100;
	float latura = 25;
	float nr_tring = 50;
	float latura_steluta = 40;
	float lungime_bar = 200;
	float latime_bar = 20;

	// sageata = dreptunghi si trunghi
	Mesh* dreptunghi2 = Tema1Obj2D::CreateDreptunghi("dreptunghi2", corner2, latime, lungime, glm::vec3(0, 0, 0), true);
	AddMeshToList(dreptunghi2);
	Mesh* triunghi = Tema1Obj2D::CreateTriunghi("triunghi", corner3, latura, glm::vec3(0, 0, 0), true);
	AddMeshToList(triunghi);

	// arc
	Mesh* arc = Tema1Obj2D::CreateArc("arc", nr_tring);
	AddMeshToList(arc);

	// balon rosu
	Mesh* balon_rosu = Tema1Obj2D::CreateBalon("balon_rosu", nr_tring, glm::vec3(1, 0, 0));
	AddMeshToList(balon_rosu);
	// balon galben
	Mesh* balon_galben = Tema1Obj2D::CreateBalon("balon_galben", nr_tring, glm::vec3(1, 1, 0));
	AddMeshToList(balon_galben);
	// capatul balonului rosu si galben
	Mesh* triunghi_rosu = Tema1Obj2D::CreateTriunghi("triunghi_rosu", corner3, latura, glm::vec3(1, 0, 0), true);
	AddMeshToList(triunghi_rosu);
	Mesh* triunghi_galben = Tema1Obj2D::CreateTriunghi("triunghi_galben", corner3, latura, glm::vec3(1, 1, 0), true);
	AddMeshToList(triunghi_galben);
	// sfoara rosu si galben
	Mesh* sfoara_rosie = Tema1Obj2D::CreateLinie("sfoara_rosie", corner1, linie_lungime1, glm::vec3(1, 0, 0));
	AddMeshToList(sfoara_rosie);
	Mesh* sfoara_galbena = Tema1Obj2D::CreateLinie("sfoara_galbena", corner1, linie_lungime1, glm::vec3(1, 1, 0));
	AddMeshToList(sfoara_galbena);
	
	// stelute
	Mesh* steluta = Tema1Obj2D::CreateSteluta("steluta", corner1, latura_steluta, glm::vec3(0, 0, 0), true);
	AddMeshToList(steluta);

	// dreptunghi putwere si scor
	Mesh* dreptunghi = Tema1Obj2D::CreateDreptunghi("dreptunghi", corner2, lungime_bar, latime_bar, glm::vec3(0, 0, 0), false);
	AddMeshToList(dreptunghi);
	Mesh* dreptunghi1 = Tema1Obj2D::CreateDreptunghi("dreptunghi1", corner2, lungime_bar - 10, latime_bar - 10, glm::vec3(1, 0, 0), true);
	AddMeshToList(dreptunghi1);

	// cercuri viata
	Mesh* cerc1 = Tema1Obj2D::CreateCerc("cerc1", nr_tring, glm::vec3(1, 0, 0));
	AddMeshToList(cerc1);
	Mesh* cerc2 = Tema1Obj2D::CreateCerc("cerc2", nr_tring, glm::vec3(1, 0, 0));
	AddMeshToList(cerc2);
	Mesh* cerc3 = Tema1Obj2D::CreateCerc("cerc3", nr_tring, glm::vec3(1, 0, 0));
	AddMeshToList(cerc3);

	// omul
	Mesh* corp = Tema1Obj2D::CreateLinie("corp", corner1, linie_lungime2, glm::vec3(0, 0, 0));
	AddMeshToList(corp);
	Mesh* mana = Tema1Obj2D::CreateLinie("mana", corner1, linie_lungime3, glm::vec3(0, 0, 0));
	AddMeshToList(mana);
	Mesh* picior = Tema1Obj2D::CreateLinie("picior", corner1, linie_lungime4, glm::vec3(0, 0, 0));
	AddMeshToList(picior);
	Mesh* cerc4 = Tema1Obj2D::CreateCerc("cerc4", nr_tring, glm::vec3(0, 0, 0));
	AddMeshToList(cerc4);
}

void Tema1::FrameStart()
{
	// tinta aduce punce avem albastru deschis
	// tita face rau avem albastru inchis
	if (culoare_fundal == true) {
		glClearColor(0.5725, 0.718, 1, 1);
	}
	else {
		glClearColor(0, 0, 0.8231, 1);
	}
	//glClearColor(0.5725, 0.718, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// arcasul meu
	// se deplaseaza pe OY si isi misca mainile dupa arc
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_arc - 110, poz_Y_arc + 70);
	RenderMesh2D(meshes["cerc4"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_arc - 110, poz_Y_arc + 50);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 2);
	RenderMesh2D(meshes["corp"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_arc - 110, poz_Y_arc - 10);
	modelMatrix *= Tema1Transform2D::Rotate(rotatie);
	modelMatrix *= Tema1Transform2D::Rotate(3.14f / 4);
	RenderMesh2D(meshes["mana"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_arc - 110, poz_Y_arc - 10);
	modelMatrix *= Tema1Transform2D::Rotate(rotatie);
	modelMatrix *= Tema1Transform2D::Rotate(3.14f / 20);
	RenderMesh2D(meshes["mana"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_arc - 110, poz_Y_arc - 75);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 4);
	RenderMesh2D(meshes["picior"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_arc - 110, poz_Y_arc - 75);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 2);
	RenderMesh2D(meshes["picior"], shaders["VertexColor"], modelMatrix);

	// arcul se poate rotii in jurul centrului si poate sa se deplaseze pe axa OY
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_arc, poz_Y_arc);
	modelMatrix *= Tema1Transform2D::Rotate(rotatie);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 2);
	RenderMesh2D(meshes["arc"], shaders["VertexColor"], modelMatrix);

	// sageata se poate rotii si ea impreuna cu arcul 
	// m-am asigurat ca dreptunghiul si triunghiul se misca impreuna pentru a face sageata
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_sageata, poz_Y_sageata);
	modelMatrix *= Tema1Transform2D::Rotate(rotatie);
	RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= Tema1Transform2D::Translate(100, -10);
	RenderMesh2D(meshes["triunghi"], shaders["VertexColor"], modelMatrix);

	// baloanele apar de jos si merg pe axa OY in sus
	//coliziune balon rosu
	dx_rosu = lungime_sageata / (cos(rotatie)) + poz_X_sageata;
	dy_rosu = sin(rotatie) * (dx_rosu - poz_X_sageata) + poz_Y_sageata;
	d_rosu = sqrt(((dx_rosu - poz_X_balon_rosu) * (dx_rosu - poz_X_balon_rosu)) + ((dy_rosu - poz_Y_balon_rosu) * (dy_rosu - poz_Y_balon_rosu)));
	if (d_rosu <= 50) {
		collision_balon_rosu = true;
		scor += 50;
		scale_x_rosu = 0;
		scale_y_rosu = 0;
		if (scor >= 1000) {
			scor = 1000;
		}
		culoare_fundal = true;
	}
	// balon rosu
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_rosu, poz_Y_balon_rosu);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 2);
	modelMatrix *= Tema1Transform2D::Scale(scale_x_rosu, scale_y_rosu);
	RenderMesh2D(meshes["balon_rosu"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_rosu + 13, poz_Y_balon_rosu - 58);
	modelMatrix *= Tema1Transform2D::Rotate(3.14f / 2);
	RenderMesh2D(meshes["triunghi_rosu"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_rosu - 3, poz_Y_balon_rosu - 50);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 3);
	RenderMesh2D(meshes["sfoara_rosie"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_rosu - 3, poz_Y_balon_rosu - 90);
	modelMatrix *= Tema1Transform2D::Rotate(3.14f / 3);
	RenderMesh2D(meshes["sfoara_rosie"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_rosu - 3, poz_Y_balon_rosu - 90);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 3);
	RenderMesh2D(meshes["sfoara_rosie"], shaders["VertexColor"], modelMatrix);
	// coliziune balon galben
	dx_galben = lungime_sageata / (cos(rotatie)) + poz_X_sageata;
	dy_galben = sin(rotatie) * (dx_galben - poz_X_sageata) + poz_Y_sageata;
	d_galben = sqrt(((dx_galben - poz_X_balon_galben) * (dx_galben - poz_X_balon_galben)) + ((dy_galben - poz_Y_balon_galben) * (dy_galben - poz_Y_balon_galben)));
	if (d_galben <= 50) {
		collision_balon_galben = true;
		scor -= 20;
		scale_x_galben = 0;
		scale_y_galben = 0;
		if (scor <= 0) {
			scor = 0;
		}
		culoare_fundal = false;
	}
	// balon galben
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_galben, poz_Y_balon_galben);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 2);
	modelMatrix *= Tema1Transform2D::Scale(scale_x_galben, scale_y_galben);
	RenderMesh2D(meshes["balon_galben"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_galben + 13, poz_Y_balon_galben - 58);
	modelMatrix *= Tema1Transform2D::Rotate(3.14f / 2);
	RenderMesh2D(meshes["triunghi_galben"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_galben - 3, poz_Y_balon_galben - 50);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 3);
	RenderMesh2D(meshes["sfoara_galbena"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_galben - 3, poz_Y_balon_galben - 90);
	modelMatrix *= Tema1Transform2D::Rotate(3.14f / 3);
	RenderMesh2D(meshes["sfoara_galbena"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_balon_galben - 3, poz_Y_balon_galben - 90);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f / 3);
	RenderMesh2D(meshes["sfoara_galbena"], shaders["VertexColor"], modelMatrix);

	// stelutele apar de la dreapta la stanga si se misca pe axa OX
	// coliziune stelute cu sageata
	dx_stea = lungime_sageata / (cos(rotatie)) + poz_X_sageata;
	dy_stea = sin(rotatie) * (dx_stea - poz_X_sageata) + poz_Y_sageata;
	d_stea = sqrt(((dx_stea - poz_X_steluta) * (dx_stea - poz_X_steluta)) + ((dy_stea - poz_Y_steluta) * (dy_stea - poz_Y_steluta)));
	if (d_stea <= 50) {
		collision_sageata_steluta = true;
		scor += 50;
		//scale_x_stea = 0;
		//scale_y_stea = 0;
		poz_X_steluta = 1280;
		poz_Y_steluta = rand() % 1000;
		if (scor >= 1000) {
			scor = 1000;
		}
		culoare_fundal = true;
	}
	// coliziune stelute cu arcul
	// scade viata, iar atunci cand nu mai are viata dispar toate ca sa faca game_over
	dx_arc_stea = poz_X_arc - poz_X_steluta;
	dy_arc_stea = poz_Y_arc - poz_Y_steluta;
	d_arc_stea = sqrt((dx_arc_stea * dx_arc_stea) + (dy_arc_stea * dy_arc_stea));
	if (d_arc_stea <= 130) {
		collision_arc_steluta = true;
		viata -= 1;
		//scale_x_stea = 0;
		//scale_y_stea = 0;
		poz_X_steluta = 1280;
		poz_Y_steluta = rand() % 1000;
		if (viata == 2) {
			scale3 = 0;
		}
		else if (viata == 1) {
			scale2 = 0;
		}
		else if (viata == 0) {
			std::cout << scor;
			game_over = true;
			exit(1);
		}
		culoare_fundal = false;
	}
	// stelute
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_steluta, poz_Y_steluta);
	modelMatrix *= Tema1Transform2D::Rotate(spin);
	modelMatrix *= Tema1Transform2D::Scale(scale_x_stea, scale_y_stea);
	RenderMesh2D(meshes["steluta"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_steluta, poz_Y_steluta);
	modelMatrix *= Tema1Transform2D::Rotate(-3.14f);
	modelMatrix *= Tema1Transform2D::Rotate(spin);
	modelMatrix *= Tema1Transform2D::Scale(scale_x_stea, scale_y_stea);
	RenderMesh2D(meshes["steluta"], shaders["VertexColor"], modelMatrix);

	// power bar
	// creste al 2lea dreptunghi atunci cand apasam tasta dreapta
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_bar, poz_Y_bar);
	RenderMesh2D(meshes["dreptunghi"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_bar + 5, poz_Y_bar + 5);
	modelMatrix *= Tema1Transform2D::Scale(mouse_press / 100, 1);
	RenderMesh2D(meshes["dreptunghi1"], shaders["VertexColor"], modelMatrix);

	// cercuri viata
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(100, poz_Y_viata);
	modelMatrix *= Tema1Transform2D::Scale(scale1, scale1);
	RenderMesh2D(meshes["cerc1"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(150, poz_Y_viata);
	modelMatrix *= Tema1Transform2D::Scale(scale2, scale2);
	RenderMesh2D(meshes["cerc2"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(200, poz_Y_viata);
	modelMatrix *= Tema1Transform2D::Scale(scale3, scale3);
	RenderMesh2D(meshes["cerc3"], shaders["VertexColor"], modelMatrix);

	// score bar
	// creste scorul o data ce am lovit un balon rosu sau o steluta
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_bar_scor, poz_Y_bar_scor);
	RenderMesh2D(meshes["dreptunghi"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Tema1Transform2D::Translate(poz_X_bar_scor + 5, poz_Y_bar_scor + 5);
	modelMatrix *= Tema1Transform2D::Scale(scor / 1000, 1);
	RenderMesh2D(meshes["dreptunghi1"], shaders["VertexColor"], modelMatrix);
	
	// resetare coordonate sageata si balon pentru a putea juca in continuare
	if (tasta_apasata == false && mouse_press != 1) {
		poz_X_sageata += mouse_press * cos(rotatie);
		poz_Y_sageata += mouse_press * sin(rotatie);
		if (poz_X_sageata > 1280) {
			poz_X_sageata = poz_X_arc;
			poz_Y_sageata = poz_Y_arc;
			mouse_press = 1;
			scale_x_rosu = 1;
			scale_y_rosu = 1;
			scale_x_galben = 1;
			scale_y_galben = 1;
			scale_x_stea = 1;
			scale_y_stea = 1;
		}
		if (poz_Y_sageata > 720) {
			poz_X_sageata = poz_X_arc;
			poz_Y_sageata = poz_Y_arc;
			mouse_press = 1;
			scale_x_rosu = 1;
			scale_y_rosu = 1;
			scale_x_stea = 1;
			scale_y_stea = 1;
		}
	}
	// daca viata este 1 o sa ne apara tinta o viata bonus ca sa nu murim asa usor
	if (viata == 1) {
		dx_cerc = lungime_sageata / (cos(rotatie)) + poz_X_sageata;
		dy_cerc = sin(rotatie) * (dx_cerc - poz_X_sageata) + poz_Y_sageata;
		d_cerc = sqrt(((dx_cerc - poz_X_cerc) * (dx_cerc - poz_X_cerc)) + ((dy_cerc - poz_Y_cerc) * (dy_cerc - poz_Y_cerc)));
		if (d_cerc <= 50) {
			collision_sageata_cerc = true;
			scale2 = 1;
			viata = 2;
			poz_X_cerc = 1280;
			poz_Y_cerc = rand() % 1000;
		}
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1Transform2D::Translate(poz_X_cerc, poz_Y_cerc);
		RenderMesh2D(meshes["cerc2"], shaders["VertexColor"], modelMatrix);
	}

	// scorul e maxim terminam jocul
	if (scor > 999) {
		exit(1);
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// misca arcul in sus pe OY
	if (window->KeyHold(GLFW_KEY_W)) {
		poz_Y_arc += deltaTime * 100;
		poz_Y_bar += deltaTime * 100;
		poz_Y_viata += deltaTime * 100;
		if (poz_X_sageata == poz_X_arc) {
			poz_Y_sageata += deltaTime * 100;
		}
	}
	// misca arcul in jos pe OY
	if (window->KeyHold(GLFW_KEY_S)) {
		if (poz_X_sageata == poz_X_arc) {
			poz_Y_sageata -= deltaTime * 100;
		}
		poz_Y_arc -= deltaTime * 100;
		poz_Y_bar -= deltaTime * 100;
		poz_Y_viata -= deltaTime * 100;
	}

	// miscare balon pe axa OY in sus
	// asigurare ca balonul o data ce ajunge sus v-a reaparea jos
	// asigurare ca balonul apare de la o anumita val pe axa OX
	poz_Y_balon_rosu += deltaTime * 200;
	if (poz_Y_balon_rosu > 720) {
		poz_Y_balon_rosu = 0;
		poz_X_balon_rosu = rand() % 1000;
	}
	if (poz_X_balon_rosu < 600) {
		poz_X_balon_rosu = rand() % 1000;
	}
	if (collision_balon_rosu == true) {
		collision_balon_rosu = false;
		poz_X_balon_rosu = rand() % 1000;
		poz_Y_balon_rosu = 0;
	}
	poz_Y_balon_galben += deltaTime * 100;
	if (poz_Y_balon_galben > 720) {
		poz_Y_balon_galben = 0;
		poz_X_balon_galben = rand() % 1000 + 100;
	}
	if (poz_X_balon_galben < 600) {
		poz_X_balon_galben = rand() % 1000 + 100;
	}
	if (collision_balon_galben == true) {
		collision_balon_galben = false;
		poz_X_balon_galben = rand() % 1000;
		poz_Y_balon_galben = 0;
	}

	// miscare stelute pe axa OX de la dreapta la stanga
	// asigurare ca steluta o data ce ajunge la marginea din stanga reapare random la dreapta
	spin += deltaTime * 10;
	poz_X_steluta -= deltaTime * 400;
	if (poz_X_steluta < 0) {
		poz_X_steluta = 1280;
		poz_Y_steluta = rand() % 1000;
	}
	if (poz_Y_steluta > 720) {
		poz_Y_steluta = rand() % 1000;
	}
	if (collision_sageata_steluta == true) {
		collision_sageata_steluta = false;
		poz_X_steluta = 1280;
		poz_Y_steluta = rand() % 1000;
	}
	if (collision_arc_steluta == true) {
		collision_arc_steluta = false;
		poz_X_steluta = 1280;
		poz_Y_steluta = rand() % 1000;
	}

	// miscare cerc viata 2 
	poz_X_cerc -= deltaTime * 400;
	if (poz_X_cerc < 0) {
		poz_X_cerc = 1280;
		poz_Y_cerc = rand() % 1000;
	}
	if (poz_Y_cerc > 720) {
		poz_Y_cerc = rand() % 1000;
	}

	// calculez cat am tinut tasta dreapta apasata
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		mouse_press += deltaTime * 50;
		tasta_apasata = true;
		if (mouse_press >= 100) {
			mouse_press = 100;
		}
	}
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	glm::ivec2 resolution = window->GetResolution();
	float distance_x;
	float distance_y;
	// am calculat coordonatele pentru ca arcul sa se miste dupa pozitia mouse-ului
	distance_x = mouseX - poz_X_arc + 25;
	distance_y = mouseY - resolution.y + poz_Y_arc;
	rotatie = atan2(distance_x, distance_y);
	rotatie -= 1.57;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
		tasta_apasata = false;
	}
}
