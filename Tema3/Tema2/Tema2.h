#pragma once
#include <Component/SimpleScene.h>
#include "Tema2_Camera.h"
#include "Tema2_Platforma.h"
#include "Tema3_CreateCub.h"
#include "Tema3_CreatePiramida.h"
#include <vector>

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color);
	void RenderSimpleMeshTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1);
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;

	int myRandomColor();
	int myRandomAppear();
	int myRandomAppearPoz();
	void addPlatforme(std::vector<Platforma>& platforme, int& next_poz);
	void addObstacole(std::vector<Cub>& cuburi);
	void addColectabile(std::vector<Piramida>& colectabile);
	void addPiramide(std::vector<Piramida>& piramide, int& z);


protected:
	Tema::Camera* camera;
	glm::mat4 projectionMatrix;
	bool changeCamera;

	glm::mat4 modelMatrix;
	float translateX_sphere, translateY_sphere, translateZ_sphere;
	float scaleX_sphere, scaleY_sphere, scaleZ_sphere;

	float scaleX_box, scaleY_box, scaleZ_box;
	float x1, y, z1, x2, z2, x3, z3;
	int culoare_box;
	int next_poz;
	int z;

	GLenum polygonMode;

	bool jump;
	bool power;
	float time;
	float timeVerde;
	float inc;
	float picatVerde;
	float scor;
	std::vector<Platforma> platforme;
	std::vector<Cub> cuburi;
	std::vector<Piramida> piramide;
	std::vector<Piramida> colectabile;
	glm::vec3 culoare;
	glm::vec3 culoareViteza;
	glm::vec3 culoareViata;
	bool picat;
	float timp;
	float timeJump;
	float viata;

	float coliziuneX, coliziuneY, coliziuneZ, distance;
	float translateX_bara, translateY_bara, translateZ_bara;
	float scaleX_bara, scaleY_bara, scaleZ_bara;
	float translateX_combustibil, translateY_combustibil, translateZ_combustibil;
	float scaleX_combustibil, scaleY_combustibil, scaleZ_combustibil;
	float scaleX_viteza, scaleY_viteza, scaleZ_viteza;
	float scaleX_viata1, scaleY_viata1, scaleZ_viata1;
	float scaleX_viata2, scaleY_viata2, scaleZ_viata2;
	float scaleX_viata3, scaleY_viata3, scaleZ_viata3;
	float scale_nolife;

	std::unordered_map<std::string, Texture2D*> mapMyTextures;
};