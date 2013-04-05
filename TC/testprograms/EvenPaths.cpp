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

class EvenPaths {
	public:
		int n, m, lm, rm, rstart;
		int stk[55], dgr[55];
		int seq[55], seqCnt;
		ll A[1<<17], B[1<<17], C[1<<17];
		vector<int> adj[55], inv[55];
		int pos[55], id[55], unk[55];
		
		string rooms;
		vector<string> maze;

		int countbits(int s) {
			int res = 0;
			while ( s ) {
				res += s & 1;
				s >>= 1;
			}
			return res;
		}

		void topsort() {
			memset(dgr, 0, sizeof(dgr));
			for ( int i = 0; i < n; i ++ )
				FOREACH(it, adj[i])
					dgr[*it]++;
			int top = 0;
			for ( int i = 0; i < n; i ++ )
				if ( dgr[i] == 0 ) stk[top++] = i;
			seqCnt = 0;
			while ( top ) {
				int x = stk[--top];
				seq[seqCnt++] = x;
				FOREACH(y, adj[x]) {
					dgr[*y]--;
					if ( dgr[*y] == 0 ) stk[top++] = *y;
				}
			}
		}

		void expandLeft(int s) {
			static int f[55], g[55];
			memset(f, 0, sizeof(f));
			f[0] = 1;
			for ( int i = 0; i < seqCnt; i ++ )
				if ( f[i] ) {
					int x = seq[i];
					FOREACH(it, adj[x]) {
						int y = *it;
						if ( pos[y] == -1 ) continue;
						if ( rooms[y] == '?' && id[y] < lm && (s & (1 << id[y])) )
							f[pos[y]] ^= f[i];
						else if ( rooms[y] == '-' )
							f[pos[y]] ^= f[i];
					}
				}
			memset(g, 0, sizeof(g));
			g[rm] = f[seqCnt-1];
			for ( int i = 0; i < seqCnt; i ++ )
				if ( f[i] ) {
					int x = seq[i];
					FOREACH(it, adj[x]) {
						int y = *it;
						if ( pos[y] == -1 || rooms[y] == '-' || pos[y] < rstart ) continue;
						g[id[y] - lm] ^= f[i];
					}
				}
			int msk = 0;
			for ( int i = 0; i <= rm; i ++ )
				msk |= g[i] << i;
			A[msk]++;
		}

		void expandRight(int s) {
			static int f[55];
			memset(f, 0, sizeof(f));
			f[seqCnt-1] = 1;
			for ( int i = seqCnt - 1; i > rstart; i -- )
				if ( f[i] ) {
					int x = seq[i];
					FOREACH(it, inv[x]) {
						int y = *it;
						if ( pos[y] == -1 || pos[y] < rstart ) continue;
						if ( rooms[y] == '?' && !(s & (1 << (id[y] - lm))) ) continue;
						f[pos[y]] ^= f[i];
					}
				}
			int msk = 0;
			msk |= 1 << rm;
			for ( int i = 0; i < rm; i ++ )
				msk |= f[pos[unk[lm + i]]] << i;
			B[msk]++;
		}

		void transform(ll *X, int l, int r) {
			if ( l == r ) return;
			int mid = (l + r) / 2;
			transform(X, l, mid);
			transform(X, mid + 1, r);
			for ( int k = mid + 1; k <= r; k ++ ) 
				X[k - mid - 1 + l] += X[k];
		}

		void untransform(ll *X, int l, int r) {
			if ( l == r ) return;
			int mid = (l + r) / 2;
			for ( int k = mid + 1; k <= r; k ++ ) 
				X[k - mid - 1 + l] -= X[k];
			untransform(X, l, mid);
			untransform(X, mid + 1, r);
		}

		long long theCount(vector <string> _maze, string _rooms) {
			maze = _maze, rooms = _rooms;
			n = maze.size();
			int fool = 0;
			for ( int i = 0; i < n; i ++ )
				if ( rooms[i] == '?' )
					fool ++;

			for ( int i = 0; i < n; i ++ )
				for ( int j = 0; j < n; j ++ )
					if ( i != j && maze[i][j] == 'Y' ) {
						adj[i].push_back(j);
						inv[j].push_back(i);
					}
			topsort();
			int st = 0;
			while ( seq[st] != 0 ) st ++;
			memmove(seq, seq + st, sizeof(int)*(seqCnt-st));
			seqCnt -= st;
			while ( seqCnt > 0 && seq[seqCnt-1] != 1 ) seqCnt--;
			if ( seqCnt==0 ) return 1LL << fool;

			memset(pos, -1, sizeof(pos));
			for ( int i = 0; i < seqCnt; i ++ )
				pos[seq[i]] = i;
			m = 0;
			memset(id, -1, sizeof(id));
			for ( int i = 0; i < seqCnt; i ++ ) 
				if ( rooms[seq[i]] == '?' ) {
					fool--;
					unk[m++] = seq[i];
					id[seq[i]] = m-1;
				}
			lm = m / 2, rm = m - lm;

			rstart = pos[unk[lm]];

			for ( int s = 0, upperlim = 1 << lm; s < upperlim; s ++ ) 
				expandLeft(s);
			for ( int s = 0, upperlim = 1 << rm; s < upperlim; s ++ ) 
				expandRight(s);

			int sz = 1 << (rm + 1);
			transform(A, 0, sz - 1);
			transform(B, 0, sz - 1);
			for ( int i = 0; i < sz; i ++ )
				C[i] = A[i] * B[i];
			untransform(C, 0, sz - 1);
			ll ans = 0;
			for ( int i = 0; i < sz; i ++ )
				if ( countbits(i) % 2 == 0 ) 
					ans += C[i];
			return ans * (1LL << fool);
		}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <string> p0, string p1, bool hasAnswer, long long p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}" << "," << "\"" << p1 << "\"";
	cout << "]" << endl;
	EvenPaths *obj;
	long long answer;
	obj = new EvenPaths();
	clock_t startTime = clock();
	answer = obj->theCount(p0, p1);
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

	vector <string> p0;
	string p1;
	long long p2;

	/*{
		// ----- test 0 -----
		string t0[] = {"NYY","NNN","NYN"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "--?";
		p2 = 1ll;
		all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 1 -----
		string t0[] = {"NYYNN","NNNNY","NYNNN","YNNNN","NNNNN"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "--?" "?" "?";
		p2 = 4ll;
		all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
		// ------------------
	}
	
	{
		// ----- test 2 -----
		string t0[] = {"NNNNN","NNYYN","YNNNY","NNNNN","NNNNN"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "--?" "?" "?";
		p2 = 8ll;
		all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		string t0[] = {"NNYNYNNY","NNNNNNNN","NNNNNYYY","NYNNNNNN","NNNNNNNN","NYNYNNNN","NYNNYNNN","NNNYYNYN"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "----?" "?" "?-";
		p2 = 4ll;
		all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 4 -----
		string t0[] = {"NYNNNNYYYYYYYNYNYNNN","NNNNNNNNNNNNNNNNNNNN","NNNNYNYYNYNNNNYNYNYN","NNNNNNNNNNNNNNNNYYNN","NNNYNNNNNNYYNNYYNNNY","NYNNYNYYYYNYNYNYYYNN","NNNYYNNNYNYYNNYNYYNY","NNNYNNYNYNYNYNYYYYYN","NYNYYNNNNNNYYNNYYNNN","NNNNNNNNNNYNYNNNYYNN","NYNNNNNNNNNYNNNNYNNY","NNNNNNNNNNNNNNNNNNNN","NNNYNNNNNNNNNNYNNYNN","NNNYYNYNNYNNNNNYYYNN","NNNNNNNNNNNNNNNNNYNN","NYNYNNNNNNNNNNYNNNNN","NNNNNNNNNNNNNNNNNNNN","NYNNNNNNNNNNNNNNNNNN","NYNNNNNNNYNYYNNYYYNN","NYNNNNNNNNNNYNYNYYNN"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "---?" "?-?" "?--?" "?--?-?---";
		p2 = 136ll;
		all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
		// ------------------
	}*/

	{
		// ----- test 5 -----
		string t0[] = {"NYNNNNNYYNYNNNNNNNNNNYNNYNNNNYNYNN", "NNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNYNN", "YYNNNYYYNNYNNNYNNYYNNYNYYYNNNYYYNN", "YYYNYYYNYYYYYNYYNYYYYYYYYYYYYYYYNY", "YNYNNNNYYNYNYNYNYYYNNYNYYYNYNYYYNN", "NYNNNNYYYNNNNNYNNNYNNYNYYYNNNNNYNN", "YYNNNNNYYNYNNNYNNYYNNYNYYYNNNNNYNN", "NYNNNNNNYNYNNNNNNNNNNNNNNYNNNNNYNN", "NNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNYNN", "YYYNYYNYYNYYYNYNYNYNYYYYYYYYYYYNYN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNN", "YYYNYNYYYNYNYNYNYYYNYYNYYYYYYYYYYY", "YYYNNYNYYNYNNNYNNYNNNYNYYYNYNYYYNN", "YYYNYYYNYYYYYNNYYYYYYNYYYYYYNYYYYY", "YYNNNNNNYNYNNNNNNNYNNYNNYYNNNNNYNN", "YYYNYYYYYYNYYNYNYYYNYYYYYYYYYNYYYY", "NYYNNYYYNNYNNNYNNYYNNYNYYYNYNYYYNN", "YYNNNNNYYNNNNNYNNNYNNYNNNNNNNYNYNN", "NYNNNNNYYNYNNNNNNNNNNYNNYYNNNYNYNN", "YYYNYYYYYYYYYNYYYNYNYYYYYYYNYYYYYY", "YYYNYYNYYNYNYNYNYYNNNYNYYYYYYYYYYN", "NYNNNNNYYNYNNNNNNNNNNNNNYYNNNYNYNN", "YNYNYYYYYNYYNNYNNYYNYYNYYYYYYYYYYY", "YYNNNNNYYNYNNNYNNYYNNYNNYNNNNNNYNN", "NYNNNNNYYNYNNNNNNNNNNNNNNNNNNYNYNN", "NYNNNNNNYNNNNNNNNNNNNNNNNNNNNYNYNN", "YYYNYYYYYNYNYNYNYYYNNYNYYYNYNYYYYN", "YYYNNYYYYNYNNNYNNYYNNYNYYYNNNNYYNN", "YNYNNNYYYNYNYNYNYYYNNYNYYYNYNYYYNN", "NYNNNNNNYNYNNNNNNNNNNNNNNNNNNNNYNN", "YYNNNNYYYNYNNNYNNYYNNNNYYYNNNYNYNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NYYNNYYYYNYNYNNNYYYNNYNYYYNYYYYYNN", "YNYNYYYYYNYNYNYNYYYNNYNYYYYYYYNYYN"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = string("-------?""?---?""--------?""-?""?---------");
		p2 = 56ll;
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