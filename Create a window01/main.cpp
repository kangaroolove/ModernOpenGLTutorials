#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	// ��ʼ��GLFW
	glfwInit();
	// ����context�İ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ������Ⱦģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// ʹ���ִ�����������OpenGLָ��
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width = 0;
	int height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	// �����ӿ�
	glViewport(0, 0, width, height);

	// ����������ɫ
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		// �������ͼ����¼�
		glfwPollEvents();
		// ��Ⱦָ��
		// �����õ�������ɫ��������
		glClear(GL_COLOR_BUFFER_BIT);
		// ǰ�󻺳彻����ˢ����Ļ
		glfwSwapBuffers(window);
	}


	return 0;
}