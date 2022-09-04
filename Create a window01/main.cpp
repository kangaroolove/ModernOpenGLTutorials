#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	// 初始化GLFW
	glfwInit();
	// 设置context的版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 核心渲染模式
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

	// 使用现代化技术管理OpenGL指针
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width = 0;
	int height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	// 设置视口
	glViewport(0, 0, width, height);

	// 设置清屏颜色
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		// 接受鼠标和键盘事件
		glfwPollEvents();
		// 渲染指令
		// 以设置的清屏颜色进行清屏
		glClear(GL_COLOR_BUFFER_BIT);
		// 前后缓冲交换，刷新屏幕
		glfwSwapBuffers(window);
	}


	return 0;
}