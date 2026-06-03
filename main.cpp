#include <iostream>
#include <string>
#include "GradeSystem.h"

using namespace std;

void displayMenu() {
    cout << "\n========== 学生成绩管理系统 ==========" << endl;
    cout << "1. 添加学生" << endl;
    cout << "2. 删除学生" << endl;
    cout << "3. 查找学生" << endl;
    cout << "4. 显示所有学生" << endl;
    cout << "5. 按平均成绩排序显示" << endl;
    cout << "6. 按单科成绩排序显示" << endl;
    cout << "7. 更新学生成绩" << endl;
    cout << "8. 显示统计信息" << endl;
    cout << "9. 保存数据" << endl;
    cout << "0. 退出系统" << endl;
    cout << "========================================" << endl;
    cout << "请选择操作 (0-9): ";
}

int main() {
    GradeSystem system("students.txt");
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();  // 清除输入缓冲区的换行符

        if (choice == 1) {
            // 添加学生
            string id, name;
            double math, english, chinese;

            cout << "\n请输入学号: ";
            getline(cin, id);
            cout << "请输入姓名: ";
            getline(cin, name);
            cout << "请输入数学成绩: ";
            cin >> math;
            cout << "请输入英语成绩: ";
            cin >> english;
            cout << "请输入语文成绩: ";
            cin >> chinese;
            cin.ignore();

            Student student(id, name, math, english, chinese);
            system.addStudent(student);
        }
        else if (choice == 2) {
            // 删除学生
            string id;
            cout << "\n请输入要删除的学号: ";
            getline(cin, id);
            system.removeStudent(id);
        }
        else if (choice == 3) {
            // 查找学生
            string id;
            cout << "\n请输入要查找的学号: ";
            getline(cin, id);
            Student* student = system.findStudent(id);
            if (student) {
                cout << "找到学生信息：" << endl;
                student->display();
            } else {
                cout << "错误：学号不存在！" << endl;
            }
        }
        else if (choice == 4) {
            // 显示所有学生
            system.displayAll();
        }
        else if (choice == 5) {
            // 按平均成绩排序
            system.displaySortedByAverage();
        }
        else if (choice == 6) {
            // 按单科排序
            cout << "\n选择排序科目 (1=数学, 2=英语, 3=语文): ";
            int scoreType;
            cin >> scoreType;
            cin.ignore();
            system.displaySortedByScore(scoreType);
        }
        else if (choice == 7) {
            // 更新成绩
            string id;
            double math, english, chinese;
            cout << "\n请输入学号: ";
            getline(cin, id);
            cout << "请输入新的数学成绩: ";
            cin >> math;
            cout << "请输入新的英语成绩: ";
            cin >> english;
            cout << "请输入新的语文成绩: ";
            cin >> chinese;
            cin.ignore();

            system.updateStudentScore(id, math, english, chinese);
        }
        else if (choice == 8) {
            // 显示统计信息
            system.showStatistics();
        }
        else if (choice == 9) {
            // 保存数据
            system.saveToFile();
        }
        else if (choice == 0) {
            // 退出
            cout << "\n是否保存数据后退出? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                system.saveToFile();
            }
            cout << "感谢使用，再见！" << endl;
            break;
        }
        else {
            cout << "错误：无效的选择，请重试！" << endl;
        }
    }

    return 0;
}