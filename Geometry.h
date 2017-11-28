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

struct Sphere {
    vector<Point> p;

    Sphere();
};


vector<Cylinder> vCylinders;
vector<Sphere> vSpheres;
