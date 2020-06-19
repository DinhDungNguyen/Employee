#include<iostream>
#include"list.h"
using namespace std;

void menu() {
    cout << "==============================================="<<endl;
    cout << "= 1 - Nhap thong tin nhan vien                =" << endl;
    cout << "= 2 - Tim thong tin nhan vien                 =" << endl;
    cout << "= 3 - Import danh sach nhan vien tu file csv  =" << endl;
    cout << "= 4 - Diem danh nhan vien                     =" << endl;
    cout << "= 5 - Xem thong tin diem danh theo thang      =" << endl;
    cout << "= 0 - Thoat                                   =" << endl;
    cout << "===============================================" << endl;
}

int main() {
    List list;
    list.read_file();

    int choice;
    while (true) {
        menu();
        cout << "> ";
        cin >> choice;
        fflush(stdin);

        if (choice == 1) {
            list.add_employee_at_last();
            list.write_file();

        }
        else if (choice == 2) {
            int search_choice = 0;

            cout << "=1 - Tim kiem theo ma nhan vien " << endl;
            cout << "=2 - Tim kiem theo ten nhan vien " << endl;
            cout << "=3 - Tim kiem theo chuc vu" << endl;
            cout << "> ";

            cin >> search_choice;
            cin.ignore();
            if(search_choice == 1){
                cout << "Nhap ma nhan vien nguoi muon tim: ";
                string search_id;
                getline(cin, search_id);
                if (list.check_if_contain_by_id(search_id) == true) {
                    cout << list.search_employee_by_id(search_id).get_ma_nhan_vien() << ", "
                         << list.search_employee_by_id(search_id).get_ten() << ", "
                         << list.search_employee_by_id(search_id).get_dia_chi() << ", "
                         << list.search_employee_by_id(search_id).get_bo_phan() <<endl;
                }
                else {
                    cout << "Khong tim thay nguoi do" << endl;
                }
            } else if(search_choice == 2){
                string search_name;
                cout << "Nhap ten nhan vien can tim: ";
                getline(cin, search_name);
                if(list.check_if_contain_by_name(search_name) == true){
                    cout << list.search_employee_by_name(search_name).get_ma_nhan_vien() << ", "
                         << list.search_employee_by_name(search_name).get_ten() << ", "
                         << list.search_employee_by_name(search_name).get_dia_chi() << ", "
                         << list.search_employee_by_name(search_name).get_bo_phan()<< endl;
                } else{
                    cout<< "Khong tim thay nguoi do" << endl;
                }
            } else if(search_choice == 3){
                string search_department;
                cout << "Nhap bo phan lam viec can tim: ";
                getline(cin, search_department);
                if(list.check_if_contain_by_name(search_department) == true){
                    cout << list.search_employee_by_department(search_department).get_ma_nhan_vien() << ", "
                         << list.search_employee_by_department(search_department).get_ten() << ", "
                         << list.search_employee_by_department(search_department).get_dia_chi() << ", "
                         << list.search_employee_by_department(search_department).get_bo_phan()<< endl;
                } else{
                    cout<< "Khong tim thay nguoi do" << endl;
                }

            } else {
                cout << "Lua chon khong hop le" <<endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        else if (choice == 3){
            list.read_csv_file();
            list.write_file();
        }
        else if(choice == 4){
            list.input_Atd();
            list.print_Atd_file();
            list.update_Atd();
        }
        else if(choice == 5){

        }
        else if (choice == 0){
            cout << "Cam on!!\n";
            break;
        }
        else if (cin.fail()) {
            cout << "Lua chon khong hop le" << endl;
            cin.clear();
            cin.ignore(10000, '\n');  // skips 10000 characters to the next newline
        }
        else {
            cout << "Lua chon khong hop le" << endl;
        }
        cout << endl;
    }
}
