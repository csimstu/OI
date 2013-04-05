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

class CrossingTheRiver {
public:
	int cnt[111];
	bool isPossible(int waterWidth, int landWidth, int waterL, int waterR, int landL, int landR) {
		bool suc = true;
		int rem1 = 0, rem2 = 0, rem3 = 0;

		for ( int x = min(landL, waterL); x <= max(landR, waterR); x ++ ) {
			if ( waterL <= x && x <= waterR && landL <= x && x <= landR ) 
				suc &= cnt[x] >= 2, rem3 += cnt[x] - 2;
			else if ( waterL <= x && x <= waterR )
				suc &= cnt[x] >= 1, rem1 += cnt[x] - 1;
			else if ( landL <= x && x <= landR )
				suc &= cnt[x] >= 1, rem2 += cnt[x] - 1;
		}

		int need1 = waterWidth - (waterR - waterL + 1) - rem1,
			need2 = landWidth - (landR - landL + 1) - rem2;
		need1 = max(0, need1);
		need2 = max(0, need2);

		suc &= need1 + need2 <= rem3;

		return suc;
	}
	string isItEvenPossible(int waterWidth, int landWidth, vector <int> blockHeight, int depth) {
		memset(cnt, 0, sizeof(cnt));
		int n = blockHeight.size();
		for ( int i = 0; i < n; i ++ )
			cnt[blockHeight[i]] ++;
		if ( cnt[depth] >= waterWidth ) return "POSSIBLE";

		for ( int waterL = depth; waterL <= depth + 1; waterL ++ )
			for ( int waterR = waterL; waterR <= 100; waterR ++ )
				for ( int landL = waterR - depth; landL <= waterR - depth + 1; landL ++ )
					for ( int landR = landL; landR <= 100; landR ++ ) {
						if ( isPossible(waterWidth, landWidth, waterL, waterR, landL, landR) )
							return "POSSIBLE";
					}
		return "IMPOSSIBLE";
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, vector <int> p2, int p3, bool hasAnswer, string p4) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p2[i];
	}
	cout << "}" << "," << p3;
	cout << "]" << endl;
	CrossingTheRiver *obj;
	string answer;
	obj = new CrossingTheRiver();
	clock_t startTime = clock();
	answer = obj->isItEvenPossible(p0, p1, p2, p3);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p4 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
	if (hasAnswer) {
		res = answer == p4;
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

	int p0;
	int p1;
	vector <int> p2;
	int p3;
	string p4;
	{
		// ----- test 0 -----
		p0 = 3;
		p1 = 3;
		int t2[] = {3,4,4,5,5,6};
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 2;
		p4 = "POSSIBLE";
		all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, true, p4) && all_right;
		// ------------------
	}

	{
		// ----- test 1 -----
		p0 = 3;
		p1 = 3;
		int t2[] = {3,4,4,5,6,6};
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 2;
		p4 = "IMPOSSIBLE";
		all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, true, p4) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		p0 = 5;
		p1 = 2;
		int t2[] = {4,4,4,4,4};
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 4;
		p4 = "POSSIBLE";
		all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, true, p4) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		p0 = 5;
		p1 = 5;
		int t2[] = {5,5,5,5,5,5,2,3,4,4,6,7,3,2};
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 2;
		p4 = "POSSIBLE";
		all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, true, p4) && all_right;
		// ------------------
	}
	{
		// ----- test 4 -----
		p0 = 5;
		p1 = 7;
		int t2[] = {6,6,6,6,6,6,6,6,6,6,6,6,7,8,9,10};
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 5;
		p4 = "POSSIBLE";
		all_right = KawigiEdit_RunTest(4, p0, p1, p2, p3, true, p4) && all_right;
		// ------------------
	}

	{
		// ----- test 5 -----
		p0 = 1;
		p1 = 1;
		int t2[] = {5,3,4};
		p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
		p3 = 2;
		p4 = "IMPOSSIBLE";
		all_right = KawigiEdit_RunTest(5, p0, p1, p2, p3, true, p4) && all_right;
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
