#include "Tema3.h"

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	camera = new Camera::Camera();
	camera->Set(glm::vec3(0, 0.5, 3.5f), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 100.0f);
	initialProjection = projectionMatrix;

	const string textureLoc = "Source/Teme/Tema3/skybox/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "front.jpg").c_str(), GL_REPEAT);
		mapTextures["front"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "back.jpg").c_str(), GL_REPEAT);
		mapTextures["back"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "bottom.jpg").c_str(), GL_REPEAT);
		mapTextures["bottom"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "top.jpg").c_str(), GL_REPEAT);
		mapTextures["top"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "left.jpg").c_str(), GL_REPEAT);
		mapTextures["left"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "right.jpg").c_str(), GL_REPEAT);
		mapTextures["right"] = texture;
	}

	const string textureLoc2 = "Source/Teme/Tema3/Textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc2 + "SeamlessRoad.jpg").c_str(), GL_REPEAT);
		mapTextures["Road"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc2 + "DamagedSeamlessRoad.jpg").c_str(), GL_REPEAT);
		mapTextures["DamagedRoad"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc2 + "City.png").c_str(), GL_REPEAT);
		mapTextures["City"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc2 + "GroundWithGrass.jpg").c_str(), GL_REPEAT);
		mapTextures["Ground"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc2 + "Grass2.png").c_str(), GL_REPEAT);
		mapTextures["Grass"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc2 + "StreetLight.png").c_str(), GL_REPEAT);
		mapTextures["StreetLight"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc2 + "Bitcoin.png").c_str(), GL_REPEAT);
		mapTextures["Collectable"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc2 + "Roadblock.png").c_str(), GL_REPEAT);
		mapTextures["Roadblock"] = texture;
	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = CreateObjects::CreateSquare("Square");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		vector<VertexFormat> vertices_back
		{
			VertexFormat(glm::vec3(-15, -5,  0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(15, -5,  0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(15, 105,  0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-15, 105,  0), glm::vec3(0, 0, 0)),
		};

		vector<unsigned short> indices_back =
		{
			0, 1, 2,
			0, 2, 3
		};

		CreateMesh("rectangle_back", vertices_back, indices_back);
	}

	{
		vector<VertexFormat> vertices_fuel
		{
			VertexFormat(glm::vec3(-10, 0,  0), glm::vec3(0, 1, 0)),
			VertexFormat(glm::vec3(10, 0,  0), glm::vec3(0, 1, 0)),
			VertexFormat(glm::vec3(10, 100,  0), glm::vec3(0, 1, 0)),
			VertexFormat(glm::vec3(-10, 100,  0), glm::vec3(0, 1, 0)),
		};

		vector<unsigned short> indices_fuel =
		{
			0, 1, 2,
			0, 2, 3
		};

		CreateMesh("rectangle_fuel", vertices_fuel, indices_fuel);
	}

	
	Shader* shader = new Shader("NormalShader");
	shader->AddShader("Source/Teme/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Teme/Tema3/Shaders/FragmentShader2D.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	Shader* shader_hud = new Shader("2DShader");
	shader_hud->AddShader("Source/Teme/Tema3/Shaders/VertexShader2D.glsl", GL_VERTEX_SHADER);
	shader_hud->AddShader("Source/Teme/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader_hud->CreateAndLink();
	shaders[shader_hud->GetName()] = shader_hud;

	Shader* shader_dis_ver = new Shader("VertexDistortionShader");
	shader_dis_ver->AddShader("Source/Teme/Tema3/Shaders/DeformationVertexShader.glsl", GL_VERTEX_SHADER);
	shader_dis_ver->AddShader("Source/Teme/Tema3/Shaders/DeformationFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader_dis_ver->CreateAndLink();
	shaders[shader_dis_ver->GetName()] = shader_dis_ver;

	Shader* shader_dis_col = new Shader("ColorDistortionShader");
	shader_dis_col->AddShader("Source/Teme/Tema3/Shaders/ColorVertexShader.glsl", GL_VERTEX_SHADER);
	shader_dis_col->AddShader("Source/Teme/Tema3/Shaders/DeformationFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader_dis_col->CreateAndLink();
	shaders[shader_dis_col->GetName()] = shader_dis_col;

	Shader* shader_texture = new Shader("TextureShader");
	shader_texture->AddShader("Source/Teme/Tema3/Shaders/VertexTextureShader.glsl", GL_VERTEX_SHADER);
	shader_texture->AddShader("Source/Teme/Tema3/Shaders/FragmentTextureShader.glsl", GL_FRAGMENT_SHADER);
	shader_texture->CreateAndLink();
	shaders[shader_texture->GetName()] = shader_texture;

	Shader* shader_grass = new Shader("GrassShader");
	shader_grass->AddShader("Source/Teme/Tema3/Shaders/VertexGrassShader.glsl", GL_VERTEX_SHADER);
	shader_grass->AddShader("Source/Teme/Tema3/Shaders/FragmentTextureShader.glsl", GL_FRAGMENT_SHADER);
	shader_grass->CreateAndLink();
	shaders[shader_grass->GetName()] = shader_grass;

	glm::ivec2 resolution = window->GetResolution();
	Text = new TextRenderer(resolution.x, resolution.y);
	Text->Load("Source/TextRenderer/Fonts/Arial.ttf", 18);


	// Initializarea platformelor pregenerate
	Tema3::Initialize();
}

void Tema3::Initialize() {
	platformRows.resize(15);
	grassPlatformRows.resize(15);
	grassRows.resize(40);
	streetLightRows.resize(8);

	for (int i = 0; i < platformRows.size(); i++) {
		platformRows[i].platforms.resize(3);
		grassPlatformRows[i].platforms.resize(10);
	}

	for (int i = 0; i < streetLightRows.size(); i++) {
		streetLightRows[i].streetLights.resize(2);
	}

	for (int i = 0; i < grassRows.size(); i++) {
		grassRows[i].platforms.resize(4);
	}

	for (int i = 0; i < platformRows.size(); i++) {
		for (int j = 0; j < platformRows[i].platforms.size(); j++) {
			if (j == 0) {
				platformRows[i].platforms[j].x = -1;
			}
			else if (j == 1) {
				platformRows[i].platforms[j].x = 0;
			}
			else if (j == 2) {
				platformRows[i].platforms[j].x = 1;
			}

			if (i == 0) {
				platformRows[i].platforms[j].z = initialPlatformZ;
			}
			else {
				platformRows[i].platforms[j].z = platformRows[i - 1].platforms[j].z - 3;
			}

			platformRows[i].platforms[j].color = platformNormalColor;
			platformRows[i].platforms[j].render = true;
		}
	}

	for (int i = 0; i < grassPlatformRows.size(); i++) {
		for (int j = 0; j < grassPlatformRows[i].platforms.size() / 2; j++) {
			if (j == 0) {
				grassPlatformRows[i].platforms[j].x = initalLeftGrassX;
			}
			else {
				grassPlatformRows[i].platforms[j].x = grassPlatformRows[i].platforms[j - 1].x - 3.7;
			}

			if (i == 0) {
				grassPlatformRows[i].platforms[j].z = initialGrassPlatformZ;
			}
			else {
				grassPlatformRows[i].platforms[j].z = grassPlatformRows[i - 1].platforms[j].z - 4;
			}
		}

		for (int j = grassPlatformRows[i].platforms.size() / 2; j < grassPlatformRows[i].platforms.size(); j++) {
			if (j == grassPlatformRows[i].platforms.size() / 2) {
				grassPlatformRows[i].platforms[j].x = initalRightGrassX;
			}
			else {
				grassPlatformRows[i].platforms[j].x = grassPlatformRows[i].platforms[j - 1].x + 3.7;
			}

			if (i == 0) {
				grassPlatformRows[i].platforms[j].z = initialGrassPlatformZ;
			}
			else {
				grassPlatformRows[i].platforms[j].z = grassPlatformRows[i - 1].platforms[j].z - 4;
			}
		}
	}

	for (int i = 0; i < grassRows.size(); i++) {
		for (int j = 0; j < grassRows[i].platforms.size() / 2; j++) {
			if (j == 0) {
				grassRows[i].platforms[j].x = initalLeftGrassRowX;
			}
			else {
				grassRows[i].platforms[j].x = grassRows[i].platforms[j - 1].x - 9.35;
			}

			if (i == 0) {
				grassRows[i].platforms[j].z = initialGrassZ;
			}
			else {
				grassRows[i].platforms[j].z = grassRows[i - 1].platforms[j].z - 1.25;
			}

			grassRows[i].platforms[j].moveLeft = rand() % 2;
			grassRows[i].platforms[j].rotationY = rand() % 30;
		}

		for (int j = grassRows[i].platforms.size() / 2; j < grassRows[i].platforms.size(); j++) {
			if (j == grassRows[i].platforms.size() / 2) {
				grassRows[i].platforms[j].x = initalRightGrassRowX;
			}
			else {
				grassRows[i].platforms[j].x = grassRows[i].platforms[j - 1].x + 9.35;
			}

			if (i == 0) {
				grassRows[i].platforms[j].z = initialGrassZ;
			}
			else {
				grassRows[i].platforms[j].z = grassRows[i - 1].platforms[j].z - 1.25;
			}

			grassRows[i].platforms[j].moveLeft = rand() % 2;
			grassRows[i].platforms[j].rotationY = rand() % 30;
		}
	}

	for (int i = 0; i < streetLightRows.size(); i++) {
		for (int j = 0; j < streetLightRows[i].streetLights.size(); j++) {
			streetLightRows[i].streetLights[j].x = 0;

			if (i == 0) {
				streetLightRows[i].streetLights[j].z = initialGrassZ;
			}
			else {
				streetLightRows[i].streetLights[j].z = streetLightRows[i - 1].streetLights[j].z - 6;
			}
		}
	}
}

Mesh* Tema3::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

void Tema3::drawHud()
{
	glm::ivec2 resolution = window->GetResolution();

	float textWidth, textHight;
	if (gameStart) {
		std::string scoreText = std::to_string(score);
		std::string livesText = std::to_string(lives);

		Text->RenderText(&textWidth, &textHight, "Score: " + scoreText, 70, 20.0f, 1.5f, glm::vec3(0, 0, 0));
		Text->RenderText(&textWidth, &textHight, "Lives: " + livesText, 70, 50.0f, 1.5f, glm::vec3(0, 0, 0));
	}
	// Ecranul de new game contine doua butoane: New Game si Exit Game. 
	// De asemenea apare si titlul temei.
	// Daca se da hover pe acestea se schimba culoarea la text.
	else if (newGameScreen) {
		Text->RenderText(&textWidth, &textHight, "SKYROADS", resolution.x / 2, resolution.y / 2 - 200, 3, glm::vec3(0, 0, 0));
		Text->RenderText(&textWidthNewGame, &textHightNewGame, "New Game", resolution.x / 2, resolution.y / 2 - 100, 2, newGamesNewGameColor);
		Text->RenderText(&textWidthExitGame, &textHightExitGame, "Exit Game", resolution.x / 2, resolution.y / 2 - 50, 2, newGamesExitGameColor);
	}

	else if (gameOverScreen && backgoundColorR <= 0 && backgoundColorG <= 0 && backgoundColorB <= 0) {
		if (youDiedColor < 0.75) {
			youDiedColor += 0.002;
		}
		Text->RenderText(&textWidth, &textHight, "YOU DIED", resolution.x / 2, resolution.y / 2 - 200, 3, glm::vec3(youDiedColor, 0, 0));
		if (youDiedColor >= 0.75) {
			std::string scoreText = std::to_string(score);
			Text->RenderText(&textWidthNewGame, &textHightNewGame, "New Game", resolution.x / 2, resolution.y / 2 - 100, 2, exitGamesNewGameColor);
			Text->RenderText(&textWidthExitGame, &textHightExitGame, "Exit Game", resolution.x / 2, resolution.y / 2 - 50, 2, exitGamesExitGameColor);
			Text->RenderText(&textWidth, &textHight, "Score: " + scoreText, resolution.x / 2, resolution.y / 2, 2, glm::vec3(0.75, 0, 0));
			Text->RenderText(&textWidth, &textHight, deathBy, resolution.x / 2, resolution.y / 2 + 150, 2, glm::vec3(0.75, 0, 0));
		}
	}
	// Ecranul de pauza este asemanator cu cel de new game cu exceptia faptului
	// ca exista acum si butonul de Continue.
	else if (pauseGameScreen) {
		Text->RenderText(&textWidthContinue, &textHightContinue, "Continue", resolution.x / 2, resolution.y / 2 - 150, 2, newGamesContinueColor);
		//cout << textWidthContinue << " " << textHightContinue << endl;
		Text->RenderText(&textWidthNewGame, &textHightNewGame, "New Game", resolution.x / 2, resolution.y / 2 - 100, 2, newGamesNewGameColor);
		Text->RenderText(&textWidthExitGame, &textHightExitGame, "Exit Game", resolution.x / 2, resolution.y / 2 - 50, 2, newGamesExitGameColor);
	}

	if (gameStart) {
		// proiectia trebuie sa fie ortografica ca sa randam obiecte 2D
		projectionMatrix = glm::ortho(0.0f, (float)resolution.x, 0.0f, (float)resolution.y, 0.0f, 100.0f);

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(50, 100, 0));
		modelMatrix *= glm::scale(modelMatrix, glm::vec3(1, fuelScale, 1));
		NewRender::RenderMesh(meshes["rectangle_fuel"], shaders["2DShader"], modelMatrix, glm::vec3(0, 1, 0), camera, projectionMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(100, 200, 0));
		NewRender::RenderMesh(meshes["rectangle_back"], shaders["2DShader"], modelMatrix, glm::vec3(0, 0, 0), camera, projectionMatrix);

		// Revenim la proiectia initiala (proiectie perspectiva)
		projectionMatrix = initialProjection;
	}
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer

	// Backgroundul din timpul jocului e verde.
	if (gameStart) {
		backgoundColorR = 0.5;
		backgoundColorG = 0;
		backgoundColorB = 0;
		glClearColor(backgoundColorR, backgoundColorG, backgoundColorB, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	// Backgroundul din ecranul new game si pause game e alb.
	else if (newGameScreen) {
		glClearColor(backgoundColorR, backgoundColorG, backgoundColorB, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	// Backgroundul din ecranul game over e negru 
	// facandu-se tranzitia de la verde la negru mai intai.
	else if (gameOverScreen) {
		if (backgoundColorR >= 0 || backgoundColorB >= 0) {
			backgoundColorR -= 0.005;
		}
		glClearColor(backgoundColorR, backgoundColorG, backgoundColorB, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else if (pauseGameScreen) {
		backgoundColorB = 0.5;
		glClearColor(backgoundColorR, backgoundColorG, backgoundColorB, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

bool Tema3::collisionSphere(Tema3::platform plat, float playerX, float playerY, float playerZ, float radius)
{
	float x = fmax(plat.x - 0.5, fmin(playerX, plat.x + 0.5));
	float y = fmax(plat.y, fmin(playerY, plat.y));
	float z = fmax(plat.z - 1.5, fmin(playerZ, plat.z + 1.5));

	float distance = sqrt((x - playerX) * (x - playerX) +
		(y - playerY) * (y - playerY) +
		(z - playerZ) * (z - playerZ));

	return distance <= radius;
}

bool Tema3::collisionCoin(Tema3::misc coin, float playerX, float playerY, float playerZ, float radius)
{
	float x = fmax(coin.x - 0.25, fmin(playerX, coin.x + 0.25));
	float y = fmax(coin.y - 0.25, fmin(playerY, coin.y + 0.25));
	float z = fmax(coin.z, fmin(playerZ, coin.z));

	float distance = sqrt((x - playerX) * (x - playerX) +
		(y - playerY) * (y - playerY) +
		(z - playerZ) * (z - playerZ));

	return distance <= radius;
}

bool Tema3::collisionRoadblock(Tema3::misc roadblock, float playerX, float playerY, float playerZ, float radius)
{
	float x = fmax(roadblock.x - 0.5, fmin(playerX, roadblock.x + 0.5));
	float y = fmax(roadblock.y + 0.25, fmin(playerY, roadblock.y + 0.25));
	float z = fmax(roadblock.z, fmin(playerZ, roadblock.z));

	float distance = sqrt((x - playerX) * (x - playerX) +
		(y - playerY) * (y - playerY) +
		(z - playerZ) * (z - playerZ));

	return distance <= radius;
}

bool Tema3::find(int vector[], int number, int size) {
	for (int i = 0; i < size; i++) {
		if (vector[i] == number) {
			return true;
		}
	}

	return false;
}

void Tema3::Update(float deltaTimeSeconds)
{
	if (gameStart) {
		glm::mat4 modelMatrix;

		for (int i = 0; i < platformRows.size(); i++) {
			for (int j = 0; j < platformRows[i].platforms.size(); j++) {
				// Daca o linie de platforme ajunge la o anumita distanta in spatele jucatorului aceste platforme vor fi sterse 
				if (platformRows[i].platforms[j].z >= 9) {
					platformRows.erase(platformRows.begin());

					// Va fi generata alta linie de platforme
					row row;
					row.platforms.resize(3);
					row.initiateScore = true;
					howEmpty = rand() % 100 + 1;

					// Alegerea culorii unei platforme
					for (int k = 0; k < row.platforms.size(); k++) {
						powerColor = rand() % 200 + 1;
						if (find(red, powerColor, 2)) {
							row.platforms[k].color = platformRed;
						}
						else if (find(green, powerColor, 30)) {
							row.platforms[k].color = platformGreen;
						}
						else if (find(yellow, powerColor, 10)) {
							row.platforms[k].color = platformYellow;
						}
						else if (find(orange, powerColor, 10)) {
							row.platforms[k].color = platformOrange;
						}
						else {
							row.platforms[k].color = platformNormalColor;
						}

						// Alegerea tipului unei platforme (spatiu liber sau solid)
						row.platforms[k].z = platformRows[platformRows.size() - 1].platforms[j].z - 3;
						if (k == 0) {
							row.platforms[k].x = -1;

							if (howEmpty <= 25 || (howEmpty > 25 && howEmpty <= 45) || (howEmpty > 45 && howEmpty <= 50) || (howEmpty > 75 && howEmpty <= 95)) {
								row.platforms[k].render = true;

								int collectable = rand() % 10 + 1;
								if (collectable <= 2) {
									row.platforms[k].collectable = true;
									row.platforms[k].collect.x = row.platforms[k].x;
									row.platforms[k].collect.z = row.platforms[k].z;
								}

								int roadblock = rand() % 30 + 1;
								if (roadblock <= 2) {
									row.platforms[k].roadblock = true;
									row.platforms[k].block.x = row.platforms[k].x;
									row.platforms[k].block.z = row.platforms[k].z - 1.5;
								}
							}
							else {
								row.platforms[k].render = false;
							}
						}
						else if (k == 1) {
							row.platforms[k].x = 0;

							if (howEmpty <= 25 || (howEmpty > 25 && howEmpty <= 45) || (howEmpty > 50 && howEmpty <= 70) || howEmpty > 95) {
								row.platforms[k].render = true;

								int collectable = rand() % 10 + 1;
								if (collectable <= 2) {
									row.platforms[k].collectable = true;
									row.platforms[k].collect.x = row.platforms[k].x;
									row.platforms[k].collect.z = row.platforms[k].z;
								}

								int roadblock = rand() % 30 + 1;
								if (roadblock <= 2) {
									row.platforms[k].roadblock = true;
									row.platforms[k].block.x = row.platforms[k].x;
									row.platforms[k].block.z = row.platforms[k].z - 1.5;
								}
							}
							else {
								row.platforms[k].render = false;
							}
						}
						else if (k == 2) {
							row.platforms[k].x = 1;

							if (howEmpty <= 25 || (howEmpty > 50 && howEmpty <= 70) || (howEmpty > 70 && howEmpty <= 75) || (howEmpty > 75 && howEmpty <= 95)) {
								row.platforms[k].render = true;

								int collectable = rand() % 10 + 1;
								if (collectable <= 2) {
									row.platforms[k].collectable = true;
									row.platforms[k].collect.x = row.platforms[k].x;
									row.platforms[k].collect.z = row.platforms[k].z;
								}

								int roadblock = rand() % 30 + 1;
								if (roadblock <= 2) {
									row.platforms[k].roadblock = true;
									row.platforms[k].block.x = row.platforms[k].x;
									row.platforms[k].block.z = row.platforms[k].z - 1.5;
								}
							}
							else {
								row.platforms[k].render = false;
							}
						}
					}
				
					// Adaug linia la vector
					platformRows.emplace_back(row);
					break;
				}

				// Scalez si plasez platforma
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(platformRows[i].platforms[j].x, platformRows[i].platforms[j].y, platformRows[i].platforms[j].z));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0, 3));

				if (platformRows[i].platforms[j].render) {
					// Verificarea coliziunii sferei cu platformele
					if (Tema3::collisionSphere(platformRows[i].platforms[j], playerX, playerY, playerZ, radius) && !goingDown) {
						// Daca platforma atinsa este rosie atunci se termina jocul
						if (platformRows[i].platforms[j].color == platformRed) {
							gameOverScreen = true;
							gameStart = false;
							deathBy = "You've been killed by... a SMOOTH CRIMINAL";
						}
						// Daca platforma atinsa este verde atunci se adauga combustibil
						else if (platformRows[i].platforms[j].color == platformGreen) {
							playerColor = platformRows[i].platforms[j].color;
							fuelScale += 0.2;
							distortion = true;
							distortionTemp = 0;

							if (fuelScale > 1.0) {
								fuelScale = 1.0;
							}
						}
						// Daca platforma atinsa este galbena atunci se scade combustibil
						else if (platformRows[i].platforms[j].color == platformYellow) {
							playerColor = platformRows[i].platforms[j].color;
							fuelScale -= 0.1;
							distortion = true;
							distortionTemp = 0;

							if (fuelScale < 0) {
								fuelScale = 0;
							}

						}
						// Daca platforma atinsa este portocalie atunci
						// se blocheaza viteza la viteza maxima din acel moment 
						// si se blocheaza si tastele 'W' si 'S'
						else if (platformRows[i].platforms[j].color == platformOrange) {
							playerColor = platformRows[i].platforms[j].color;
							blockedKeys = true;
							distortion = true;
							distortionTemp = 0;
							blockedKeysTemp = 0;
						}

						// Dupa ce se trece de portiunea de joc pregenerata se porneste scorul si combustibilul incepe sa scada
						if (platformRows[i].initiateScore && !firstPlatform) {
							firstPlatform = true;
							score++;
							pseudoScore++;
						}

						// Schimb culoarea platformei la atingerea ei de catre sfera(jucator)
						platformRows[i].platforms[j].color = platformOnColor;
						NewRender::RenderMeshWithTexture(meshes["box"], shaders["TextureShader"], modelMatrix, platformRows[i].platforms[j].color, camera, projectionMatrix, mapTextures["Road"], 2);
					}
					else {
						NewRender::RenderMeshWithTexture(meshes["box"], shaders["TextureShader"], modelMatrix, platformRows[i].platforms[j].color, camera, projectionMatrix, mapTextures["Road"], 2);
					}		

					// Daca platforma contine element colectabil atunci o plasez corespunzator in scena.
					if (platformRows[i].platforms[j].collectable) {
						glm::mat4 modelMatrixCollectable = glm::mat4(1);
						modelMatrixCollectable = glm::translate(modelMatrixCollectable, glm::vec3(platformRows[i].platforms[j].collect.x, platformRows[i].platforms[j].collect.y, platformRows[i].platforms[j].collect.z));
						modelMatrixCollectable = glm::rotate(modelMatrixCollectable, RADIANS(platformRows[i].platforms[j].collect.coinRotation), glm::vec3(0, 1, 0));
						modelMatrixCollectable = glm::scale(modelMatrixCollectable, glm::vec3(0.5, 0.5, 0));

						NewRender::RenderMeshWithTexture(meshes["Square"], shaders["TextureShader"], modelMatrixCollectable, glm::vec3(0, 0, 0), camera, projectionMatrix, mapTextures["Collectable"], 2);

						// Animatia elementului colectabil consta in rotirea acestuia.
						platformRows[i].platforms[j].collect.coinRotation += 200 * deltaTimeSeconds;

						if (platformRows[i].platforms[j].collect.coinRotation > 360) {
							platformRows[i].platforms[j].collect.coinRotation = 0;
						}
					}

					// Daca platforma contine obstacol atunci il plasez corespunzator in scena.
					if (platformRows[i].platforms[j].roadblock) {
						glm::mat4 modelMatrixRoadblock = glm::mat4(1);
						modelMatrixRoadblock = glm::translate(modelMatrixRoadblock, glm::vec3(platformRows[i].platforms[j].block.x, platformRows[i].platforms[j].block.y, platformRows[i].platforms[j].block.z));
						modelMatrixRoadblock = glm::rotate(modelMatrixRoadblock, RADIANS(platformRows[i].platforms[j].block.fallingRotation), glm::vec3(1, 0, 0));
						modelMatrixRoadblock = glm::scale(modelMatrixRoadblock, glm::vec3(1, 0.5, 0));

						NewRender::RenderMeshWithTexture(meshes["Square"], shaders["TextureShader"], modelMatrixRoadblock, glm::vec3(0, 0, 0), camera, projectionMatrix, mapTextures["Roadblock"], 2);
						
						// Daca obstacolul a fost atins atunci se incepe animatia.
						// Animatia consta in rotirea acestuia pana ajunge in pozitie orizontala
						// mimand astfel actiunea de doborare a obstacolului.
						if (platformRows[i].platforms[j].block.startFalling && platformRows[i].platforms[j].block.fallingRotation > -90) {
							platformRows[i].platforms[j].block.fallingRotation -= 800 * deltaTimeSeconds;

							if (platformRows[i].platforms[j].block.y > 0) {
								platformRows[i].platforms[j].block.y -= 2 * deltaTimeSeconds;
							}
						}
					}
				}
				else {
					NewRender::RenderMeshWithTexture(meshes["box"], shaders["TextureShader"], modelMatrix, glm::vec3(0, 0, 0), camera, projectionMatrix, mapTextures["DamagedRoad"], 2);
				}

				// Daca sfera are coliziune cu un spatiu gol atunci se va incepe animatia de cadere din scena
				if (Tema3::collisionSphere(platformRows[i].platforms[j], playerX, playerY, playerZ, radius) && !platformRows[i].platforms[j].render) {
					goingDown = true;
				}

				// Daca este coliziune cu un element colectabil atunci maresc scorul
				// si nu mai randez acel element dupa.
				if (platformRows[i].platforms[j].collectable && Tema3::collisionCoin(platformRows[i].platforms[j].collect, playerX, playerY, playerZ, radius)) {
					score += 10;
					platformRows[i].platforms[j].collectable = false;
				}

				// Daca este coliziune cu un obstacol se scade din vieti
				// si anunt ca obstacolul poate sa inceapa animatia de cadere.
				if (platformRows[i].platforms[j].roadblock && !platformRows[i].platforms[j].block.startFalling && Tema3::collisionCoin(platformRows[i].platforms[j].block, playerX, playerY, playerZ, radius)) {
					lives--;
					if (lives == 0) {
						gameOverScreen = true;
						gameStart = false;
						deathBy = "Don't go through the roadblocks, you are not Hercules";
					}
					
					platformRows[i].platforms[j].block.startFalling = true;
				}

				// Daca s-a pornit jocul atunci platformele se pot misca
				if (startGame) {
					if (!blockedKeys) {
						platformRows[i].platforms[j].z += playerSpeed * deltaTimeSeconds;

						// Misc elementele colectabile si obstacolele odata cu platformele
						if (platformRows[i].platforms[j].collectable) {
							platformRows[i].platforms[j].collect.z = platformRows[i].platforms[j].z;
						}
						if (platformRows[i].platforms[j].roadblock) {
							platformRows[i].platforms[j].block.z = platformRows[i].platforms[j].z - 1.5;
						}
					}
					else {
						platformRows[i].platforms[j].z += maxSpeed * deltaTimeSeconds;

						if (platformRows[i].platforms[j].collectable) {
							platformRows[i].platforms[j].collect.z = platformRows[i].platforms[j].z;
						}
						if (platformRows[i].platforms[j].roadblock) {
							platformRows[i].platforms[j].block.z = platformRows[i].platforms[j].z - 1.5;
						}
					}
				}
			}
		}

		if (startGame) {
			if (score != 0) {
				fuelScale -= 0.0001 * (playerSpeed / 2);
			}

			if (fuelScale <= 0) {
				gameOverScreen = true;
				gameStart = false;
				deathBy = "Ups..You are out of fuel, please refill at the nearest gas station";
			}
		}

		// Animatie de saritura (se comporta ca o minge)
		if (goUp && !goingDown) {
			wasGoingUp = true;
			// Dupa impactul cu suprafata scad viteza sariturii urmatoare
			if (playerY < playerInitialY && temp != 0 && !goingDown) {
				playerY = playerInitialY;
				jumpSpeed *= 0.3;
				temp = 0;
			}

			temp += 0.005;
			playerY = playerInitialY + jumpSpeed * temp - g * temp * temp / 2;

			if (jumpSpeed <= 0.135) {
				playerY = playerInitialY;
				wasGoingUp = false;
				goUp = false;
				jumpSpeed = 5;
				temp = 0;
			}
		}

		// Animatia de moarte (cadere prin scena)
		if (goingDown) {
			if (!wasGoingUp || temp == 0) {
				playerY = playerInitialY - g * tempDown * tempDown / 2;
				tempDown += 0.005;
			}
			else {
				playerY = playerInitialY + jumpSpeed * temp - g * temp * temp / 2;
				temp += 0.005;
			}
			
		}

		// Jocul se sfarseste cand sfera ajunge la o anumita adancime
		if (playerY < -5) {
			gameOverScreen = true;
			gameStart = false;

			deathBy = "Please don't jump into holes. Suicide is not an option!";
		}

		// Randarea sferei distorsionate cu culoaera aferenta
		if (distortion) {
			distortionTemp++;

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(playerX, playerY, playerZ));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(radius * 2, radius * 2, radius * 2));
			NewRender::RenderMeshNoise(meshes["sphere"], shaders["VertexDistortionShader"], modelMatrix, playerColor, camera, projectionMatrix, globalTemp);

			if (distortionTemp % 200 == 0 && !blockedKeys) {
				playerColor = platformRed;
				distortion = false;
			}
			else if (distortionTemp % 600 == 0) {
				playerColor = platformRed;
				distortion = false;
			}
		}
		// Randarea sferei nedistorsionate
		else if (!distortion) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(playerX, playerY, playerZ));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(radius * 2, radius * 2, radius * 2));
			NewRender::RenderMeshNoise(meshes["sphere"], shaders["ColorDistortionShader"], modelMatrix, playerColor, camera, projectionMatrix, globalTemp);
		}

		globalTemp += 0.001;

		// Incheierea blocarii tastelor 'W' si 'S'
		if (blockedKeys) {
			blockedKeysTemp++;

			if (blockedKeysTemp % 600 == 0) {
				blockedKeys = false;
			}
		}

		// Mutarea Camerei Third si First Person
		if (!cameraThirdPerson) {
			camera->Set(glm::vec3(playerX, playerY + 0.5, playerZ + 0.1), glm::vec3(playerX, playerY + 0.25, 0), glm::vec3(0, 1, 0));
		}
		else {
			camera->Set(glm::vec3(0, 1, 3.5f), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
		}

		// Update Score
		if (startGame && score >= 1) {
			pseudoScore++;
			globalTempInt++;
			if (pseudoScore % 100 == 0) {
				score++;
			}
		}
		
		// Schimb dificultatea jocului (maresc viteza)
		/*if (globalTempInt % 5000 == 0) {
			minSpeed++;
			maxSpeed++;
			drift++;
			acceleration++;

			if (playerSpeed < minSpeed) {
				playerSpeed = minSpeed;
			}
		}*/

		// Randez skyboxul.
		NewRender::RenderSkyBox(meshes["Square"], shaders["TextureShader"], camera, projectionMatrix, mapTextures);

		// Randez orasul.
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 3.65, -49));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(40, 10, 0));
		NewRender::RenderMeshWithTexture(meshes["Square"], shaders["TextureShader"], modelMatrix, glm::vec3(0, 0, 0), camera, projectionMatrix, mapTextures["City"], 2);

		// Randez stalpii de lumina.
		for (int i = 0; i < streetLightRows.size(); i++) {
			for (int j = 0; j < streetLightRows[i].streetLights.size(); j++) {
				if (streetLightRows[i].streetLights[j].z >= 10) {
					streetLightRows.erase(streetLightRows.begin());
					streetLightRow streetLightRow;
					streetLightRow.streetLights.resize(2);

					for (int k = 0; k < streetLightRow.streetLights.size(); k++) {
						streetLightRow.streetLights[k].x = 0;
						streetLightRow.streetLights[k].z = streetLightRows[streetLightRows.size() - 1].streetLights[j].z - 6;
					}

					streetLightRows.emplace_back(streetLightRow);
					break;
				}

				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(streetLightRows[i].streetLights[j].x, streetLightRows[i].streetLights[j].y, streetLightRows[i].streetLights[j].z));

				if (j == 0) {
					modelMatrix = glm::rotate(modelMatrix, RADIANS(-180.0f), glm::vec3(0, 1, 0));
				}
				modelMatrix = glm::scale(modelMatrix, glm::vec3(3, 2, 0));
				NewRender::RenderMeshWithTexture(meshes["Square"], shaders["TextureShader"], modelMatrix, glm::vec3(0, 0, 0), camera, projectionMatrix, mapTextures["StreetLight"], 2);

				if (startGame) {
					if (!blockedKeys) {
						streetLightRows[i].streetLights[j].z += playerSpeed * deltaTimeSeconds;
					}
					else {
						streetLightRows[i].streetLights[j].z += maxSpeed * deltaTimeSeconds;
					}
				}
			}
		}

		// Randez platformele cu iarba.
		for (int i = 0; i < grassPlatformRows.size(); i++) {
			for (int j = 0; j < grassPlatformRows[i].platforms.size(); j++) {
				if (grassPlatformRows[i].platforms[j].z >= 10) {
					grassPlatformRows.erase(grassPlatformRows.begin());
					grassPlatformRow grassPlatformRow;
					grassPlatformRow.platforms.resize(10);

					for (int k = 0; k < grassPlatformRow.platforms.size() / 2; k++) {
						if (k == 0) {
							grassPlatformRow.platforms[k].x = initalLeftGrassX;
						}
						else {
							grassPlatformRow.platforms[k].x = grassPlatformRow.platforms[k - 1].x - 3.7;
						}

						grassPlatformRow.platforms[k].z = grassPlatformRows[grassPlatformRows.size() - 1].platforms[j].z - 4;
					}

					for (int k = grassPlatformRow.platforms.size() / 2; k < grassPlatformRow.platforms.size(); k++) {
						if (k == grassPlatformRow.platforms.size() / 2) {
							grassPlatformRow.platforms[k].x = initalRightGrassX;
						}
						else {
							grassPlatformRow.platforms[k].x = grassPlatformRow.platforms[k - 1].x + 3.7;
						}

						grassPlatformRow.platforms[k].z = grassPlatformRows[grassPlatformRows.size() - 1].platforms[j].z - 4;
					}

					grassPlatformRows.emplace_back(grassPlatformRow);
					break;
				}

				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(grassPlatformRows[i].platforms[j].x, grassPlatformRows[i].platforms[j].y, grassPlatformRows[i].platforms[j].z));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(1, 0, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(3.7, 4, 0));
				NewRender::RenderMeshWithTexture(meshes["Square"], shaders["TextureShader"], modelMatrix, glm::vec3(0, 0, 0), camera, projectionMatrix, mapTextures["Ground"], 2);

				if (startGame) {
					if (!blockedKeys) {
						grassPlatformRows[i].platforms[j].z += playerSpeed * deltaTimeSeconds;
					}
					else {
						grassPlatformRows[i].platforms[j].z += maxSpeed * deltaTimeSeconds;
					}
				}
			}
		}

		// Randez randurile de iarba.
		for (int i = 0; i < grassRows.size(); i++) {
			for (int j = 0; j < grassRows[i].platforms.size(); j++) {
				if (grassRows[i].platforms[j].z >= 10) {
					grassRows.erase(grassRows.begin());
					grassRow grassRow;
					grassRow.platforms.resize(4);

					for (int k = 0; k < grassRow.platforms.size() / 2; k++) {
						if (k == 0) {
							grassRow.platforms[k].x = initalLeftGrassRowX;
						}
						else {
							grassRow.platforms[k].x = grassRow.platforms[k - 1].x - 9.35;
						}

						grassRow.platforms[k].rotationY = rand() % 30;
						grassRow.platforms[k].z = grassRows[grassRows.size() - 1].platforms[j].z - 1.25;
						grassRow.platforms[k].moveLeft = rand() % 2;
					}

					for (int k = grassRow.platforms.size() / 2; k < grassRow.platforms.size(); k++) {
						if (k == grassRow.platforms.size() / 2) {
							grassRow.platforms[k].x = initalRightGrassRowX;
						}
						else {
							grassRow.platforms[k].x = grassRow.platforms[k - 1].x + 9.35;
						}

						grassRow.platforms[k].z = grassRows[grassRows.size() - 1].platforms[j].z - 1.25;
						grassRow.platforms[k].rotationY = rand() % 30;
						grassRow.platforms[k].moveLeft = rand() % 2;
					}

					grassRows.emplace_back(grassRow);
					break;
				}

				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(grassRows[i].platforms[j].x, grassRows[i].platforms[j].y, grassRows[i].platforms[j].z));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(grassRows[i].platforms[j].rotationY), glm::vec3(0, 1, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(grassRows[i].platforms[j].rotationX), glm::vec3(1, 0, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(9.25, 0.5, 0));
				NewRender::RenderMeshWithTexture(meshes["Square"], shaders["GrassShader"], modelMatrix, glm::vec3(0, 0, 0), camera, projectionMatrix, mapTextures["Grass"], grassRows[i].platforms[j].moveLeft);

				if (startGame) {
					if (!blockedKeys) {
						grassRows[i].platforms[j].z += playerSpeed * deltaTimeSeconds;
					}
					else {
						grassRows[i].platforms[j].z += maxSpeed * deltaTimeSeconds;
					}
				}
			}
		}

	}
}

void Tema3::FrameEnd()
{
	drawHud();
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{

	if (window->KeyHold(GLFW_KEY_A) && playerX > -1 && !goingDown && startGame) {
		playerX -= deltaTime * drift;
	}

	if (window->KeyHold(GLFW_KEY_D) && playerX < 1 && !goingDown && startGame) {
		playerX += deltaTime * drift;
	}

	if (window->KeyHold(GLFW_KEY_W) && startGame && !goingDown && !blockedKeys) {
		if (playerSpeed < maxSpeed) {
			playerSpeed += acceleration * deltaTime;
		}
	}

	if (window->KeyHold(GLFW_KEY_S) && startGame && !goingDown && !blockedKeys) {
		if (playerSpeed > minSpeed) {
			playerSpeed -= acceleration * deltaTime;
		}
	}
}

void Tema3::OnKeyPress(int key, int mods)
{
	// Pentru a schimba schimba tipul camerei se apasa pe 'C'
	if (key == GLFW_KEY_C){
		cameraThirdPerson = !cameraThirdPerson;
	}

	// Pentru a sari se apasa pe 'SPACE'
	if (key == GLFW_KEY_SPACE && (!goUp || jumpSpeed < 5) && !goingDown && startGame) {
		wasGoingUp = false;
		playerY = playerInitialY;
		goUp = true;
		jumpSpeed = 5;
		temp = 0;
	}

	// Pentru a incepe jocul dupa ce s-a dat 'New Game' se apasa pe 'ENTER'
	if (key == GLFW_KEY_ENTER && !startGame && gameStart) {
		startGame = true;
	}

	// Pentru a pune jocul pe pauza se apasa tasta 'P'
	if (key == GLFW_KEY_P) {
		newGamesContinueColor = glm::vec3(0, 0, 0);
		newGamesNewGameColor = glm::vec3(0, 0, 0);
		newGamesExitGameColor = glm::vec3(0.75, 0, 0);
		pauseGameScreen = true;
		gameStart = false;
	}
}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	glm::ivec2 resolution = window->GetResolution();
	// Ecran new game.
	if (gameStart) {
		if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
		{
			float sensivityOX = 0.001f;
			float sensivityOY = 0.001f;

			if (cameraThirdPerson) {
				// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
				// use the sensitivity variables for setting up the rotation speed
				camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
				camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
			}
		}
	}


	if (newGameScreen) {
		if (mouseX < resolution.x / 2 + textWidthNewGame / 2 && mouseX > resolution.x / 2 - textWidthNewGame / 2
			&& mouseY > resolution.y / 2 - 100 && mouseY < resolution.y / 2 - 100 + textHightNewGame) {

			newGamesNewGameColor = glm::vec3(0.75, 0.75, 0.75);
		}
		else if (mouseX < resolution.x / 2 + textWidthExitGame / 2 && mouseX > resolution.x / 2 - textWidthExitGame / 2
			&& mouseY > resolution.y / 2 - 50 && mouseY < resolution.y / 2 - 50 + textHightExitGame) {

			newGamesExitGameColor = glm::vec3(0.5, 0, 0);
		}
		else {
			newGamesNewGameColor = glm::vec3(0, 0, 0);
			newGamesExitGameColor = glm::vec3(0.75, 0, 0);
		}
	}
	// Ecran game over.
	else if (gameOverScreen && youDiedColor >= 0.75) {
		if (mouseX < resolution.x / 2 + textWidthNewGame / 2 && mouseX > resolution.x / 2 - textWidthNewGame / 2
			&& mouseY > resolution.y / 2 - 100 && mouseY < resolution.y / 2 - 100 + textHightNewGame) {

			exitGamesNewGameColor = glm::vec3(0.5, 0, 0);
		}
		else if (mouseX < resolution.x / 2 + textWidthExitGame / 2 && mouseX > resolution.x / 2 - textWidthExitGame / 2
			&& mouseY > resolution.y / 2 - 50 && mouseY < resolution.y / 2 - 50 + textHightExitGame) {

			exitGamesExitGameColor = glm::vec3(0.5, 0, 0);
		}
		else {
			exitGamesNewGameColor = glm::vec3(0.75, 0, 0);
			exitGamesExitGameColor = glm::vec3(0.75, 0, 0);
		}
	}
	// Ecran pause game.
	else if (pauseGameScreen) {
		if (mouseX < resolution.x / 2 + textWidthNewGame / 2 && mouseX > resolution.x / 2 - textWidthNewGame / 2
			&& mouseY > resolution.y / 2 - 150 && mouseY < resolution.y / 2 - 150 + textHightNewGame) {

			newGamesContinueColor = glm::vec3(0.75, 0.75, 0.75);
		}
		else if (mouseX < resolution.x / 2 + textWidthNewGame / 2 && mouseX > resolution.x / 2 - textWidthNewGame / 2
			&& mouseY > resolution.y / 2 - 100 && mouseY < resolution.y / 2 - 100 + textHightNewGame) {

			newGamesNewGameColor = glm::vec3(0.75, 0.75, 0.75);
		}
		else if (mouseX < resolution.x / 2 + textWidthExitGame / 2 && mouseX > resolution.x / 2 - textWidthExitGame / 2
			&& mouseY > resolution.y / 2 - 50 && mouseY < resolution.y / 2 - 50 + textHightExitGame) {

			newGamesExitGameColor = glm::vec3(0.5, 0, 0);
		}
		else {
			newGamesContinueColor = glm::vec3(0, 0, 0);
			newGamesNewGameColor = glm::vec3(0, 0, 0);
			newGamesExitGameColor = glm::vec3(0.75, 0, 0);
		}
	}
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	glm::ivec2 resolution = window->GetResolution();
	// Ecran new game.
	if (newGameScreen) {
		// Daca se da click pe new game atunci se reseteaza variabilele.
		if (mouseX < resolution.x / 2 + textWidthNewGame / 2 && mouseX > resolution.x / 2 - textWidthNewGame / 2
			&& mouseY > resolution.y / 2 - 100 && mouseY < resolution.y / 2 - 100 + textHightNewGame) {

			newGameScreen = false;
			gameStart = true;
		}
		// Daca se da click pe exit game se iese din joc.
		else if (mouseX < resolution.x / 2 + textWidthExitGame / 2 && mouseX > resolution.x / 2 - textWidthExitGame / 2
			&& mouseY > resolution.y / 2 - 50 && mouseY < resolution.y / 2 - 50 + textHightExitGame) {

			exit(-1);
		}
	}
	// Ecran game over.
	else if (gameOverScreen && youDiedColor >= 0.75) {
		// Daca se da click pe new game atunci se reseteaza variabilele.
		if (mouseX < resolution.x / 2 + textWidthNewGame / 2 && mouseX > resolution.x / 2 - textWidthNewGame / 2
			&& mouseY > resolution.y / 2 - 100 && mouseY < resolution.y / 2 - 100 + textHightNewGame) {

			platformRows.clear();
			firstPlatform = false;
			startGame = false;
			goUp = false;
			blockedKeys = false;
			goingDown = false;
			distortion = false;
			wasGoingUp = false;

			score = 0;
			pseudoScore = 0;
			distortionTemp = 0;
			blockedKeysTemp = 0;
			playerX = 0;
			playerY = 0.25;
			playerZ = 1.5;
			playerSpeed = 5;
			maxSpeed = 10;
			jumpSpeed = 5;
			temp = 0;
			tempDown = 0;
			globalTemp = 0;
			fuelScale = 1;
			drift = 2;
			acceleration = 5;
			minSpeed = 5;
			maxSpeed = 10;
			globalTempInt = 1;
			lives = 3;

			youDiedColor = 0;
			gameOverScreen = false;
			gameStart = true;
			cameraThirdPerson = true;
			
			camera->Set(glm::vec3(playerX, 1, 3.5f), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			playerColor = platformRed;
			Tema3::Initialize();
		}
		// Daca se da click pe exit game se iese din joc.
		else if (mouseX < resolution.x / 2 + textWidthExitGame / 2 && mouseX > resolution.x / 2 - textWidthExitGame / 2
			&& mouseY > resolution.y / 2 - 50 && mouseY < resolution.y / 2 - 50 + textHightExitGame) {

			exit(-1);
		}
	}
	// Ecran pause game.
	else if (pauseGameScreen) {
		// Daca se doreste continuarea jocului atunci se schimba ecranul si se continua jocul de unde a ramas.
		if (mouseX < resolution.x / 2 + textWidthNewGame / 2 && mouseX > resolution.x / 2 - textWidthNewGame / 2
			&& mouseY > resolution.y / 2 - 150 && mouseY < resolution.y / 2 - 150 + textHightNewGame) {

			pauseGameScreen = false;
			gameStart = true;
		}
		// Daca se da click pe new game atunci se reseteaza variabilele.
		else if (mouseX < resolution.x / 2 + textWidthNewGame / 2 && mouseX > resolution.x / 2 - textWidthNewGame / 2
			&& mouseY > resolution.y / 2 - 100 && mouseY < resolution.y / 2 - 100 + textHightNewGame) {

			platformRows.clear();
			firstPlatform = false;
			startGame = false;
			goUp = false;
			blockedKeys = false;
			goingDown = false;
			distortion = false;
			wasGoingUp = false;

			score = 0;
			pseudoScore = 0;
			distortionTemp = 0;
			blockedKeysTemp = 0;
			playerX = 0;
			playerY = 0.25;
			playerZ = 1.5;
			playerSpeed = 5;
			maxSpeed = 10;
			jumpSpeed = 5;
			temp = 0;
			tempDown = 0;
			globalTemp = 0;
			fuelScale = 1;
			drift = 2;
			acceleration = 5;
			minSpeed = 5;
			maxSpeed = 10;
			globalTempInt = 1;
			lives = 3;

			youDiedColor = 0;
			gameOverScreen = false;
			gameStart = true;
			cameraThirdPerson = true;

			camera->Set(glm::vec3(playerX, 1, 3.5f), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			playerColor = platformRed;
			Tema3::Initialize();
		}
		// Daca se da click pe exit game se iese din joc.
		else if (mouseX < resolution.x / 2 + textWidthExitGame / 2 && mouseX > resolution.x / 2 - textWidthExitGame / 2
			&& mouseY > resolution.y / 2 - 50 && mouseY < resolution.y / 2 - 50 + textHightExitGame) {

			exit(-1);
		}
	}
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
	glm::ivec2 resolution = window->GetResolution();

	// Se da spatiul in care o safie randat textul.
	Text = new TextRenderer(resolution.x, resolution.y);
	Text->Load("Source/TextRenderer/Fonts/Arial.ttf", 18);
}