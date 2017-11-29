static double colors[6][3] = {
    {0.0f, 0.0f, 0.0f},     // black
    {1.0f, 0.0f, 0.0f},     // red
    {0.0f, 1.0f, 0.0f},     // green
    {0.0f, 0.0f, 1.0f},     // blue
    {1.0f, 1.0f, 1.0f},     // white
    {0.0f, 1.0f, 1.0f}      // yellow
};



static int slicesObj = 8;
int screenSizeHorizontal, screenSizeVertical;
GLint WindowID1, WindowID2, WindowID3;

static int Rand(int mod) {
    return rand() % mod;
}

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

void loadLastSesion() {
    freopen("last_session.lovelive", "r", stdin);
    double x, y, z;
    string s;
    while (cin >> s) {
        if (s == "sphere")  glColor3d(0.0d, 1.0d / (Rand(4) + 1.0d), 0.0d);
        if (s == "cylinder")    glColor3d( 0.64d, 0.16d, 0.16d);
        glBegin(GL_QUAD_STRIP);
        while (cin >> s && s != "glEnd") {
            cin >> x >> y >> z;
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void createSphere(double x, double y, double z, double r) {
    double theta = 0.0f, theta2 = 2.0 * PI / slicesObj;
    double omega = 0.0f;

    Sphere ssp;
    FOR(i, 0, slicesObj) {
        omega = 0.0d;
        glBegin(GL_QUAD_STRIP);
        cout << "sphere" << endl;
        vp p;
        FOR(j, 0, slicesObj + 1) {
                double x1 = x + r * cos(omega) * cos(theta);
                double x2 = x + r * cos(omega) * cos(theta2);

                double y1 = y + r * cos(omega) * sin(theta);
                double y2 = y + r * cos(omega) * sin(theta2);

                double z1 = z + r * sin(omega);
                double z2 = z + r * sin(omega);

                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);

                cout << "p " << x1 << " " << y1 << " " << z1 << endl;
                cout << "p " << x2 << " " << y2 << " " << z2 << endl;

                p.pb(Point(x1, y1, z1));
                p.pb(Point(x2, y2, z2));

                omega += (2.0 * PI) / slicesObj;
        }
        glEnd();
        cout << "glEnd" << endl;

        ssp.add(p);

        theta = theta2;
        theta2 += 2.0 * PI / slicesObj;
    }
    vSpheres.pb(ssp);
}



void createCylinder(double r, double R, double h, Matrix m) {
    double theta = 0.0f;
    glColor3d( 0.64d, 0.16d, 0.16d);

    Cylinder cyl;
    FOR(i, 0, slicesObj) {
        glBegin(GL_QUAD_STRIP);
        cout << "cylinder" << endl;
        FOR(j, 0, slicesObj + 1) {
            Matrix aux1 = m * Matrix::createTranslation(R * cos(theta), 0, R * sin(theta));
            Matrix aux2 = m * Matrix::createTranslation(r * cos(theta) * 0.7, h, r * sin(theta) * 0.7);

            cyl.bot.pb(Point(aux1.mat[0][3], aux1.mat[1][3], aux1.mat[2][3]));
            cyl.top.pb(Point(aux2.mat[0][3], aux2.mat[1][3], aux2.mat[2][3]));

            glVertex3f(aux1.mat[0][3], aux1.mat[1][3], aux1.mat[2][3]);
            glVertex3f(aux2.mat[0][3], aux2.mat[1][3], aux2.mat[2][3]);

            cout << "p " << aux1.mat[0][3] << " " << aux1.mat[1][3] << " " << aux1.mat[2][3] << endl;
            cout << "p " << aux2.mat[0][3] << " " << aux2.mat[1][3] << " " << aux2.mat[2][3] << endl;
            theta += (2.0 * PI) / slicesObj;
        }

        glEnd();
        cout << "glEnd" << endl;
    }

    // vCylinders.pb(cyl);
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
    FOR(i, 0, vSpheres.size()) {
        FOR(j, 0, vSpheres[i].v.size()) {
            FOR(k, 0, vSpheres[i].v[j].size()) {
                cout << "v "; vSpheres[i].v[j][k].pprint();
            }
        }
    }

    int iSalto = slicesObj * 2;
    FOR(i, 0, vCylinders.size()) {
        int iPAct = i * iSalto;
        // Bot Face
        cout << "f ";
        FOR(j, 0, slicesObj) {
            cout << iPAct + (j * 2) + 1 << " \n"[j == slicesObj - 1];
        }

        // Top Face
        cout << "f ";
        FOR(j, 0, slicesObj) {
            cout << iPAct + (j * 2 + 1) + 1 << " \n"[j == slicesObj - 1];
        }

        // Lateral Faces
        FOR(j, 0, slicesObj) {
            cout << "f " << iPAct + (j * 2) + 1 << " " << iPAct + (j * 2 + 1) + 1 << " ";
            cout << iPAct + (j * 2 + 3) % (2 * slicesObj) + 1 << " " << iPAct + (j * 2 + 2) % (2 * slicesObj) + 1 << endl;
        }
    }

    int iSSalto = vCylinders.size() * 2 * slicesObj;
    iSalto = slicesObj * 2;
    FOR(i, 0, vCylinders.size()) {
        int iPAct = i * iSalto;
        // Lateral Faces
        FOR(j, 0, slicesObj) {
            cout << "f " << iSSalto + iPAct + (j * 2) + 1 << " " << iSSalto + iPAct + (j * 2 + 1) + 1 << " ";
            cout << iSSalto + iPAct + (j * 2 + 3) % (2 * slicesObj) + 1 << " " << iSSalto + iPAct + (j * 2 + 2) % (2 * slicesObj) + 1 << endl;
        }
    }
}
