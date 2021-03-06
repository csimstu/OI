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
ll f[51][10000];

class RollingDiceDivOne {
public:
	long long mostLikely(vector <int> dice) {
		int n = dice.size();
		int m = 0;
		for ( int i = 0; i < n; i ++ )
			m += dice[i];
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for ( int i = 0; i < n; i ++ ) {
			for ( int j = i; j <= m; j ++ )
				if ( f[i][j] )
					fprintf(stderr, "%lld ", f[i][j]);
			puts("");
			for ( int j = m; j >= 0; j -- )
				for ( int k = 1; k <= dice[i]; k ++ )
					if ( j >= k )
						f[i+1][j] += f[i][j-k];
		}
		for ( int j = n; j <= m; j ++ )
			if ( f[n][j] ) 
				fprintf(stderr, "%lld ", f[n][j]);
		puts("");
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, bool hasAnswer, long long p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}";
	cout << "]" << endl;
	RollingDiceDivOne *obj;
	long long answer;
	obj = new RollingDiceDivOne();
	clock_t startTime = clock();
	answer = obj->mostLikely(p0);
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

	vector <int> p0;
	long long p1;

	{
		// ----- test 0 -----
		int t0[] = {3,1,8,1,1,3};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 11ll;
		all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
		// ------------------
	}

	return 0;

	{
		// ----- test 1 -----
		int t0[] = {10};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 1ll;
		all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		int t0[] = {2,3,4,5};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 9ll;
		all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		int t0[] = {1,10,1};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 3ll;
		all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
		// ------------------
	}

	return 0;

	{
		// ----- test 4 -----
		int t0[] = {382828264,942663792,291832707,887961277,546603677,545185615,146267547,6938117,167567032,84232402,700781193,452172304,816532384,951089120,448136091,280899512,256093435,39595226,631504901,154772240};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 4366828428ll;
		all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
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
