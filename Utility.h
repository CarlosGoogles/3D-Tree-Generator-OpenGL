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


void createSphere(double x, double y, double z, double r) {
    double theta = 0.0f, theta2 = 2.0 * PI / slicesObj;
    double omega = 0.0f;

    FOR(i, 0, slicesObj) {
        omega = 0;
        glBegin(GL_QUAD_STRIP);
        FOR(j, 0, slicesObj) {
                glVertex3f(x + r * cos(omega) * cos(theta), y + r * cos(omega) * sin(theta), z + r * sin(omega));
                glVertex3f(x + r * cos(omega) * cos(theta2), y + r * cos(omega) * sin(theta2), z + r * sin(omega));
                omega += (2.0 * PI) / slicesObj;
        }
        glVertex3f(x + r * cos(omega) * cos(theta), y + r * cos(omega) * sin(theta), z + r * sin(omega));
        glVertex3f(x + r * cos(omega) * cos(theta2), y + r * cos(omega) * sin(theta2), z + r * sin(omega));
        glEnd();

        theta = theta2;
        theta2 += 2.0 * PI / slicesObj;
    }
}

void createCylinder(double r, double R, double h, Matrix m) {
    double theta = 0.0f;
    glColor3d( 0.64d, 0.16d, 0.16d);
    //cout << r << " " << R << " " << h << endl;


    Cylinder cyl;
    FOR(i, 0, slicesObj) {
        glBegin(GL_QUAD_STRIP);
        FOR(j, 0, slicesObj + 1) {
            Matrix aux1 = m * Matrix::createTranslation(R * cos(theta), 0, R * sin(theta));
            Matrix aux2 = m * Matrix::createTranslation(r * cos(theta) * 0.7, h, r * sin(theta) * 0.7);

            cyl.bot.pb(Point(aux1.mat[0][3], aux1.mat[1][3], aux1.mat[2][3]));
            cyl.top.pb(Point(aux2.mat[0][3], aux2.mat[1][3], aux2.mat[2][3]));

            glVertex3f(aux1.mat[0][3], aux1.mat[1][3], aux1.mat[2][3]);
            glVertex3f(aux2.mat[0][3], aux2.mat[1][3], aux2.mat[2][3]);
            theta += (2.0 * PI) / slicesObj;
        }

        glEnd();
    }

    vCylinders.pb(cyl);
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
