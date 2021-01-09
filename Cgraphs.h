#ifndef Cgraphs_H
#define Cgraphs_H

#include<iostream>
#include <vector>
#include<queue>
#include<unordered_map>
typedef long long ll;
using namespace std;


class Cgraph
{

private:
	unordered_map<ll, bool>used;
		unordered_map<ll, ll>parent;
		unordered_map<ll, ll>ways;
		unordered_map<ll, ll>dist;
		unordered_map<ll, vector<ll>>adj;

public:
	// Cgraph(ll n)
	// {
	// 	this->n = n;
		

	void dfs(ll src, vector<ll>&R)
	{
		R.push_back(src);
		used[src] = true;
		for(auto children:adj[src])
		{
			if(!used[children])
			{
				// cout<<children<<endl;
				parent[children] = src;
				dfs(children, R);
			}
		}
	}

	bool IsCycle()
	{
		vector<ll>node_list;
		for(auto u:adj)
 			node_list.push_back(u.first);
 		unordered_map<ll, bool>Vis;
 		for(ll i=0; i<node_list.size(); ++i)
 		{
 			if(Vis.count(node_list[i]) == 0)
 			{
 				// dfs(node_list[i], R);
 				if(dfsCycle(node_list[i], Vis))
 					return true;
 			}
 		}
 		return false;
	}



	bool dfsCycle(ll v, unordered_map<ll, bool>&Vis) 
	{
  		Vis[v] = 1;
  		for (ll s : adj[v]) 
  		{
    		if (Vis[s] == 1) { return true; }
    		if (Vis[s] == 0 && dfsCycle(s, Vis))
      		return true;
  		}
 
  		used[v] = 2;
  		return false;
	}


	void bfs(ll k, vector<ll>&R)
	{
		queue<ll> q;
		q.push(k);
		ways[k]=1;
		used[k]=1;
		while(!q.empty())
		{
			ll node=q.front();
			R.push_back(node);
			q.pop();
			for(auto it:adj[node])
			{
				if(used.count(it) == 0)
				{
					dist[it]=dist[node]+1;
					used[it]=1;
					ways[it]+=ways[node];
					q.push(it);
				}
				else
				{
					if(dist[node]+1==dist[it])
					{
						ways[it]+=ways[node];
					}
				}
			}
		}
	}





 
	vector<vector<ll>> traverse_h()
	{

		vector<ll>node_list;

		vector<vector<ll>>Vec;

 		for(auto u:adj)
 			node_list.push_back(u.first);

 		for(ll i=0; i<node_list.size(); ++i)
 		{
 			vector<ll>R;
 			if(used.count(node_list[i]) == 0)
 			{
 				// dfs(node_list[i], R);
 				bfs(node_list[i], R);
 			}
 			Vec.push_back(R);
 		}
 		return Vec;
	}


	void add_edge(ll a, ll b)
	{
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

};

#endif