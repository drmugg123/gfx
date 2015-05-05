#include "gfx/sprite_batch.hpp"

gfx::SpriteBatch::SpriteBatch() {
	this->max = 10000; //max sprites to be able to render. this is only 0.2 mb vram
	this->current = 0;

	this->vbo = 0;
	this->vao = 0;
	this->defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
gfx::SpriteBatch::SpriteBatch(unsigned int max) {
	this->max = max;
	this->current = 0;

	this->vbo = 0;
	this->vao = 0;
	this->defaultUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
gfx::SpriteBatch::~SpriteBatch() {
	if(glIsVertexArray(this->vao) == GL_TRUE) {
    	glDeleteVertexArrays(1, &this->vao);
	}
	if(glIsBuffer(this->vbo) == GL_TRUE) {
		glDeleteBuffers(1, &this->vbo);
	}
}

void gfx::SpriteBatch::initialize(int v_pos, int v_uv) {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	int totalBufferSize = (sizeof(float)*7)*this->max;
	glBufferData(GL_ARRAY_BUFFER, totalBufferSize, NULL, GL_DYNAMIC_DRAW); 

    glEnableVertexAttribArray(v_pos);
    glVertexAttribPointer(v_pos, 3, GL_FLOAT, GL_FALSE, sizeof(float)*7, (GLvoid*)0);
	glVertexAttribDivisor(v_pos, 1);

    glEnableVertexAttribArray(v_uv);
    glVertexAttribPointer(v_uv, 4, GL_FLOAT, GL_FALSE, sizeof(float)*7, (GLvoid*)(sizeof(float)*3)); 
	glVertexAttribDivisor(v_uv, 1);

	this->tempBuffer.reserve(this->max * 7);
}

void gfx::SpriteBatch::draw(const glm::vec2& pos, float scale, const glm::vec4& uv) {
	if((this->current/7) >= this->max) {
		printf("spritebatch can't render more than %u sprites\n", this->max);
		return;
	}

	this->tempBuffer[this->current] = pos.x;
	this->tempBuffer[this->current + 1] = pos.y;
	this->tempBuffer[this->current + 2] = scale;
	this->tempBuffer[this->current + 3] = uv.x;
	this->tempBuffer[this->current + 4] = uv.y;
	this->tempBuffer[this->current + 5] = uv.z;
	this->tempBuffer[this->current + 6] = uv.w;
	
	this->current += 7;
}

void gfx::SpriteBatch::drawAll() {
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*this->current, (GLvoid*)&this->tempBuffer[0]);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->current/7);
	this->current = 0;
}
