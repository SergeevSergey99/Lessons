#include <GL/freeglut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(const string& s, char delim) {
    stringstream ss(s);
    string item;
    vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}



struct object
{
    struct point
    {
        double x;
        double y;
        double z;
    }; 
    struct normal
    {
        double x;
        double y;
        double z;
    };
    struct face
    {
        unsigned int vertex_1;
        unsigned int vertex_2;
        unsigned int vertex_3;

        unsigned int normal_1;
        unsigned int normal_2;
        unsigned int normal_3;
    };
    // vertices
    vector<int> fs;
    vector<point> v;
    vector<normal> vn;
    // faces
    vector<face> f;
    void Load(string fileName)
    {
        ifstream fin(fileName);

        string str;
        int j = 0;
        int facecnt = 0;
        while (fin.is_open())
        {
            getline(fin, str);
            if (fin.eof())
            {

                fin.close();
            }
            if (str[0] == 'v' and str[1] == ' ')
            {
                if(facecnt!=0)
                {
                    fs.push_back(facecnt);
                    facecnt = 0;
                }
                vector<string> vertexs = split(str, ' ');

                point _v;
                _v.x = stod(vertexs[2]) / 1000.0;
                _v.y = stod(vertexs[3]) / 1000.0;
                _v.z = stod(vertexs[4]) / 1000.0;
                v.push_back(_v);

            }
            if (str[0] == 'v' and str[1] == 'n')
            {
                vector<string> vertexs = split(str, ' ');

                normal _v;
                _v.x = stod(vertexs[2]);
                _v.y = stod(vertexs[3]);
                _v.z = stod(vertexs[4]);
                vn.push_back(_v);

            }
            if (str[0] == 'f' and str[1] == ' ')
            {
                facecnt++;
                vector<string> faces = split(str, ' ');

                vector<string> face1 = split(faces[1], '/');
                vector<string> face2 = split(faces[2], '/');
                vector<string> face3 = split(faces[3], '/');
                face _f;
                _f.vertex_1 = stoi(face1[0]) - 1;
                _f.vertex_2 = stoi(face2[0]) - 1;
                _f.vertex_3 = stoi(face3[0]) - 1;

                _f.normal_1 = stoi(face1[1]) - 1;
                _f.normal_2 = stoi(face2[1]) - 1;
                _f.normal_3 = stoi(face3[1]) - 1;

                f.push_back(_f);
            }
            if (j % 1000 == 0)
                cout << j << endl;
            j++;
        }
        cout << "Readed" << endl;


    }
    void draw()
    {
        glBegin(GL_TRIANGLES);
        srand(0);
        glColor3f(0.0f, 0.0f, 1.0f);
        int findex = 0;
        int cnt = 0;
        for (int i = 0; i < f.size(); i++)
        {
            if(findex < fs.size() and cnt >= fs[findex])
            {
                glColor3f(rand()%101 / 100.0f, rand() % 101 / 100.0f, rand() % 101 / 100.0f);

                findex++;
                cnt = 0;
            }
            cnt++;
            glNormal3f(
                vn[f[i].normal_1].x,
                vn[f[i].normal_1].y,
                vn[f[i].normal_1].z);
            glVertex3f(
                v[f[i].vertex_1].x,
                v[f[i].vertex_1].y,
                v[f[i].vertex_1].z);

            glNormal3f(
                vn[f[i].normal_2].x,
                vn[f[i].normal_2].y,
                vn[f[i].normal_2].z);
            glVertex3f(
                v[f[i].vertex_2].x,
                v[f[i].vertex_2].y,
                v[f[i].vertex_2].z);

            glNormal3f(
                vn[f[i].normal_3].x,
                vn[f[i].normal_3].y,
                vn[f[i].normal_3].z);
            glVertex3f(
                v[f[i].vertex_3].x,
                v[f[i].vertex_3].y,
                v[f[i].vertex_3].z);
        }
        glEnd();
    }
};




object MyObject;
int a = 0;
double x = 0, y = -2.0, z = -16;
void Display()
{
    glClearColor(0.6, 0.6, 0.6, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
    glLoadIdentity();


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);


    glTranslated(x,y,z);
    glRotated(50.0 * a * 0.005, 0, 1, 0);
   
    a++;

    MyObject.draw();

    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();
}

void Keyboard(unsigned char Key, int X, int Y)
{
    if (Key == 27)
        exit(0);
    if (Key == 'w')
    {
        z++;
        cout << x << " " << y << " " << z << endl;
    }
    if (Key == 's')
    {
        z--;
        cout << x << " " << y << " " << z << endl;
    }
    if (Key == 'd')
    {
        x++;
        cout << x << " " << y << " " << z << endl;
    }
    if (Key == 'a')
    {
        x--;
        cout << x << " " << y << " " << z << endl;
    }
    if (Key == 'r')
    {
        y++;
        cout << x << " " << y << " " << z << endl;
    }
    if (Key == 'f')
    {
        y--;
        cout << x << " " << y << " " << z << endl;
    }
    if (Key == ' ')
    {
        x = 0;
        y = 0;
        z = 0;

        cout << x << " " << y << " " << z << endl;
    }
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
    MyObject.Load("BMW_M3_GTR.obj");

    // Инициализация
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // положение создаваемого окна относительно верхнего левого угла экрана
    glutInitWindowPosition(0, 0);
    // Размер окна
    glutInitWindowSize(1400, 1000);
    // Создание окна с именем
    glutCreateWindow("SERGEEV SERGEY 11-6");

    glutDisplayFunc(Display);       // Задание функции отрисовки
    glutKeyboardFunc(Keyboard);     // Задание функции клавиатуры
    
    glutFullScreen();       // Переход в полноэкранный режим

    initialize(); // настройки пространства

    glutMainLoop(); // запуск основного цикла
}