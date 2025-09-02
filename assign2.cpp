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
    vector<pair<int, string>> MDT; // (MDTC , Def);=
  
    
    ifstream a;
    a.open("Assign2.asm");  // Changed to ifstream to read the file
    
    string h;
    int i = 0;
    
    while(getline(a, h)) {  
        
        int x = h.length();
        
      
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
    
    a.open("Assign2.asm");  // Changed to ifstream to read the file
    
    //i = 0;
    
    for(auto d : MNT){
    	
    	string mac = d.second.first; // taking NAME of Macro
    	i = d.second.second; //taking MDTC of macro
    	
    	bool z = 0;
    	
    	while(getline(a, h)) {  
    	
    		if (h == "%endmacro") {
        		z = 0;
        		break;
        	}
		
		if(z == 1){MDT.push_back(make_pair(i,h));}
	      
		if (h.find(mac) != string::npos) {
			z = 1;
        	}
        	
        	
    	}
    	
    
    }

    a.close();
    
    cout<<"MNT is as follows -->> \n";
    cout<<"MNTC --> MACRO --> MDTC \n";
    for(auto d : MNT){
    	cout<<d.first<<" --> "<<d.second.first<< " --> "<<d.second.second<< "\n";
    
    }
    
    cout<<"\n\nMDT is as follows -->> \n";
    cout<<"MDTC --> DEF \n";
    for(auto d : MDT){
    	cout<<d.first<<" --> "<<d.second<< "\n";
    
    }
    
    
    
    return 0;
}
