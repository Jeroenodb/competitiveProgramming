#include <fstream>
#include <iostream>
#include <assert.h>
#include "point.h"
using namespace std;
static ofstream fout;
static bool initialized = false;
struct G_LAYERS {
    G_LAYERS() {
        fout << "LAYER\n";
    }
    ~G_LAYERS() {
        fout << "END\n";
    }
};
#define G_LAYER() G_LAYERS l;
#define TT template<typename T>
void G_PAUSE() {
    fout << "PAUSE\n";
}
void G_INIT(string path) {
    fout = ofstream(path);
    initialized = true;
}
TT void G_POINT(const point<T>& p, string color="") {
    if(color=="") color = "red";
    fout <<"PT " << p << ' ' << color << "\n";
}
TT void G_SEGMENT(const point<T>& a, const point<T>& b, string color="") {
    if(color=="") color = "white";
    fout << "SEG " <<  a << ' ' << b-a << ' ' << color << '\n';
}
TT void G_POLYGON(const vector<point<T>>& v, string color="") {
    // has to be convex
    if(color=="") color = "green";
    fout << "POLY " <<  v.size() << ' ';
    for(auto& p : v)
        fout << p << ' ';
    fout << color << '\n';
}
struct root {
    ~root() {
        cout << "Remove this library before submitting\n";
        G_PAUSE();
    }
} G_R;
#undef TT

