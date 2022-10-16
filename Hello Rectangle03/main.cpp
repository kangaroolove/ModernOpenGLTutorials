// ���������ͷ�ļ�
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

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

	// ���ö�����ɫ��
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// �ڶ�������ָ���˴��ݵ�Դ���ַ�������
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

	// ����Ƭ����ɫ��
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

	// ��ɫ���������ӵ���������Ժ�ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	
	// �����������
	GLuint EBO;
	// ���㻺�����
	GLuint VBO;
	// ������������������Ƕ�������ָ��
	GLuint VAO;
	// ����һ��VAO ID
	glGenVertexArrays(1, &VAO);
	// ����һ��VBO ID
	glGenBuffers(1, &VBO);
	// ����һ��VEO ID
	glGenBuffers(1, &EBO);

	// �Ӱ�֮��������Ӧ�ð󶨺����ö�Ӧ��VBO������ָ��
	glBindVertexArray(VAO);
	// �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���ƶ������ݵ�������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ��Ŀ����GL_ELEMENT_ARRAY_BUFFER��ʱ��VAO�ᴢ��glBindBuffer�ĺ������á�
	// ��Ҳ��ζ����Ҳ�ᴢ������ã�����ȷ����û���ڽ��VAO֮ǰ����������黺�壬��������û�����EBO������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	// ��һ����������Ӧlayout(location = 0)
	// �ڶ����������������Դ�С����Ӧvec3
	// ��������������ʾϣ�����ݱ�׼��
	// ���ĸ���������������������֮��ļ������һ��λ����3��GLfloat֮��
	// ����������������ڻ�������ʼλ�õ�ƫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// ���ö������ԣ���Ӧlayout(location = 0),��������Ĭ�Ϲر�
	glEnableVertexAttribArray(0);

	// ���VBO�����������ٱ��޸�(���Ǳ������ģ���ΪglVertexAttribPointer�Ѿ�ע���˵�ǰ��VBO, �������ǿ��԰�ȫ�Ľ��)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// ���VAO�����������ٱ��޸�(����κ�buffer/array����ֹİ����bugs,����һ����ϰ��, ���Ǽ�ס��Ҫ���EBO)
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

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// ʹ�õ�ǰ�������ɫ����VAO������ͼԪ
		// ��һ������������
		// �ڶ��������������������ʼ����
		// ���������������ƶ��ٸ�����
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// ǰ�󻺳彻����ˢ����Ļ
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}