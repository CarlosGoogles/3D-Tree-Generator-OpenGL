struct Point {
    double x, y, z;
    Point() {}
    Point (double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

    void pprint() {
        cout << x << " " << y << " " << z << endl;
    }
};
typedef vector<Point> vp;

struct Cylinder {
    vp bot;
    vp top;

    Cylinder() {}

    void add(Point b, Point t) {
        bot.pb(b);
        top.pb(t);
    }
};

struct Sphere {
    vector<vp> v;

    Sphere() {}
    void add(vp p) {
        v.pb(p);
    }
};


vector<Cylinder> vCylinders;
vector<Sphere> vSpheres;
