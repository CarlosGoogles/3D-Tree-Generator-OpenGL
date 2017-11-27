
static const string names[6] = { "base", "height", "", "angle", "rand", "" };
static const double namesPos[6][3] = {
    {-0.60f,  0.10f, 0.00f},
    {-0.65f, -0.30f, 0.00f},
    {-0.65f, -0.70f, 0.00f},
    { 0.40f,  0.10f, 0.00f},
    { 0.40f, -0.30f, 0.00f},
    { 0.40f, -0.70f, 0.00f}
};

static double angleObj = 40.0f;
static double baseObj = 1.1f;
static double heightObj = 5.0f;
static double randyObj = 5.5f;
static double valObj[6] = {baseObj, heightObj, 0, angleObj, randyObj, 0};

void mouseButtonPressedModifier(int button, int key, int x, int y) {
    if (key == 0)   return;
    if (button == 2)    return;

    ii pressed = findWherePressed(x, y);
    if (pressed.first == -1)    return;

    if (button == 3)    pressed.second *= -1.0f;

    if (pressed.first == 0) {
        baseObj += pressed.second * 0.1f;
        baseObj = min(2.0, baseObj);
        baseObj = max(0.2, baseObj);
        valObj[pressed.first] = baseObj;
    }
    else if (pressed.first == 1) {
        heightObj += pressed.second * 0.1f;
        heightObj = min(7.0, heightObj);
        heightObj = max(3.0, heightObj);
        valObj[pressed.first] = heightObj;
    }
    else if (pressed.first == 3) {
        angleObj += pressed.second;
        angleObj = min(60.0, angleObj);
        angleObj = max(20.0, angleObj);
        valObj[pressed.first] = angleObj;
    }
    else if (pressed.first == 4) {
        randyObj += pressed.second * 0.1f;
        randyObj = min(9.0, randyObj);
        randyObj = max(4.0, randyObj);
        valObj[pressed.first] = randyObj;
    }


    glutPostRedisplay();
}

void displayModifier() {
    glutSetWindow(WindowID3);

    camaraWindowWidth = glutGet(GLUT_WINDOW_WIDTH);
    camaraWindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    glutMouseFunc(mouseButtonPressedModifier);

    // clear the draw buffer .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything

    glLineWidth(5.0f);

    // Add Title
    drawStrokeText("Object Modifications", -0.90f, 0.50f, 0, 0.0015f, 0.0015f, 0.0f, colors[3]);

    // Create minus buttons
    FOR(i, 0, 6) {
        if (i == 2 || i == 5)   continue;
        // Create buttons
        glBegin(GL_POLYGON); {
            glColor3f(colors[2][0],  colors[2][1], colors[2][2]);
            glVertex2f(arrButtonMin[i][0], arrButtonMin[i][1]);
            glVertex2f(arrButtonMin[i][2], arrButtonMin[i][1]);
            glVertex2f(arrButtonMin[i][2], arrButtonMin[i][3]);
            glVertex2f(arrButtonMin[i][0], arrButtonMin[i][3]);
        } glEnd();

        // Add text: names
        drawStrokeText(names[i], namesPos[i][0], namesPos[i][1], namesPos[i][2], 0.001f, 0.001f, 0.0f, colors[3]);

        // Add text: numbers
        drawStrokeText(to_string(valObj[i]), arrPlusSign[i][0][0], arrPlusSign[i][0][1], 0, 0.001f, 0.001f, 0.0f, colors[5]);
    }

    glFlush();
}

void createWindowModifier() {
    glutInitWindowSize (screenSizeHorizontal * 1.0f / 3.0f, screenSizeVertical / 2.0f);
    glutInitWindowPosition (screenSizeHorizontal * 2.0f / 3.0f, screenSizeVertical / 2.0f);
    WindowID3 = glutCreateWindow("Modifier"); // Create a camera
    glutDisplayFunc(displayModifier);   // Register display callback
}
