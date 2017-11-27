#include <bits/stdc++.h>
#include <GL/glut.h>

#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define pb push_back

using namespace std;

typedef pair<int, int> ii;

void reCreateTree();

#include "Utility.h"
#include "CameraWindow.h"
#include "ModifierWindow.h"

GLuint makeaTree;

void makeCylinder(double height, double base) {
    int randd = rand() % 50 + 20;
    GLUquadric *obj = gluNewQuadric();
    //gluQuadricDrawStyle(obj, GLU_LINE);
    glColor3f( 0.64f, 0.16f, 0.16f);
    glPushMatrix();
        glRotatef(-90.0f, 1.00f, 0.0f, 0.0f);
        gluCylinder(obj, base, 0.8f * base, height, 20.0f, 20.0f);
    glPopMatrix();
    glutSwapBuffers();
}


void makeTree(double height, double base){
    double angle;
    makeCylinder(height, base);
    glTranslatef(0.0f, height, 0.0f);
    height -= height * 0.2f;
    base -= base * 0.3f;

    int ramas = rand() % 3 + 3;
    FOR(a, 0, ramas) {
        angle = rand() % 50 + 20;
        if (angle > 48)
            angle = -(rand() % 50 + 20);
        if (height > 1) {
            glPushMatrix();
            int randy = rand() % 2;
            if(randy % 2 == 0){
                glRotatef(angle, 1, randy, 1);
            }
            else{
                glRotatef(angle, 1, (- randy), 1);
            }
            makeTree(height,base);
            glPopMatrix();
        }
    }
    glColor3f(0.0f, 1.0f / (rand() % 3 + 1), 0.0f);
    glutSolidSphere(0.2f, 10, 10);

}

void reCreateTree() {
    glutSetWindow(WindowID1);

    // clear the draw buffer .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    makeaTree = glGenLists(1);
    glNewList(makeaTree, GL_COMPILE);
    makeTree(heightObj, baseObj);
    glEndList();
}

void init(void) {
    reCreateTree();
}

void display() {
    glutSetWindow(WindowID1);

    glLoadIdentity();
    glRotatef(-camaraRot[2], 0.0f, 0.0f, 1.0f);
    glRotatef(-camaraRot[1], 0.0f, 1.0f, 0.0f);
    glRotatef(-camaraRot[0], 1.0f, 0.0f, 0.0f);
    glTranslatef(-camaraMov[0], -camaraMov[1], -camaraMov[2]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glRotatef(angsObj[0], 1.0f, 0.0f, 0.0f);
        glRotatef(angsObj[1], 0.0f, 1.0f, 0.0f);
        glRotatef(angsObj[2], 0.0f, 0.0f, 1.0f);
        glCallList(makeaTree);

    glPopMatrix();
    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, (GLdouble) w/(GLdouble) h, 0.001f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, -8.0f, -50.0f);
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
    glutInitWindowSize (screenSizeHorizontal * 2.0f / 3.0f, screenSizeVertical); glutInitWindowPosition(0, 0);
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
