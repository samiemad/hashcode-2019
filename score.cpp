#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;
ll R; 			// Number of rows
ll C; 			// Number of columns
ll D; 			// Number of drones
ll T; 			// Max time allowed
ll W; 			// Max payload of a drone
ll P; 			// Number of Products
ll w[100]; 		// Weight of product i

ll H;			// Number of warehouses
pll h[100];		// Location of each warehouses
ll hp[100][100];// Count of product j in warehouse i

ll O;			// Number of Orders
pll o[100];		// Location of each order
vll op[100];	// products for each order

int main(int argc, char** argv){
	cin>>R>>C>>D>>T>>W>>P;
	for(int i=0; i<P; ++i){
		cin>>w[i];
	}
	cin>>H;
	for(int i=0; i<H; ++i){
		ll x, y;
		cin>>x>>y;
		h[i] = pll(x,y);
		for(int j=0; j<P; ++j){
			cin>>hp[i][j];
		}
	}
	cin>>O;
	for(int i=0; i<O; ++i){
		ll x, y;
		cin>>x>>y;
		o[i] = pll(x,y);
		int sz;
		cin>> sz;
		op[i] = vll(sz);
		for(int j=0; j<sz; ++j){
			cin>>x;
			op[i][j] = x;
		}
	}

	cout<<"0";
	return 0;
}
