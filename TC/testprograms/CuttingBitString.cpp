#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;
typedef long long ll;

map<ll, bool> mp;
int w[55][55], f[55];


class CuttingBitString {
public:
	bool ok(string s) {
		int h = s.length();
		if ( s[0] == '0' ) return false;
		ll t = 0;
		for ( int i = 0; i < h; i ++ ) {
			t += (s[i]-'0') * (1LL<<(h-i-1));
		}
		return mp.count(t);
	}

	int getmin(string S) {
		for ( ll x = 1; x < (1LL << 50); x *= 5 )
			mp[x] = true;
		int len = S.length();
		memset(w, 0, sizeof(w));
		for ( int i = 0; i < len; i ++ )
			for ( int j = i; j < len; j ++ )
				w[i][j] = ok(S.substr(i, j-i+1));
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;
		for ( int i = 0; i < len; i ++ )
			for ( int j = 0; j <= i; j ++ )
				if ( w[j][i] )
					f[i+1] = min(f[i+1], f[j]+1);
		if ( f[len] <= len ) return f[len];
		return -1;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, string p0, bool hasAnswer, int p1) {
	cout << "Test " << testNum << ": [" << "\"" << p0 << "\"";
	cout << "]" << endl;
	CuttingBitString *obj;
	int answer;
	obj = new CuttingBitString();
	clock_t startTime = clock();
	answer = obj->getmin(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p1 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p1;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	string p0;
	int p1;
	{
	// ----- test 0 -----
	p0 = "101101101";
	p1 = 3;
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}
	{
	// ----- test 1 -----
	p0 = "1111101";
	p1 = 1;
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = "00000";
	p1 = -1;
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = "110011011";
	p1 = 3;
	all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
	// ------------------
	}
	{
	// ----- test 4 -----
	p0 = "1000101011";
	p1 = -1;
	all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
	// ------------------
	}
	{
	// ----- test 5 -----
	p0 = "111011100110101100101110111";
	p1 = 5;
	all_right = KawigiEdit_RunTest(5, p0, true, p1) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
