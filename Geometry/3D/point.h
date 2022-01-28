#ifndef GEOPOINT
#define GEOPOINT
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
namespace geo3D{
#define TT template<typename T>
TT struct point {
    T x,y,z;
    template<typename R> operator point<R>()
    { return point<R>{x,y,z}; }
    auto operator+(const point& v) const {
        return point{x+v.x,y+v.y,z+v.z};
    }
    auto operator-(const point& v) const {
        return point{x-v.x,y-v.y,z-v.z};
    }
    auto operator*(T c) const { // scalar multiple
        return point{c*x,c*y,c*z};
    }
    auto operator*(const point& v) const { // cross product
        return point{y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x};
    }
    auto operator|(const point& v) const { // in product
        return x*v.x+y*v.y+z*v.z;
    }
    bool operator==(const point& o) const {
        return x==o.x and y==o.y and z == o.z;
    }
    bool operator!=(const point& o) const {
        return !(*this==o);
    }
    bool operator<(const point& o) const {
        if(x!=o.x) return x<o.x;
        if(y!=o.y) return y<o.y;
        return z<o.z;
    }
};
TT const point<T> zero = {0,0,0};
TT auto operator*(T c, const point<T>& p) {
    return point<T>{c*p.x,c*p.y,c*p.z};
}


TT auto norm(const point<T>& p) {return p|p;};
TT auto abs(const point<T>& p) {return sqrt(norm(p));}
TT auto sgn(T a) {return a==0?0:(a>0?1:-1);}
TT auto ccw(const point<T>& p1, const point<T>& p2, const point<T>& p3) {auto u = p2-p1, v = p3-p2; return u*v;}
TT void read(point<T>& p) {
    cin >> p.x >> p.y >> p.z;
}
TT ostream& operator<<(ostream& c, const point<T>& p) {
    return c << p.x << ' ' << p.y << ' ' << p.z;
}
TT istream& operator>>(istream& c, point<T>& p) {
    return c >> p.x >> p.y >> p.z;
}
}
using namespace geo3D;
namespace std {
    TT struct hash<point<T>> {
        std::size_t operator()(const point<T>& p) const noexcept
        {
            return p.x ^ (p.y *5) ^ (p.z*3); // or use boost::hash_combine
        }
    };
}

#undef TT
#endif
