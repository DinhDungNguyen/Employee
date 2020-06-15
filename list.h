#ifndef LIST_H
#define LIST_H

#include"Employee.h"
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
class List {
public:
    Employee* first;
    Employee* last;

    List();
    List(Employee&); // add first employee to the list.
    List(const List&);
    ~List();

    void read_file();
    void read_csv_file();
    void write_file();
    void append_file(const string&);
    //void table();

    int size_of_list();

    void display_list();
    void add_employee_at_last();
    void add_employee_at_last(Employee& employee);
    void update_employee_info(string);
    Employee& search_employee_by_id(string);
    Employee& search_employee_by_name(string);
    Employee& search_employee_by_department(string);
    void print_statistics();

    //void swap(Employee*&, Employee*&);
    bool check_if_contain_by_id(string id);
    bool check_if_contain_by_name(string name);
    bool check_if_contain_by_depart(string depart);
};
#endif // LIST_H
