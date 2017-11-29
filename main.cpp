#include <bits/stdc++.h>
#include <GL/glut.h>
#define _ ios_base::sync_with_stdio(0), cin.tie(0), cin.tie(0), cout.tie(0), cout.precision(15);

#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define pb push_back

#define PI 3.14159265358979323846

using namespace std;

typedef pair<int, int> ii;

static double baseObj = 0.3f;
static double heightObj = 4.0f;
static int branchesObj = 3;
static int colorActLeaves = 7;
static int slicesObj = 8;

void reCreateTree();
void displayModifier();

static double angsObj[3] = { 0.0f, 0.0f, 0.0f };
static double valObj[9] = { angsObj[0], angsObj[1], angsObj[2], 0, baseObj, heightObj, (double)branchesObj, (double)slicesObj, (double)colorActLeaves };

#include "Geometry.h"
#include "Matrix.h"
#include "Utility.h"
#include "CameraWindow.h"
#include "ModifierWindow.h"

GLuint makeaTree;

void makeTree(double height, double base, const bool b, Matrix matrizActual, int lvl) {
    createCylinder(base, 0.8d * base, height * (1.0d - lvl * 0.08d), matrizActual, colors[6], (1.0d - lvl * 0.15d));

    Matrix matrizMoved = matrizActual * Matrix::createTranslation(0.0d, height * (1.0d - lvl * 0.08d), 0.0d);

    height -= height * 0.2f;
    base -= base * 0.3f;
    int ramas = Rand(3) + 3;
    if (b)  ramas = 6;
    FOR(a, 0, ramas) {
        if (height > 1.0d) {
            double angle = Rand(30) + 10.0, x = 1, y = 1;
            Matrix matrizCycle = matrizMoved;
            if (Rand(2) % 2 == 0)     angle = -angle;
            if (Rand(2) % 2 == 0)     x = -x;
            if (Rand(2) % 2 == 0)     y = -y;

            matrizCycle = matrizCycle * Matrix::createRotationMatrix(x * 0.8d, y * 1.d, 0.8d, angle * PI / 180.d);
            makeTree(height, base, false, matrizCycle, lvl + 1);
        }
    }
    // glColor3d(0.0d, 1.0d / (Rand(4) + 1.0d), 0.0d);
    matrizMoved = matrizMoved * Matrix::originalPos();
    createSphere(matrizMoved.mat[0][3], matrizMoved.mat[1][3], matrizMoved.mat[2][3], 0.2d, colors[colorActLeaves]);
}

static bool lastSession = true;
void reCreateTree() {
    vCylinders.clear();
    vSpheres.clear();

    glutSetWindow(WindowID1);

    // clear the draw budder .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything

    glClearColor(1.0d, 1.0d, 1.0d, 1.0d);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);


    makeaTree = glGenLists(1);
    glNewList(makeaTree, GL_COMPILE);

    if (lastSession) {
        lastSession = false;
        loadLastSesion();
    }
    else {
        freopen("last_session.lovelive", "w", stdout);
        cout << baseObj << " " << heightObj << " " << branchesObj << " " << slicesObj << " " << colorActLeaves << endl;
        makeTree(heightObj, baseObj, true, Matrix::identity(), 0);
        toOBJ();
    }

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
