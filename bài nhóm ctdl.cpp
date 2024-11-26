#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

// Hàm kiểm tra thông tin đăng nhập
bool login(string& username) {
    string inputUser, inputPass, storedUser, storedPass;
    ifstream file("Employees.txt");

    if (!file.is_open()) {
        cerr << "Khong the mo file Employees.txt!" << endl;
        return false;
    }

    cout << "Nhap username: ";
    cin >> inputUser;
    cout << "Nhap password: ";
    cin >> inputPass;

    while (file >> storedUser >> storedPass) {
        if (storedUser == inputUser && storedPass == inputPass) {
            username = inputUser;
            file.close();
            return true;
        }
    }
    file.close();
    cout << "Sai ten dang nhap hoac mat khau!" << endl;
    return false;
}

// Hàm hiển thị thông tin tài khoản
void viewAccountInfo(const string& username) {
    ifstream file(username + ".txt");
    if (!file.is_open()) {
        cout << "Khong tim thay thong tin tai khoan cua ban!" << endl;
        return;
    }

    cout << "\nThong tin tai khoan:\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Hàm đổi mật khẩu
void changePassword(const string& username) {
    string currentPass, newPass1, newPass2, storedUser, storedPass;
    ifstream file("Employees.txt");
    ofstream tempFile("Temp.txt");

    if (!file.is_open() || !tempFile.is_open()) {
        cerr << "Khong the mo file de cap nhat mat khau!" << endl;
        return;
    }

    cout << "Nhap mat khau hien tai: ";
    cin >> currentPass;

    bool userFound = false, passwordUpdated = false;
    while (file >> storedUser >> storedPass) {
        if (storedUser == username) {
            userFound = true;
            if (storedPass == currentPass) {
                cout << "Nhap mat khau moi: ";
                cin >> newPass1;
                cout << "Nhap lai mat khau moi: ";
                cin >> newPass2;

                if (newPass1 == newPass2) {
                    tempFile << storedUser << " " << newPass1 << endl;
                    passwordUpdated = true;
                }
                else {
                    cout << "Mat khau moi khong trung khop!" << endl;
                    tempFile << storedUser << " " << storedPass << endl;
                }
            }
            else {
                cout << "Mat khau hien tai khong dung!" << endl;
                tempFile << storedUser << " " << storedPass << endl;
            }
        }
        else {
            tempFile << storedUser << " " << storedPass << endl;
        }
    }

    file.close();
    tempFile.close();

    if (userFound && passwordUpdated) {
        remove("Employees.txt");
        rename("Temp.txt", "Employees.txt");
        cout << "Mat khau da duoc cap nhat thanh cong!" << endl;
    }
    else {
        remove("Temp.txt");
        if (!userFound) {
            cout << "Khong tim thay tai khoan cua ban!" << endl;
        }
    }
}

// Hàm menu chính
void showMenu(const string& username) {
    int choice;

    do {
        cout << "\nMENU EMPLOYEE\n";
        cout << "1. Xem thong tin tai khoan\n";
        cout << "2. Doi password\n";
        cout << "3. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewAccountInfo(username);
            break;
        case 2:
            changePassword(username);
            break;
        case 3:
            cout << "Thoat chuong trinh!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 3);
}

// Hàm chính
int main() {
    string username;

    if (login(username)) {
        showMenu(username);
    }
    else {
        cout << "Dang nhap that bai!" << endl;
    }

    return 0;
}
