#include<bits/stdc++.h>


using namespace std;

int main(){


    map<int, string>m;

    m.insert(make_pair(2, "123"));
    //m.insert(make_pair(1, 100));

    map<int, string>::iterator itr;
    itr = m.begin();
    int index = itr->second.length();
    int u = (int)itr->second[index-1] - 48;

    cout<<u;




    //m.erase(itr);
    /*
    for (itr = m.begin(); itr != m.end(); ++itr) { 
            cout << '\t' << itr->first 
            << '\t' << itr->second << '\n'; 
    } */


    return 0;
}