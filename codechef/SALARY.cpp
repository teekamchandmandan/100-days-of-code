# include <iostream>
# include <vector>
# include <string>
# include <math.h>
# include <unordered_set>
# include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> vec;
    int count,minm,temp;

    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        vec.clear();
        count=0;
        minm = 100000009;
        for(int i=0;i<n;i++){
            cin>>temp;
            minm = min(temp,minm);
            vec.push_back(temp);
        }
        for(auto elem: vec){
            count+=(elem-minm);
        }
        
        cout<<count<<"\n";
    }
    return 0;
}