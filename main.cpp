#include <bits/stdc++.h>

#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)

using namespace std;

#include <GL/glut.h>

GLuint makeaTree;
//float x,y,z;
// angle for rotating triangle
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f,y;

void makeCylinder(float height, float base){
int randd =
randd=rand()%50+20;
GLUquadric *obj = gluNewQuadric();
//gluQuadricDrawStyle(obj, GLU_LINE);
glColor3f(0.64f, 0.16, 0.16f);glPushMatrix();
glRotatef(-90, 1.0,0.0,0.0);
gluCylinder(obj, base,base-(0.2*base), height, 20,20);
glPopMatrix();
glutSwapBuffers();
}


void makeTree(float height, float base){
    int randy = 0;
    float angle;
    makeCylinder(height, base);
    glTranslatef(0.0f, height, 0.0f);
    height -= height * 0.2f;
    base -= base * 0.3f;

    FOR(a, 0, 3) {
        angle = rand() % 50 + 20;
        if (angle > 48)
            angle = -(rand() % 50 + 20);
        if (height > 1) {
            randy = rand() % 50 + 20;
            glPushMatrix();
            glRotatef(angle, 1, 0, 1);
            makeTree(height,base);
            glPopMatrix();
        }
        else glColor3f(0.0,1.0/a,0.0);glutSolidSphere(.2,10,10);
    }
}

void init(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    makeaTree = glGenLists(1);
    glNewList(makeaTree, GL_COMPILE);
    makeTree(4, 0.2f);
    glEndList();
}

//void keyboard(unsigned char key, int x, int y){
//switch (key){
//case 'x':
//x +=10;
//glutPostRedisplay();
//break;
//case 'y':
//y +=10;
//glutPostRedisplay();
//break;
//case 'z':
//z+=10;
//glutPostRedisplay();
//break;
//}
//}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(x, 1.0f, 0.0f, 0.0f);
    glRotatef(y, 0.0f, 1.0f, 0.0f);
    glRotatef(z, 0.0f, 0.0f, 1.0f);
    glCallList(makeaTree);

    glPopMatrix();
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)  exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {
    float fraction = 0.1f;

    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.41f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.41f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, (GLfloat) w/(GLfloat) h, 0.001f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, -8.0f, -50.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1200, 800); glutInitWindowPosition(0,0);
    glutCreateWindow("3D Tree Using Recursion");
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutDisplayFunc(display);

    glutMainLoop();

    return EXIT_SUCCESS;
}
