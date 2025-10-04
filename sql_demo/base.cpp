#include "base.h"
#include <stdexcept>
// std::ostream& operator<<(std::ostream& out, const Base& b){
//     out << "Data Base: " << b.name << '\n';
//     for(auto table : b.base){
//         out << "  " << "Table: " << table.first << '\n';
//         for(auto row : table.second.id_data){
//             out << "      " << "ID: " << row.first << '\n';
//             for(auto data : row.second){
//                 out << "          " << data.first <<"---" << data.second << '\n';
//             }
//         }
//     }
//     return out;
// }

void Base::print(){
    std::cout << "Data Base: " << name << '\n';
    for(auto table : base){
        std::cout << "  " << "Table: " << table.first << '\n';
        for(auto row : table.second.id_data){
            std::cout << "      " << table.second.primary_key << ": " << row.first << '\n';
            for(auto data : row.second){
                std::cout << "          " << data.first <<"---" << data.second << '\n';
            }
        }
    }
}

void Base::create_table(const std::string& table_name, const std::string& p_key, const std::vector<std::string> param){
    Table table;
    table.primary_key = p_key;
    table.keys = param;
    base[table_name] = table;
}

void Base::insert(const std::string& table_name, const std::string& p_key_val, const std::vector<std::string> param_val){
    if(!base.contains(table_name))
        throw std::invalid_argument("Table does not exist");

    if(base[table_name].keys.size() != param_val.size())
        throw std::invalid_argument("invalid values");

    if(base[table_name].id_data.contains(p_key_val))
        throw std::invalid_argument("Primary key should be unique");

    Table& table = base[table_name];
    for(int i = 0; i < param_val.size(); i++){
        table[p_key_val][table.keys[i]] = param_val[i];
    }
}