// ���������ͷ�ļ�
#include <GL/freeglut.h>
// �����ص�����
void RenderSceneCB(void);

void main(int argc, char** argv)
{
	// ��ʼ��glut
	glutInit(&argc, argv);
	// ��ʼ��glut����ʾģʽGLUT_DOUBLE����Ϊ˫���壬RGBAΪ��ɫ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// ��ʼ�����ڵĳߴ�
	glutInitWindowSize(1024, 768);
	// ��ʼ�����ڵ�λ��
	glutInitWindowPosition(100, 100);
	// ���ô��ڵı���
	glutCreateWindow("Create a window");
	// RenderSceneCB��һ���ص�������GLUT�����ڲ�ѭ�����ϵ����������
	glutDisplayFunc(RenderSceneCB);
	// ����������ɫ
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	// �������¼�ѭ��
	glutMainLoop();
}

void RenderSceneCB(void)
{
	// ��glClearColor���õ���ɫ��������
	glClear(GL_COLOR_BUFFER_BIT);
	// ����ǰ�󻺳�
	glutSwapBuffers();
}