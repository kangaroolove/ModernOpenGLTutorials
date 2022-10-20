// 必须包含的头文件
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"color = ourColor;\n"
"}\n\0";

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

	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloTriangle", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// 使用现代化技术管理OpenGL指针
	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	// 设置视口
	glViewport(0, 0, width, height);

	// 设置顶点着色器
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 第二个参数指定了传递的源码字符串数量
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex shader error" << std::endl;
	}

	// 设置片段着色器
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment shader error" << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Shader program link error" << std::endl;
	}

	// 着色器对象连接到程序对象以后，删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		 0.5f, -0.5f, 0.0f, // Right 
		 0.0f,  0.5f, 0.0f  // Top   
	};

	// 顶点缓冲对象
	GLuint VBO;
	// 顶点数组对象，里面存的是顶点属性指针
	GLuint VAO;
	// 生成一个VAO ID
	glGenVertexArrays(1, &VAO);
	// 生成一个VBO ID
	glGenBuffers(1, &VBO);

	// 从绑定之后起，我们应该绑定和配置对应的VBO和属性指针
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 复制顶点数据到缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 配置顶点属性指针
	// 第一个参数：对应layout(location = 0)
	// 第二个参数：顶点属性大小，对应vec3
	// 第三个参数：表示希望数据标准化
	// 第四个参数：步长，顶点属性之间的间隔，下一个位置再3个GLfloat之后
	// 第五个参数：数据在缓冲中起始位置的偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// 启用顶点属性，对应layout(location = 0),顶点属性默认关闭
	glEnableVertexAttribArray(0);

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

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		double timeValue = glfwGetTime();
		float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		// 获取uniform的地址
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		// 设置uniform的值
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// 使用当前激活的着色器，VAO来绘制图元
		// 第一个参数：类型
		// 第二个参数：顶点数组的起始索引
		// 第三个参数：绘制多少个顶点
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		// 前后缓冲交换，刷新屏幕
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}