#include <iostream>

using namespace std;

class Parent
{
public:
	Parent();
	void showinfo();
	int pcount;
	~Parent();
protected:
	int pnumber;
private:
	int pdata;
};

class Child:public Parent//公有继承
{
public:
	void show()
	{
		cout<<pcount<<pnumber<<endl;
	}
protected:

private:
	int cdata;
};

int main()
{
	Parent p;
	p.pcount = 10;
	
	cout<<sizeof(p)<<endl;
	
	Child c;
	c.pcount = 100;
	cout<<sizeof(c)<<endl;
	
	cout<<"123"<<endl;
	return 0;
}