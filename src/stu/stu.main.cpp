#include "stu.h"
//stu类成员函数的实现
Student::Student()
{
    name=" ";
}

Student::Student(string na,string id,string pa,string ma):name(na),ID(id),password(pa),majoy(ma)
{}

string Student::Getname()                 //提取姓名
{
   return name;
}

string Student::GetID()                   //提取工号（账号）
{
   return ID;
}

string Student::Getpassword()             //提取密码
{
   return password;
}

string Student::Getmajoy()                   //提取专业信息
{
   return majoy;
}

void Student::Display()                   //输出数据信息
{
  
}

void Student::Input()                     //输入数据
{

}