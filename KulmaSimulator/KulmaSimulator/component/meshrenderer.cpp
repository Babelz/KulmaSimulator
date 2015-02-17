#include "component/meshrenderer.h"
#include "simulator.h"
MeshRenderer::MeshRenderer(Mesh* mesh) : mesh(mesh) {
	enable();
}

MeshRenderer::~MeshRenderer() {}

void MeshRenderer::onDraw(SpriteBatch& spriteBatch) {
	effect->bind();
	// TODO move somewhere else
	glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		static_cast<float>(1280) / 720,
		0.1f, 100.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0, 2.0, 4.0),   // eye
		glm::vec3(0.0, 0.0, 0.0),   // direction
		glm::vec3(0.0, 1.0, 0.0)  // up
		);

	glm::mat4 model = glm::mat4(1.0f);

	GLuint mvploc = glGetUniformLocation(effect->getProgram(), "MVP");
	glAssert();
	glUniformMatrix4fv(mvploc, 1, GL_FALSE, glm::value_ptr(projection * view * model));
	glAssert();

	glAssert();
	glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices().size());
	glAssert();
	effect->unbind();
	glAssert();
}

void MeshRenderer::onInitialize() {



	effect = Simulator::getInstance().getContent().load<Effect>("shader/trivial");

	glGenVertexArrays(1, &VAO);
	glAssert();
	glBindVertexArray(VAO);
	glAssert();
	glGenBuffers(1, &VBO);
	glAssert();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 5));

	glAssert();
	glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(GLfloat), mesh->getVertices().data(), GL_STATIC_DRAW);
	glAssert();
}