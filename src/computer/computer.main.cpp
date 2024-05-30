#include "computer.h"    

Computer::Computer(string id,string stu,string user,string se):ID(id),stu_id(stu),currentUser(user),Reserver(se)
{}
void Check(ComputerStatus status)                     //检查设备情况
{
     switch (status) {  
        case FREE:  
            std::cout << "计算机当前处于空闲状态,可以进行预约。" << std::endl;  
            break;  
        case BUSY:  
            std::cout << "计算机当前正在使用中。" << std::endl;  
            break;  
        case RESERVED:  
            std::cout << "计算机已被预约。" << std::endl;  
            break;  
        case BROKEN:  
            std::cout << "计算机已损坏。" << std::endl;  
            break;  
     }
}

void ChangeStatus(ComputerStatus status)              //改变设备状态
{
    cout<<"该计算机的状态是："<<status<<endl;
    int i;
    cout<<"请输入您要修改的状态，1为空闲，2为使用中，3为已被预约，4为已损坏:"<<endl;
    cin>>i;
    switch(i)
    {
        case 1:
        status=FREE;
        cout<<"当前状态已修改为："<<status<<endl;
        break;

        case 2:
        status=BUSY;
        cout<<"当前状态已修改为："<<status<<endl;
        break;

        case 3:
        status=RESERVED;
        cout<<"当前状态已修改为："<<status<<endl;
        break;

        case 4:
        status=BROKEN;
        cout<<"当前状态已修改为："<<status<<endl;
        break;
    }
    cout<<"经过修改，该计算机的状态是："<<status<<endl;
}

string Computer::GetcurrentUser()        //获取当前使用人
{
    return currentUser;
}

string Computer::GetID()                    //获取学生ID
{
    return ID;
}

string Computer::showReservations()                     //展示该机器预约信息
{
    for (const auto& reservation : Reserver)
    {  
            std::cout << "Reserved by: " << Reserver.username  
                      << ", Time: " << Reserver.startTime << " - " << Reserver.endTime << std::endl;        //包含预约人，开始和使用时间
    }  
}

 void addReservation(const std::string& username, const std::string& startTime, const std::string& endTime)     //添加预约
 {  
        if (status == ComputerStatus::FREE)                 //判断机器是否能被使用，若能，则修改为被预约状态
        {  
            status = ComputerStatus::RESERVED;  
        }  
        reservations.emplace_back(ReservationPeriod{username, startTime, endTime});  //包含使用人信息，开始和结束时间
    }  