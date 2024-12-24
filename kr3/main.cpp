#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


// Employee structure
struct Employee {
    int id;
    string name;
    string position;
    double performanceRating;
};

// Employee Database class
class EmployeeDatabase {
private:
    vector<Employee> employees;
public:
    void addEmployee(const Employee& emp) {
        employees.push_back(emp);
        cout << "Employee added successfully!\n";
    }

    void displayEmployees() {
        if (employees.empty()) {
            cout << "No employees in the database.\n";
            return;
        }
        cout << "\nEmployee List:\n";
        for (const auto& emp : employees) {
            cout << "ID: " << emp.id << ", Name: " << emp.name
                 << ", Position: " << emp.position
                 << ", Performance Rating: " << emp.performanceRating << endl;
        }
    }

    Employee* findEmployeeById(int id) {
        for (auto& emp : employees) {
            if (emp.id == id) return &emp;
        }
        return nullptr;
    }

    void updatePerformance(int id, double newRating) {
        Employee* emp = findEmployeeById(id);
        if (emp) {
            emp->performanceRating = newRating;
            cout << "Performance updated successfully!\n";
        } else {
            cout << "Employee not found!\n";
        }
    }

    void displayTopPerformers(int topN) {
        if (employees.empty()) {
            cout << "No employees in the database to evaluate.\n";
            return;
        }

        vector<Employee> sortedEmployees = employees;
        sort(sortedEmployees.begin(), sortedEmployees.end(), [](const Employee& a, const Employee& b) {
            return a.performanceRating > b.performanceRating;
        });

        cout << "\nTop " << topN << " Performers:\n";
        for (int i = 0; i < min(topN, (int)sortedEmployees.size()); ++i) {
            const auto& emp = sortedEmployees[i];
            cout << "ID: " << emp.id << ", Name: " << emp.name
                 << ", Position: " << emp.position
                 << ", Performance Rating: " << emp.performanceRating << endl;
        }
    }
};

// Auto Regulation System class
class AutoRegulationSystem {
public:
    void evaluatePerformance(EmployeeDatabase& db) {
        int topN;
        cout << "\nEnter the number of top performers to display: ";
        cin >> topN;
        db.displayTopPerformers(topN);
    }
};

// Menu Function
void displayMenu() {
    cout << "\nEmployee Management System\n";
    cout << "1. Add Employee\n";
    cout << "2. Display Employees\n";
    cout << "3. Update Performance\n";
    cout << "4. Evaluate Performance\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}


int main() {
    EmployeeDatabase db;
    AutoRegulationSystem ars;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                Employee emp;
                cout << "Enter Employee ID: ";
                cin >> emp.id;
                cin.ignore(); // Clear newline
                cout << "Enter Name: ";
                getline(cin, emp.name);
                cout << "Enter Position: ";
                getline(cin, emp.position);
                cout << "Enter Performance Rating: ";
                cin >> emp.performanceRating;
                db.addEmployee(emp);
                break;
            }
            case 2:
                db.displayEmployees();
                break;
            case 3: {
                int id;
                double newRating;
                cout << "Enter Employee ID to update: ";
                cin >> id;
                cout << "Enter new Performance Rating: ";
                cin >> newRating;
                db.updatePerformance(id, newRating);
                break;
            }
            case 4:
                ars.evaluatePerformance(db);
                break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
