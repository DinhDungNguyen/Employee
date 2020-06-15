#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include"Date.h"
#include <string>
using namespace std;

class Employee {
public:
    string ma_nhan_vien, ten, dia_chi, bo_phan;
    Date* ngay_sinh;

public:
    Employee* next;
    Employee* previous;

    Employee();
    Employee(string, string, string, string, int, int, int);
    Employee(const Employee&);
    ~Employee();

    bool compare_id(string);
    void show();
    void update_info(Employee&);
    void copy_info(const Employee&);

    string get_ma_nhan_vien();
    string get_ten();
    string get_dia_chi();
    string get_bo_phan();
    int get_ngay();
    int get_thang();
    int get_nam();

    friend ostream& operator<<(ostream& out, const Employee&);
    friend istream& operator>>(istream& cin, Employee&);
};

#endif // EMPLOYEE_H
