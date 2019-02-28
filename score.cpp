#include <bits/stdc++.h>
#include <sstream>
using namespace std;
int N;
pair<int, vector<string>> arr[100001];
char typ;
string tag;
int num;

//////

int solN;
vector<int> solOrder[100001];

/////
vector<string> solTags[100001];

vector<string> mergeTags(vector<string> a, vector<string> b)
{
	map<string, bool> exist;
	vector<string> res;
	for (int i = 0; i < a.size(); i++)
	{
		if (!exist[a[i]])
			res.push_back(a[i]);
		exist[a[i]] = true;
	}

	for (int i = 0; i < b.size(); i++)
	{
		if (!exist[b[i]])
			res.push_back(b[i]);
		exist[b[i]] = true;
	}
	return res;
}

vector<string> intersect(vector<string> a, vector<string> b)
{
	map<string, bool> exist;
	vector<string> res;
	for (int i = 0; i < a.size(); i++)
	{
		exist[a[i]] = true;
	}

	for (int i = 0; i < b.size(); i++)
	{
		if (exist[b[i]])
			res.push_back(b[i]);
	}
	return res;
}

vector<string> diff(vector<string> a, vector<string> b)
{
	map<string, bool> exist;
	vector<string> res;
	for (int i = 0; i < a.size(); i++)
	{
		exist[a[i]] = true;
	}

	for (int i = 0; i < b.size(); i++)
	{
		if (!exist[b[i]])
			res.push_back(b[i]);
	}
	return res;
}

vector<string> getTags(int x)
{
	if (solOrder[x].size() == 1)
	{
		return arr[solOrder[x][0]].second;
	}
	return mergeTags(arr[solOrder[x][0]].second, arr[solOrder[x][1]].second);
}

int main(int argc, char **argv)
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> typ >> num;
		arr[i].first = typ;
		for (int j = 0; j < num; j++)
		{
			cin >> tag;
			arr[i].second.push_back(tag);
		}
	}

	ifstream sin = ifstream(argv[1]);

	sin >> solN;
	string s;
	stringstream linestream;
	int a, b;
	long long solution = 0;
	getline(sin, s);
	for (int i = 0; i < solN; ++i)
	{
		getline(sin, s);
		// cout << s << endl;

		bool t = false;
		for (int j = 0; j < s.size(); j++)
		{
			t |= (s[j] == ' ');
		}
		stringstream ss(s);
		ss >> a;
		solOrder[i].push_back(a);
		if (t)
		{
			ss >> b;
			solOrder[i].push_back(b);
		}

		solTags[i] = getTags(i);

		if (i != 0)
		{
			int r, y, u;
			r = intersect(solTags[i], solTags[i - 1]).size();
			y = diff(solTags[i], solTags[i - 1]).size();
			u = diff(solTags[i - 1], solTags[i]).size();
			solution += min(r, min(y, u));
		}
	}
	cout << solution << endl;
	return 0;
}