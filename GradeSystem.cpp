#include "GradeSystem.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

GradeSystem::GradeSystem(string filename) : filename(filename) {
    loadFromFile();  // 初始化时自动从文件加载
}

bool GradeSystem::addStudent(const Student& student) {
    // 检查学号是否已存在
    if (idIndex.find(student.getId()) != idIndex.end()) {
        cout << "错误：学号已存在！" << endl;
        return false;
    }

    idIndex[student.getId()] = students.size();
    students.push_back(student);
    cout << "✓ 学生添加成功！" << endl;
    return true;
}

bool GradeSystem::removeStudent(string id) {
    auto it = idIndex.find(id);
    if (it == idIndex.end()) {
        cout << "错误：学号不存在！" << endl;
        return false;
    }

    int index = it->second;
    students.erase(students.begin() + index);
    idIndex.erase(it);

    // 重建索引
    idIndex.clear();
    for (int i = 0; i < students.size(); i++) {
        idIndex[students[i].getId()] = i;
    }

    cout << "✓ 学生删除成功！" << endl;
    return true;
}

Student* GradeSystem::findStudent(string id) {
    auto it = idIndex.find(id);
    if (it == idIndex.end()) {
        return nullptr;
    }
    return &students[it->second];
}

void GradeSystem::displayAll() const {
    if (students.empty()) {
        cout << "暂无学生数据！" << endl;
        return;
    }

    cout << "\n========== 所有学生信息 ==========" << endl;
    for (const auto& student : students) {
        student.display();
    }
    cout << "=================================" << endl << endl;
}

void GradeSystem::displaySortedByAverage() const {
    if (students.empty()) {
        cout << "暂无学生数据！" << endl;
        return;
    }

    // 创建副本用于排序
    vector<Student> sorted_students = students;
    sort(sorted_students.begin(), sorted_students.end(),
         [](const Student& a, const Student& b) {
             return a.getAverageScore() > b.getAverageScore();
         });

    cout << "\n========== 按平均成绩排序 ==========" << endl;
    for (const auto& student : sorted_students) {
        student.display();
    }
    cout << "===================================" << endl << endl;
}

void GradeSystem::displaySortedByScore(int scoreType) const {
    if (students.empty()) {
        cout << "暂无学生数据！" << endl;
        return;
    }

    vector<Student> sorted_students = students;
    
    if (scoreType == 1) {  // 数学
        sort(sorted_students.begin(), sorted_students.end(),
             [](const Student& a, const Student& b) {
                 return a.getMathScore() > b.getMathScore();
             });
        cout << "\n========== 按数学成绩排序 ==========" << endl;
    } else if (scoreType == 2) {  // 英语
        sort(sorted_students.begin(), sorted_students.end(),
             [](const Student& a, const Student& b) {
                 return a.getEnglishScore() > b.getEnglishScore();
             });
        cout << "\n========== 按英语成绩排序 ==========" << endl;
    } else if (scoreType == 3) {  // 语文
        sort(sorted_students.begin(), sorted_students.end(),
             [](const Student& a, const Student& b) {
                 return a.getChineseScore() > b.getChineseScore();
             });
        cout << "\n========== 按语文成绩排序 ==========" << endl;
    }

    for (const auto& student : sorted_students) {
        student.display();
    }
    cout << "===================================" << endl << endl;
}

bool GradeSystem::updateStudentScore(string id, double math, double english, double chinese) {
    Student* student = findStudent(id);
    if (!student) {
        cout << "错误：学号不存在！" << endl;
        return false;
    }

    student->setMathScore(math);
    student->setEnglishScore(english);
    student->setChineseScore(chinese);
    cout << "✓ 成绩更新成功！" << endl;
    return true;
}

bool GradeSystem::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "错误：无法打开文件进行写入！" << endl;
        return false;
    }

    for (const auto& student : students) {
        file << student.toFileFormat() << endl;
    }

    file.close();
    cout << "✓ 数据已保存到文件！" << endl;
    return true;
}

bool GradeSystem::loadFromFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "提示：数据文件不存在，将创建新文件。" << endl;
        return true;
    }

    students.clear();
    idIndex.clear();

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            Student student = Student::fromFileFormat(line);
            idIndex[student.getId()] = students.size();
            students.push_back(student);
        }
    }

    file.close();
    cout << "✓ 数据已从文件加载！" << endl;
    return true;
}

void GradeSystem::showStatistics() const {
    if (students.empty()) {
        cout << "暂无学生数据！" << endl;
        return;
    }

    double mathSum = 0, englishSum = 0, chineseSum = 0;
    double mathMax = students[0].getMathScore(), mathMin = students[0].getMathScore();
    double englishMax = students[0].getEnglishScore(), englishMin = students[0].getEnglishScore();
    double chineseMax = students[0].getChineseScore(), chineseMin = students[0].getChineseScore();

    for (const auto& student : students) {
        mathSum += student.getMathScore();
        englishSum += student.getEnglishScore();
        chineseSum += student.getChineseScore();

        mathMax = max(mathMax, student.getMathScore());
        mathMin = min(mathMin, student.getMathScore());
        englishMax = max(englishMax, student.getEnglishScore());
        englishMin = min(englishMin, student.getEnglishScore());
        chineseMax = max(chineseMax, student.getChineseScore());
        chineseMin = min(chineseMin, student.getChineseScore());
    }

    cout << fixed << setprecision(2);
    cout << "\n========== 成绩统计信息 ==========" << endl;
    cout << "总人数：" << students.size() << endl << endl;
    cout << "数学成绩 - 平均: " << mathSum / students.size() 
         << " | 最高: " << mathMax << " | 最低: " << mathMin << endl;
    cout << "英语成绩 - 平均: " << englishSum / students.size() 
         << " | 最高: " << englishMax << " | 最低: " << englishMin << endl;
    cout << "语文成绩 - 平均: " << chineseSum / students.size() 
         << " | 最高: " << chineseMax << " | 最低: " << chineseMin << endl;
    cout << "===================================" << endl << endl;
}

void GradeSystem::clear() {
    students.clear();
    idIndex.clear();
}

int GradeSystem::getStudentCount() const {
    return students.size();
}