#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class CUserName {
private:
    string strHoten, strDiachi, strSDT, strEmail;
public:
    CUserName() {}
    CUserName(const string& strName, const string& strAddress, const string& strPhoneNumber, const string& strEmailAddress)
        : strHoten(strName), strDiachi(strAddress), strSDT(strPhoneNumber), strEmail(strEmailAddress) {
    }

    string GetHoten() const { return strHoten; }
    string GetDiaChi() const { return strDiachi; }
    string GetSDT() const { return strSDT; }
    string GetEmail() const { return strEmail; }

    void SetHoten(const string& strHoten) { this->strHoten = strHoten; }
    void SetDiachi(const string& strDiachi) { this->strDiachi = strDiachi; }
    void SetSDT(const string& strSDT) { this->strSDT = strSDT; }
    void SetEmail(const string& strEmail) { this->strEmail = strEmail; }

    friend ostream& operator<<(ostream& os, const CUserName& user) {
        os << user.strHoten << "\n" << user.strDiachi << "\n" << user.strSDT << "\n" << user.strEmail << "\n";
        return os;
    }

    bool operator==(const CUserName& another) const {
        return GetHoten() == another.GetHoten() &&
            GetDiaChi() == another.GetDiaChi() &&
            GetSDT() == another.GetSDT() &&
            GetEmail() == another.GetEmail();
    }

    CUserName& operator=(const CUserName& another) {
        this->SetHoten(another.GetHoten());
        this->SetDiachi(another.GetDiaChi());
        this->SetSDT(another.GetSDT());
        this->SetEmail(another.GetEmail());
        return *this;
    }

    void ReadFromFile(ifstream& file) {
        getline(file, strHoten);
        getline(file, strDiachi);
        getline(file, strSDT);
        getline(file, strEmail);
    }
};

class CNode {
private:
    CUserName cData;
    CNode* pNext;
public:
    CNode() : pNext(nullptr) {}
    CNode(const CUserName& cValues) : cData(cValues), pNext(nullptr) {}
    friend class CAdministrator;
    friend class CEmployeeList;
};

class CAdministrator : public CUserName {
private:
    CNode* pEmployee;
public:
    CAdministrator() : pEmployee(nullptr) {}
    CAdministrator(const string& strName, const string& strAddress, const string& strPhoneNumber, const string& strEmailAddress)
        : CUserName(strName, strAddress, strPhoneNumber, strEmailAddress), pEmployee(nullptr) {
    }

    void AddEmployee(const CAdministrator& admin) {
        CNode* pNewNode = new CNode(admin);
        pNewNode->pNext = pEmployee;
        pEmployee = pNewNode;
    }

    void SearchEmployee(const string& strName) {
        CNode* pCurrent = pEmployee;
        while (pCurrent != nullptr) {
            if (pCurrent->cData.GetHoten() == strName) {
                cout << "Thong tin nhan vien:\n" << pCurrent->cData << endl;
                return;
            }
            pCurrent = pCurrent->pNext;
        }
        cout << "Khong tim thay nhan vien co ten: " << strName << endl;
    }

    CUserName* Search(const string& strHoten) {
        for (CNode* pCurrent = pEmployee; pCurrent != nullptr; pCurrent = pCurrent->pNext) {
            if (pCurrent->cData.GetHoten() == strHoten) {
                return &pCurrent->cData;
            }
        }
        return nullptr;
    }

    void PopFront() {
        if (!pEmployee) return;
        CNode* pTemp = pEmployee;
        pEmployee = pEmployee->pNext;
        delete pTemp;
    }

    void Remove(const string& strUsername) {
        if (!pEmployee) {
            cout << "Khong xoa duoc\n";
            return;
        }
        CUserName* pReject = Search(strUsername);
        if (!pReject) {
            cout << "Khong xoa duoc\n";
            return;
        }
        if (pEmployee->cData == *pReject) {
            this->PopFront();
            cout << "Da xoa\n";
            return;
        }
        CNode* pCurrent = pEmployee;
        while (pCurrent->pNext != nullptr) {
            if (pCurrent->pNext->cData == *pReject) {
                CNode* pTemp = pCurrent->pNext;
                pCurrent->pNext = pTemp->pNext;
                delete pTemp;
                cout << "Da xoa\n";
                return;
            }
            pCurrent = pCurrent->pNext;
        }
    }

    void ReadFromFile(const string& strFilename) {
        ifstream file(strFilename);
        if (file.is_open()) {
            string strName, strAddress, strPhoneNumber, strEmailAddress;
            while (getline(file, strName) && getline(file, strAddress) && getline(file, strPhoneNumber) && getline(file, strEmailAddress)) {
                CAdministrator admin(strName, strAddress, strPhoneNumber, strEmailAddress);
                AddEmployee(admin);
            }
            file.close();
        }
        else {
            cout << "Khong mo duoc file!" << endl;
        }
    }

    void SaveToFile(const string& strFilename) {
        ofstream file(strFilename);
        CNode* pTemp = pEmployee;
        while (pTemp) {
            file << pTemp->cData;
            pTemp = pTemp->pNext;
        }
        file.close();
    }

    void UpdateFileAfterDeletion(const string& strFilename) {
        SaveToFile(strFilename);
    }

    void Display() const {
        CNode* pCurrent = pEmployee;
        while (pCurrent != nullptr) {
            cout << pCurrent->cData << endl;
            pCurrent = pCurrent->pNext;
        }
    }

    ~CAdministrator() {
        while (pEmployee) {
            CNode* pTemp = pEmployee;
            pEmployee = pEmployee->pNext;
            delete pTemp;
        }
    }
};

class CEmployeeList {
private:
    CNode* pEmployee;
public:
    CEmployeeList() : pEmployee(nullptr) {}
};

// Hàm cập nhật thông tin của employee
void updateEmployeeInfo(const string& username) {
    string filename = username + ".txt";
    ifstream infile(filename);
    if (!infile) {
        cout << "Khong tim thay thong tin!" << endl;
        return;
    }

    string name, address, phone, email;
    cout << "Nhap ho ten moi (hoac de trong de giu nguyen): ";
    cin.ignore();
    getline(cin, name);
    cout << "Nhap dia chi moi (hoac de trong de giu nguyen): ";
    getline(cin, address);
    cout << "Nhap so dien thoai moi (hoac de trong de giu nguyen): ";
    getline(cin, phone);
    cout << "Nhap dia chi email moi (hoac de trong de giu nguyen): ";
    getline(cin, email);

    string currentName, currentAddress, currentPhone, currentEmail;
    getline(infile, currentName);
    getline(infile, currentAddress);
    getline(infile, currentPhone);
    getline(infile, currentEmail);
    infile.close();

    if (name.empty()) name = currentName;
    if (address.empty()) address = currentAddress;
    if (phone.empty()) phone = currentPhone;
    if (email.empty()) email = currentEmail;

    ofstream outfile(filename);
    outfile << name << endl;
    outfile << address << endl;
    outfile << phone << endl;
    outfile << email << endl;
    outfile.close();

    cout << "Cap nhat thong tin thanh cong!" << endl;
}
// Hàm hiển thị thông tin Employees
void displayAllEmployees() {
    ifstream infile("Employees.txt");
    if (!infile) {
        cout << "Khong the mo file!\n";
        return;
    }

    string username, password;
    vector<pair<string, string>> users;

    // Đọc username và password từ file Employees.txt
    while (getline(infile, username) && getline(infile, password)) {
        users.push_back({ username, password });
    }
    infile.close();

    if (users.empty()) {
        cout << "Danh sach nhan vien trong.\n";
        return;
    }

    cout << "Danh sach nhan vien:\n";
    cout << "--------------------------------------\n";

    for (const auto& user : users) {
        string filename = user.first + ".txt";
        ifstream userfile(filename);

        if (!userfile) {
            cout << "Khong the mo file! " << filename << ".\n";
            continue;
        }

        string name, address, phone, email;

        // Đọc thông tin từ file của từng nhân viên
        getline(userfile, name);
        getline(userfile, address);
        getline(userfile, phone);
        getline(userfile, email);
        userfile.close();

        // Hiển thị thông tin nhân viên
        cout << "Username: " << user.first << endl;
        cout << "Mat khau: " << user.second << endl;
        cout << "Ho ten: " << name << endl;
        cout << "Dia chi: " << address << endl;
        cout << "So dien thoai: " << phone << endl;
        cout << "Dia chi email: " << email << endl;
        cout << "--------------------------------------\n";
    }
}



// Menu chức năng cho Employee
void MenuEmployee() {
    CEmployeeList employeeList;
    int iChoice;
    while (true) {
        system("cls");
        cout << "\n******************Menu EMPLOYEES*******************\n";
        cout << " 1. Xem thong tin tai khoan\n";
        cout << " 2. Doi password\n";
        cout << " 3. Thoat!\n";
        cout << " ***************************************************\n";
        cout << "Chon chuc nang: ";
        cin >> iChoice;
        if (iChoice == 1) {
            // Hiển thị thông tin của employee
            // (Chức năng này cần được triển khai thêm)
        }
        else if (iChoice == 2) {
            // Đổi password
            // (Chức năng này cần được triển khai thêm)
        }
        else if (iChoice == 3) {
            break;
        }
        else {
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        system("pause");
    }
}

// Menu chức năng cho Admin
void MenuAdmin() {
    CAdministrator admin;
    admin.ReadFromFile("Administrators.txt");
    while (true) {
        system("cls");
        cout << "*******************Menu********************\n";
        cout << " 1. Them Employee\n";
        cout << " 2. Tim kiem Employee\n";
        cout << " 3. Xoa Employee\n";
        cout << " 4. Cap nhat Employee\n";
        cout << " 5. Hien thi thong tin Employee\n";
        cout << " 6. Thoat!\n";
        cout << "*******************************************\n";
        int iChoice;
        cout << "Chon chuc nang: ";
        cin >> iChoice;
        cin.ignore();
        if (iChoice == 1) {
            // Thêm Employee
            // (Chức năng này cần được triển khai thêm)
        }
        else if (iChoice == 2) {
            cout << "Nhap ten nhan vien can tim: ";
            string strUsername;
            getline(cin, strUsername);
            admin.SearchEmployee(strUsername);
        }
        else if (iChoice == 3) {
            cout << "Nhap ten nhan vien can xoa: ";
            string strUsername;
            getline(cin, strUsername);
            admin.Remove(strUsername);
            admin.UpdateFileAfterDeletion("Employees.txt");
            cout << "Danh sach nhan vien sau khi cap nhat:\n";
            admin.Display();
        }
        else if (iChoice == 4) {
            cout << "Nhap username can cap nhat: ";
            string username;
            cin >> username;
            updateEmployeeInfo(username);
        }
        else if (iChoice == 5) {
            displayAllEmployees();
        }
        else if (iChoice == 6) {
            break;
        }
        else {
            cout << "Lua chon khong hop le.\n";
        }
        system("pause");
    }
}

int main() {
    int iChoice;
    while (true) {
        system("cls");
        cout << "*******************Menu*********************\n";
        cout << " 1. Admin\n";
        cout << " 2. Employee\n";
        cout << " 3. Thoat!\n";
        cout << "********************************************\n";
        cout << "Chon chuc nang: ";
        cin >> iChoice;
        if (iChoice == 1) {
            MenuAdmin();
        }
        else if (iChoice == 2) {
            MenuEmployee();
        }
        else if (iChoice == 3) {
            break;
        }
        else {
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
    }
    return 0;
}