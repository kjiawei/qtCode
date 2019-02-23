#include <iostream>
#include <iomanip>//cout控制符
#include <cstdio>
#include <cstring>
//#include <windows.h>

extern "C"//C++里添加C库函数
{
	//#include "myhead.h"
	#include <stdio.h>
}

#define 

class Car
{
public://作用域
	//存储信息的变量-属性
	std::string color;
	
	unsigned int gas_tank;
	
	
	Car(void);//构造器
	void fill_tank(float liter);
	int running(void);
};

//构造器:初始化
Car::Car(void)//不用写函数返回值void
{
	color = "WHITE";
}

void Car::fill_tank(float liter)
{
	gas_tank += liter;
}

int Car::running(void)
{
	std::cout<<"123...\n";
}

int main()
{
	Car mycar;//创建对象
	
	mycar.wheel = 5;//修改构造值
	mycar.setColor("RED");
	
	std::cout<<"mycar color is:"<<mycar.color<<std::endl;//endl自动换行
	std::cout<<"mycar color is:"<<mycar.wheel<<"\n";
	return 0;
} 

