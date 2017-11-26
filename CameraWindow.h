#include <cstdlib>
#include <GL/glut.h>
#include <bits/stdc++.h>

#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)

using namespace std;

typedef pair<int, int> ii;

static const double arrButtonMin[6][4] = {
    {-0.90f,  0.25f, -0.70f, -0.05f},
    {-0.90f, -0.15f, -0.70f, -0.45f},
    {-0.90f, -0.55f, -0.70f, -0.85f},
    { 0.10f,  0.25f,  0.30f, -0.05f},
    { 0.10f, -0.15f,  0.30f, -0.45f},
    { 0.10f, -0.55f,  0.30f, -0.85f}
};

static const double arrMinusSign[6][4] = {
    {-0.85f,  0.10f, -0.75f,  0.10f},
    {-0.85f, -0.30f, -0.75f, -0.30f},
    {-0.85f, -0.70f, -0.75f, -0.70f},
    { 0.15f,  0.10f,  0.25f,  0.10f},
    { 0.15f, -0.30f,  0.25f, -0.30f},
    { 0.15f, -0.70f,  0.25f, -0.70f}
};

static const double arrButtonPlus[6][4] = {
    {-0.30f,  0.25f, -0.10f, -0.05f},
    {-0.30f, -0.15f, -0.10f, -0.45f},
    {-0.30f, -0.55f, -0.10f, -0.85f},
    { 0.70f,  0.25f,  0.90f, -0.05f},
    { 0.70f, -0.15f,  0.90f, -0.45f},
    { 0.70f, -0.55f,  0.90f, -0.85f}
};

static const double arrPlusSign[6][2][4] = {
    {
        {-0.25f,  0.10f, -0.15f,  0.10f},
        {-0.20f,  0.20f, -0.20f,  0.00f},
    },
    {
        {-0.25f, -0.30f, -0.15f, -0.30f},
        {-0.20f, -0.20f, -0.20f, -0.40f},
    },
    {
        {-0.25f, -0.70f, -0.15f, -0.70f},
        {-0.20f, -0.60f, -0.20f, -0.80f},
    },
    {
        { 0.75f,  0.10f,  0.85f,  0.10f},
        { 0.80f,  0.20f,  0.80f,  0.00f},
    },
    {
        { 0.75f, -0.30f,  0.85f, -0.30f},
        { 0.80f, -0.20f,  0.80f, -0.40f},
    },
    {
        { 0.75f, -0.70f,  0.85f, -0.70f},
        { 0.80f, -0.60f,  0.80f, -0.80f},
    }
};

static const string names[6] = { "boom", "dolly", "truck", "tilt", "pan", "roll" };
static const double namesPos[6][3] = {
    {-0.65f,  0.10f, 0.00f},
    {-0.60f, -0.30f, 0.00f},
    {-0.65f, -0.70f, 0.00f},
    { 0.40f,  0.10f, 0.00f},
    { 0.40f, -0.30f, 0.00f},
    { 0.40f, -0.70f, 0.00f}
};

static double camaraWindowWidth;
static double camaraWindowHeight;

static double camaraMov[3] = {0.0f, 0.0f, 0.0f}; // boom, dolly, truck
static double camaraRot[3] = {0.0f, 0.0f, 0.0f}; // tilt, pan, roll

GLint WindowID1, WindowID2;

const static double colors[5][3] = {
    {0.0f, 0.0f, 0.0f},     // black
    {1.0f, 0.0f, 0.0f},     // red
    {0.0f, 1.0f, 0.0f},     // green
    {0.0f, 0.0f, 1.0f},     // blue
    {1.0f, 1.0f, 1.0f}      // white
};


static bool between(double a, double b, double c) {
    return a <= b && b <= c;
}

ii findWherePressed(int x, int y) {
    double xx = 2.0f * x / camaraWindowWidth - 1.0f;
    double yy = -(2.0f * y / camaraWindowHeight - 1.0f);

    FOR(i, 0, 6) {
        if (between(arrButtonMin[i][0], xx, arrButtonMin[i][2]) &&
            between(arrButtonMin[i][3], yy, arrButtonMin[i][1])) {
            return ii(i, -1);
        }
    }

    FOR(i, 0, 6) {
        if (between(arrButtonPlus[i][0], xx, arrButtonPlus[i][2]) &&
            between(arrButtonPlus[i][3], yy, arrButtonPlus[i][1])) {
            return ii(i, 1);
        }
    }

    return ii(-1, 0);
}


void mouseButtonPressed(int button, int key, int x, int y) {
    if (key == 0)   return;
    if (button == 2)    return;

    ii pressed = findWherePressed(x, y);
    if (pressed.first == -1)    return;

    if (pressed.first < 3) {
        camaraMov[pressed.first] += pressed.second;
    }
    else {
        camaraRot[pressed.first - 3] += pressed.second;
    }

    cout << button << " " << key << " " << x << " " << y << endl;

    cout << "boom:\t" << camaraMov[0] << endl;
    cout << "dolly:\t" << camaraMov[1] << endl;
    cout << "truck:\t" << camaraMov[2] << endl;

    cout << "tilt:\t" << camaraRot[0] << endl;
    cout << "pan:\t" << camaraRot[1] << endl;
    cout << "roll:\t" << camaraRot[2] << endl;

    glutPostRedisplay();
}

void drawStrokeText(string s, double x, double y, double z, double sx, double sy, double sz) {
    glPushMatrix();
        glColor3f(colors[3][0], colors[3][1], colors[3][2]);
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        FOR(i, 0, s.length()) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
        }
    glPopMatrix();
}

void displayCamera() {

    glutSetWindow(WindowID2);

    camaraWindowWidth = glutGet(GLUT_WINDOW_WIDTH);
    camaraWindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    glutMouseFunc(mouseButtonPressed);

    // clear the draw buffer .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything

    glLineWidth(5.0f);

    // Add Title
    drawStrokeText("Camera", -0.80f, 0.50f, 0, 0.0035f, 0.0035f, 0.0f);

    // Create minus buttons
    FOR(i, 0, 6) {
        // Create buttons
        glBegin(GL_POLYGON); {
            glColor3f(colors[1][0],  colors[1][1], colors[1][2]);
            glVertex2f(arrButtonMin[i][0], arrButtonMin[i][1]);
            glVertex2f(arrButtonMin[i][2], arrButtonMin[i][1]);
            glVertex2f(arrButtonMin[i][2], arrButtonMin[i][3]);
            glVertex2f(arrButtonMin[i][0], arrButtonMin[i][3]);
        } glEnd();

        // Create minus line
        glColor3f(colors[0][0], colors[0][1], colors[0][2]);
        glBegin(GL_LINES);
            glVertex2f(arrMinusSign[i][0], arrMinusSign[i][1]);
            glVertex2f(arrMinusSign[i][2], arrMinusSign[i][3]);
        glEnd();

        // Add text
        drawStrokeText(names[i], namesPos[i][0], namesPos[i][1], namesPos[i][2], 0.001f, 0.001f, 0.0f);
    }

    // Create plus buttons
    FOR(i, 0, 6) {
        // Create buttons
        glBegin(GL_POLYGON); {
            glColor3f(colors[2][0],  colors[2][1], colors[2][2]);
            glVertex2f(arrButtonPlus[i][0], arrButtonPlus[i][1]);
            glVertex2f(arrButtonPlus[i][2], arrButtonPlus[i][1]);
            glVertex2f(arrButtonPlus[i][2], arrButtonPlus[i][3]);
            glVertex2f(arrButtonPlus[i][0], arrButtonPlus[i][3]);
        } glEnd();

        // Create plus sign
        glColor3f(colors[0][0],  colors[0][1], colors[0][2]);

        FOR(j, 0, 2) {
            glBegin(GL_LINES);
                glVertex2f(arrPlusSign[i][j][0], arrPlusSign[i][j][1]);
                glVertex2f(arrPlusSign[i][j][2], arrPlusSign[i][j][3]);
            glEnd();
        }
    }

    glFlush();
}

void createWindowCamera() {
    WindowID2 = glutCreateWindow("Camera"); // Create a camera
    glutDisplayFunc(displayCamera);   // Register display callback
}

