#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<fstream>
#include<utility>  

using namespace std;

int main() {

    vector<pair<int, pair<string,int>>> MNT;   // (MNCT, name ,MDTC);=
  
    
    ifstream a;
    a.open("Assign2.asm");  // Changed to ifstream to read the file
    
    string h;
    int i = 0;
    
    while(getline(a, h)) {  
        
        int x = h.length();
        
        // For symbol table entry (lines with ':')
        if (h.find("%macro") != string::npos) {
            i++;
            string g = "";
            for(int j=7;j<x;j++){
            	if(h[j] == ' '){
            		break;
            	}
            	
            	g += h[j];
            }
            
            MNT.push_back(make_pair(i,make_pair(g,i)));
        }
    }

    a.close();
    
    cout<<"MNT is as follows -->> \n";
    cout<<"MNTC --> MACRO --> MDTC \n";
    for(auto d : MNT){
    	cout<<d.first<<" --> "<<d.second.first<< " --> "<<d.second.second<< "\n";
    
    }
    
    
    
    return 0;
}

