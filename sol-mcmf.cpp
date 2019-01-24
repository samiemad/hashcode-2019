#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long L;
typedef vector<L> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
  int N;
  VVL cap, flow, cost;
  VI found;
  VL dist, pi, width;
  VPII dad;

  MinCostMaxFlow(int N) :
    N(N), cap(N, VL(N)), flow(N, VL(N)), cost(N, VL(N)),
    found(N), dist(N), pi(N), width(N), dad(N) {}

  void AddEdge(int from, int to, L cap, L cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
  }

  void Relax(int s, int k, L cap, L cost, int dir) {
    L val = dist[s] + pi[s] - pi[k] + cost;
    if (cap && val < dist[k]) {
      dist[k] = val;
      dad[k] = make_pair(s, dir);
      width[k] = min(cap, width[s]);
    }
  }

  L Dijkstra(int s, int t) {
    fill(found.begin(), found.end(), false);
    fill(dist.begin(), dist.end(), INF);
    fill(width.begin(), width.end(), 0);
    dist[s] = 0;
    width[s] = INF;

    while (s != -1) {
      int best = -1;
      found[s] = true;
      for (int k = 0; k < N; k++) {
        if (found[k]) continue;
        Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
        Relax(s, k, flow[k][s], -cost[k][s], -1);
        if (best == -1 || dist[k] < dist[best]) best = k;
      }
      s = best;
    }

    for (int k = 0; k < N; k++)
      pi[k] = min(pi[k] + dist[k], INF);
    return width[t];
  }

  pair<L, L> GetMaxFlow(int s, int t) {
    L totflow = 0, totcost = 0;
    while (L amt = Dijkstra(s, t)) {
      totflow += amt;
      for (int x = t; x != s; x = dad[x].first) {
        if (dad[x].second == 1) {
          flow[dad[x].first][x] += amt;
          totcost += amt * cost[dad[x].first][x];
        } else {
          flow[x][dad[x].first] -= amt;
          totcost -= amt * cost[x][dad[x].first];
        }
      }
    }
    return make_pair(totflow, totcost);
  }
};

int V,E,R,C,X;
int v[10004];
int t[1003];
vector<pair<int,int>> adj[1003];
vector<pair<int,int>> rdj[1003];
int rv[1000006];
int re[1000006];
int rn[1000006];

int main(){
	cin>>V>>E>>R>>C>>X;
	for(int i=0; i<V; ++i){
		cin>>v[i];
	}
	for(int i=0; i<E; ++i){
		int K;
		cin>>t[i]>>K;
		for(int j=0; j<K; ++j){
			int x,l;
			cin>>x>>l;
			adj[i].push_back({x,l});
			rdj[x].push_back({i,l});
		}
	}
	map<pair<int,int>,int> req;
	for(int i=0; i<R; ++i){
		cin>>rv[i]>>re[i]>>rn[i];
        if(v[rv[i]] > X)    continue;
		req[{rv[i],re[i]}] += rn[i];
	}
	const int RR = req.size();
	MinCostMaxFlow mcmf(RR+C+2);
	int i=0;
	for(auto rr:req){
	    int vv = rr.first.first;
	    int ee = rr.first.second;
	    int nn = rr.second;
		mcmf.AddEdge(0, i+1, v[vv], 0);
		mcmf.AddEdge(i+1, RR+C+1, v[vv], t[ee]*nn);
		for(auto c:adj[ee]){
            mcmf.AddEdge(i+1, c.first+RR+1, v[vv], c.second*nn);
		}
		i++;
	}
	for(int i=0; i<C; ++i){
	    mcmf.AddEdge(i+RR+1, C+RR+1, X, 0);
	}
	auto res = mcmf.GetMaxFlow(0, C+RR+1);
//	cerr<<"\nres=("<<res.first<<","<<res.second<<")\n";

	for(int i=0; i<C+RR+2; ++i){
    	for(int j=0; j<C+RR+2; ++j){
//	        cerr<<"f["<<i<<"]["<<j<<"] = "<<mcmf.flow[i][j]<<"\n";
	    }
	}

	cout<<C<<"\n";
	for(int i=0; i<C; ++i){
		cout<<i;
		int t=0;
		int j=0;
		for(auto rr:req){
            int vv = rr.first.first;
            int ee = rr.first.second;
            int nn = rr.second;
		    int f = mcmf.flow[j+1][i+RR+1];
//		    if(f) cerr<<f<<"("<<v[vv]<<"), ";
	        if(f==v[vv]){
    			cout<<" "<<vv;
    			t += v[vv];
			}
			j++;
		}
		cout<<"\n";
//	    cerr<<"\n"<<i<<": "<<t<<"/"<<mcmf.flow[i+RR+1][C+RR+1]<<"\n";
	}
	return 0;
}
