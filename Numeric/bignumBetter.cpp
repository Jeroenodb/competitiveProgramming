#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <iomanip>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
const int mxN = 1e5+1;
const int b = 1e4;
struct bignum {
    vector<unsigned int> d;
    int sgn=1;
    bignum(int l) {
        if(l<0) sgn=-1, l=-l;
        d = {(unsigned int)l};
    }
    bignum(const string& s) {
        for(auto& c : s) {
            *this *= 10;
            *this += c-'0';
        }
    }
    void trim() {
        while(!d.empty() and !d.back()) d.pop_back();
    }
    friend bignum& operator+=(bignum& a, const bignum& o) {
        int carry = 0;
        int n = max(o.d.size(), a.d.size());
        a.d.resize(n);
        for(int i=0;i<n;++i) {
            if(carry==0 and i>=o.d.size()) break;
            a.d[i]+=carry;
            if(i<(int)o.d.size()) {
                a.d[i]+=o.d[i];
            }
            carry = 0;
            while(a.d[i]>=b) {
                carry++;
                a.d[i]-=b;
            }
        }
        if(carry!=0) {
            a.d.push_back(carry);
        }
        return a;
    }
    friend bignum operator+(bignum a, const bignum& b) {
        return a+=b;
    }
    friend bignum& operator*=(bignum& a,const bignum& o) {
        int total = o.d.size()+a.d.size();
        a.d.resize(total);
        return a;
    }
    friend bignum operator*(bignum a, const bignum& b) {
        return a*=b;
    }
    friend bool operator==(const bignum& a, const bignum& b) {
        return a.d==b.d;
    }
    friend bool operator<(const bignum& a, const bignum& b) {
        if(a.d.size()<b.d.size()) return true;
        if(b.d.size()<a.d.size()) return false;
        return a.d<b.d;
    }
};
ostream& operator<<(ostream& c, const bignum& l) {
    c << l.d.back();
    for(int i=l.d.size()-1; --i>0;) {
        c << setw(9) << setfill('0') << l.d[i];
    }
    return c;
}
int main() {
    bignum a(2);
    for(int i=1;i<=20;++i) {
        a= a*a;
    }
    cout << a << endl;

}