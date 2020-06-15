#ifndef DATE_H
#define DATE_H
#include"iostream"
using namespace std;

class Date {
public:
    int ngay;
    int thang;
    int nam;

public:
    Date();
    Date(int, int, int);
    Date(const Date&);

    void copy_date(const Date&);
    friend void update_date(Date&, int, int, int);
    friend ostream& operator<<(ostream&, const Date&);
    string store_string_date();

    int get_nam_sinh();
};
#endif // DATE_H
