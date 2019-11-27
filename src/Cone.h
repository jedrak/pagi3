#pragma once
#include "Drawable.h"
class Cone : public Drawable
{
private:
	float R, H;
	int i = 30;
	GLuint VBO, VAO;
	glm::vec3 color, position;
	
public:
	Cone(Shader shader, float R, float H, glm::vec3 position, glm::vec3 color) : Drawable(shader), R(R), H(H), position(position), color(color){
		float vertices[] = {
			position.x,  position.y, position.z, color.x, color.y, color.z
		};
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

		// color coord attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		
	}

	void setIter(int value) {
		this->i = value;
	}


	void Draw() {
		this->getShader()->setFloat("r", R);
		//this->getShader()->setFloat("h", H);
		this->getShader()->setInt("i", i);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);
	}
};

