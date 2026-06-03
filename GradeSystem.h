#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <map>
#include <string>
#include "Student.h"

using namespace std;

class GradeSystem {
private:
    vector<Student> students;           // 存储所有学生
    map<string, int> idIndex;           // 学号到索引的映射（快速查找）
    string filename;                    // 数据文件名

public:
    GradeSystem(string filename = "students.txt");

    // 增加学生
    bool addStudent(const Student& student);

    // 删除学生（按学号）
    bool removeStudent(string id);

    // 查找学生（按学号）
    Student* findStudent(string id);

    // 显示所有学生
    void displayAll() const;

    // 按平均成绩排序并显示
    void displaySortedByAverage() const;

    // 按成绩排序
    void displaySortedByScore(int scoreType) const;  // 1=数学, 2=英语, 3=语文

    // 更新学生成绩
    bool updateStudentScore(string id, double math, double english, double chinese);

    // 文件操作
    bool saveToFile();      // 保存到文件
    bool loadFromFile();    // 从文件加载

    // 统计功能
    void showStatistics() const;  // 显示统计信息

    // 清空所有数据
    void clear();

    // 获取学生数量
    int getStudentCount() const;
};

#endif