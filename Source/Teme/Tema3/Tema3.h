#pragma once
#include <Component/SimpleScene.h>
#include "CreateObjects.h"
#include "NewCamera.h"
#include "NewRender.h"
#include "Transform2D.h"
#include <TextRenderer/TextRenderer.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <Core/Engine.h>

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	typedef struct
	{
		float x;
		float y = 0.25;
		float z;
		float coinRotation = 0;
		bool startFalling = false;
		float fallingRotation = 0;

	}misc;

	typedef struct
	{
		float x;
		float y = 0;
		float z;
		glm::vec3 color;
		bool render;
		bool collectable = false;
		bool roadblock = false;
		misc collect;
		misc block;

	}platform;

	typedef struct
	{
		float x;
		float y = 0.2;
		float z;
		float rotationX = -30;
		float rotationY = 0;
		int moveLeft;

	}grass;

	typedef struct
	{
		float x;
		float y = 1;
		float z;

	}streetLight;

	typedef struct
	{
		std::vector<platform> platforms;
		bool initiateScore = false;

	}row;

	typedef struct
	{
		std::vector<platform> platforms;

	}grassPlatformRow;

	typedef struct
	{
		std::vector<grass> platforms;

	}grassRow;

	typedef struct
	{
		std::vector<streetLight> streetLights;

	}streetLightRow;

	std::vector<grassRow> grassRows;
	std::vector<grassPlatformRow> grassPlatformRows;
	std::vector<row> platformRows;
	std::vector<streetLightRow> streetLightRows;
	std::string deathBy;

	
	bool ortho = false;
	bool goLeft = false;
	bool goRight = false;
	bool goUp = false;
	bool goingDown = false;
	bool wasGoingUp = false;
	bool startGame = false;
	bool blockedKeys = false;
	bool firstPlatform = false;
	bool distortion = false;

	bool gameStart = false;
	bool newGameScreen = true;
	bool gameOverScreen = false;
	bool pauseGameScreen = false;

	int lives = 3;
	int g = 15;
	int drift = 2;
	int acceleration = 5;
	int minSpeed = 5;
	int maxSpeed = 10;
	int globalTempInt = 1;
	int howEmpty;
	int powerColor;
	int score = 0;
	int pseudoScore = 0;
	int moveLeft = 0;
	int distortionTemp = 0;
	int blockedKeysTemp = 0;
	int red[2] = {1, 55};
	int green[30] = {2, 12, 22, 32, 42, 52, 62, 72, 82, 92, 
					 5, 15, 25, 35, 45, 55, 65, 75, 85, 95,
					 6, 16, 26, 36, 46, 56, 66, 76, 86, 96};
	int yellow[10] = {3, 13, 23, 33, 43, 53, 63 ,73, 83, 93};
	int orange[10] = {4, 14, 24 , 34, 44, 54, 64, 74, 84, 94};

	float left = 0.01, right = 10, up = 10, down = 0.01;
	float fov = 40;
	float Zfar = 400;
	float Znear = 0.01;

	float initialPlatformZ = 3.5;
	float initialGrassPlatformZ = 4.5;
	float initialGrassZ = 6.5;
	float initalLeftGrassX = -3.35;
	float initalLeftGrassRowX = -6.125;
	float initalRightGrassX = 3.35;
	float initalRightGrassRowX = 6.125;
	float playerInitialX = 0;
	float playerInitialY = 0.25;
	float playerX = 0;
	float playerY = 0.25;
	float playerZ = 1.5;
	float playerSpeed = 5;
	float jumpSpeed = 5;
	float temp = 0;
	float tempDown = 0;
	float globalTemp = 0;
	float fuelScale = 1;

	float backgoundColorR = 0.5, backgoundColorG = 0, backgoundColorB = 0.5;
	float textHightNewGame, textWidthNewGame, textWidthExitGame, textHightExitGame, textWidthContinue, textHightContinue;
	float youDiedColor = 0;
	glm::vec3 newGamesNewGameColor = glm::vec3(0, 0, 0);
	glm::vec3 newGamesExitGameColor = glm::vec3(0.75, 0, 0);
	glm::vec3 exitGamesNewGameColor = glm::vec3(0.75, 0, 0);
	glm::vec3 exitGamesExitGameColor = glm::vec3(0.75, 0, 0);
	glm::vec3 newGamesContinueColor = glm::vec3(0, 0, 0);

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	void drawHud();
	void Initialize();
	bool find(int vector[], int number, int size);
	bool collisionSphere(platform plat, float playerX, float playerY, float playerZ, float radius);
	bool collisionCoin(Tema3::misc coin, float playerX, float playerY, float playerZ, float radius);
	bool collisionRoadblock(Tema3::misc roadblock, float playerX, float playerY, float playerZ, float radius);
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	TextRenderer* Text;
	GLuint VAO, VBO;
	std::unordered_map<std::string, Texture2D*> mapTextures;

protected:
	Camera::Camera *camera;
	glm::mat4 projectionMatrix;
	glm::vec3 platformNormalColor = glm::vec3(0, 0, 0);
	//glm::vec3 platformNormalColor = glm::vec3(0, 0.8, 1);
	glm::vec3 platformOnColor = glm::vec3(1, 0, 1);
	glm::vec3 platformYellow = glm::vec3(1, 1, 0);
	glm::vec3 platformRed = glm::vec3(1, 0, 0);
	glm::vec3 platformOrange = glm::vec3(1, 0.5, 0);
	glm::vec3 platformGreen = glm::vec3(0, 0.9, 0);
	glm::vec3 playerColor = glm::vec3(1, 0, 0);
	glm::mat4 initialProjection;
	bool cameraThirdPerson = true;
	float radius = 0.25;
};
