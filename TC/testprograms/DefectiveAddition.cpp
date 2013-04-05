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
const int kMod = 1000000007;

void add(int &a, int b) {
	a += b;
	a %= kMod;
}

int mul(int a, int b) {
	return (ll)a * b % kMod;
}

int f[55], g[55][2][2];

class DefectiveAddition {
public:
	int count(vector <int> cards, int des) {
		int n = cards.size();
		int tmp = 0;
		for ( int i = 0; i < n; i ++ ) 
			tmp ^= cards[i];
		int res = tmp == des;

		for ( int i = 29; ((tmp&(1<<(i+1))) == (des&(1<<(i+1)))) && i >= 0; i-- ) {
			memset(g, 0, sizeof(g));
			g[0][0][0] = 1;
			for ( int j = 0; j < n; j ++ ) 
				for ( int s1 = 0; s1 <= 1; s1 ++ ) 
					for ( int s2 = 0; s2 <= 1; s2 ++ ) 
						if ( g[j][s1][s2] ) {
							//fill 0
							if ( s2 ) {
								if ( cards[j]&(1<<i) )
									add(g[j+1][s1][1], mul(g[j][s1][s2], 1<<i));
								else
									add(g[j+1][s1][1], mul(g[j][s1][s2], (((1<<i)-1)&cards[j])+1));
							} else {
								if ( cards[j]&(1<<i) )
									add(g[j+1][s1][1], g[j][s1][s2]);
								else
									add(g[j+1][s1][0], mul(g[j][s1][s2], (((1<<i)-1)&cards[j])+1));
							}
							//fill 1
							if ( cards[j]&(1<<i) ) {
								add(g[j+1][s1^1][s2], mul(g[j][s1][s2], (((1<<i)-1)&cards[j])+1));
							}
						}
			f[i] = 0;
			add(f[i], g[n][(des&(1<<i))>0][1]);
			add(res, f[i]);
		}
		return res;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, int p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << p1;
	cout << "]" << endl;
	DefectiveAddition *obj;
	int answer;
	obj = new DefectiveAddition();
	clock_t startTime = clock();
	answer = obj->count(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p2;
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

	vector <int> p0;
	int p1;
	int p2;
	{
		// ----- test 0 -----
		int t0[] = {2,3};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 2;
		p2 = 3;
		all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
		// ------------------
	}
	{
		// ----- test 1 -----
		int t0[] = {1,2,3};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 1;
		p2 = 6;
		all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		int t0[] = {4,5,7,11};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 6;
		p2 = 240;
		all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		int t0[] = {1,2,3,4,5,6,7,8,9,10};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 15;
		p2 = 1965600;
		all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 4 -----
		int t0[] = {1,2,3,4,5,6,7,8,9,10};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 16;
		p2 = 0;
		all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 5 -----
		int t0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 1;
		p2 = 949480669;
		all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
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