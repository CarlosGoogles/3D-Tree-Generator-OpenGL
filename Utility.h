static double colors[6][3] = {
    {0.0f, 0.0f, 0.0f},     // black
    {1.0f, 0.0f, 0.0f},     // red
    {0.0f, 1.0f, 0.0f},     // green
    {0.0f, 0.0f, 1.0f},     // blue
    {1.0f, 1.0f, 1.0f},     // white
    {0.0f, 1.0f, 1.0f}      // yellow
};

static int slicesObj = 20;
int screenSizeHorizontal, screenSizeVertical;
GLint WindowID1, WindowID2, WindowID3;

static bool between(double a, double b, double c) {
    return a <= b && b <= c;
}

string to_string(double d) {
    ostringstream str;
    str << d;
    return str.str();
}

void drawStrokeText(string s, double x, double y, double z, double sx, double sy, double sz, double color[]) {
    glPushMatrix();
        glColor3f(color[0], color[1], color[2]);
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        FOR(i, 0, s.length()) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
        }
    glPopMatrix();
}

// Get the horizontal and vertical screen sizes in pixel
// https://stackoverflow.com/questions/8690619/how-to-get-screen-resolution-in-c
void GetDesktopResolution() {
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   screenSizeHorizontal = desktop.right;
   screenSizeVertical = desktop.bottom;
}

struct Point {
    double x, y, z;
    Point() {}
    Point (double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

    void pprint() {
        cout << x << " " << y << " " << z << endl;
    }
};

struct Cylinder {
    vector<Point> bot;
    vector<Point> top;

    Cylinder() {}

    void add(Point b, Point t) {
        bot.pb(b);
        top.pb(t);
    }
};


vector<Cylinder> vCylinders;

void toOBJ() {
    freopen("Tree.obj", "w", stdout);
    cout << fixed << setprecision(5) << endl;

    // Save all vertices for each cylinder
    FOR(i, 0, vCylinders.size()) {
        FOR(j, 0, slicesObj) {
            cout << "v "; vCylinders[i].bot[j].pprint();
            cout << "v "; vCylinders[i].top[j].pprint();
        }
    }

    int iSalto = slicesObj * 2;
    FOR(i, 0, vCylinders.size()) {
        // Bot Face
        cout << "f ";
        FOR(j, 0, slicesObj) {
            cout << i * iSalto + j * 2 << " \n"[j == slicesObj - 1];
        }

        // Top Face
        cout << "f ";
        FOR(j, 0, slicesObj) {
            cout << i * iSalto + j * 2 + 1 << " \n"[j == slicesObj - 1];
        }

        // Lateral Faces
        FOR(j, 0, slicesObj) {
            cout << "f " << i * iSalto + j * 2 << " " << i * iSalto + (j * 2 + 1) << " ";
            cout << i * iSalto + (j * 2 + 1) % (2 * slicesObj) << " " << i * iSalto + (j * 2) % (2 * slicesObj) << endl;
        }
    }
}

void matrixMultiplication(double x, double y, double z, double h) {
    double mat1[4][4];
    double mat2[4][1] = { 0.0f, h, 0.0f};
    double res[4][1];

    FOR(i, 0, 4) {
        FOR(j, 0, 1) {
            FOR(k, 0, 4) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
