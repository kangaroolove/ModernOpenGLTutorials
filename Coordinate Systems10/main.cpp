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

const int ScreenWidth = 800;
const int ScreenHeight = 600;

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
	// 使用现代化技术管理OpenGL指针
	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	// 设置视口
	glViewport(0, 0, width, height);

	Shader ourShader("shader/shader.vs", "shader/shader.frag");

	float vertices[] = {
		// positions                    // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// 顶点缓冲对象
	GLuint VBO;
	// 顶点数组对象，里面存的是顶点属性指针
	GLuint VAO;

	GLuint EBO;
	// 生成一个VAO ID
	glGenVertexArrays(1, &VAO);
	// 生成一个VBO ID
	glGenBuffers(1, &VBO);

	glGenBuffers(1, &EBO);

	// 从绑定之后起，我们应该绑定和配置对应的VBO和属性指针
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 复制顶点数据到缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 配置顶点属性指针
	// 第一个参数：对应layout(location = 0)
	// 第二个参数：顶点属性大小，对应vec3
	// 第三个参数：表示希望数据标准化
	// 第四个参数：步长，顶点属性之间的间隔，下一个位置再3个GLfloat之后
	// 第五个参数：数据在缓冲中起始位置的偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	// 启用顶点属性，对应layout(location = 0),顶点属性默认关闭
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	unsigned int texture1;
	unsigned int texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// 设置纹理包装格式：x和y都重复，默认的包装形式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置算法格式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int pictureWidth = 0;
	int pictureHeight = 0;
	int nrChannels = 0;

	// 翻转Y轴
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data1 = stbi_load("res/wood.jpg", &pictureWidth, &pictureHeight, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pictureWidth, pictureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置算法格式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data2 = stbi_load("res/smile.png", &pictureWidth, &pictureHeight, &nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pictureWidth, pictureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data2);

	// 告诉opengl每个采样器属于哪个纹理单元（只需要做一次）。
	// 在设置uniform之前，先激活shader
	ourShader.Use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);


	// 解绑VBO，避免数据再被修改(这是被允许的，因为glVertexAttribPointer已经注册了当前的VBO, 所以我们可以安全的解绑)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 解绑VAO，避免数据再被修改(解绑任何buffer/array来防止陌生的bugs,这是一个好习惯)
	glBindVertexArray(0);

	// 设置清屏颜色
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// 一般当你打算绘制多个物体，你首先要生成/配置所有VAO（和必须的VBO及属性指针），然后储存它们供后面使用，
	// 当我们打算绘制物体时就拿出相应的VAO，绑定它，绘制完物体后，在解绑VAO。

	while (!glfwWindowShouldClose(window))
	{
		// 接受鼠标和键盘事件
		glfwPollEvents();
		// 渲染指令

		// 以设置的清屏颜色进行清屏
		glClear(GL_COLOR_BUFFER_BIT);

		// 绑定纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.Use();

		glm::mat4 model(1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 projecton(1.0f);

		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projecton = glm::perspective(glm::radians(45.0f), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(ourShader.Program, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.Program, "view");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		ourShader.setMat4("projection", projecton);

		glBindVertexArray(VAO);
		// 使用当前激活的着色器，VAO来绘制图元
		// 第一个参数：类型
		// 第二个参数：顶点数组的起始索引
		// 第三个参数：绘制多少个顶点
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// 前后缓冲交换，刷新屏幕
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}