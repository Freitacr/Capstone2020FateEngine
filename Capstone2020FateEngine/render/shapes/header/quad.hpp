#include "../../base/header/baseRender.hpp"

#ifndef ENGINE_SHAPE_QUAD
#define ENGINE_SHAPE_QUAD


class Quad {

private:
	RenderingObject rData;
	float x, y, z;
	void setupRenderingData();

public:
	void render();
	Quad();
	Quad(float globalX, float globalY, float globalZ, std::vector<const char *> & textureFileNames, std::vector<const char *> & textureIdentifiers);


};

#endif