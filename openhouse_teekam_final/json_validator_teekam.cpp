# include <iostream>
# include <vector>
# include <fstream>
# include <unordered_set>

using namespace std;

bool checkObject(string query);
bool checkArray(string query);
bool checkNumber(string query);
bool checkString(string query);
bool checkJSON(string query);
void split(string query, vector<string> &parts);

bool checkNumber(string query){
    int i=0, decimalCount = 0;
    if (query[0] == '-') i++; // negative numbers
    for(; i<query.size();i++){
        if(query[i] == '.')
            decimalCount++;
        else if(query[i] <'0' || query[i] > '9')
            return false;
    }
    if(decimalCount>1)
        return false;
    return true;
}

bool checkString(string query){
    int size = query.size();
    if(query[0] !=  query[size-1])
        return false;
    else
        for(int i=1; i<size-1; i++)
            if(query[i] == query[0])
                return false;
    return true;
}

bool checkJSON(string query){
    // checks if a string contains JSON object, array, number, boolean or undefined. otherwise returns false.
    if(query == "") return true;
    if(query[0] == '{'){ //  for any object.
        if (!checkObject(query)){ 
            return false;
        }
    }
    else if(query[0] == '['){ // for array 
        if(!checkArray(query)){
            return false;
        }
    }
    else if(query[0] == '\"' || query[0] == '\''){ // check for string
        if(!checkString(query)){
            return false;
        }
    }
    else if((query[0] >= '0' && query[0] <='9') || (query[0] == '-')){
        if(!checkNumber(query)){
            return false;
        }
    }
    else{
        if(query == "undefined" || query == "null" || query == "true" || query == "false"){
            return true;
        }
        return false;
    }
    return true;
}
void split(string query, vector<string> &parts){
    int size = query.size(), prev=1;
    if(size<=2) return;
    bool openBracket = false;
    char quoteOrBracket;
    unordered_set<char> openingChars({'\'','\"','[',']','{','}'}); // to not split on , inside objects and arrays.
    for(int i = 1; i<size-1; i++){
        if(openingChars.find(query[i]) != openingChars.end()){
            if(!openBracket){
                openBracket = true;
                quoteOrBracket = query[i];
            }
            else{
                if(quoteOrBracket == query[i]){
                    openBracket = false;
                }
                if(quoteOrBracket == '[' && query[i] == ']')
                    openBracket = false;
                if(quoteOrBracket == '{' && query[i] == '}')
                    openBracket = false;
            }
        }
        if(query[i] == ',' && !openBracket){
            parts.push_back(query.substr(prev, i-prev));
            prev = i+1;
        }
    }
    parts.push_back(query.substr(prev,size-1-prev));
}

bool checkArray(string query){
    int size = query.size();
    vector<string> parts;
    if(query[0] != '[' || query[size-1] != ']') // base case
        return false;
    
    split(query, parts);
    
    for(auto line: parts){
        if(checkJSON(line) == false){
            return false;
        }
    }
  	return true;
}

bool checkObject(string query){
  	int size = query.size(), prev=1;
  	vector<string> parts;
  	if(query[0] !='{' || query[size-1] !='}') // base case
        return false;
    
    split(query, parts);
    
    for(auto line : parts){
        int i = 1;
        if(line[0] != '\"' && line[0] != '\'')
            return false;
        while(i<line.size() && line[i] != line[0]) i++;
        if(i == line.size()) return false;
        i++;
        while(line[i] == ' ') i++; // ignoring any space
        if(line[i] != ':') return false;
        i++;
        while(line[i] == ' ') i++;
        
        if(checkJSON(line.substr(i)) == false){
            return false;
        }
    }
    return true;
	}
int main(){
    ifstream cin("testJSON.txt");
    string testString;

    while(getline(cin,testString)){
        if(testString == "")
            break;
        if(checkJSON(testString)){
            cout<< testString << " Valid \n";
        }
        else{
            cout<< testString << " Invalid\n";
        }
    }
    return 0;
}
  
  
