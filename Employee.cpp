#include"Employee.h"
#include<iostream>
#include<string>
using namespace std;

//contructor
Employee::Employee(string ma_nhan_vien, string ten, string dia_chi, string bo_phan, int ngay, int thang, int nam)
    : ma_nhan_vien(ma_nhan_vien), ten(ten), dia_chi(dia_chi), bo_phan(bo_phan){
    this->ngay_sinh = new Date(ngay, thang, nam);
    this->next = nullptr;
    this->previous = nullptr;
}
Employee::Employee(const Employee& p)
    : ma_nhan_vien(p.ma_nhan_vien), ten(p.ten), dia_chi(p.dia_chi), bo_phan(p.bo_phan) {
    this->ngay_sinh = new Date(*p.ngay_sinh);
    this->next = nullptr;
    this->previous = nullptr;
}
Employee::Employee()
    : ma_nhan_vien(""), ten(""), dia_chi(""), bo_phan(""){
    this->ngay_sinh = new Date();
    this->next = nullptr;
    this->previous = nullptr;
}
Employee::~Employee() {
    this->next = nullptr;
    this->previous = nullptr;
    delete this->ngay_sinh;
}

//print employee
void Employee::show() {
    cout << "Ma Nhan Vien: " << this->ma_nhan_vien <<", Ten: " << this->ten
    << ", Ngay sinh: " << *this->ngay_sinh
    << ", Dia chi: " << this->dia_chi
    << ", Bo phan lam viec: " << this->bo_phan << endl;
}


bool Employee::compare_id(string id) {
    if (this->ma_nhan_vien == id) {
        return true;
    }
    else {
        return false;
    }
}

// clear cin
void clear_input() {
    cin.clear();
    cin.ignore(10000, '\n');  // skips 10000 characters to the next newline
}

// kiem tra xem nhap ngay co hop le khong
void check_date(int ngay, int thang, int nam) throw(string()) {
    if (thang <= 0 || thang > 12 || nam < 0)
        throw string();

    if ((thang <= 7 && thang % 2 == 1) || (thang >= 8 && thang % 2 == 0)) {
        if (ngay <= 0 || ngay > 31)
            throw string();
    }
    else if ((thang <= 7 && thang % 2 == 0) || (thang >= 8 && thang % 2 == 1)) {
        if (thang == 2) {
            if (nam % 400 == 0 || (nam % 4 == 0 && nam % 100 != 0)) { // nam nhuan
                if (ngay <= 0 || ngay > 29)
                    throw string();
            }
            else {
                if (ngay <= 0 || ngay > 28)
                    throw string();
            }
        }
        else {
            if (ngay <= 0 || ngay > 30)
                throw string();
        }
    }
}


ostream& operator<<(ostream& out, const Employee& employee) {
    out << employee.ma_nhan_vien << endl;
    return out;
}

istream& operator>>(istream& cin, Employee& employee) {
    cout << "Ten: ";
    cin.ignore();
    getline(cin,employee.ten);

    cout<< "Ma nhan vien: ";
    getline(cin,employee.ma_nhan_vien);

    // input Date
    do {
        try {
            int ngay, thang, nam; // for Date
            cout << "Ngay, thang, nam sinh: ";
            cin >> ngay >> thang >> nam;

            if (cin.fail()) {
                throw runtime_error("");
            }

            check_date(ngay, thang, nam); // kiem tra tinh hop le cua ngay sinh

            clear_input(); //don dep input thua con sot lai
            employee.ngay_sinh = new Date(ngay, thang, nam);
            break;
        }
        catch (runtime_error e) {
            cout << "Nhap thong tin sai" << endl;
            clear_input();
        }
        catch (string s) {
            cout << "Ngay thang nam khong hop le" << endl;
        }
    } while (true);
    cout << "Dia chi: ";
    getline(cin,employee.dia_chi);
    cout << "Bo phan lam viec: ";
    getline(cin,employee.bo_phan);

    return cin;
}

void Employee::update_info(Employee& employee) {
    cin >> employee;
}

void Employee::copy_info(const Employee& e) {
    this->ma_nhan_vien = e.ma_nhan_vien;
    this->ten = e.ten;
    this->dia_chi = e.dia_chi;
    this->bo_phan = e.bo_phan;
    this->ngay_sinh->copy_date(*e.ngay_sinh);
}


string Employee::get_ma_nhan_vien() {
    return this->ma_nhan_vien;
}

string Employee::get_ten() {
    return this->ten;
}

string Employee::get_dia_chi() {
    return this->dia_chi;
}

string Employee::get_bo_phan() {
    return this->bo_phan;
}

int Employee::get_ngay(){
    return this->ngay_sinh->ngay;
}
int Employee::get_thang(){
    return this->ngay_sinh->thang;
}
int Employee::get_nam(){
    return this->ngay_sinh->nam;
}
