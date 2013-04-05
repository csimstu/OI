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
const ll kInf = 0x3f3f3f3f3f3f3f3fLL;

struct Number {
	ll val;
	int dig[22], nDig;
	void init() {
		ll tmp = val;
		nDig = 0;
		while ( tmp ) {
			dig[nDig++] = tmp % 10;
			tmp /= 10;
		}
		reverse(dig, dig + nDig);
	}
};

class FavouriteDigits {
	public:
		ll eval(ll N, int digit1, int count1, int digit2, int count2) {
			if ( digit1 > digit2 ) {
				swap(digit1, digit2);
				swap(count1, count2);
			}
			Number num;
			num.val = N;
			num.init();
			{
				int cnt1 = 0, cnt2 = 0;
				for ( int i = 0; i < num.nDig; i ++ ) {
					if ( num.dig[i] == digit1 ) cnt1 ++;
					if ( num.dig[i] == digit2 ) cnt2 ++;
				}
				if ( cnt1 >= count1 && cnt2 >= count2 )
					return N;
			}
			for ( int i = num.nDig - 1; i >= 0; i -- ) {
				int cnt1tmp = 0, cnt2tmp = 0;
				for ( int j = 0; j < i; j ++ ) {
					if ( num.dig[j] == digit1 ) cnt1tmp ++;
					if ( num.dig[j] == digit2 ) cnt2tmp ++;
				}
				for ( int x = num.dig[i] + 1; x <= 9; x ++ ) {
					int cnt1 = cnt1tmp, cnt2 = cnt2tmp;
					if ( x == digit1 ) cnt1 ++;
					if ( x == digit2 ) cnt2 ++;
					int left1 = max(0, count1 - cnt1),
						left2 = max(0, count2 - cnt2);
					if ( num.nDig - 1 - i >= left1 + left2 ) {
						ll ans2 = 0;
						for ( int k = 0; k < i; k ++ )
							ans2 = ans2 * 10 + num.dig[k];
						ans2 = ans2 * 10 + x;
						for ( int k = 0; k < num.nDig-1-i-left1-left2; k ++ )
							ans2*=10;
						for ( int k = 0; k < left1; k ++ )
							ans2 = ans2 * 10 + digit1;
						for ( int k = 0; k < left2; k ++ )
							ans2 = ans2 * 10 + digit2;
						return ans2;
					}
				}
			}
			return kInf;
		}
		long long findNext(long long N, int digit1, int count1, int digit2, int count2) {
			if ( digit1 > digit2 ) {
				swap(digit1, digit2);
				swap(count1, count2);
			}
			Number num;
			num.val = N;
			num.init();

			if ( num.nDig < count1 + count2 ) {
				N = 1;
				for ( int k = 0; k < count1 + count2 - 1; k ++ )
					N *= 10;
				num.val = N;
				num.init();
			}

			ll tmp = 1;
			for ( int i = 0; i < num.nDig; i ++ )
				tmp *= 10;
			ll ans1 = eval(tmp, digit1, count1, digit2, count2),
			   ans2 = eval(N, digit1, count1, digit2, count2);
			return min(ans1, ans2);
		}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, long long p0, int p1, int p2, int p3, int p4, bool hasAnswer, long long p5) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << p2 << "," << p3 << "," << p4;
	cout << "]" << endl;
	FavouriteDigits *obj;
	long long answer;
	obj = new FavouriteDigits();
	clock_t startTime = clock();
	answer = obj->findNext(p0, p1, p2, p3, p4);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p5 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p5;
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
	int p1;
	int p2;
	int p3;
	int p4;
	long long p5;

	{
		// ----- test 0 -----
		p0 = 1111111111ll;
		p1 = 4;
		p2 = 1;
		p3 = 3;
		p4 = 14;
		p5 = 47ll;
		all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}
	return 0;
	{
		// ----- test 1 -----
		p0 = 47ll;
		p1 = 5;
		p2 = 0;
		p3 = 9;
		p4 = 1;
		p5 = 49ll;
		all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		p0 = 47ll;
		p1 = 5;
		p2 = 0;
		p3 = 3;
		p4 = 1;
		p5 = 53ll;
		all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		p0 = 47ll;
		p1 = 2;
		p2 = 1;
		p3 = 0;
		p4 = 2;
		p5 = 200ll;
		all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 4 -----
		p0 = 123456789012345ll;
		p1 = 1;
		p2 = 2;
		p3 = 2;
		p4 = 4;
		p5 = 123456789012422ll;
		all_right = KawigiEdit_RunTest(4, p0, p1, p2, p3, p4, true, p5) && all_right;
		// ------------------
	}

	{
		// ----- test 5 -----
		p0 = 92ll;
		p1 = 1;
		p2 = 1;
		p3 = 0;
		p4 = 0;
		p5 = 100ll;
		all_right = KawigiEdit_RunTest(5, p0, p1, p2, p3, p4, true, p5) && all_right;
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