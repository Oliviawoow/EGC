#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Tema1Obj2D
{
	Mesh* CreateDreptunghi(std::string name, glm::vec3 leftBottomCorner, float lungime, float latime, glm::vec3 color, bool fill = false);
	Mesh* CreateTriunghi(std::string name, glm::vec3 leftBottomCorner, float latura, glm::vec3 color, bool fill);
	Mesh* CreateArc(std::string name, float nr_tring);
	Mesh* CreateBalon(std::string name, float nr_tring, glm::vec3 color);
	Mesh* CreateCerc(std::string name, float nr_tring, glm::vec3 color);
	Mesh* CreateSteluta(std::string name, glm::vec3 center, float latura, glm::vec3 color, bool fill);
	Mesh* CreateLinie(std::string name, glm::vec3 stanga, glm::vec3 lungime, glm::vec3 color);
}

