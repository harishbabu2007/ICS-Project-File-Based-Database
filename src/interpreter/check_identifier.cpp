#include "interpreter/interpreter.h"

bool is_identifier(const string& s){
    vector<string> token=tokenize(s);
    for(auto i=s.begin();i<s.end();i++){
         if(((*i)>='0' && (*i)<='9')||((*i)>='a' && (*i)<='z')||((*i)>='A' && (*i)<='Z')||((*i)=='_')){
               continue;
         }
         else{
            return false;
         }
        }
      return true;
}