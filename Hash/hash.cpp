#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>
using namespace std;




class Hash {
	typedef long long ll;

	string s;
	ll P;
	vector <ll> MOD;
	vector <vector <ll> > POW;
	vector <vector <ll> > Hashes;
public:

	void initHashes() {
		Hashes.resize(s.size(), vector <ll> (MOD.size(), 0));
		for (int i = 0; i < s.size(); i++) {
			for (int m = 0; m < MOD.size(); m++) {
				ll ppow = POW[1][m];
				ll mmod = MOD[m];
				if (i == 0) {
					Hashes[i][m] = s[0] % mmod;
				} else {
					Hashes[i][m] = (((Hashes[i - 1][m] * ppow) % mmod) + s[i]) % MOD[m];
				}
			}
		}
	}

	Hash() {}
	Hash(string & s, vector <ll> & MOD, vector <vector <ll> > & POW) : s(s), MOD(MOD), POW(POW) {
		initHashes();
	}
	Hash(string & s, vector <ll> & MOD, ll P) : s(s), MOD(MOD), P(P) {
		POW = vector < vector < ll > >(s.size() + 1, vector <ll>(MOD.size()));
		for (int i = 0; i < MOD.size(); i++) {
			POW[0][i] = 1;
		}
		for (int i = 1; i <= s.size(); i++) {
			for (int m = 0; m < MOD.size(); m++) {
				POW[i][m] = (POW[i - 1][m] * P) % MOD[m];
			}
		}
		initHashes();
	}


	ll  getHash(int l, int r, int MODi) {
		assert(l <= r);
		if (l == 0)
			return Hashes[r][MODi];
		ll mmod = MOD[MODi];
		ll HashL = (Hashes[l - 1][MODi] * POW[r - l + 1][MODi]) % mmod;
		ll HashR = Hashes[r][MODi];
		return (HashR - HashL + mmod) % mmod;
	}

	bool substringEquals(Hash & a, Hash & b, int aL, int aR, int bL, int bR) {
		int nMOD = max(a.MOD.size(), b.MOD.size());
		for (int i = 0; i < nMOD; i++) {
			if (a.MOD[i] != b.MOD[i])
				return false;
			if (a.getHash(aL, aR, i) != b.getHash(bL, bR, i))
				return false;
		}
		return true;
	}

	bool substringEquals(Hash & other, int aL, int aR, int bL, int bR) {
		return substringEquals((*this), other, aL, aR, bL, bR);  // ????
	}

	string getString() {
		return s;
	}

};




int main() {
	string a, b;
	int l1, r1, l2, r2;
	cin >> a >> b;
	cin >> l1 >> r1 >> l2 >> r2;
	vector <long long> myMod(2);
	myMod[0] = 1e9 + 7;
	myMod[1] = 1e9 + 9;
	Hash ah(a, myMod, 37);
	Hash bh(b, myMod, 37);
	cout << (ah.substringEquals(bh, l1, r1, l2, r2) ? "Equal" : "Not equal") << endl;
	return 0;
}
