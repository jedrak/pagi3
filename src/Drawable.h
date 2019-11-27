#pragma once
#include <Shader.h>

class Drawable
{
	Shader _shader;
public:
	Drawable(Shader s) : _shader(s) {}
	virtual void Draw() = 0;
	Shader* getShader() { return &_shader; }
};