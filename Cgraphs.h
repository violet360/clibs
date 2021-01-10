#ifndef Cgraphs_H
#define Cgraphs_H

#include<iostream>
#include <vector>
#include<queue>
#include<stack>
#include<unordered_map>
typedef long long ll;
using namespace std;


class Cgraph
{

private:
	bool b = false;
	unordered_map<ll, bool>used;
	unordered_map<ll, ll>parent;
	unordered_map<ll, ll>ways;
	unordered_map<ll, ll>dist;
	unordered_map<ll, vector<ll>>adj;
	stack<ll>mystack;

public:
	



	void DFS0(ll u,unordered_map<ll, ll>& disc,unordered_map<ll, ll>& low,unordered_map<ll, ll>& parent,unordered_map<ll, bool>& articulation_Point)
	{
		static ll time = 0;
		disc[u] = low[u] = time;
		time+=1;
		ll children = 0;

		for(ll v: adj[u])
		{
			if(disc[v]==-1)	//If v is not visited
			{
				children += 1;
				parent[v] = u;
				DFS0(v,disc,low,parent,articulation_Point);
				low[u] = min(low[u],low[v]);

				if(parent[u]==-1 and children>1)	//Case-1: U is root
					articulation_Point[u] = true;

				if(parent[u]!=-1 and low[v]>=disc[u])	//Case-2: Atleast 1 component will get separated
					articulation_Point[u] = true;
			}
			else if(v!=parent[u])	//Ignore child to parent edge
				low[u] = min(low[u],disc[v]);
		}	
	}


	vector<ll> findAPs_Tarjan()
	{
		unordered_map<ll, ll> disc;
		unordered_map<ll, ll> low;
		unordered_map<ll, ll> parent;
		unordered_map<ll, bool>articulation_Point;
		// vector<bool> articulation_Point(V,false);
		vector<ll>node_list;

		vector<vector<ll>>Vec;

 		for(auto u:adj)
 		{
 			// cout<<u.first<<" ";
 			node_list.push_back(u.first);
 		}

 		for(auto u:node_list)
 		{
 			// cout<<u<<"--";
 			disc[u]= -1;
 			low[u] = -1;
 			parent[u] = -1;
 			articulation_Point[u] = false;
 		}

		for(auto u:node_list)
		{
			if(disc[u]==-1)
			{
				// cout<<u<<" ";
				DFS0(u,disc,low,parent,articulation_Point);
			}
		}

		vector<ll>res;
		// for(int i=0;i<V;++i)
		for(ll i:node_list)
			if(articulation_Point[i]==true)
				res.push_back(i);

		return res;
	}
















	unordered_map<ll, vector<ll>> reverse(vector<ll>&nodes)
	{

		unordered_map<ll, vector<ll>>rev;
		for(ll i=0; i<nodes.size(); ++i)
		{
			for(ll j: adj[i])
				rev[j].push_back(i);
		}

		return rev;
	}

	void DFS2(ll src, vector<ll>&R, unordered_map<ll, vector<ll>>&adj)
	{

		R.push_back(src);
		used[src] = true;
		for(auto children:adj[src])
		{
			if(!used[children])
			{
				parent[children] = src;
				DFS2(children, R, adj);
			}
		}
		
	}

	vector<vector<ll>> findSCCs()
	{

		vector<ll>node_list;

		vector<vector<ll>>Vec;

 		for(auto u:adj)
 		{
 			// cout<<u.first<<" ";
 			node_list.push_back(u.first);
 		}

 		for(auto u:node_list)
 		{
 			used[u] = false;
 		}

		b = true;



		for(ll i=0; i<node_list.size(); ++i)
 		{
 			vector<ll>R;
 			if(!used[node_list[i]])
 			{
 				dfs(node_list[i], R);
 			}
 		}








		unordered_map<ll, vector<ll>>res = reverse(node_list);
		
		for(auto u:node_list)
 		{
 			used[u] = false;
 		}

		// cout<<"Strongly Connected Components are:\n";
		while(!mystack.empty())
		{
			vector<ll>R;
			int curr = mystack.top();
			mystack.pop();
			if(used[curr]==false)
			{
				DFS2(curr, R, res);
				Vec.push_back(R);
			}
		}
 		for(auto u:node_list)
 		{
 			used[u] = false;
 		}

 		b = false;


 		for(auto u:node_list)
 		{
 			used[u] = false;
 		}


		return Vec;
	}

	void dfs(ll src, vector<ll>&R)
	{
		cout<<src<<" ";
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
		if(b)
		(this->mystack).push(src);
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
	void add_edge_D(ll a, ll b)
	{
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

};

#endif
