#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// declar o variabila pt schimbare culoare fundal
bool culoare_fundal = false;
// declar o variabila pentru schimbarea formei
int schimb_forma = 1;
// declar 3 variabile de pozitie ca sa pot sa misc obiectul
float x = 0.1, y = 1, z = -2;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		// EX 2:
		// mi-am creat o sfera
		Mesh* mesh1 = new Mesh("sphere");
		mesh1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh1->GetMeshID()] = mesh1;

		// mi-am creat un teapot
		Mesh* mesh2 = new Mesh("teapot");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh2->GetMeshID()] = mesh2;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// EX 3:
	// schimbare culoare ecran daca tasta 'c' a fost apasata
	// altfel ramane la culoarea initiala
	// apes un buton, se schimba culoarea, eliberez butonul, culoarea revine la cea inițială
	if (culoare_fundal == true) {
		glClearColor(1, 1, 0, 0);
	}
	else {
		glClearColor(0, 0, 0, 1);
	}

	// sets the clear color for the color buffer
	//glClearColor(0, 0, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	//RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// EX 4:
	// initial nu am apasat tasta 'l' si forma mea v-a fi un cub
	// am apasat o data tasta 'l' forma mea devine o sfera, iar daca mai apas o data forma mea v-a fi un teapot
	// asa am realizat ciclarea formei prin 3 stari
	if (schimb_forma == 1) {
		RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
	} else if (schimb_forma == 2) {
		RenderMesh(meshes["sphere"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
	} else {
		RenderMesh(meshes["teapot"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
	}

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	// EX 2:
	// mi-am pus noua sfera in plan
	RenderMesh(meshes["sphere"], glm::vec3(0.1, 0.3f, 0), glm::vec3(0.75f));

	// EX 5:
	RenderMesh(meshes["sphere"], glm::vec3(x, y, z), glm::vec3(0.75f));
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input

	// Ex 5:
	// comenzile ca sa ma pot misca pe axele x, y, z
	if (window->KeyHold(GLFW_KEY_A)) {
		x -= 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		x += 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_W)) {
		y += 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		y -= 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_E)) {
		z += 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_Q)) {
		z -= 1.5 * deltaTime;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
	}

	// EX 3:
	// daca apas tasta 'c' inseamna ca trebuie sa se schimbe culoarea la fundal
	if (key == GLFW_KEY_C) {
		culoare_fundal = true;
	}

	// EX 4:
	// daca apas tasta 'l' schimb_forma v-a creste si imi v-a schimba obiectul in urmatoarea forma
	// o data ce forma a trecut prin cele 3 stari ma asigur ca o v-a lua de la capat reinitializand
	// shimb_forma la 1
	if (key == GLFW_KEY_L) {
		schimb_forma++;
		if (schimb_forma == 4) {
			schimb_forma = 1;
		}
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event

	// EX 3:
	// daca nu mai apas tasta 'c' inseamna ca fundalul revine la normal
	if (key == GLFW_KEY_C) {
		culoare_fundal = false;
	}
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
