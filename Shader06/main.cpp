// ���������ͷ�ļ�
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

int main(int argc, char** argv)
{
	// ��ʼ��GLFW
	glfwInit();
	// ����context�İ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ������Ⱦģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloTriangle", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// ʹ���ִ�����������OpenGLָ��
	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	// �����ӿ�
	glViewport(0, 0, width, height);

	Shader ourShader("shader/shader.vs", "shader/shader.frag");

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Left  
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Right 
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f // Top   
	};

	// ���㻺�����
	GLuint VBO;
	// ������������������Ƕ�������ָ��
	GLuint VAO;
	// ����һ��VAO ID
	glGenVertexArrays(1, &VAO);
	// ����һ��VBO ID
	glGenBuffers(1, &VBO);

	// �Ӱ�֮��������Ӧ�ð󶨺����ö�Ӧ��VBO������ָ��
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���ƶ������ݵ�������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	// ��һ����������Ӧlayout(location = 0)
	// �ڶ����������������Դ�С����Ӧvec3
	// ��������������ʾϣ�����ݱ�׼��
	// ���ĸ���������������������֮��ļ������һ��λ����3��GLfloat֮��
	// ����������������ڻ�������ʼλ�õ�ƫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	// ���ö������ԣ���Ӧlayout(location = 0),��������Ĭ�Ϲر�
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// ���VBO�����������ٱ��޸�(���Ǳ�����ģ���ΪglVertexAttribPointer�Ѿ�ע���˵�ǰ��VBO, �������ǿ��԰�ȫ�Ľ��)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// ���VAO�����������ٱ��޸�(����κ�buffer/array����ֹİ����bugs,����һ����ϰ��)
	glBindVertexArray(0);

	// ����������ɫ
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// һ�㵱�������ƶ�����壬������Ҫ����/��������VAO���ͱ����VBO������ָ�룩��Ȼ�󴢴����ǹ�����ʹ�ã�
	// �����Ǵ����������ʱ���ó���Ӧ��VAO��������������������ڽ��VAO��

	while (!glfwWindowShouldClose(window))
	{
		// �������ͼ����¼�
		glfwPollEvents();
		// ��Ⱦָ��

		// �����õ�������ɫ��������
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();
		glBindVertexArray(VAO);
		// ʹ�õ�ǰ�������ɫ����VAO������ͼԪ
		// ��һ������������
		// �ڶ��������������������ʼ����
		// ���������������ƶ��ٸ�����
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		// ǰ�󻺳彻����ˢ����Ļ
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}