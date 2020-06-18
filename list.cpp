#include "list.h"
#include "Date.h"

List::List() : first(nullptr), last(nullptr) {}
List::List(Employee& employee) : first(&employee), last(&employee) {
    employee.next = nullptr;
    employee.previous = nullptr;
}
List::List(const List& list) : first(list.first), last(list.last) {}

List::~List() {
    Employee* employee = this->first;
    Employee* next_employee;

    while (employee != nullptr) {
        next_employee = employee->next;

        delete employee; // next and previous became nullptr pointer
        employee = next_employee;
    }
}

int List::size_of_list() {
    Employee* current_employee = this->first;
    int list_size = 0;

    while (current_employee != nullptr) {
        list_size++;
        current_employee = current_employee->next;
    }
        return list_size;
    }

void List::display_list() {
    if (first == nullptr) { // list empty
        cout << "Khong co gi de hien thi" << endl;
        return;
    }
    Employee* current_employee = this->first;

    while (current_employee != nullptr) {
        current_employee->show();
        current_employee = current_employee->next;
    }
}


    void List::add_employee_at_last() {
        Employee* new_employee = new Employee();
        cin >> *new_employee;

        if (this->first == nullptr) {
            this->first = new_employee;
        }
        else {
            this->last->next = new_employee;
        }

        new_employee->previous = this->last;
        new_employee->next = nullptr;
        this->last = new_employee;
    }
    void List::add_employee_at_last(Employee& employee) {
        Employee* new_employee = &employee;

        if (this->first == nullptr) {
            this->first = new_employee;
        }
        else {
            this->last->next = new_employee;
        }

        new_employee->previous = this->last;
        new_employee->next = nullptr;
        this->last = new_employee;
    }
    Employee& List::search_employee_by_id(string id) {
        Employee* current_employee = this->first;

        while (current_employee != nullptr && current_employee->compare_id(id) == false) { // search for the correct employee in the list
            current_employee = current_employee->next;
        }

        return *current_employee;
    }

    Employee& List::search_employee_by_name(string name){
        Employee* current_employee = this->first;
        while(current_employee != nullptr && current_employee->get_ten()!= name){
            current_employee = current_employee->next;
        }
        return *current_employee;
    }

    Employee& List::search_employee_by_department(string depart){
        Employee* current_employee = this->first;
        while(current_employee != nullptr && current_employee->get_bo_phan()!= depart){
            current_employee = current_employee->next;
        }
        return *current_employee;
    }

    void List::update_employee_info(string id) {
        Employee* employee = &search_employee_by_id(id);

        if (employee == nullptr) {
            cout << "Khong tim thay nguoi nay" << endl;
            return;
        }

        employee->update_info(*employee);
    }

    bool List::check_if_contain_by_id(string id) {
        Employee* current_employee = this->first;

        while (current_employee != nullptr) {
            if (current_employee->compare_id(id) == true) {
                return true;
            }
            current_employee = current_employee->next;
        }

        return false;
    }
    bool List::check_if_contain_by_name(string name){
        Employee* current_employee = this->first;
        while (current_employee != nullptr) {
            if (current_employee->get_ten() == name) {
                return true;
            }
            current_employee = current_employee->next;
        }
        return false;
    }
    bool List::check_if_contain_by_depart(string depart){
        Employee* current_employee = this->first;
        while (current_employee != nullptr) {
            if (current_employee->get_bo_phan() == depart) {
                return true;
            }
            current_employee = current_employee->next;
        }
        return false;
    }


    void List::read_file() {
        int i = 1;
        string maNhanVien, hoTen;
        string diaChi, boPhan;
        string ngay_str, thang_str, nam_str;
        int ngay, thang, nam;

        ifstream reader("D:\\employee.txt");
        if (!reader) {
            cout << "Error opening input file" << endl;
            return;
        }

        while (!reader.eof()) {
            // lay thong tin tu file
            if (i == 1)
                getline(reader, maNhanVien, ',');
            else if (i == 2)
                getline(reader, hoTen, ',');
            else if (i == 3){

            getline(reader, ngay_str, '/');
            getline(reader, thang_str, '/');
            getline(reader, nam_str, ',');

            stringstream converter;

            converter.str(ngay_str);
            converter >> ngay;
            converter.clear();
            converter.str(thang_str);
            converter >> thang;
            converter.clear();
            converter.str(nam_str);
            converter >> nam;
            converter.clear();

    }
        else if (i == 4)
            getline(reader, diaChi, ',');
        else if (i == 5) {
            getline(reader, boPhan);
            i = 0;
            Employee* employee_new = new Employee(maNhanVien, hoTen, diaChi, boPhan, ngay, thang, nam);
            this->add_employee_at_last(*employee_new);
            continue;
        }
        i++;
    }
    reader.close();
}
void List::read_csv_file(){
    int i = 1;
    string maNhanVien, hoTen;
    string diaChi, boPhan;
    string ngay_str, thang_str, nam_str;
    int ngay, thang, nam;

    ifstream reader("D:\\ImportData.csv");
    if (!reader) {
        cout << "Error opening input file" << endl;
        return;
    }

    while (!reader.eof()) {
        // lay thong tin tu file
        if (i == 1){
            getline(reader, maNhanVien, ',');
        }
        else if (i == 2)
            getline(reader, hoTen, ',');
        else if (i == 3) {

            getline(reader, ngay_str, '/');
            getline(reader, thang_str, '/');
            getline(reader, nam_str, ',');

            stringstream converter;

            converter.str(ngay_str);
            converter >> ngay;
            converter.clear();
            converter.str(thang_str);
            converter >> thang;
            converter.clear();
            converter.str(nam_str);
            converter >> nam;
            converter.clear();
        }
        else if (i == 4)
            getline(reader, diaChi, ',');
        else if (i == 5) {
            getline(reader, boPhan);
            i = 0;
            Employee* employee_new = new Employee(maNhanVien, hoTen, diaChi, boPhan, ngay, thang, nam);
            this->add_employee_at_last(*employee_new);
        }
        i++;
    }
    reader.close();
};
void List::write_file() {
    fstream f;
    f.open("D:\\employee.txt",ios::out);
    if (!f) {
        cout << "Error opening file for output" << endl;
        return;
    }
    Employee* currentnode = this->first;
    while (currentnode != nullptr) {
        string info = currentnode->get_ma_nhan_vien() + "," + currentnode->get_ten() + ","
            + to_string(currentnode->get_ngay()) + "/" + to_string(currentnode->get_thang()) + "/" + to_string(currentnode->get_nam()) + ","
            + currentnode->get_dia_chi() + ","
            + currentnode->get_bo_phan();
        currentnode = currentnode->next;

        f << info << endl;
    }
    f.close();
}
/*
void List::table(){
    Employee* currentnode = this->first;
    int count=0;
    for (currentnode; currentnode != nullptr; currentnode = currentnode->next){
        count++;
    }
    int arr[count][31];
    for(int i = 1; i < count-1; i++){
        const char *id = "currentnode->get_ma_nhan_vien()";
        arr[i][0] = atoi(id);
    }
    for(int i = 1; i <= 30;i++){
        for(int j = 1; j < 31 ; j++){
            arr[0][i] = j;
        }
    }
    fstream f;
    f.open("D:\\January.txt",ios::out);
    if(!f){
        cout<<"error opening file for output" << endl;
        return;
    }
    for(int i = 0; i <= count-1; i++){
        for(int j = 0; j<= 30; j++){
            cout << arr[i][j] + " ";
        }
        cout << endl;
    }

}*/


