#include "interpreter/interpreter.h"

vector<string> tokenize(const string& s) {
    vector<string> tokens;
    string x="";
    int length=s.size();
    for(int i=0;i<length;i++){
        char c=s[i];
        if(isspace(c)){
            if(!x.empty()){
                tokens.push_back(x);
                x="";
            }
            continue;
        }
        else if((c==',')||(c=='(')||(c==')')||(c==';')||(c=='=')){
                if(!x.empty()){
                tokens.push_back(x);
                x="";
            }
             tokens.push_back(string(1,c));
        }
        else{
            x+=c;
        }
    }
       if (!x.empty())
        tokens.push_back(x);
    return tokens;
}