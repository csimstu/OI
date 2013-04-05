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
#include <cassert>
#include <cstring>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)

using namespace std;
typedef long long ll;

class CheckerExpansion {
public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h) {
		vector<string> ret(h, string(w, '?'));
		for ( int i = 0; i < h; i ++ )
			for ( int j = 0; j < w; j ++ ) {
				ll x = x0+j, y = y0+h-i-1;
				bool have = true;
				have &= (x+y)%2==0;
				have &= x>=y;
				have &= (x+y)/2+1<=t;
				if ( !have ) 
					ret[i][j] = '.';
				else
					ret[i][j] = ((x+y)/2+1)&1?'A':'B';
			}
		return ret;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, long long p0, long long p1, long long p2, int p3, int p4, bool hasAnswer, vector <string> p5) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << p2 << "," << p3 << "," << p4;
	cout << "]" << endl;
	CheckerExpansion *obj;
	vector <string> answer;
	obj = new CheckerExpansion();
	clock_t startTime = clock();
	answer = obj->resultAfter(p0, p1, p2, p3, p4);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "{";
		for (int i = 0; int(p5.size()) > i; ++i) {
			if (i > 0) {
				cout << ",";
			}
			cout << "\"" << p5[i] << "\"";
		}
		cout << "}" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "{";
	for (int i = 0; int(answer.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << answer[i] << "\"";
	}
	cout << "}" << endl;
	if (hasAnswer) {
		if (answer.size() != p5.size()) {
			res = false;
		} else {
			for (int i = 0; int(answer.size()) > i; ++i) {
				if (answer[i] != p5[i]) {
					res = false;
				}
			}
		}
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
	
	long long p0;
	long long p1;
	long long p2;
	int p3;
	int p4;
	vector <string> p5;
	
	{
	// ----- test 0 -----
	p0 = 1ll;
	p1 = 0ll;
	p2 = 0ll;
	p3 = 4;
	p4 = 4;
	string t5[] = {"....","....","....","A..."};
			p5.assign(t5, t5 + sizeof(t5) / sizeof(t5[0]));
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 5ll;
	p1 = 4ll;
	p2 = 1ll;
	p3 = 3;
	p4 = 4;
	string t5[] = {"A..","...","B..",".B."};
			p5.assign(t5, t5 + sizeof(t5) / sizeof(t5[0]));
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 1024ll;
	p1 = 1525ll;
	p2 = 512ll;
	p3 = 20;
	p4 = 2;
	string t5[] = {"B...B...B...........",".B.A.B.A.B.........."};
			p5.assign(t5, t5 + sizeof(t5) / sizeof(t5[0]));
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 53ll;
	p1 = 85ll;
	p2 = 6ll;
	p3 = 5;
	p4 = 14;
	string t5[] = {".....",".....","B....",".B.A.",".....",".....",".....",".....",".....",".....","B....",".B...","..B..",".A.B."};
			p5.assign(t5, t5 + sizeof(t5) / sizeof(t5[0]));
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, p4, true, p5) && all_right;
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
