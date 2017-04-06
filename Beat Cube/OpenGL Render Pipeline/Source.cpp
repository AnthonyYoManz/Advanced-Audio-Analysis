#include <iostream>
#include <GL/glew.h>
#include <glm/matrix.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "dix/Window.h"
#include "dix/Framebuffer.h"
#include "dix/FileLoader.h"
#include "dix/Texture.h"
#include "dix/Shader.h"
#include "TriangleMesh.h"
#include "PlaneMesh.h"
#include "CubeMesh.h"
#include "PerfectlyGenericObject.h"
#include <AudioAnalysis.h>	//my library
#include <SFML/Audio.hpp>
const double D_PI = 3.14159265359;
const float F_PI = 3.14159265359f;

int main()
{
	dix::Window window;
	window.initialise("Bumpin Cube", 1280, 960, NULL, NULL);
	window.setAsCurrentContext();
	window.setVsync(true);

	glewExperimental = GL_TRUE;
	glewInit();
	
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) <<  "\n";
	glViewport(0, 0, 1280, 960);

	glm::mat4 projectionMatrix = glm::perspective(60.0f * 3.142f / 180.0f, (float)1280 / (float)960, 0.1f, 100.f);
	glm::mat4 orthoMatrix = glm::ortho(0.0f, 1280.0f, 960.0f, 0.0f, 0.1f, 100.0f);
	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.5f));


	dix::Shader perspVertShader;
	perspVertShader.load("ass/vert.vert", dix::ShaderType::VERTEX);
	dix::Shader litFragShader;
	litFragShader.load("ass/frag.frag", dix::ShaderType::FRAGMENT);
	dix::Shader screenVertShader;
	screenVertShader.load("ass/screen.vert", dix::ShaderType::VERTEX);
	dix::Shader shadelessFragShader;
	shadelessFragShader.load("ass/shadeless.frag", dix::ShaderType::FRAGMENT);
	dix::Shader outlineFirstPassVertShader;
	outlineFirstPassVertShader.load("ass/outlineFirstPass.vert", dix::ShaderType::VERTEX);
	dix::Shader outlineFirstPassFragShader;
	outlineFirstPassFragShader.load("ass/outlineFirstPass.frag", dix::ShaderType::FRAGMENT);
	dix::Shader outlineFragShader;
	outlineFragShader.load("ass/normsOutline.frag", dix::ShaderType::FRAGMENT);

	GLuint defaultProgram = glCreateProgram();
	glAttachShader(defaultProgram, perspVertShader.getHandle());
	glAttachShader(defaultProgram, litFragShader.getHandle());
	glLinkProgram(defaultProgram);
	
	GLint outlineFirstPassProgram = glCreateProgram();
	glAttachShader(outlineFirstPassProgram, outlineFirstPassVertShader.getHandle());
	glAttachShader(outlineFirstPassProgram, outlineFirstPassFragShader.getHandle());
	glLinkProgram(outlineFirstPassProgram);
	
	GLuint outlineProgram = glCreateProgram();
	glAttachShader(outlineProgram, screenVertShader.getHandle());
	glAttachShader(outlineProgram, outlineFragShader.getHandle());
	glLinkProgram(outlineProgram);
	
	GLuint screenProgram = glCreateProgram();
	glAttachShader(screenProgram, screenVertShader.getHandle());
	glAttachShader(screenProgram, shadelessFragShader.getHandle());
	glLinkProgram(screenProgram);

	GLint defaultProjMatU = glGetUniformLocation(defaultProgram, "projMat");
	GLint defaultViewMatU = glGetUniformLocation(defaultProgram, "viewMat");
	GLint defaultModelMatU = glGetUniformLocation(defaultProgram, "modelMat");
	GLint outlineFirstPassProjMatU = glGetUniformLocation(outlineFirstPassProgram, "projMat");
	GLint outlineFirstPassViewMatU = glGetUniformLocation(outlineFirstPassProgram, "viewMat");
	GLint outlineFirstPassModelMatU = glGetUniformLocation(outlineFirstPassProgram, "modelMat");
	GLint outlineProjMatU = glGetUniformLocation(outlineProgram, "projMat");
	GLint outlineViewMatU = glGetUniformLocation(outlineProgram, "viewMat");
	GLint outlineModelMatU = glGetUniformLocation(outlineProgram, "modelMat");
	GLint outlineTextureWidthU = glGetUniformLocation(outlineProgram, "textureWidth");
	GLint outlineTextureHeightU = glGetUniformLocation(outlineProgram, "textureHeight");
	GLint outlineLineColourU = glGetUniformLocation(outlineProgram, "outlineColour");
	GLint outlineSensitivityU = glGetUniformLocation(outlineProgram, "sensitivity");
	GLint screenProjMatU = glGetUniformLocation(screenProgram, "projMat");
	GLint screenViewMatU = glGetUniformLocation(screenProgram, "viewMat");
	GLint screenModelMatU = glGetUniformLocation(screenProgram, "modelMat");

	float outlineColour[] = { 0.0f, 1.0f, 0.0f, 0.5f };
	float sensitivity = 0.9f;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CubeMesh cube;
	cube.load();

	PlaneMesh plane;
	plane.load();

	TriangleMesh triangle;
	triangle.load();

	PerfectlyGenericObject myObject, screen;
	myObject.initialise(&cube);
	screen.initialise(&plane);

	float checkerBoardPixels[] = {
		0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f
	};

	dix::Texture texChecker;
	texChecker.create(dix::Vector2u(2, 2), checkerBoardPixels);

	dix::Framebuffer fbOutlineFirstPass;
	fbOutlineFirstPass.initialise(1280, 960, dix::FramebufferAttachment::DEPTH_BUFFER, true, false);
	

	FrequencySelectedBeats beats;
	beats.loadFromFile("necro.beat");
	unsigned int locLastBeat = 0;
	float offset = 0.0f;
	float offsetChange = 1.0f;
	float offsetRevertSpeed = 4.0f;

	sf::Music tune;
	tune.openFromFile("necro.ogg");
	tune.setLoop(false);
	tune.play();
	glfwSetTime(0.0);
	float time = 0.0f;
	while (!window.shouldClose())
	{
		float dt = glfwGetTime();
		time = tune.getPlayingOffset().asSeconds();
		glfwSetTime(0.0);

		window.pollEvents();

		myObject.tick(dt);
		
		unsigned int curInstant = (time/1024)*44100;

		if (offset > 0)
		{
			offset -= offsetRevertSpeed * dt;
			if (offset < 0)
			{
				offset = 0;
			}
		}
		viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.5f));
		FrequencyOutlier* beat = beats.getLastBeatBefore(curInstant);
		if (beat)
		{
			unsigned int lastBeat = beat->m_instant;
			//Compare recently found last beat to previous recorded value, if different there might be a beat
			if (lastBeat != locLastBeat)
			{
				//Limit detected beats to subband 0, and only those with a threshold over 400 while the camera's offset is at 0.
				if (beat->m_subbands.at(0) == 0 && beat->m_thresholds.at(0) > 400.0f && offset == 0)
				{
					//Beat detected, zoom on cube
					offset = offsetChange;
					locLastBeat = lastBeat;
				}
			}
		}
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, offset));

		fbOutlineFirstPass.bindBuffer();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, texChecker.getHandle());
		glUseProgram(outlineFirstPassProgram);
		glUniformMatrix4fv(outlineFirstPassProjMatU, 1, NULL, &projectionMatrix[0][0]);
		glUniformMatrix4fv(outlineFirstPassViewMatU, 1, NULL, &viewMatrix[0][0]);
		myObject.draw(outlineFirstPassModelMatU);

		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
		glDisable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(screenProgram);
		glBindTexture(GL_TEXTURE_2D, fbOutlineFirstPass.getTexture().getHandle());
		screen.draw(screenModelMatU);

		glUseProgram(outlineProgram);
		glBindTexture(GL_TEXTURE_2D, fbOutlineFirstPass.getExtraTexture().getHandle());
		glUniform1f(outlineTextureWidthU, fbOutlineFirstPass.getSize().m_x);
		glUniform1f(outlineTextureHeightU, fbOutlineFirstPass.getSize().m_y);
		glUniform4fv(outlineLineColourU, 1, outlineColour);
		glUniform1f(outlineSensitivityU, sensitivity);
		screen.draw(outlineModelMatU); 
		
		window.swapBuffers();
	}
	fbOutlineFirstPass.cleanup();
	myObject.cleanup();
	plane.unload();
	cube.unload();
	triangle.unload();
	window.cleanup();
	glfwTerminate();
	return 0;
}