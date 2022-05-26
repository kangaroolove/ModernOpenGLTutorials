// 必须包含的头文件
#include <GL/freeglut.h>
// 声明回调函数
void RenderSceneCB(void);

void main(int argc, char** argv)
{
	// 初始化glut
	glutInit(&argc, argv);
	// 初始化glut的显示模式GLUT_DOUBLE代表为双缓冲，RGBA为颜色缓冲
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// 初始化窗口的尺寸
	glutInitWindowSize(1024, 768);
	// 初始化窗口的位置
	glutInitWindowPosition(100, 100);
	// 设置窗口的标题
	glutCreateWindow("Create a window");
	// RenderSceneCB是一个回调函数，GLUT会在内部循环不断调用这个函数
	glutDisplayFunc(RenderSceneCB);
	// 设置清屏颜色
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	// 进入主事件循环
	glutMainLoop();
}

void RenderSceneCB(void)
{
	// 以glClearColor设置的颜色进行清屏
	glClear(GL_COLOR_BUFFER_BIT);
	// 交换前后缓冲
	glutSwapBuffers();
}