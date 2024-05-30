#include "admin.h"
//admin类成员函数的实现
admin::admin()
{
    name=" ";
}

admin::admin(string na,string id,string pa):name(na),ID(id),password(pa)
{}

string admin::Getname()                 //提取姓名
{
   return name;
}

string admin::GetID()                   //提取工号（账号）
{
   return ID;
}

string admin::Getpassword()             //提取密码
{
   return password;
}

void admin::Display()                   //输出数据信息
{
  
}

void admin::Input()                     //输入数据
{

}