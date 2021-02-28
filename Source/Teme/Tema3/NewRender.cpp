#include "NewRender.h"
#include <Core/Engine.h>
#include <cmath>

void NewRender::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Camera::Camera* camera, glm::mat4 projectionMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	mesh->Render();
}

void NewRender::RenderMeshNoise(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Camera::Camera* camera, glm::mat4 projectionMatrix, float time)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	GLint loc_time = glGetUniformLocation(shader->program, "time");
	glUniform1f(loc_time, time);

	mesh->Render();
}

void NewRender::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Camera::Camera* camera, glm::mat4 projectionMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties

	// TODO: Set material property uniforms (object color) 
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void NewRender::RenderMeshWithTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Camera::Camera* camera, glm::mat4 projectionMatrix, Texture2D* texture, int moveLeft)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (color != glm::vec3(0, 0, 0)) {
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));
	}
	else {
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	}

	if (moveLeft < 2) {
		glUniform1f(glGetUniformLocation(shader->program, "time"), (GLfloat)Engine::GetElapsedTime());
		glUniform1i(glGetUniformLocation(shader->program, "moveLeft"), moveLeft);
	}

	//TODO : activate texture location 0
	glActiveTexture(GL_TEXTURE0);

	//TODO : Bind the texture1 ID
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//TODO : Send texture uniform value
	glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void NewRender::RenderTextureSkyBox(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Camera::Camera* camera, glm::mat4 projectionMatrix, Texture2D* texture)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));

	//TODO : activate texture location 0
	glActiveTexture(GL_TEXTURE0);

	//TODO : Bind the texture1 ID
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		

	//TODO : Send texture uniform value
	glUniform1i(glGetUniformLocation(shader->program, "texture1"), 0);

	glUniform1i(glGetUniformLocation(shader->program, "twoTextures"), 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void NewRender::RenderSkyBox(Mesh* mesh, Shader* shader, Camera::Camera* camera, glm::mat4 projectionMatrix, std::unordered_map<std::string, Texture2D*> mapTextures)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -50));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 0));
	NewRender::RenderTextureSkyBox(mesh, shader, modelMatrix, camera, projectionMatrix, mapTextures["front"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -50, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(180.0f), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 0));
	NewRender::RenderTextureSkyBox(mesh, shader, modelMatrix, camera, projectionMatrix, mapTextures["bottom"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 50, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(180.0f), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 0));
	NewRender::RenderTextureSkyBox(mesh, shader, modelMatrix, camera, projectionMatrix, mapTextures["top"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(50, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 0));
	NewRender::RenderTextureSkyBox(mesh, shader, modelMatrix, camera, projectionMatrix, mapTextures["right"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-50, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 0));
	NewRender::RenderTextureSkyBox(mesh, shader, modelMatrix, camera, projectionMatrix, mapTextures["left"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 50));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(180.0f), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 0));
	NewRender::RenderTextureSkyBox(mesh, shader, modelMatrix, camera, projectionMatrix, mapTextures["back"]);
}