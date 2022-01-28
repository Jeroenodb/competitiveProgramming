#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <numeric>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
const int mxN = 1e5+1;

vector<int> suffixArray(string& s, int symbols = 28) {

    s.push_back('a'-1);
    int n = s.length();
	vector<int> oldlabel(n);
	for (int i = 0; i < n-1; ++i) {
		oldlabel[i] = s[i] - 'a' + 1;
	}

    vector<int> sufarr(n);
    iota(all(sufarr),0);
    sort(all(sufarr), [&](int a, int b) {return oldlabel[a] < oldlabel[b];});
	int maxk = 0;
	while ((1 << maxk) < n) ++maxk;
    // output of radix sort
    int mxCnt = max(symbols+1,n);
    vector<int> output(n),count(mxCnt);
	for (int k = 0; k < maxk; ++k) {
		for(int& i: sufarr) {
            i-=1<<k;
            while(i<0) i+=n;
        }
        //radix sort
        fill(count.begin(),count.end(),0);
        for(int i=0;i<n;++i) {
            count[oldlabel[i]]++;
        }
        for(int i=1;i<mxCnt;++i) {
            count[i]+=count[i-1];
        }
        for(int i=n-1;i>=0;--i) {
            output[--count[oldlabel[sufarr[i]]]] = sufarr[i];
        }
        swap(sufarr,output);
		output[sufarr[0]] = 0;
		int l = 0;
		for (int i = 1; i < n; ++i) {
            int io = sufarr[i]+(1<<k);
            while(io>=n) io-=n;
            int jo = sufarr[i-1]+(1<<k);
            while(jo>=n) jo-=n;
			if (pair<int,int>{oldlabel[sufarr[i]],oldlabel[io]}  > pair<int,int>{oldlabel[sufarr[i - 1]], oldlabel[jo]} ) 
                l++;
			output[sufarr[i]] = l;
		}
        swap(output,oldlabel);
        // for(int i=0;i<n;++i) {
        //     cout << s.substr(sufarr[i]) << endl;
        // } cout << endl;
		if(l==n-1) break;
	}
    return sufarr;
}
vector<int> kasai(string& s, vector<int>& sa) {
    int n=s.size(),k=0;
    vector<int> lcp(n,0);
    vector<int> rank(n,0);

    for(int i=0; i<n; i++) rank[sa[i]]=i;

    for(int i=0; i<n; i++, k?k--:0) {
        if(rank[i]==n-1) {k=0; continue;}
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]]=k;
    }
    return lcp;
}
int main() {
    cin.sync_with_stdio(false);  cin.tie(NULL);
    string s; cin >> s;
    auto ans = suffixArray(s);
    for(int i:ans) {
        cout << i << ' ';
    }
}