#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)

struct image
{
	image(int i, bool o, vector<string> t) : tags(t), idx(i), orient(o) {}

	vector<string> tags;
	ll idx;
	ll val = 0;
	bool orient;
};

ll N;
vector<image> img;
vll imgg[2];
map<string, int> freq;
vector<pll> ord[2];

vector<pll> sol[2];

ll getval(vector<pll> &a, bool o)
{
	if (!o)
	{
		return a.empty() ? -1 : a.back().first;
	}
	else
	{
		return a.size() < 2 ? -1 : (a.back().first + a[a.size() - 2].first);
	}
}

int main(int argc, char **argv)
{
	cin >> N;
	int img0 = 0, img1 = 0;
	for (int i = 0; i < N; ++i)
	{
		int x;
		char c;
		vector<string> tmp;
		cin >> c >> x;
		for (int j = 0; j < x; ++j)
		{
			string s;
			cin >> s;
			freq[s]++;
			tmp.push_back(s);
		}
		imgg[c != 'H'].push_back(i);
		img.push_back(image(i, c != 'H', tmp));
	}

	for (auto im : img)
	{
		for (auto t : im.tags)
		{
			im.val += freq[t];
		}
		ord[im.orient].pb(mp(im.val, im.idx));
	}

	sort(ord[0].begin(), ord[0].end());
	sort(ord[1].begin(), ord[1].end());

	bool f = false;

	while (ord[0].size() > 0 || ord[1].size() > 1)
	{
		ll v0 = getval(ord[0], 0);
		ll v1 = getval(ord[1], 1);
		if (v0 < 0 && v1 < 0)
			break;

		if (v0 > v1)
		{
			sol[f].pb(mp(-10, ord[0].back().second));
			ord[0].pop_back();
		}
		else
		{
			sol[f].pb(mp(ord[1].back().second, ord[1][ord[1].size() - 2].second));
			ord[1].pop_back();
			ord[1].pop_back();
		}
		f = !f;
	}

	reverse(sol[0].begin(), sol[0].end());

	cout << (sol[0].size() + sol[1].size()) << "\n";

	// cout << (sol[0].size()) << "\n";
	// for(auto x:sol[0]) cout<<x.first<<" "<<x.second<<" ; ";cout<<"\n";
	// cout << (sol[1].size()) << "\n";
	// for(auto x:sol[1]) cout<<x.first<<" "<<x.second<<" ; ";cout<<"\n";

	for (int i = 0; i < sol[0].size(); ++i)
	{
		if (sol[0][i].first > 0)
		{
			cout << sol[0][i].first << " ";
		}
		cout << sol[0][i].second << "\n";
	}
	for (int i = 0; i < sol[1].size(); ++i)
	{
		if (sol[1][i].first > 0)
		{
			cout << sol[1][i].first << " ";
		}
		cout << sol[1][i].second << "\n";
	}
	return 0;
}
