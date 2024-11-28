#include <bits/stdc++.h>
using namespace std;

template <class DataType>
class LinkedList;

class userName {
private:
    string Hoten, Diachi, SDT, Email;
public:
    userName() {}
    userName(string name, string address, string phoneNumber, string emailAddress)
        : Hoten(name), Diachi(address), SDT(phoneNumber), Email(emailAddress) {}

    string getHoten() const { return Hoten; }
    string getDiaChi() const { return Diachi; }
    string getSDT() const { return SDT; }
    string getEmail() const { return Email; }

    void setHoten(string hoten) { Hoten = hoten; }
    void setDiachi(string dc) { Diachi = dc; }
    void setSDT(string sdt) { SDT = sdt; }
    void setEmail(string email) { Email = email; }

    friend ostream &operator<<(ostream &os, const userName &user) {
        os << user.Hoten << "\n" << user.Diachi << "\n" << user.SDT << "\n" << user.Email << "\n";
        return os;
    }

    bool operator==(const userName &another) const {
        return getHoten() == another.getHoten() &&
               getDiaChi() == another.getDiaChi() &&
               getSDT() == another.getSDT() &&
               getEmail() == another.getEmail();
    }

    userName& operator=(const userName& another) {
        if (this != &another) {
            this->setHoten(another.getHoten());
            this->setDiachi(another.getDiaChi());
            this->setSDT(another.getSDT());
            this->setEmail(another.getEmail());
        }
        return *this;
    }

    void readFromFile(ifstream &file) {
        getline(file, Hoten);
        getline(file, Diachi);
        getline(file, SDT);
        getline(file, Email);
    }
};

template<class DataType>
class Node {
private:
    DataType data;
    Node <DataType> *next;
    friend class LinkedList <DataType>;
public:
    Node() : next(NULL) {}
    Node(DataType values) : data(values), next(NULL) {}

    friend class Administrator;
    friend class Employee;
};

template<class DataType>
class LinkedList {
private:
    Node <DataType> *root;
public:
    LinkedList() : root(nullptr) {}

    void searchEmployee(userName * x, const string &name) {
        Node <DataType> *current = root;
        while (current != NULL) {
            if (current->data.getHoten() == name) {
                cout << "Thong tin nhan vien:\n" << current->data << endl;
                return;
            }
            current = current->next;
        }
        cout << "Khong tim thay nhan vien co ten: " << name << endl;
    }
    ~LinkedList() {
        while (root != nullptr) {
            Node<DataType>* temp = root;
            root = root->next;
            delete temp;
        }
    }
};

class Administrator : public userName {
private:
    Node <Administrator> * Admin;
public:
    Administrator() : Admin(NULL) {}
    Administrator(string name, string address, string phoneNumber, string emailAddress)
        : userName(name, address, phoneNumber, emailAddress), Admin(NULL) {}
};

class Employee : public userName {
private:
    Node <Employee>*employee;
public: 
    Employee() : employee(NULL) {}
    Employee(string name, string address, string phoneNumber, string emailAddress)
        : userName(name, address, phoneNumber, emailAddress), employee(NULL) {}
};

string searchFileAndReturnContents(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Khong Tim Thay Nhan Vien!" << fileName << endl;
        return "";
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void removeEmployeeFromEmployFile(const string& employeeName) {
    ifstream file("Employees.txt");
    if (!file) {
        cerr << "Khong tim thay file Employees.txt" << endl;
        return;
    }

    string employeeFile = employeeName + ".txt";
    ofstream tempFile(employeeFile );

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line != employeeName) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();
    remove("Employees.txt");
    rename(employeeFile.c_str(), "Employees.txt");

    if (found) {
        string employeeFileName = employeeName + ".txt";
        if (remove(employeeFileName.c_str()) == 0) {
            cout << "File " << employeeFileName << " xoa thanh cong!" << endl;
        } 
        else {
            cerr << "Xoa file that bai!" << employeeFileName << endl;
        }
    } 
    else {
        cout << "Khong tim thay nhan vien " << employeeName << " de xoa!" << endl;
    }
}

/*
void MenuAdmin(){
    //system("cls");
    while (true) {
        //system("cls");
        cout << "\n********************Menu*******************\n";
        cout << "         1.Them Employee\n";
        cout << "         2.Tim kiem Employee\n";
        cout << "         3.Xoa Employee\n";
        cout << "         4.Cap nhat Employee\n";
        cout << "         5.Hien thi thong tin Employee\n";
        cout << "         6.Thoat!\n";
        cout << " ******************************************\n";
        cout << "Chon chuc nang: ";
        //system("cls");
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 5) {
            //Admin.display();
        } 
        else if (choice == 2) {
            string name;
            cout << "Nhap vao ten can tim: ";
            getline(cin, name);
            
            string fileName = name + ".txt"; // Assumes the file extension is .txt
            string contents = searchFileAndReturnContents(fileName);

            if (!contents.empty()) {
                cout << "Contents of the file " << fileName << ":\n" << contents << endl;
            } 
        }
        else if (choice == 3) {
            string name;
            cout << "Nhap vao ten can xoa: ";
            getline(cin, name);
            string fileName = name + ".txt"; 
            char choice;
            cout << "Ban co muon xoa nhan vien nay khong? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                removeEmployeeFromEmployFile(name);
            }
            else {
                cout << "File " << fileName << " khong tim thay hoac rong!" << endl;
            }
        }

        else if (choice == 6) {
            break;
        }

        else {
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        
        system("pause");
    }
}
*/

void MenuAdministrator()
{
    //textcolor(12);
    cout << "\t************ MENU ADMIN ************" << endl;
    //textcolor(14);
    cout << "\t    1. Them Employee                " << endl;
    cout << "\t    2. Xoa Employee                 " << endl;
    cout << "\t    3. Tim Employee                 " << endl;
    cout << "\t    4. Cap nhat Employee            " << endl;
    cout << "\t    5. Hien thi thong tin Employee  " << endl;
    cout << "\t    6. Thoat                        " << endl;
    //textcolor(12);
    cout << "\t************************************" << endl;
}

void MenuAdmin(){
    while (true){
        system("cls");
        MenuAdministrator();
                        //textcolor(3);
                        cout << " Moi ban chon chuc nang: ";
                        //textcolor(15);
                        int k;
                        cin >> k;
        if (k == 1)
        {

        }
        else if (k == 2){
            string name;
            cout << "Nhap vao ten can xoa: ";
            getline(cin, name);
            string fileName = name + ".txt"; 
            char choice;
            cout << "Ban co muon xoa nhan vien nay khong? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                removeEmployeeFromEmployFile(name);
            }
            else {
                cout << "File " << fileName << " khong tim thay hoac rong!" << endl;
            }
        }
        else if (k == 3){
            string name;
            cout << "Nhap vao ten can tim: ";
            getline(cin, name);
            
            string fileName = name + ".txt"; // Assumes the file extension is .txt
            string contents = searchFileAndReturnContents(fileName);

            if (!contents.empty()) {
                cout << "Contents of the file " << fileName << ":\n" << contents << endl;
            } 
        }
        else if (k == 4){

        }
        else if (k == 5){

        }
                        
        else if (k == 6)
        {

        }
        else{
            cout << " Lua chon khong hop le!" << endl;
        }
    }
}

int main() {
    int chucvu;
    while (true) {
        cout << "----------------CHUC VU------------------\n";
        cout << "       1.Administrator\n";
        cout << "       2.Employee\n";
        cout << "       Chuc vu cua ban la: ";
        cin >> chucvu;
        cin.ignore();
        if (chucvu == 1) {
            MenuAdmin();
        } else if (chucvu == 2) {
            //MenuEmployee();
        } else {
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }    
    }
        
    /*
    string name;
    cout << "Nhap vao ten can tim: ";
    getline(cin, name);
    
    string fileName = name + ".txt"; // Assumes the file extension is .txt
    string contents = searchFileAndReturnContents(fileName);

    if (!contents.empty()) {
        cout << "Contents of the file " << fileName << ":\n" << contents << endl;

        // Ask if the user wants to delete the employee
        char choice;
        cout << "Do you want to delete this employee? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            removeEmployeeFromEmployFile(name);
        }
    } else {
        cout << "File " << fileName << " not found or empty." << endl;
    }
    */
    return 0;
}

