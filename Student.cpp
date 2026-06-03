#include "Student.h"
#include <sstream>
#include <iomanip>

Student::Student() : id(""), name(""), mathScore(0), englishScore(0), chineseScore(0) {}

Student::Student(string id, string name, double math, double english, double chinese)
    : id(id), name(name), mathScore(math), englishScore(english), chineseScore(chinese) {}

string Student::getId() const { return id; }
string Student::getName() const { return name; }
double Student::getMathScore() const { return mathScore; }
double Student::getEnglishScore() const { return englishScore; }
double Student::getChineseScore() const { return chineseScore; }

void Student::setId(string id) { this->id = id; }
void Student::setName(string name) { this->name = name; }
void Student::setMathScore(double score) { this->mathScore = score; }
void Student::setEnglishScore(double score) { this->englishScore = score; }
void Student::setChineseScore(double score) { this->chineseScore = score; }

double Student::getAverageScore() const {
    return (mathScore + englishScore + chineseScore) / 3.0;
}

void Student::display() const {
    cout << fixed << setprecision(2);
    cout << "学号: " << id << " | 姓名: " << name 
         << " | 数学: " << mathScore << " | 英语: " << englishScore
         << " | 语文: " << chineseScore << " | 平均: " << getAverageScore() << endl;
}

string Student::toFileFormat() const {
    stringstream ss;
    ss << id << "," << name << "," << mathScore << "," 
       << englishScore << "," << chineseScore;
    return ss.str();
}

Student Student::fromFileFormat(string line) {
    stringstream ss(line);
    string id, name, math_str, english_str, chinese_str;
    
    getline(ss, id, ',');
    getline(ss, name, ',');
    getline(ss, math_str, ',');
    getline(ss, english_str, ',');
    getline(ss, chinese_str, ',');
    
    return Student(id, name, stod(math_str), stod(english_str), stod(chinese_str));
}