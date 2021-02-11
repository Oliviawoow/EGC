// Copyright Oprea Olivia Maria-Magdalena 333CA 2020
#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

protected:
	glm::mat3 modelMatrix;

	float poz_X_arc;
	float poz_Y_arc;
	float poz_X_sageata;
	float poz_Y_sageata;
	float poz_X_balon_galben;
	float poz_Y_balon_galben;
	float poz_X_balon_rosu;
	float poz_Y_balon_rosu;
	float poz_X_steluta;
	float poz_Y_steluta;
	float poz_X_bar;
	float poz_Y_bar;
	float poz_X_bar_scor;
	float poz_Y_bar_scor;
	float poz_X_cerc;
	float poz_Y_cerc;

	float scor;
	float viata;
	bool collision_balon_rosu;
	bool collision_balon_galben;
	bool collision_sageata_steluta;
	bool collision_arc_steluta;
	bool collision_sageata_cerc;

	float lungime_sageata;
	float dx_rosu;
	float dy_rosu;
	float d_rosu;
	float scale_x_rosu;
	float scale_y_rosu;
	float dx_galben;
	float dy_galben;
	float d_galben;
	float scale_x_galben;
	float scale_y_galben;
	float dx_stea;
	float dy_stea;
	float d_stea;
	float scale_x_stea;
	float scale_y_stea;
	float dx_arc_stea;
	float dy_arc_stea;
	float d_arc_stea;
	float scale1;
	float scale2;
	float scale3;
	float dx_cerc;
	float dy_cerc;
	float d_cerc;
	float poz_Y_viata;

	float rotatie;
	float spin;
	float mouse_press;
	bool tasta_apasata;
	bool game_over;

	bool culoare_fundal;
};
