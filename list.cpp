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
string trang_thai;
int ngay,thang, pos;
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

    void List::search_employee_by_name(string name){
        Employee* current_employee = this->first;
        while(current_employee != nullptr){
            if (StringUtils::containIgnoreCase(current_employee->get_ten(), name)) {
                current_employee->show();
        }
        current_employee = current_employee->next;
        };
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
        int i = 0;
        while (current_employee != nullptr) {
            if (current_employee->compare_id(id) == true) {
                return true;
                pos = i;
            }
            current_employee = current_employee->next;
            i++;
        }

        return false;
    }
    bool List::check_if_contain_by_name(string name){
        Employee* current_employee = this->first;
        while (current_employee != nullptr) {
            if (StringUtils::containIgnoreCase(current_employee->get_ten(), name)) {
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
    void check_Date(int ngay, int thang, int nam) throw(string()) {
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
    void clear_Input() {
        cin.clear();
        cin.ignore(10000, '\n');  // skips 10000 characters to the next newline
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
            Employee* employee_new = new Employee(maNhanVien, hoTen, diaChi, boPhan, ngay, thang, nam);
            this->add_employee_at_last(*employee_new);
            i = 0;
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
                Employee* employee_new = new Employee(maNhanVien, hoTen, diaChi, boPhan, ngay, thang, nam);
                this->add_employee_at_last(*employee_new);
                i=0;
                continue;
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

void List::print_Atd_file(){
    int array[5000][31];
    if(thang == 1){
        fstream file;
        file.open("D:\\012020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31\n";
        file << info;
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }


        file.close();
    }
    if(thang == 2){
        fstream file;
        file.open("D:\\022020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 29; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 29; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 3){
        fstream file;
        file.open("D:\\032020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 4){
        fstream file;
        file.open("D:\\042020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 30; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 30; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 5){
        fstream file;
        file.open("D:\\052020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 6){
        fstream file;
        file.open("D:\\012020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 30; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 30; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 7){
        fstream file;
        file.open("D:\\072020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 8){
        fstream file;
        file.open("D:\\082020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 9){
        fstream file;
        file.open("D:\\012020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 30; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 30; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 10){
        fstream file;
        file.open("D:\\102020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 11){
        fstream file;
        file.open("D:\\112020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 30; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 30; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }
    if(thang == 12){
        fstream file;
        file.open("D:\\122020.txt",ios::out);
        if (!file) {
            cout << "Error opening file for output" << endl;
            return;
        };
        Employee* currentnode = this->first;
        string info = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31\n";
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                 array[i][j] = List::atd();
            }
            currentnode = currentnode->next;
        }
        for(int i = 0; i < List::size_of_list(); i++){
            for(int j = 0; j < 31; j++){
                file << array[i][j] << ", ";
            }
            file << "\n" ;
        }
        file << info;
        file.close();
    }

}

void List::update_Atd(){
    string ngay1, ngay2, ngay3, ngay4, ngay5, ngay6, ngay7, ngay8, ngay9,ngay10, ngay11,
            ngay12,ngay13, ngay14,ngay15,ngay16,ngay17, ngay18, ngay19,ngay20, ngay21,
            ngay22, ngay23, ngay24, ngay25, ngay26, ngay27, ngay28, ngay29, ngay30, ngay31;
    int i = 1,j=0, Ngay1, Ngay2, Ngay3, Ngay4, Ngay5, Ngay6,Ngay7, Ngay8, Ngay9, Ngay10,
            Ngay11, Ngay12, Ngay13, Ngay14, Ngay15, Ngay16,Ngay17, Ngay18, Ngay19, Ngay20,
            Ngay21, Ngay22, Ngay23, Ngay24, Ngay25, Ngay26,Ngay27, Ngay28, Ngay29, Ngay30, Ngay31;
    int arr[5000][31];
    if(thang == 1){
        ifstream file("D:\\012020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, ',');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            }
            else if(i == 31){
                getline(file, ngay31, '\n');
            converter.str(ngay31);
            converter >> Ngay31;
            converter.clear();
            arr[j][i-1] = Ngay31;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 2){
        ifstream file("D:\\022020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay29, '\n');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 3){
        ifstream file("D:\\032020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, ',');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            }
            else if(i == 31){
                getline(file, ngay31, '\n');
            converter.str(ngay31);
            converter >> Ngay31;
            converter.clear();
            arr[j][i-1] = Ngay31;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 4){
        ifstream file("D:\\042020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, '\n');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 5){
        ifstream file("D:\\052020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, ',');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            }
            else if(i == 31){
                getline(file, ngay31, '\n');
            converter.str(ngay31);
            converter >> Ngay31;
            converter.clear();
            arr[j][i-1] = Ngay31;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 6){
        ifstream file("D:\\062020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, '\n');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 7){
        ifstream file("D:\\072020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, ',');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            }
            else if(i == 31){
                getline(file, ngay31, '\n');
            converter.str(ngay31);
            converter >> Ngay31;
            converter.clear();
            arr[j][i-1] = Ngay31;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 8){
        ifstream file("D:\\082020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, ',');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            }
            else if(i == 31){
                getline(file, ngay31, '\n');
            converter.str(ngay31);
            converter >> Ngay31;
            converter.clear();
            arr[j][i-1] = Ngay31;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 9){
        ifstream file("D:\\092020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, '\n');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            i = 0;
            j++;
            continue;
            }
                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 10){
        ifstream file("D:\\102020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, ',');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            }
            else if(i == 31){
                getline(file, ngay31, '\n');
            converter.str(ngay31);
            converter >> Ngay31;
            converter.clear();
            arr[j][i-1] = Ngay31;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 11){
        ifstream file("D:\\112020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, '\n');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }
    if(thang == 12){
        ifstream file("D:\\122020.txt");
        if(!file){
            cout << "Error opening file"<<endl;
            return;
        }
        while(!file.eof()){
            stringstream converter;
            if(i == 1){
                getline(file, ngay1, ',');
            converter.str(ngay1);
            converter >> Ngay1;
            converter.clear();
            arr[j][i-1] = Ngay1;
            }
            else if(i == 2){
                getline(file, ngay2, ',');
            converter.str(ngay2);
            converter >> Ngay2;
            converter.clear();
            arr[j][i-1] = Ngay2;
            }
            else if(i == 3){
                getline(file, ngay3, ',');
            converter.str(ngay3);
            converter >> Ngay3;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 4){
            getline(file, ngay4, ',');
            converter.str(ngay4);
            converter >> Ngay4;
            converter.clear();
            arr[j][i-1] = Ngay4;
            }
            else if(i == 5){
            getline(file, ngay5, ',');
            converter.str(ngay5);
            converter >> Ngay5;
            converter.clear();
            arr[j][i-1] = Ngay5;
            }
            else if(i == 6){
                getline(file, ngay6, ',');
            converter.str(ngay6);
            converter >> Ngay6;
            converter.clear();
            arr[j][i-1] = Ngay6;
            }
            else if(i == 7){
                getline(file, ngay7, ',');
            converter.str(ngay7);
            converter >> Ngay7;
            converter.clear();
            arr[j][i-1] = Ngay7;
            }
            else if(i == 8){
                getline(file, ngay8, ',');
            converter.str(ngay8);
            converter >> Ngay8;
            converter.clear();
            arr[j][i-1] = Ngay8;
            }
            else if(i == 9){
                getline(file, ngay9, ',');
            converter.str(ngay9);
            converter >> Ngay9;
            converter.clear();
            arr[j][i-1] = Ngay9;
            }
            else if(i == 10){
                getline(file, ngay10, ',');
            converter.str(ngay10);
            converter >> Ngay10;
            converter.clear();
            arr[j][i-1] = Ngay10;
            }
            else if(i == 11){
                getline(file, ngay11, ',');
            converter.str(ngay11);
            converter >> Ngay11;
            converter.clear();
            arr[j][i-1] = Ngay11;
            }
            else if(i == 12){
                getline(file, ngay12, ',');
            converter.str(ngay12);
            converter >> Ngay12;
            converter.clear();
            arr[j][i-1] = Ngay12;
            }
            else if(i == 13){
                getline(file, ngay13, ',');
            converter.str(ngay13);
            converter >> Ngay13;
            converter.clear();
            arr[j][i-1] = Ngay13;
            }
            else if(i == 14){
                getline(file, ngay14, ',');
            converter.str(ngay14);
            converter >> Ngay14;
            converter.clear();
            arr[j][i-1] = Ngay14;
            }
            else if(i == 15){
                getline(file, ngay15, ',');
            converter.str(ngay15);
            converter >> Ngay15;
            converter.clear();
            arr[j][i-1] = Ngay15;
            }
            else if(i == 16){
                getline(file, ngay16, ',');
            converter.str(ngay16);
            converter >> Ngay16;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 17){
                getline(file, ngay17, ',');
            converter.str(ngay17);
            converter >> Ngay17;
            converter.clear();
            arr[j][i-1] = Ngay3;
            }
            else if(i == 18){
                getline(file, ngay18, ',');
            converter.str(ngay18);
            converter >> Ngay18;
            converter.clear();
            arr[j][i-1] = Ngay18;
            }
            else if(i == 19){
                getline(file, ngay19, ',');
            converter.str(ngay19);
            converter >> Ngay19;
            converter.clear();
            arr[j][i-1] = Ngay19;
            }
            else if(i == 20){
                getline(file, ngay20, ',');
            converter.str(ngay20);
            converter >> Ngay20;
            converter.clear();
            arr[j][i-1] = Ngay20;
            }
            else if(i == 21){
                getline(file, ngay21, ',');
            converter.str(ngay21);
            converter >> Ngay21;
            converter.clear();
            arr[j][i-1] = Ngay21;
            }
            else if(i == 22){
                getline(file, ngay22, ',');
            converter.str(ngay22);
            converter >> Ngay22;
            converter.clear();
            arr[j][i-1] = Ngay22;
            }
            else if(i == 23){
                getline(file, ngay23, ',');
            converter.str(ngay23);
            converter >> Ngay23;
            converter.clear();
            arr[j][i-1] = Ngay23;
            }
            else if(i == 24){
                getline(file, ngay24, ',');
            converter.str(ngay24);
            converter >> Ngay24;
            converter.clear();
            arr[j][i-1] = Ngay24;
            }
            else if(i == 25){
                getline(file, ngay25, ',');
            converter.str(ngay25);
            converter >> Ngay25;
            converter.clear();
            arr[j][i-1] = Ngay25;
            }
            else if(i == 26){
                getline(file, ngay26, ',');
            converter.str(ngay26);
            converter >> Ngay26;
            converter.clear();
            arr[j][i-1] = Ngay26;
            }
            else if(i == 27){
                getline(file, ngay27, ',');
            converter.str(ngay27);
            converter >> Ngay27;
            converter.clear();
            arr[j][i-1] = Ngay27;
            }
            else if(i == 28){
                getline(file, ngay28, ',');
            converter.str(ngay28);
            converter >> Ngay28;
            converter.clear();
            arr[j][i-1] = Ngay28;
            }
            else if(i == 29){
                getline(file, ngay1, ',');
            converter.str(ngay29);
            converter >> Ngay29;
            converter.clear();
            arr[j][i-1] = Ngay29;
            }
            else if(i == 30){
                getline(file, ngay30, ',');
            converter.str(ngay30);
            converter >> Ngay30;
            converter.clear();
            arr[j][i-1] = Ngay30;
            }
            else if(i == 31){
                getline(file, ngay31, '\n');
            converter.str(ngay31);
            converter >> Ngay31;
            converter.clear();
            arr[j][i-1] = Ngay31;
            i = 0;
            j++;
            continue;
            }

                }
        arr[pos][ngay] = List::atd(trang_thai);
            }




}
void List::input_Atd(){
    string ma_nhan_vien;
    int nam;
    while(true){
        cout << "Ma nhan vien: ";
        cin.ignore();
        getline(cin, ma_nhan_vien);
        if(List::check_if_contain_by_id(ma_nhan_vien) == false){
            cout << "Nhap sai ma nhan vien" << endl;
            clear_Input();
        }
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    do {
        try {
                cout << "Nhap ngay thang nam muon diem danh: ";
                cin >> ngay >> thang >> nam;

                if (cin.fail()) {
                    throw runtime_error("");
                }

                check_Date(ngay, thang, nam); // kiem tra tinh hop le cua ngay sinh

                clear_Input(); //don dep input
                break;
            }
            catch (runtime_error e) {
                cout << "Nhap thong tin sai " << endl;
                clear_Input();
            }
            catch (string s) {
                cout << "Ngay thang nam khong hop le" << endl;
            }
        } while (true);
    while(true){
        cout << "Trang thai diem danh: ";
        cin.ignore();
        getline(cin, trang_thai);
        if(trang_thai != "DL" && trang_thai != "DLNN" && trang_thai != "N" && trang_thai != "NP"){
            cout << "Nhap sai trang thai";
            clear_Input();
        }
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}
    int List::atd(){
        int temp= 0;
        return temp;
    }
    int List::atd(string trang_thai){
        int temp;
        if(trang_thai == "NP")
            return temp = -1;
        else if(trang_thai == "N")
            return temp = -2;
        else if(trang_thai == "DL")
                return temp = 2;
        else if (trang_thai == "DLNN")
                return temp = 1;
        else return temp;

        }



