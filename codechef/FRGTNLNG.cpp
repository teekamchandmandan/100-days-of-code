# include <iostream>
# include <vector>
# include <string>
# include <unordered_set>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> vec;
    unordered_set<string> set;
    string temp;
    int count,len;

    int t,n,k;
    cin>>t;
    while(t--){
        cin>>n>>k;
        vec.clear();
        set.clear();
        for(int i=0;i<n;i++){
            cin>>temp;
            vec.push_back(temp);
        }
        for(int j=0;j<k;j++){
            cin>>count;
            while(count--){
                cin>>temp;
                set.insert(temp);
            }
        }
        len = vec.size();
        for(int i=0;i<len;i++){
            if(set.find(vec[i])==set.end()){
                cout<< "NO ";
            }
            else {
                cout<< "YES ";
            }
        }
        cout<<"\n";
    }
    return 0;
}