
static const double arrButtonMin2[8][4] = {
    {-0.90f,  0.55f, -0.70f,  0.35f},
    {-0.90f,  0.25f, -0.70f,  0.05f},
    {-0.90f, -0.05f, -0.70f, -0.25f},
    {-0.90f, -0.35f, -0.70f, -0.55f},
    {-0.05f,  0.55f,  0.15f,  0.35f},
    {-0.05f,  0.25f,  0.15f,  0.05f},
    {-0.05f, -0.05f,  0.15f, -0.25f},
    {-0.05f, -0.35f,  0.15f, -0.55f},
};

static const double arrPlusSign2[8][4] = {
    {-0.25f,  0.40f, -0.15f,  0.10f},
    {-0.25f,  0.10f, -0.15f, -0.30f},
    {-0.25f, -0.20f, -0.15f, -0.70f},
    {-0.25f, -0.50f, -0.15f, -0.70f},
    { 0.75f,  0.40f,  0.85f,  0.10f},
    { 0.75f,  0.10f,  0.85f, -0.30f},
    { 0.75f, -0.20f,  0.85f, -0.70f},
    { 0.75f, -0.50f,  0.85f, -0.70f},
};

static const double namesPosModifier[8][3] = {
    {-0.65f,  0.40f, 0.00f},
    {-0.65f,  0.10f, 0.00f},
    {-0.65f, -0.20f, 0.00f},
    {-0.65f, -0.50f, 0.00f},
    { 0.20f,  0.40f, 0.00f},
    { 0.20f,  0.10f, 0.00f},
    { 0.20f, -0.20f, 0.00f},
    { 0.20f, -0.50f, 0.00f},
};

static const double btnRender[4] = {-0.90f, -0.65f, -0.20f, -0.85f};

static const string names[8] = { "rot x", "rot y", "rot z", "", "base", "height", "branches", "slices" };

static double angsObj[3] = { 0.0f, 0.0f, 0.0f };
static double baseObj = 0.4f;
static double heightObj = 4.0f;
static int branchesObj = 3;
static double valObj[8] = { angsObj[0], angsObj[1], angsObj[2], 0, baseObj, heightObj, (double)branchesObj, (double)slicesObj };

static double modifierWindowWidth;
static double modifierWindowHeight;

ii findWherePressedModifier(int x, int y) {
    double xx = 2.0f * x / modifierWindowWidth - 1.0f;
    double yy = -(2.0f * y / modifierWindowHeight - 1.0f);

    FOR(i, 0, 8) {
        if (between(arrButtonMin2[i][0], xx, arrButtonMin2[i][2]) &&
            between(arrButtonMin2[i][3], yy, arrButtonMin2[i][1])) {
            return ii(i, 1);
        }
    }

    if (between(btnRender[0], xx, btnRender[2]) &&
        between(btnRender[3], yy, btnRender[1])) {
        return ii(8, 1);
    }

    return ii(-1, 0);
}

void mouseButtonPressedModifier(int button, int key, int x, int y) {
    if (key == 0)   return;

    ii pressed = findWherePressedModifier(x, y);
    if (pressed.first == -1)    return;

    if (button == 4 || button == 2)    pressed.second *= -1.0f;

    if (pressed.first < 3) {
        angsObj[pressed.first] += pressed.second;
        valObj[pressed.first] = angsObj[pressed.first];
    }
    else if (pressed.first == 4) {
        baseObj += pressed.second * 0.1f;
        baseObj = min(2.0, baseObj);
        baseObj = max(0.2, baseObj);
        valObj[pressed.first] = baseObj;
    }
    else if (pressed.first == 5) {
        heightObj += pressed.second * 0.1f;
        heightObj = min(7.0, heightObj);
        heightObj = max(3.0, heightObj);
        valObj[pressed.first] = heightObj;
    }
    else if (pressed.first == 6) {
        branchesObj += pressed.second;
        branchesObj = min(5, branchesObj);
        branchesObj = max(2, branchesObj);
        valObj[pressed.first] = branchesObj;
    }
    else if (pressed.first == 7) {
        slicesObj += pressed.second * 0.1f;
        slicesObj = min(15, slicesObj);
        slicesObj = max(3, slicesObj);
        valObj[pressed.first] = slicesObj;
    }
    else if (button == 0 && pressed.first == 8) {
        reCreateTree();
    }

    glutPostRedisplay();
}

void displayModifier() {
    glutSetWindow(WindowID3);

    modifierWindowWidth = glutGet(GLUT_WINDOW_WIDTH);
    modifierWindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    glutMouseFunc(mouseButtonPressedModifier);

    // clear the draw buffer .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything

    glLineWidth(5.0f);

    // Add Title
    drawStrokeText("Object Modifications", -0.90f, 0.75f, 0, 0.0015f, 0.0015f, 0.0f, colors[3]);

    // Create minus buttons
    FOR(i, 0, 8) {
        if (i == 3)   continue;
        // Create buttons
        glBegin(GL_POLYGON); {
            glColor3f(colors[2][0],  colors[2][1], colors[2][2]);
            glVertex2f(arrButtonMin2[i][0], arrButtonMin2[i][1]);
            glVertex2f(arrButtonMin2[i][2], arrButtonMin2[i][1]);
            glVertex2f(arrButtonMin2[i][2], arrButtonMin2[i][3]);
            glVertex2f(arrButtonMin2[i][0], arrButtonMin2[i][3]);
        } glEnd();

        // Add text: names
        drawStrokeText(names[i], namesPosModifier[i][0], namesPosModifier[i][1], namesPosModifier[i][2], 0.001f, 0.001f, 0.0f, colors[3]);

        // Add text: numbers
        drawStrokeText(to_string(valObj[i]), arrPlusSign2[i][0], arrPlusSign2[i][1], 0, 0.001f, 0.001f, 0.0f, colors[5]);
    }

    // Boton Render
    glBegin(GL_POLYGON); {
            glColor3f(colors[2][0],  colors[2][1], colors[2][2]);
            glVertex2f(btnRender[0], btnRender[1]);
            glVertex2f(btnRender[2], btnRender[1]);
            glVertex2f(btnRender[2], btnRender[3]);
            glVertex2f(btnRender[0], btnRender[3]);
    } glEnd();
    drawStrokeText("Render", -0.75f, -0.80f, 0, 0.001f, 0.001f, 0.0f, colors[1]);

    glFlush();
}

void createWindowModifier() {
    glutInitWindowSize (screenSizeHorizontal * 1.0f / 3.0f, screenSizeVertical * 3.0f / 7.0f);
    glutInitWindowPosition (screenSizeHorizontal * 2.0f / 3.0f, screenSizeVertical / 2.0f);
    WindowID3 = glutCreateWindow("Modifier"); // Create a camera
    glutDisplayFunc(displayModifier);   // Register display callback
}
