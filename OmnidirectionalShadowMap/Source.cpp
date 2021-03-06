#include <vector>

#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\math\vec.h"
#include "src\math\mat4.h"

#define STB_IMAGE_IMPLEMENTATION
#include "src\utils\stb_image.h"
#include "src\utils\utils.h"

using namespace core;
using namespace graphics;
using namespace math;

#define ArrayCount(A) (sizeof(A)/sizeof(A[0]))

void RenderScene(GLuint ShaderID, GLuint CubeVAO)
{
	mat4 Model = mat4::Scale(5.0f);
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, "Model"), 1, GL_FALSE, Model.Elements);	
	glDisable(GL_CULL_FACE);
	glUniform1i(glGetUniformLocation(ShaderID, "ReverseNormals"), -1);	
	glBindVertexArray(CubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glUniform1i(glGetUniformLocation(ShaderID, "ReverseNormals"), 1);
	glEnable(GL_CULL_FACE);

	Model = mat4::Translation(vec3(4.0f, -3.5f, 0.0f));
    Model = Model * mat4::Scale(0.5f);
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, "Model"), 1, GL_FALSE, Model.Elements);		
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Model = mat4::Translation(vec3(2.0f, 3.0f, 1.0f));
	Model = Model * mat4::Scale(0.75f);
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, "Model"), 1, GL_FALSE, Model.Elements);		
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Model = mat4::Translation(vec3(-3.0f, -1.0f, 0.0f));
	Model = Model * mat4::Scale(0.5f);
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, "Model"), 1, GL_FALSE, Model.Elements);		
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Model = mat4::Translation(vec3(-1.5f, 1.0f, 1.5f));
	Model = Model * mat4::Scale(0.5f);
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, "Model"), 1, GL_FALSE, Model.Elements);		
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Model = mat4::Translation(vec3(-1.5f, 2.0f, -3.0f));
	Model = Model * mat4::Rotate(60.0f, vec3(1.0f, 0.0f, 1.0f));
	Model = Model * mat4::Scale(0.75f);
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, "Model"), 1, GL_FALSE, Model.Elements);		
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main(void)
{
	window Window("WindowName", 900, 540);
	glClearColor(0.3f, 0.3f, 0.8f, 1.0f);

	shader Shader("src/shaders/vertex.vert", "src/shaders/fragment.frag");
	shader ShadowMapShader("src/shaders/shadowmap.vert", "src/shaders/shadowmap.frag", "src/shaders/shadowmap.geom");

	float CubeVertices[] = {
		// back face
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
		// front face
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
		1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		// left face
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		// right face
		1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
		1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
		1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		// top face
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
		1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
	};

    GLuint CubeVAO, CubeVBO;
	glGenVertexArrays(1, &CubeVAO);
	glGenBuffers(1, &CubeVBO);
	glBindVertexArray(CubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(3*sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(6*sizeof(float)));
	glBindVertexArray(0);

	GLuint WoodTexture = LoadTexture("wood.png");

	GLuint ShadowMapFB;
	glGenFramebuffers(1, &ShadowMapFB);

	const int ShadowMapWidth = 1024, ShadowMapHeight = 1024;	
	GLuint ShadowCubemap;
	glGenTextures(1, &ShadowCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ShadowCubemap);
	for(int I = 0; I < 6; I++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + I, 0, GL_DEPTH_COMPONENT, ShadowMapWidth, ShadowMapHeight, 0,
					 GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFB);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ShadowCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ShadowMapShader.Enable();	
	vec3 LightPosWorld = vec3(0.0f, 0.0f, 0.0f);
	float Near = 1.0f;
	float Far = 25.0f;
	mat4 LightProjection = mat4::Perspective(90.0f, (float)ShadowMapWidth/(float)ShadowMapHeight, Near, Far);
	mat4 LightSpaceTransforms[6];
	LightSpaceTransforms[0] = LightProjection * mat4::LookAt(LightPosWorld, LightPosWorld + vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f,  0.0f));
	LightSpaceTransforms[1] = LightProjection * mat4::LookAt(LightPosWorld, LightPosWorld + vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f,  0.0f));
	LightSpaceTransforms[2] = LightProjection * mat4::LookAt(LightPosWorld, LightPosWorld + vec3(0.0f, 1.0f, 0.0f), vec3(0.0f,  0.0f,  1.0f));
	LightSpaceTransforms[3] = LightProjection * mat4::LookAt(LightPosWorld, LightPosWorld + vec3(0.0f, -1.0f, 0.0f), vec3(0.0f,  0.0f, -1.0f));
	LightSpaceTransforms[4] = LightProjection * mat4::LookAt(LightPosWorld, LightPosWorld + vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, -1.0f,  0.0f));
	LightSpaceTransforms[5] = LightProjection * mat4::LookAt(LightPosWorld, LightPosWorld + vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, -1.0f,  0.0f));
	for(int I = 0; I < 6; I++)
	{
		glUniformMatrix4fv(glGetUniformLocation(ShadowMapShader.ShaderID, ("LightSpaceMatrices[" + std::to_string(I) + "]").c_str()), 
						   1, GL_FALSE, LightSpaceTransforms[I].Elements);
	}
	glUniform3fv(glGetUniformLocation(ShadowMapShader.ShaderID, "LightPos"), 1, &LightPosWorld.x);
	glUniform1f(glGetUniformLocation(ShadowMapShader.ShaderID, "FarPlane"), Far);

	Shader.Enable();
	mat4 Projection = mat4::Perspective(45.0f, (float)Window.Width/(float)Window.Height, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(Shader.ShaderID, "Projection"), 1, GL_FALSE, Projection.Elements);
	glUniform1i(glGetUniformLocation(Shader.ShaderID, "DiffuseTexture"), 0);
	glUniform1i(glGetUniformLocation(Shader.ShaderID, "ShadowMap"), 1);

 	float DeltaTime = 0.0f;
	float LastFrame = 0.0f;
	while(!Window.Closed())
	{
		float CurrentFrame = (float)glfwGetTime();
		DeltaTime = CurrentFrame - LastFrame;
		LastFrame = CurrentFrame;						 
		Window.ProcessInput(DeltaTime);

		ShadowMapShader.Enable();
		glViewport(0, 0, ShadowMapWidth, ShadowMapHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFB);
		glClear(GL_DEPTH_BUFFER_BIT);
		RenderScene(ShadowMapShader.ShaderID, CubeVAO);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Window.Width, Window.Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Shader.Enable();
		mat4 View = mat4::LookAt(Window.Camera.Position, Window.Camera.Position + Window.Camera.Front);
		glUniformMatrix4fv(glGetUniformLocation(Shader.ShaderID, "View"), 1, GL_FALSE, View.Elements);

		glUniform3fv(glGetUniformLocation(Shader.ShaderID, "CamPosWorld"), 1, &Window.Camera.Position.x);
		glUniform3fv(glGetUniformLocation(Shader.ShaderID, "LightPosWorld"), 1, &LightPosWorld.x);
		glUniform1f(glGetUniformLocation(Shader.ShaderID, "FarPlane"), Far);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, WoodTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, ShadowCubemap);
		RenderScene(Shader.ShaderID, CubeVAO);

		glfwPollEvents();
		glfwSwapBuffers(Window.Window);
	}

	system("PAUSE");
	return(0);
}