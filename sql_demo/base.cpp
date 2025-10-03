#include "base.h"

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
            std::cout << "      " << "ID: " << row.first << '\n';
            for(auto data : row.second){
                std::cout << "          " << data.first <<"---" << data.second << '\n';
            }
        }
    }
}