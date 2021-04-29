#include <GL/freeglut.h>
void Display()
{
    glClearColor(0.6, 0.6, 0.6, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
    glLoadIdentity();


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glTranslated(0,0,1.0 -10.0);

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();
}

void Keyboard(unsigned char Key, int X, int Y)
{
    if (Key == 27)
        exit(0);
}

void initialize()
{
    glMatrixMode(GL_PROJECTION);                // set matrix mode
    glLoadIdentity();                           // reset projection matrix
    GLfloat aspect = (GLfloat)1400.0/ 1000;
    gluPerspective(45, aspect, 1.0f, 500.0f);   // set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);                 // specify which matrix is the current matrix
    glClearDepth(1.0f);                         // specify the clear value for the depth buffer
    glEnable(GL_DEPTH_TEST);
}
void main(int argc, char* argv[])
{

    // Инициализация
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // положение создаваемого окна относительно верхнего левого угла экрана
    glutInitWindowPosition(0, 0);
    // Размер окна
    glutInitWindowSize(1400, 1000);
    // Создание окна с именем
    glutCreateWindow("OpenGL");

    glutDisplayFunc(Display);       // Задание функции отрисовки
    glutKeyboardFunc(Keyboard);     // Задание функции клавиатуры
    
    glutFullScreen();       // Переход в полноэкранный режим

    initialize(); // настройки пространства

    glutMainLoop(); // запуск основного цикла
}