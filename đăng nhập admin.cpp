#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Hàm đọc dữ liệu từ file vào vector
vector<string> readFile(const string& fileName) {
    vector<string> data;
    ifstream file(fileName);
    string line;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            data.push_back(line);
        }
        file.close();
    }
    
    return data;
}

// Hàm ghi dữ liệu vào file
void writeFile(const string& fileName, const vector<string>& data) {
    ofstream file(fileName);
    if (file.is_open()) {
        for (const string& line : data) {
            file << line << endl;
        }
        file.close();
    }
}

// Hàm kiểm tra đăng nhập của admin
bool adminLogin(const vector<string>& admins) {
    string username, password;
    cout << "Nhập tên đăng nhập: ";
    cin >> username;
    cout << "Nhập mật khẩu: ";
    cin >> password;

    for (const string& admin : admins) {
        stringstream ss(admin);
        string adminUser, adminPass;
        getline(ss, adminUser, ',');
        getline(ss, adminPass);
        
        if (adminUser == username && adminPass == password) {
            return true;
        }
    }
    
    return false;
}

// Hàm kiểm tra đăng nhập của employee
string employeeLogin(const vector<string>& employees) {
    string username, password;
    cout << "Nhập tên đăng nhập: ";
    cin >> username;
    cout << "Nhập mật khẩu: ";
    cin >> password;

    for (const string& employee : employees) {
        stringstream ss(employee);
        string empUser, empPass;
        getline(ss, empUser, ',');
        getline(ss, empPass);
        
        if (empUser == username && empPass == password) {
            return username;
        }
    }
    
    return "";
}

// Hàm thêm quản trị viên mới
void addAdmin(vector<string>& admins) {
    string username, fullName, address, phone, email;
    cout << "Nhập tên đăng nhập mới: ";
    cin >> username;

    // Kiểm tra tên đăng nhập đã tồn tại
    for (const string& admin : admins) {
        stringstream ss(admin);
        string adminUser;
        getline(ss, adminUser, ',');
        if (adminUser == username) {
            cout << "Tên đăng nhập đã tồn tại!" << endl;
            return;
        }
    }

    string password = "111111";
    cout << "Nhập họ tên: ";
    cin.ignore();
    getline(cin, fullName);
    cout << "Nhập địa chỉ: ";
    getline(cin, address);
    cout << "Nhập số điện thoại: ";
    getline(cin, phone);
    cout << "Nhập địa chỉ email: ";
    getline(cin, email);

    // Thêm admin vào danh sách
    admins.push_back(username + "," + password);
    writeFile("Administrators.txt", admins);
    
    // Tạo file [username].txt cho admin
    ofstream file(username + ".txt");
    if (file.is_open()) {
        file << "Họ tên: " << fullName << endl;
        file << "Địa chỉ: " << address << endl;
        file << "Số điện thoại: " << phone << endl;
        file << "Địa chỉ email: " << email << endl;
        file.close();
    }

    cout << "Thêm quản trị viên thành công!" << endl;
}

// Hàm thêm nhân viên mới
void addEmployee(vector<string>& employees) {
    string username, fullName, address, phone, email;
    cout << "Nhập tên đăng nhập mới: ";
    cin >> username;

    // Kiểm tra tên đăng nhập đã tồn tại
    for (const string& employee : employees) {
        stringstream ss(employee);
        string empUser;
        getline(ss, empUser, ',');
        if (empUser == username) {
            cout << "Tên đăng nhập đã tồn tại!" << endl;
            return;
        }
    }

    string password = "111111";
    // Thêm employee vào danh sách
    employees.push_back(username + "," + password);
    writeFile("Employees.txt", employees);

    // Tạo file [username].txt cho employee
    ofstream file(username + ".txt");
    if (file.is_open()) {
        cout << "Nhập họ tên: ";
        cin.ignore();
        getline(cin, fullName);
        cout << "Nhập địa chỉ: ";
        getline(cin, address);
        cout << "Nhập số điện thoại: ";
        getline(cin, phone);
        cout << "Nhập địa chỉ email: ";
        getline(cin, email);

        file << "Họ tên: " << fullName << endl;
        file << "Địa chỉ: " << address << endl;
        file << "Số điện thoại: " << phone << endl;
        file << "Địa chỉ email: " << email << endl;
        file.close();
    }

    cout << "Thêm nhân viên thành công!" << endl;
}

// Hàm xem thông tin nhân viên
void viewEmployeeInfo(const string& username) {
    ifstream file(username + ".txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Không tìm thấy thông tin nhân viên!" << endl;
    }
}

int main() {
    vector<string> admins = readFile("Administrators.txt");
    vector<string> employees = readFile("Employees.txt");

    string username;
    string userType;
    
    cout << "Đăng nhập hệ thống:\n";
    cout << "Chọn loại người dùng (admin/employee): ";
    cin >> userType;

    if (userType == "admin") {
        if (adminLogin(admins)) {
            cout << "Đăng nhập thành công!" << endl;
            int choice;
            do {
                cout << "\nChức năng quản trị:\n";
                cout << "1. Thêm quản trị viên\n";
                cout << "2. Thêm nhân viên\n";
                cout << "3. Xem thông tin nhân viên\n";
                cout << "4. Đăng xuất\n";
                cout << "Chọn chức năng: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        addAdmin(admins);
                        break;
                    case 2:
                        addEmployee(employees);
                        break;
                    case 3:
                        cout << "Nhập tên nhân viên: ";
                        cin >> username;
                        viewEmployeeInfo(username);
                        break;
                    case 4:
                        cout << "Đăng xuất!" << endl;
                        break;
                    default:
                        cout << "Lựa chọn không hợp lệ!" << endl;
                }
            } while (choice != 4);
        } else {
            cout << "Đăng nhập không thành công!" << endl;
        }
    } else if (userType == "employee") {
        username = employeeLogin(employees);
        if (!username.empty()) {
            cout << "Đăng nhập thành công!" << endl;
            int choice;
            do {
                cout << "\nChức năng nhân viên:\n";
                cout << "1. Xem thông tin cá nhân\n";
                cout << "2. Đăng xuất\n";
                cout << "Chọn chức năng: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        viewEmployeeInfo(username);
                        break;
                    case 2:
                        cout << "Đăng xuất!" << endl;
                        break;
                    default:
                        cout << "Lựa chọn không hợp lệ!" << endl;
                }
            } while (choice != 2);
        } else {
            cout << "Đăng nhập không thành công!" << endl;
        }
    } else {
        cout << "Lựa chọn loại người dùng không hợp lệ!" << endl;
    }

    return 0;
}
