#ifndef BASE_H
#define BASE_H
#include <unordered_map>
#include <string>
#include <iostream>


class Base;
class Table{
    std::unordered_map<std::string, std::unordered_map<std::string,std::string>> id_data;
    std::string name;
public:
    Table() = default;
    Table(const std::string& n) : name(n){}
    const std::string& get_name(){return name;}
    std::unordered_map<std::string,std::string>& operator[](const std::string& id){
        return id_data[id];
    }
    friend class Base;
    //friend std::ostream& operator<<(std::ostream& out, const Base& base);
};


class Base{
    std::unordered_map<std::string, Table> base;
    std::string name;
public:
    Base() = default;
    Base(const std::string& n) : name(n){}
    void print();
    Table& operator[](const std::string& table_name){
        return base[table_name];
    }
    //friend std::ostream& operator<<(std::ostream& out, const Base& base);

};

#endif