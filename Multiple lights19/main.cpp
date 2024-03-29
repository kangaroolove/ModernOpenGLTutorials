// 必须包含的头文件
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

const int ScreenWidth = 800;
const int ScreenHeight = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = ScreenWidth / 2.0f;
float lastY = ScreenHeight / 2.0f;
bool firstMouse = true;

//时间
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

int main(int argc, char** argv)
{
	// 初始化GLFW
	glfwInit();
	// 设置context的版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 核心渲染模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "HelloTriangle", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// 使用现代化技术管理OpenGL指针
	//glewExperimental = GL_TRUE;
	glewInit();

	// 打开深度测试
	glEnable(GL_DEPTH_TEST);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	// 设置视口
	glViewport(0, 0, width, height);

	Shader cubeShader("shader/cubeShader.vs", "shader/cubeShader.frag");
	Shader lightCubeShader("shader/lightCubeShader.vs", "shader/lightCubeShader.frag");

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	// position all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};

	// 顶点缓冲对象
	GLuint VBO;
	// 顶点数组对象，里面存的是顶点属性指针
	GLuint cubeVAO;

	// 生成一个VAO ID
	glGenVertexArrays(1, &cubeVAO);
	// 生成一个VBO ID
	glGenBuffers(1, &VBO);

	// 从绑定之后起，我们应该绑定和配置对应的VBO和属性指针
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 复制顶点数据到缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// 配置顶点属性指针
	// 第一个参数：对应layout(location = 0)
	// 第二个参数：顶点属性大小，对应vec3
	// 第三个参数：表示希望数据标准化
	// 第四个参数：步长，顶点属性之间的间隔，下一个位置再3个GLfloat之后
	// 第五个参数：数据在缓冲中起始位置的偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	// 启用顶点属性，对应layout(location = 0),顶点属性默认关闭
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	GLuint lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	// 只需要绑定VBO, 不再需要复制到缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(0));
	glEnableVertexAttribArray(0);

	unsigned int diffuseMap = loadTexture("res/container2.png");
    unsigned int specularMap = loadTexture("res/container2_specular.png");

	cubeShader.Use();
	cubeShader.setInt("material.diffuse", 0);
    cubeShader.setInt("material.specular", 1);

	// 设置清屏颜色
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// 一般当你打算绘制多个物体，你首先要生成/配置所有VAO（和必须的VBO及属性指针），然后储存它们供后面使用，
	// 当我们打算绘制物体时就拿出相应的VAO，绑定它，绘制完物体后，在解绑VAO。

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// 渲染指令

		// 以设置的清屏颜色进行清屏
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cubeShader.Use();
		//cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		//cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		cubeShader.setVec3("viewPos", camera.Position);
		// material properties
		cubeShader.setFloat("material.shininess", 32.0f);

		cubeShader.setVec3("dirLight.direction", -2.0f, -1.0f, -0.3f);
		cubeShader.setVec3("dirLight.ambient", 0.05, 0.05f, 0.05f);
		cubeShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		cubeShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);


		for (int i = 0; i < 4; i++)
		{
			cubeShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
			cubeShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.5f, 0.5f, 0.5f);
			cubeShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", 0.8f, 0.8f, 0.8f);
			cubeShader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
			cubeShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
			cubeShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
			cubeShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
		}

		cubeShader.setVec3("spotLight.position", camera.Position);
		cubeShader.setVec3("spotLight.direction", camera.Front);
		cubeShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		cubeShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		cubeShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		cubeShader.setFloat("spotLight.constant", 1.0f);
		cubeShader.setFloat("spotLight.linear", 0.09f);
		cubeShader.setFloat("spotLight.quadratic", 0.032f);
		cubeShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		cubeShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(camera.Zoom), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);
		cubeShader.setMat4("projection", projection);

		glm::mat4 view = camera.GetViewMatrix();
		cubeShader.setMat4("view", view);

		glm::mat4 model(1.0f);
		cubeShader.setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubeShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightCubeShader.Use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightCubeShader.setMat4("model", model);

		glBindVertexArray(lightCubeVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightCubeShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// 前后缓冲交换，刷新屏幕
		glfwSwapBuffers(window);
		// 接受鼠标和键盘事件
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyborad(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyborad(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyborad(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyborad(RIGHT, deltaTime);
}

unsigned int loadTexture(const char* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width;
	int height;
	int nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
		{
			format = GL_RED;
		}
		else if (nrComponents == 3)
		{
			format = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path:"<<path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
