# include <iostream>
# include <vector>
# include <fstream>
using namespace std;
bool checkJSON(string query);
bool checkArray(string query);

bool checkNumber(string query){
    int decimalCount = 0;
    for(int i=0; i<query.size();i++){
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
bool checkAllTypes(string line, int i){

    // checks if a string contains JSON object, array, number, boolean or undefined. otherwise returns false.

    if(line[i] == '{'){ // recursive call for any object.
        if (!checkJSON(line.substr(i))){ 
            return false;
        }
    }
    else if(line[i] == '['){ // for array 
        if(!checkArray(line.substr(i)))
            return false;
    }
    else if(line[i] == '"' || line[i] == '\''){ // check for string
        if(!checkString(line.substr(i)))
            return false;
    }
    else if(line[i] >= '0' && line[i] <='9'){
        if(!checkNumber(line.substr(i)))
            return false;
    }
    else{
        string checkVariable = line.substr(i);
        if(checkVariable == "undefined" || checkVariable == "null" || checkVariable == "true" || checkVariable == "false"){
            return true;
        }
        return false;
    }
    return true;
}
void split(string query, vector<string> &parts){
    int size = query.size(), prev=1;
    bool openBracket = false;
    char quote;

    for(int i = 1; i<size-1; i++){
        if(query[i] == '\'' || query[i] == '\"'){  // ensuring that the split , is not in a string element.
            if(!openBracket){
                openBracket = true;
                quote = query[i];
            }
            else{
                if(quote == query[i]){
                    openBracket = false;
                }
            }
        }
        if(query[i] == ',' && !openBracket){
            parts.push_back(query.substr(prev, i-prev));
            prev = i+1;
        }
    }
    parts.push_back(query.substr(prev));

}

bool checkArray(string query){
    int size = query.size();
    vector<string> parts;
    if(query[0] != '[' || query[size-1] != ']') // base case
        return false;
    
    split(query, parts);
    
    for(auto line: parts){
        if(checkAllTypes(line, 0) == false){
            return false;
        }
    }
  	return true;
}


bool checkJSON(string query){
  	int size = query.size(), prev=1;
  	vector<string> parts;
  
  	if(query[0] !='{' || query[size-1] !='}') // base case
        return false;
  
    split(query, parts);

    for(auto line : parts){
        int i = 1;
        if(line[0] != '"')
            return false;
        while(i<line.size() &&line[i] != '"') i++;
        if(i == line.size()) return false;

        while(line[i] == ' ') i++; // ignoring any space
        if(line[i] != ':') return false;
        while(line[i] == ' ') i++;

        if(checkAllTypes(line, i) == false){
            return false;
        }
    }
    return true;
	}
int main(){
    string testString = "{'x':[10,null,null,null]}";
    if(checkJSON(testString)){
        cout<<"Indeed a valid JSON";
    }
    else{
        cout<<"Incorrect JSON";
    }
    return 0;
}
  
  
