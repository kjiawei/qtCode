#include <iostream>
#include <fstream>//保存信息到本地文件
#include <list>
#include <map>

//程序设计思路:查询学生成绩(目的)
//数据模型:list容器
//函数功能与主逻辑实现:增删查改 文件处理扩展 排序

//学生成绩管理系统
using namespace std;

class Date
{
public:
    Date(int &date);
    ~Date();
    void showDate()
    {
        //cout<<"date:"<<date<<endl;
    }
private:
    int year;
    int month;
    int date;
};

//template<typename T1,typename T2,typename T3,typename T4,typename T5>
//插入学生信息函数模板

//学生类
class Student
{
public:
    Student(string name,float score);
    //~Student();
    void showStudent(string name);
    void showScore(string name);//const &会改变实参
    bool insertInfo(/*const string &name,int pid,int sex,float score,int grade*/);
    bool deleteInfo();
    bool updateInfo();
    void pjScore();
    void totalScore();
    void showHelp();
    void tongji();
    void exitSys();
    void sortScore();//按分数排序
protected:

private:
    string name;//名字
    //string address;//地址
    int pid;//学号
    //int birthdate;//生日
    int sex;//性别
    float score;//分数
    int grade;//年级
    string className;//课程
};

Student::Student(string name = "123",float score = 0.0)
{
    cout<<"************学生成绩管理系统*************"<<endl;
    cout<<"  输入信息(i)  "<<" 查询成绩(s)  "<<"  帮助(h)"<<endl;//cout格式控制
    cout<<"  删除信息(w)  "<<" 平均成绩(p)  "<<"人数统计(r)"<<endl;
    cout<<"  修改信息(c)  "<<" 总分成绩(t)  "<<"退出系统(q)"<<endl;
    cout<<"****************************************"<<endl;

    this->name = name;
    this->score = score;
}

bool Student::insertInfo(/*const string &name,int pid,int sex,float score,int grade*/)
{
    cout<<"请输入学生信息(名字,分数),结束:ok+回车"<<endl;
    string stuinfo;//string student[];//学生详细信息不同类型如何处理
    //ofstream outfile("E:/qtProject/test/studentfile.txt");//第一次新增写入
    ifstream infile;//读取新增文件
    //infile.open("E:/qtProject/test/score.txt");
    ofstream outfile("E:/qtProject/test/studentfile2.txt");
    char studentInfo[50];//新增学生信息数组
   // map<string,string> chfont;
    while(/*!infile.eof()*/stuinfo != "ok")
    {
//        infile.getline(studentInfo,50);
//        string str = studentInfo;
//        cout<<"0:"<<str<<endl;
//        int pos = str.find(",");
//        cout<<"1:"<<pos<<endl;
//        string sbuf = str.substr(0,pos);
//        cout<<"2:"<<sbuf<<endl;
//        str.replace(0,pos+1,"");//,ji qian -> kong
//        cout<<"3:"<<str<<endl;
        //chfont[sbuf] = str;
        //outfile.write(sbuf.data(),sbuf.size());
        //outfile.write("\n",1);
        cin>>stuinfo;//为什么会多个空行
        //outfile.write(
//        this->name = name;
//        this->pid = pid;
//        this->sex = sex;
//        this->score = score;
//        this->grade = grade;
        //cout<<stuinfo<<endl;
        break;
    }
    infile.close();
    outfile.close();
    string str;
    while(str!="ok")
    {
        cin>>str;
    }
    return true;
}

void Student::showStudent(string name)
{
    cout<<"name:"<<name<<endl;
    cout<<"grade:"<<grade<<endl;
    cout<<"sex:"<<sex<<endl;
}

void Student::showScore(string name)
{
    cout<<"score:"<<score<<endl;
    //return score;
}

//Date::Date(int &date)
//{
//    this->date = date;
//}

int main()
{
    //数据的获取:输入 本地文件
//    ifstream file;
//    char stubuf[200];//存放学生信息的数组
//    file.open("E:/qtProject/test/student.txt");
//    while(!file.eof)
//    {
//        file.getline(buf,100);
//        string str = buf;
//        str.find(" ");//空格为每条记录的分割符
//        //未完善
//    }
//    file.close();

    //string stuinfo;//学生信息
    //cin>>stuinfo;
    //while(stuinfo != ("quit"|"q"))

    //对学生数据的操作
    Student stu/*("jerry",12.2)*/;//创建一个学生  list
//    Student stu2("jerry2",12.3);
//    stu.showScore("jerry");
//    stu2.showScore("jerry2");
    stu.insertInfo();

//    map<string,float> studentmap;//学生对象容器:名字与学号映射
//    studentmap.insert(pair<string,float>("xiaoxin",60.0));//不能重复数据
//    map<string,float>::iterator iter;//map迭代器
//    for(iter = studentmap.begin();iter != studentmap.end();iter++)
//    {
//        cout<<"student name:"<<iter->first<<endl;
//        cout<<"student score:"<<iter->second<<endl;
//    }

    return 0;
}

