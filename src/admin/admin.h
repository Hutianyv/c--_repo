#ifndef _ADMIN
#define _ADMIN
#include<iostream>
#include<string>
using namespace std;
class admin
{
private:
 string name ;                          //姓名
 string password;                       //密码
 string ID;                             //工号（账号）

 

public:
 admin();                               //无参构造函数
 admin(string na,string id,string pa);      
 string Getname();                      //提取姓名 
 string GetID();                        //提取工号（账号）
 string Getpassword();                  //提取密码
 void Display();                        //显示管理员信息
 void Input();                          //输入管理员信息
};


#endif 
