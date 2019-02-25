#include <iostream>
#include <map>
#include <fstream>
#include<sstream>
#include <stdlib.h>
#include  <direct.h>
#include  <stdio.h>
using namespace std;

class Student
{
public:
    Student();
    bool save();
    bool show();
    bool add_msg();
    bool del_msg();
    bool analy(string msg);
private:
    string name;
    string ID;
    string age;
    string grade;
    unsigned int chinese;
    unsigned int math;
    unsigned int english;
    map<string,string> Stumap;
};

Student::Student()
{
    char msg[256];
    string name;
    string str_msg;
    ifstream infile;
    char cpath[256]={0};
    getcwd(cpath,256);
    sprintf(cpath,"%s%s",cpath,"/student.txt");
    cout<<cpath<<endl;
    infile.open(cpath);
    while(!infile.eof())
    {
    infile.getline(msg,sizeof(msg));
    if(strlen(msg)==0) break;
    str_msg=msg;
    int pos=str_msg.find(":");
    name=str_msg.substr(0,pos);
    Stumap[name]=str_msg;
    }
    infile.close();
}

bool Student::save()
{
   string msg;
   ofstream outfile;
   char cpath[256]={0};
   getcwd(cpath,256);
   sprintf(cpath,"%s/%s",cpath,"/student.txt");
   outfile.open(cpath,ofstream::out|ofstream::trunc);
   map<string,string>::iterator it;
   it=Stumap.begin();
   for(;it!=Stumap.end();it++)
   {
       msg=it->second;
       outfile.write(msg.c_str(),msg.size());
       outfile.write("\n",1);
   }
    outfile.close();
    return 0;
}

bool Student::add_msg()
{
    ostringstream msg;
    cout<<"请输入要添加学生的姓名：";
    cin>>name;
    cout<<"请输入学生学号：";
    cin>>ID;
    cout<<"请输入学生年龄：";
    cin>>age;
    cout<<"请输入学生班级：";
    cin>>grade;
    cout<<"请输入学生语文成绩:";
    cin>>chinese;
    cout<<"请输入学生英语成绩:";
    cin>>english;
    cout<<"请输入学生数学成绩:";
    cin>>math;
    string str=name+":"+ID+":"+age+":"+grade+":";
    string str_msg;
    msg<<str<<chinese<<":"<<english<<":"<<math;
    Stumap[name]=msg.str();
    return true;
}

bool Student::del_msg()
{
    string del_stu;
    cout<<"请输入要删除学生姓名";
    cin>>del_stu;
    Stumap.erase(del_stu);
    cout<<"删除完毕"<<endl;
    return true;
}

bool Student::analy(string msg)
{
    string str;
    int pos=msg.find(":");
    name=msg.substr(0,pos);
    msg.replace(0,pos+1,"");
    pos=msg.find(":");
    ID=msg.substr(0,pos);
    msg.replace(0,pos+1,"");
    pos=msg.find(":");
    age=msg.substr(0,pos);
    msg.replace(0,pos+1,"");
    pos=msg.find(":");
    grade= msg.substr(0,pos);
    msg.replace(0,pos+1,"");
    pos=msg.find(":");
    str=msg.substr(0,pos);
    chinese=atoi(str.c_str());
    msg.replace(0,pos+1,"");
    pos=msg.find(":");
    str=msg.substr(0,pos);
    english=atoi(str.c_str());
    msg.replace(0,pos+1,"");
    pos=msg.find(":");
    str=msg.substr(0,pos);
    math=atoi(str.c_str());
    msg.replace(0,pos+1,"");
    return true;
}

bool Student::show()
{
    string msg;
    map<string,string>::iterator it;
    it=Stumap.begin();
    for(;it!=Stumap.end();it++)
    {
        analy(it->second);
        cout<<"姓名："<<name<<"\t学号："<<ID<<"\t年龄："<<age<<"\t年级："<<grade;
        cout<<"\t语文："<<chinese<<"\t英语："<<english<<"\t数学："<<math;
        cout<<endl;
    }
    return true;
}
int main()
{
    int i;
    Student stu;
    while(1)
    {
        cout<<"         欢迎使用学生信息管理系统                "<<endl;
        cout<<"==============================================="<<endl;
        cout<<"1、添加学生"<<endl;
        cout<<"2、删除学生"<<endl;
        cout<<"3、显示学生信息"<<endl;
        cout<<"4、清屏"<<endl;
        cout<<"5、保存"<<endl;
        cout<<"==============================================="<<endl;
        cin>>i;
        switch(i)
        {
            case 1: stu.add_msg();break;
            case 2: stu.del_msg();break;
            case 3: stu.show();break;
            case 4:system("Cls");break;
            case 5:stu.save(); break;
        }

    }
    return 0;
}
