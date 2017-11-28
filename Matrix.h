struct Matrix {
    double mat[4][4];

    Matrix() {}
    static Matrix identity() {
        Matrix ret;
        double mat2[4][4] = {
            { 1.0d, 0.0d, 0.0d, 0.0d },
            { 0.0d, 1.0d, 0.0d, 0.0d },
            { 0.0d, 0.0d, 1.0d, 0.0d },
            { 0.0d, 0.0d, 0.0d, 1.0d },
        };

        FOR(i, 0, 4)    FOR(j, 0, 4)    ret.mat[i][j] = mat2[i][j];
        return ret;
    }

    static Matrix originalPos() {
        Matrix ret;
        double mat2[4][4] = {
            { 0.0d, 0.0d, 0.0d, 0.0d },
            { 0.0d, 0.0d, 0.0d, 0.0d },
            { 0.0d, 0.0d, 0.0d, 0.0d },
            { 0.0d, 0.0d, 0.0d, 1.0d },
        };

        FOR(i, 0, 4)    FOR(j, 0, 4)    ret.mat[i][j] = mat2[i][j];
        return ret;
    }

    static Matrix createTranslation(double x, double y, double z) {
        Matrix ret;
        double mat2[4][4] = {
            { 1.0d, 0.0d, 0.0d,    x },
            { 0.0d, 1.0d, 0.0d,    y },
            { 0.0d, 0.0d, 1.0d,    z },
            { 0.0d, 0.0d, 0.0d, 1.0d }
        };

        FOR(i, 0, 4)    FOR(j, 0, 4)    ret.mat[i][j] = mat2[i][j];
        return ret;
    }

    static Matrix createRotationMatrix(double x, double y, double z, double angle) {
        Matrix ret;
        double c = cos(angle);
        double s = sin(angle);
        double mat2[4][4] = {
            { x*x*(1.0d-c)+c  , x*y*(1.0d-c)-z*s, x*z*(1.0d-c)+y*s, 0.0d },
            { x*y*(1.0d-c)+z*s, y*y*(1.0d-c)+  c, y*z*(1.0d-c)-x*s, 0.0d },
            { x*z*(1.0d-c)-y*s, y*z*(1.0d-c)+x*s, z*z*(1.0d-c)+c  , 0.0d },
            {             0.0d,             0.0d,             0.0d, 1.0d }
        };

        FOR(i, 0, 4)    FOR(j, 0, 4)    ret.mat[i][j] = mat2[i][j];
        return ret;
    }

    Matrix operator * (const Matrix& m) const {
        Matrix ret;
        FOR(i, 0, 4) {
            FOR(j, 0, 4) {
                ret.mat[i][j] = 0;
                FOR(k, 0, 4) {
                    ret.mat[i][j] += mat[i][k] * m.mat[k][j];
                }
            }
        }

        return ret;
    }

    void pprint() {
        cout << fixed << setprecision(6);
        FOR(i, 0, 4) {
            FOR(j, 0, 4)    cout << mat[i][j] << "\t";
            cout << endl;
        }
        cout << endl;
    }
};
