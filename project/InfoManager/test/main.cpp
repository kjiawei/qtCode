#include <iostream>
#include <fstream>//������Ϣ�������ļ�
#include <list>
#include <map>

//�������˼·:��ѯѧ���ɼ�(Ŀ��)
//����ģ��:list����
//�������������߼�ʵ��:��ɾ��� �ļ�������չ ����

//ѧ���ɼ�����ϵͳ
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
//����ѧ����Ϣ����ģ��

//ѧ����
class Student
{
public:
    Student(string name,float score);
    //~Student();
    void showStudent(string name);
    void showScore(string name);//const &��ı�ʵ��
    bool insertInfo(/*const string &name,int pid,int sex,float score,int grade*/);
    bool deleteInfo();
    bool updateInfo();
    void pjScore();
    void totalScore();
    void showHelp();
    void tongji();
    void exitSys();
    void sortScore();//����������
protected:

private:
    string name;//����
    //string address;//��ַ
    int pid;//ѧ��
    //int birthdate;//����
    int sex;//�Ա�
    float score;//����
    int grade;//�꼶
    string className;//�γ�
};

Student::Student(string name = "123",float score = 0.0)
{
    cout<<"************ѧ���ɼ�����ϵͳ*************"<<endl;
    cout<<"  ������Ϣ(i)  "<<" ��ѯ�ɼ�(s)  "<<"  ����(h)"<<endl;//cout��ʽ����
    cout<<"  ɾ����Ϣ(w)  "<<" ƽ���ɼ�(p)  "<<"����ͳ��(r)"<<endl;
    cout<<"  �޸���Ϣ(c)  "<<" �ֳܷɼ�(t)  "<<"�˳�ϵͳ(q)"<<endl;
    cout<<"****************************************"<<endl;

    this->name = name;
    this->score = score;
}

bool Student::insertInfo(/*const string &name,int pid,int sex,float score,int grade*/)
{
    cout<<"������ѧ����Ϣ(����,����),����:ok+�س�"<<endl;
    string stuinfo;//string student[];//ѧ����ϸ��Ϣ��ͬ������δ���
    //ofstream outfile("E:/qtProject/test/studentfile.txt");//��һ������д��
    ifstream infile;//��ȡ�����ļ�
    //infile.open("E:/qtProject/test/score.txt");
    ofstream outfile("E:/qtProject/test/studentfile2.txt");
    char studentInfo[50];//����ѧ����Ϣ����
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
        cin>>stuinfo;//Ϊʲô��������
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
    //���ݵĻ�ȡ:���� �����ļ�
//    ifstream file;
//    char stubuf[200];//���ѧ����Ϣ������
//    file.open("E:/qtProject/test/student.txt");
//    while(!file.eof)
//    {
//        file.getline(buf,100);
//        string str = buf;
//        str.find(" ");//�ո�Ϊÿ����¼�ķָ��
//        //δ����
//    }
//    file.close();

    //string stuinfo;//ѧ����Ϣ
    //cin>>stuinfo;
    //while(stuinfo != ("quit"|"q"))

    //��ѧ�����ݵĲ���
    Student stu/*("jerry",12.2)*/;//����һ��ѧ��  list
//    Student stu2("jerry2",12.3);
//    stu.showScore("jerry");
//    stu2.showScore("jerry2");
    stu.insertInfo();

//    map<string,float> studentmap;//ѧ����������:������ѧ��ӳ��
//    studentmap.insert(pair<string,float>("xiaoxin",60.0));//�����ظ�����
//    map<string,float>::iterator iter;//map������
//    for(iter = studentmap.begin();iter != studentmap.end();iter++)
//    {
//        cout<<"student name:"<<iter->first<<endl;
//        cout<<"student score:"<<iter->second<<endl;
//    }

    return 0;
}

