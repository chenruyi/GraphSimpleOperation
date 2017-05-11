#include<iostream>
#include"Tourism.h"
using namespace std;
int main() 
{

	stack <int> stk;
	int choice;
	CTourism tourisum;
	tourisum.CreateGraph();
	while(true)
	{
	cout << "======景区信息管理系统=========" << endl;
	cout << "1.创建景区景点图" << "\n"
		<< "2.查询景点信息" << "\n"
		<< "3.旅游景点导航" << "\n"
		<< "4.搜索最短路径" << "\n"
		<< "5.铺设电路规划" << "\n"
		<< "0.退出" << endl;
	cout << "请输入操作编号（0~5）：";
	while (!(cin >> choice))
	{
		cout << "输入格式错误！！" << endl;
		cin.clear();
		while (cin.get() != '\n')
			continue;
	}
	switch (choice)
	{
		case 1:
		{
			//tourisum.CreateGraph();
			tourisum.GetSpotInfo();
			break;
		}
		case 2:
		{
			cout << "------查询景点------" << endl;
			int ch = 0;
			cout << "请输入你所找的景区编号：";
			cin >> ch;
			cout << "查询结果：" << endl;
			tourisum.GetSpotInfo(ch);
			
			break;
		}
		case 3:
		{
			cout << "-------景区景点导航-----" << endl;
			tourisum.TravelPath();
			break;
		}
		case 4:
		{
			cout << "--------搜索最短路径-------" << endl;
			tourisum.FindShortPath();
			break;
		}
		case 5:
		{
			cout << "--------铺设电路规划-----------"<<endl;
			tourisum.DesignPath();
			break;
		}
		case 0:
		{
			exit(0);
			break;
		}
		default: 
		{
			cout << "所选不存在，请重新输入；" << endl;
			break;
		}
	}
	}

}
