// #include "interpreter/interpreter.h"
// #include "engine/TableRead.h"

// void string_check(vector<string> tokens){
//  string table_name = tokens[2];
//     schema_t new_schema = get_schema_from_schema(table_name + "__schema_data.bin");

//     size_t num_cols = new_schema.num_cols;

//     auto j = tokens.begin() + 4;

//     while (j != tokens.end())
//     {
//         if (*j == "(")
//         {
//             j++;
//             if(*j==",") j++;
//             for(size_t i=0;i<num_cols;i++){
//                 if(new_schema.column_data[0].data_type!=STRING){
//                      j++;
//                      if (*j == ",") // skip comma between values
//                         j++;
//                      continue;
//                 }
//                 else if(*j!="'"||*(j+2)!="'"){
//                     printf("ERROR");
//                 }
//                 else{
//                     j++;
//                 }
//             }
            

//                 j++; // move to next token

//                 if (*j == ",") // skip comma between values
//                     j++;
//             }

//             // move until next row or end
//             while (j != tokens.end() && *j != "(")
//                 j++;
//         }
//         else
//         {
//             j++;
//         }
//     }

//     cout << "OK\n";
// }
