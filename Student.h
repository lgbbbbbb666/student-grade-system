#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

using namespace std;

class Student {
private:
    string id;           // 学号
    string name;         // 姓名
    double mathScore;    // 数学成绩
    double englishScore; // 英语成绩
    double chineseScore; // 语文成绩

public:
    // 构造函数
    Student();
    Student(string id, string name, double math, double english, double chinese);

    // Getter 方法
    string getId() const;
    string getName() const;
    double getMathScore() const;
    double getEnglishScore() const;
    double getChineseScore() const;

    // Setter 方法
    void setId(string id);
    void setName(string name);
    void setMathScore(double score);
    void setEnglishScore(double score);
    void setChineseScore(double score);

    // 其他方法
    double getAverageScore() const;  // 计算平均成绩
    void display() const;             // 显示学生信息

    // 转换为字符串格式（用于文件保存）
    string toFileFormat() const;
    
    // 从字符串格式创建（用于文件读取）
    static Student fromFileFormat(string line);
};

#endif