/*
 * stp-validate.cpp
 * 
 * Copyright 2019 Rajesh Pandian M <mrpaj@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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

using namespace std;

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
			// Not NEEDED FOR STP -- commenting
			
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
		else{
			cout << "Err in Input/Parsing!" << endl;
			cout <<  "Code: " << code << endl;
			exit(1);
		}
	}
	
	return 0;
}

