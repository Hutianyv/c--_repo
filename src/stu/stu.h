#ifndef _STU
#define _STU
#include<iostream>
#include<string>
using namespace std;
class Student
{
private:
 string name ;                              //姓名
 string password;                            //密码
 string ID;                                 //学号（账号）
 string majoy;                              //专业

public:
 Student();                                 //无参构造函数
 Student(string na,string id,string pa,string ma);      
 string Getname();                         //提取姓名 
 string GetID();                           //提取学号（账号）
 string Getpassword();                     //提取密码
 string Getmajoy();                        //提取专业
 void Display();                           //显示学生信息
 void Input();                             //输入学生信息
};



#endif