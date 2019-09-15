/*
 * stp-validate.cpp
 * 
 * Copyright 2019 Rajesh Pandian M <mrpaj@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <sstream>
#include <climits>
#include <vector>
#include <set>
#include <signal.h>
#include <unistd.h>
#include <cstring>
#include <cmath>
#include <chrono>
#include <iomanip> // for set precision/fixed in cout
#include <unordered_map> // for unordered map
#include <map> // for  map
#include <queue> // for  queue

#define DEFAULT -1234567890

using namespace std;

int LEVEL = 0;
// 1 -- prints debug lines 
// 0 -- submission level

#define DEBUG if(LEVEL)	 

class Edge { 
public:
	int to;
	int length; 
	
	Edge(){}
	~Edge(){}
	Edge(int t, int l){
		to = t; length = l;
	}
	bool operator < (const Edge& e){
		return length < e.length;
	}
};


class Arg{
public:
	bool isEdgesToPrint;
	
	Arg(){
		isEdgesToPrint= false;
	}
	
	Arg(int options){
		switch(options){
			case 1:
				isEdgesToPrint = true;
		}
	}
	
	~Arg(){}
	
};

void DFS(unordered_map<int, vector<int>> &graph, unordered_map<int, bool> &visited, int u){
	visited[u]= true;
	for(auto v : graph[u]){
		if(visited[v] == false)
			DFS(graph, visited, v);
	}
}

bool isConnected(set<int> &treeNodes, vector<pair<int,int>> &treeEdges, set<int> &terminalSet){
	
	unordered_map<int, vector<int>> graph; 	// adj list 
	unordered_map<int, bool> visited; 		// visited array
	
	vector<int> empty; // initialize
	for(auto node: treeNodes){
		graph[node]= empty;
		visited[node]=false;
	}
	for(auto edge : treeEdges){
		int u = edge.first;
		int v = edge.second;	
		graph[u].push_back(v);
		graph[v].push_back(u);
	}	
	
	DEBUG cout << "PRINTING TREE" << endl;
	DEBUG 
	for(auto list: graph) {
		cout << list.first << ": ";
		for(auto v : list.second)
			cout << v << " ";
		cout << endl;	
	}
	
	int start = *terminalSet.begin(); //  to get first terminal.
	
	DFS(graph, visited, start);
	
	// Checks if at least one of the tree node is not visited; 
	// if so T is disconnected 
	for(auto node: treeNodes){ 
		if(visited[node]==false)
			return false;
	}
	
	return true;
}

bool isTreeWeightAreSame(map<pair<int,int> , int> &W, vector<pair<int,int>> treeEdges, long long int stpVal){
	long long int computedStpVal = 0;
	
	for(auto edge : treeEdges){
		int u = edge.first ;
		int v = edge.second;
		if(W.find({u,v}) != W.end())
			computedStpVal += W[make_pair(u,v)];
		else{
			cout<< "WRONG: Non Existing Edge of G in T"<< endl;
			return false;
		}
	}

	if(stpVal != computedStpVal)
		return false;
	return true;
}

bool isAllTerminalsPresent(set <int> &terminalSet, set<int> &nodes){
	for(auto  a : terminalSet){
		if(nodes.find(a) == nodes.end() ) // a terminal not found
			return false;
	}
	return true;
}

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	
	vector< vector<Edge> > graph;
	map<pair<int,int> , int> W;
	
	vector <int> terminals;
	set <int> terminalSet;
	string code, type, dummy;
	int N = -1; 
	 
	while( cin>> code >> type ){
		// some benchmarks have "Section" where pace has "SECTION"
		if((code == "SECTION" || code == "Section") && type =="Graph"){
			long m, n;
			long u, v, w;
			cin >> dummy >> n;
			cin >> dummy >> m;
			N = n+1; 
			graph.resize(N); // coz graph has from index 0. where as challege its 1
			for(long i=0; i < m; i++){
				cin>> dummy >> u >> v >> w;
				graph[u].push_back(Edge(v,w));
				graph[v].push_back(Edge(u,w));
				W[make_pair(u,v)]=w;
				W[make_pair(v,u)]=w;
			}
			cin >> dummy >> ws;
		}
		else if((code == "SECTION" || code == "Section") && type =="Terminals"){
			long t, u;
			cin >> dummy >> t;
			for(long i=0; i < t; i++){
				cin>> dummy >> u;
				terminals.push_back(u);
				terminalSet.insert(terminalSet.end(), u);
			}
			cin >> dummy >> ws;
		}
		else if(code == "SECTION" && type =="Tree"){
			// Not NEEDED FOR STP -- commenting out 
			// rajesh
			/*
			cin >> dummy >> ws; // DECOMP
			cin >> dummy >> dummy; // s ,td
			long bags, bid, val ; 
			cin >> bags; // total bags
			tdEdge.resize(bags+1);
			tdBag.resize(bags+1);
			cin >> dummy >> dummy >> ws; // tw, n
			
			for(long i=0; i < bags; i++){
				string line;
				getline(cin, line); stringstream sstream(line);
				if(sstream >> dummy, dummy=="b"){
					sstream >> bid; // bag id
					//~ cout << bid << ": ";
					while(sstream >> val){
						//~ cout << val << " " ;
						tdBag[bid].push_back(val);
					}
					//~ cout << endl;
				}
			}
			long tu, tv;
			for(long i=1; i < bags; i++){ // b-1 edges is Td
				cin >>  tu >> tv;
				//~ cout<<  tu << " " << tv << endl;
				tdEdge[tu].push_back(tv);
				tdEdge[tv].push_back(tu);
			}
			cin >> dummy >> ws; // END
			cin >> dummy >> ws; // eof
			**/
			
		}
		else if( code == "EOF"){
			// last line EOF and VALUE is also consumed
			break;
		}
		else{
			cout << "Err in Input/Parsing!" << endl;
			cout <<  "Code: " << code << endl;
			exit(1);
		}
	}
	
	
	int u, v;
	long long int stpVal= DEFAULT;
	cin >>  stpVal;
	
	vector<pair<int,int>> treeEdges;
	set<int> treeNodes; // bool is for dfs in mind
	while(cin >>  u >> v ){
		//~ printf("%d %d\n",u, v);
		treeEdges.push_back({u,v});
		treeNodes.insert({u});
		treeNodes.insert({v});
	}
	
	if(stpVal == DEFAULT )
		cout << "WRONG: No VALUE Printed!" << endl;

	if(treeEdges.size() == 0)
		cout << "WRONG: No edges printed!" << endl;

	if(treeEdges.size() != treeNodes.size()-1 ){
		cout << "WRONG: Mismatch; n-1 != m" << endl;
		DEBUG printf("WRONG: Mismatch; n-1 != m i.e %ld -1 != %ld\n", treeNodes.size(), treeEdges.size() );
	}
	
	if(! isTreeWeightAreSame(W, treeEdges, stpVal) )
		cout << "WRONG: Mismatch; Sum Edge Weights printed != VALUE" << endl;
	
	if( ! isAllTerminalsPresent(terminalSet,treeNodes))
		cout << "WRONG: Missing; Not all terminals present" << endl;
	
	if( ! isConnected(treeNodes, treeEdges, terminalSet))
		cout << "WRONG: Disconnected!" << endl;
	
	cout << "All tests - done!"<< endl;
	return 0;
}

