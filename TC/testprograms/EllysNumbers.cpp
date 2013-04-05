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

class EllysNumbers {
	public:
		int prime[100000], nPrime;
		int num[5555];
		ll f[2][1 << 18];
		map<int, int> mp;
		int nAtt;
		pair<int, int> att[5555];
		int msk[5555];

		long long getSubsets(long long n, vector <string> special) {
			mp.clear();
			nAtt = nPrime = 0;
			memset(msk, 0, sizeof(msk));

			string totstr;
			FOREACH(it, special)
				totstr += *it;
			stringstream ss;
			ss << totstr;
			int r = 0;
			while ( ss >> num[r] ) r ++;
			for ( int i = 0; i < r; i ++ ) {
				int x = num[i];
				for ( int y = 2, lim = (int)sqrt(x); y <= lim; y ++ )
					if ( x % y == 0 ) {
						prime[nPrime++] = y;
						while ( x % y == 0 )
							x /= y;
					}
				if ( x > 1 )
					prime[nPrime++] = x;
			}
			sort(prime, prime + nPrime);
			nPrime = unique(prime, prime + nPrime) - prime;
			ll tmp = n;
			for ( int i = 0; i < nPrime; i ++ ) 
				if ( tmp % prime[i] == 0 ) {
					int cnt = 0;
					while ( tmp % prime[i] == 0 )
						cnt ++, tmp /= prime[i];
					att[nAtt++] = make_pair(prime[i], cnt);
					mp[prime[i]] = nAtt-1;
				}
			if ( tmp != 1 ) return 0LL;
			for ( int i = 0; i < r; i ++ ) {
				int x = num[i];
				bool fail = false;
				msk[i] = 0;
				for ( int j = 0; !fail && j < nPrime; j ++ )
					if ( mp.count(prime[j]) && x % prime[j] == 0 ) {
						int cnt = 0;
						while ( x % prime[j] == 0 )
							cnt ++, x /= prime[j];
						if ( cnt != att[mp[prime[j]]].second ) 
							fail = true;
						msk[i] |= 1 << mp[prime[j]];
					}
				if ( fail || x != 1 )
					msk[i] = -1;
			}

			f[0][0] = 1;
			int cur = 0;
			for ( int i = 0; i < r; i ++ )
				if ( msk[i] != -1 ) {
					memset(f[!cur], 0, sizeof(f[!cur]));
					for ( int s = 0; s < (1 << nAtt); s ++ ) {
						f[!cur][s] += f[cur][s];
						if ( !(s & msk[i]) )
							f[!cur][s | msk[i]] += f[cur][s];
					}
					cur ^= 1;
				}
			return f[cur][(1 << (nAtt)) - 1];
		}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, long long p0, vector <string> p1, bool hasAnswer, long long p2) {
	cout << "Test " << testNum << ": [" << p0 << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p1[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	EllysNumbers *obj;
	long long answer;
	obj = new EllysNumbers();
	clock_t startTime = clock();
	answer = obj->getSubsets(p0, p1);
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

	long long p0;
	vector <string> p1;
	long long p2;

	{
		// ----- test 0 -----
		p0 = 89136273185960LL;
		string t1[] = {"41 637 5 6877 392 4961 2107 1 5929 14104 43 1573 6", "05 49 64009 2645 3224 215 932627 131192 31 533 121", " 205 1333 25921 86387 104 2009 559 22747 5203 2131", "87 65 328 7865 26015 13 245 8 27391 281957 1763 24", "8 21160 1271 47432 40 968 16399 403 65317 295711 1", "83799 4232 10168 1519 173512 26117"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 4472ll;
		all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 1 -----
		p0 = 42ll;
		string t1[] = {"1 2 3 4 5 6 7 13 14 21 42"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 10ll;
		all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		p0 = 1337ll;
		string t1[] = {"1 13 42 666 2674"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 0ll;
		all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		p0 = 1073741824ll;
		string t1[] = {"1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 1","6384 32768 65536 131072 262144 524288 1048576 2097","152 4194304 8388608 16777216 33554432 67108864 134","217728 268435456 536870912"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 0ll;
		all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 4 -----
		p0 = 7420738134810ll;
		string t1[] = {"435 625199055 4199 33263 17 222870 284870433 72093","2379 7 11 31 247110827 23 1771 81809 851968487 13 ","476379795 1001 5 435274114 38264554 7429 239906525"," 3 227183706 887045414 606786670 3795 797605175 29"," 30 747186719 19 2 562347843 74 2294 588002688 743","6429 703 591740547 36657492 37 444178205 1002001 2","17626404"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 110ll;
		all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
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
