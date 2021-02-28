#pragma once

#include <Component/SimpleScene.h>
#include <include/glm.h>
#include "NewCamera.h"
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>

namespace NewRender 
{
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Camera::Camera* camera, glm::mat4 projectionMatrix);

	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Camera::Camera* camera, glm::mat4 projectionMatrix);

	void RenderMeshNoise(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Camera::Camera* camera, glm::mat4 projectionMatrix, float time);

	void RenderMeshWithTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Camera::Camera* camera, glm::mat4 projectionMatrix, Texture2D* texture, int moveLeft);

	void RenderTextureSkyBox(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Camera::Camera* camera, glm::mat4 projectionMatrix, Texture2D* texture);

	void RenderSkyBox(Mesh* mesh, Shader* shader, Camera::Camera* camera, glm::mat4 projectionMatrix, std::unordered_map<std::string, Texture2D*> mapTextures);

}