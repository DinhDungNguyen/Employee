#include<iostream>
#include<string>
#include"Date.h"
using namespace std;

Date::Date(int ngay, int thang, int nam) : ngay(ngay), thang(thang), nam(nam) {}
Date::Date() : ngay(0), thang(0), nam(0) {}
Date::Date(const Date& d) : ngay(d.ngay), thang(d.thang), nam(d.nam) {}

void Date::copy_date(const Date& date) {
    this->ngay = date.ngay;
    this->thang = date.thang;
    this->nam = date.nam;
}

string Date::store_string_date() {
    string s = to_string(this->ngay) + "/" + to_string(this->thang);
    s += "/" + to_string(this->nam);
    return s;
}


ostream& operator<<(ostream& o, const Date& date) {
    o << date.ngay << "/" << date.thang << "/" << date.nam;
    return o;
}
