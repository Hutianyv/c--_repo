#ifndef _COMPUTER
#define _COMPUTER
#include<iostream>
#include<string>
using namespace std;
enum ComputerStatus     //定义电脑状态，枚举
{
 FREE,               //空闲
 BUSY,               //正在使用
 RESERVED,        //已被预约
 BROKEN,             //损坏
};

// 定义预约时间段的结构体  
struct ReservationPeriod {  
    std::string username; // 预约人  
    std::string startTime; // 预约开始时间  
    std::string endTime; // 预约结束时间  
}; 

class Computer
{
    private:
    string ID;
    string currentUser; //当前使用人
    string Reserver;//预约人

    public:
    Computer();
    Computer(string id,string stu,string user,string re);
  
    bool is_reserve();      
    bool is_broken();
    bool is_busy();         //判断机器是否被预约、忙碌、损坏
    void showPeriods();         //显示空闲时间段
    string showReservations();    //显示被预约人信息
    string GetcurrentUser();     //获取当前使用人
    void addReservations();     //添加预约信息
    string stu_id;          //学生ID
    string GetID();        //获取电脑编号
    int set_stu_id();       //设置学生ID
    void showFreeTime();    //展示空闲时间段
};

void Check(ComputerStatus status);
void ChangeStatus(ComputerStatus status);

#endif 