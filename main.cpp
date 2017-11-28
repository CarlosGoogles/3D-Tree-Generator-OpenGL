#include <bits/stdc++.h>
#include <GL/glut.h>

#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define pb push_back

#define PI 3.14159265358979323846

using namespace std;

typedef pair<int, int> ii;

void reCreateTree();

#include "Geometry.h"
#include "Matrix.h"
#include "Utility.h"
#include "CameraWindow.h"
#include "ModifierWindow.h"

GLuint makeaTree;

void makeCylinder(double height, double base) {
    int randd = rand() % 50 + 20;
    GLUquadric *obj = gluNewQuadric();
    //gluQuadricDrawStyle(obj, GLU_LINE);
    glColor3d( 0.64d, 0.16d, 0.16d);
    glPushMatrix();
        glRotated(-90.0d, 1.00d, 0.0d, 0.0d);
        gluCylinder(obj, base, 0.8d * base, height, 20.0d, 20.0d);
    glPopMatrix();
    glutSwapBuffers();
}

Matrix matrizInitial;
static int cant = 1;
void makeTree(double height, double base, const bool b, Matrix matrizActual) {

    // makeCylinder(height, base);

    //glTranslated(0.0d, height, 0.0d);
    createCylinder(base, 0.8d * base, height, matrizActual);
    Matrix matrizMoved = matrizActual;
    matrizMoved = matrizMoved * Matrix::createTranslation(0, height, 0);
    //matrizMoved.pprint();

    height = height * 0.8d;
    base = base * 0.7d;
    cant ++;
    int ramas = rand() % 3 + 3;
    if (b)  ramas = 6;
    cant ++;
    FOR(a, 0, ramas) {
        double angle = rand() % 50 + 20.0;
        if (angle > 48.0d)
            angle = -(rand() % 50 + 20.0);
        if (height > 1.0d) {
            Matrix matrizCycle = matrizMoved;

            //glPushMatrix();
            int randy = rand() % 4;
            if (randy % 2 == 0){
                randy = -randy;
            }
            // glRotated(angle, 1.0d, 0.8, 1.0d);
            matrizCycle = matrizCycle * Matrix::createRotationMatrix(1.0d, 0.8d, 1.0d, angle * PI / 180.d);
            makeTree(height, base, false, matrizCycle);
            //glPopMatrix();
        }
    }
    glColor3d(0.0d, 1.0d / (rand() % 4 + 1.0d), 0.0d);
    // createSphere(0, 0, 0, 0.2d);

    matrizMoved = matrizMoved * Matrix::originalPos();
    createSphere(matrizMoved.mat[0][3], matrizMoved.mat[1][3], matrizMoved.mat[2][3], 0.2d);
    // drawStrokeText(to_string(cant ++), matrizMoved.mat[0][3], matrizMoved.mat[1][3], matrizMoved.mat[2][3], 0.008f, 0.008f, 0.0f, colors[(cant % 5 + 1)]);
    // glutSolidSphere(0.2d, 10.0d, 10.0d);
    cant --;
}

void makeTree2(double height, double base, const bool b, Matrix matrizActual) {

    makeCylinder(height, base);

    glTranslated(0.0d, height, 0.0d);
    //createCylinder(base, 0.8d * base, height, matrizActual);
    Matrix matrizMoved = matrizActual;
    matrizMoved = matrizMoved * Matrix::createTranslation(0, height, 0);
    //matrizMoved.pprint();

    height -= height * 0.2f;
    base -= base * 0.3f;

    int ramas = rand() % 3 + 3;
    if (b)  ramas = 6;
    cant ++;
    FOR(a, 0, ramas) {
        double angle = rand() % 50 + 20.0;
        if (angle > 48.0d)
            angle = -(rand() % 50 + 20.0);
        if (height > 1.0d) {
            Matrix matrizCycle = matrizMoved;

            glPushMatrix();
            int randy = rand() % 4;
            if (randy % 2 == 0){
                randy = -randy;
            }
             glRotated(angle, 1.0d, 0.8, 1.0d);
            matrizCycle = matrizCycle * Matrix::createRotationMatrix(1.0d, 0.8d, 1.0d, angle * PI / 180.d);
            makeTree2(height, base, false, matrizCycle);
            glPopMatrix();
        }
    }
    glColor3d(0.0d, 1.0d / (rand() % 4 + 1.0d), 0.0d);
     createSphere(0, 0, 0, 0.2d);

    matrizMoved = matrizMoved * Matrix::originalPos();
    // createSphere(matrizMoved.mat[0][3], matrizMoved.mat[1][3], matrizMoved.mat[2][3], 0.2d);
    // drawStrokeText(to_string(cant ++), matrizMoved.mat[0][3], matrizMoved.mat[1][3], matrizMoved.mat[2][3], 0.008f, 0.008f, 0.0f, colors[(cant % 5 + 1)]);
    // glutSolidSphere(0.2d, 10.0d, 10.0d);
}

void reCreateTree() {
    matrizInitial = Matrix::identity();
    matrizInitial.pprint();

    glutSetWindow(WindowID1);

    // clear the draw budder .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything


    glClearColor(1.0d, 1.0d, 1.0d, 1.0d);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    makeaTree = glGenLists(1);
    glNewList(makeaTree, GL_COMPILE);

    if (1)  makeTree(3, baseObj, true, matrizInitial);
    else    makeTree2(2, baseObj, true, matrizInitial);
    glEndList();


}

void init(void) {
    reCreateTree();
}

void display() {
    glutSetWindow(WindowID1);

    glLoadIdentity();
    glRotated(-camaraRot[2], 0.0d, 0.0d, 1.0d);
    glRotated(-camaraRot[1], 0.0d, 1.0d, 0.0d);
    glRotated(-camaraRot[0], 1.0d, 0.0d, 0.0d);
    glTranslated(-camaraMov[0], -camaraMov[1], -camaraMov[2]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glRotated(angsObj[0], 1.0d, 0.0d, 0.0d);
        glRotated(angsObj[1], 0.0d, 1.0d, 0.0d);
        glRotated(angsObj[2], 0.0d, 0.0d, 1.0d);
        glCallList(makeaTree);

    glPopMatrix();
    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0d, (GLdouble) w/(GLdouble) h, 0.001d, 1000.0d);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0d, -8.0d, -50.0d);
}

void render() {
    display();
    displayCamera();
    displayModifier();
}

int main(int argc, char **argv) {
    GetDesktopResolution();

    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (screenSizeHorizontal * 2.0d / 3.0d, screenSizeVertical); glutInitWindowPosition(0, 0);
    WindowID1 = glutCreateWindow("3D Tree Using Recursion");
    init();
    glutReshapeFunc(reshape);

    glutDisplayFunc(display);

    createWindowModifier();
    createWindowCamera();

    glutDisplayFunc(render);
    glutMainLoop();

    return EXIT_SUCCESS;
}
