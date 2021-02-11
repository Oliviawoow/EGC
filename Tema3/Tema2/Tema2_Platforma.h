#pragma once
#include <string>
#include <stdlib.h>     
#include <vector>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <math.h>

class Platforma {
private:
	float x, y, z;
	float scale_x, scale_y, scale_z;
	int culoare;

public:
	Platforma() = default;
	~Platforma() = default;
	// set
	void setX(float x) {
		this->x = x;
	}
	void setY(float y) {
		this->y = y;
	}
	void setZ(float z) {
		this->z = z;
	}
	void setScale_x(float scale_x) {
		this->scale_x = scale_x;
	}
	void setScale_y(float scale_y) {
		this->scale_y = scale_y;
	}
	void setScale_z(float scale_z) {
		this->scale_z = scale_z;
	}
	void setCuloare(int culoare) {
		this->culoare = culoare;
	}
	//get
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}
	float getScale_x() {
		return scale_x;
	}
	float getScale_y() {
		return scale_y;
	}
	float getScale_z() {
		return scale_z;
	}
	int getCuloare() {
		return culoare;
	}
	// coordonate
	void setCoordonate(float x, float y, float z, float scale_x, float scale_y, float scale_z, int culoare) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->scale_x = scale_x;
		this->scale_y = scale_y;
		this->scale_z = scale_z;
		this->culoare = culoare;
	}
};