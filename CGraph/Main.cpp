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
	cout << "======������Ϣ����ϵͳ=========" << endl;
	cout << "1.������������ͼ" << "\n"
		<< "2.��ѯ������Ϣ" << "\n"
		<< "3.���ξ��㵼��" << "\n"
		<< "4.�������·��" << "\n"
		<< "5.�����·�滮" << "\n"
		<< "0.�˳�" << endl;
	cout << "�����������ţ�0~5����";
	while (!(cin >> choice))
	{
		cout << "�����ʽ���󣡣�" << endl;
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
			cout << "------��ѯ����------" << endl;
			int ch = 0;
			cout << "�����������ҵľ�����ţ�";
			cin >> ch;
			cout << "��ѯ�����" << endl;
			tourisum.GetSpotInfo(ch);
			
			break;
		}
		case 3:
		{
			cout << "-------�������㵼��-----" << endl;
			tourisum.TravelPath();
			break;
		}
		case 4:
		{
			cout << "--------�������·��-------" << endl;
			tourisum.FindShortPath();
			break;
		}
		case 5:
		{
			cout << "--------�����·�滮-----------"<<endl;
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
			cout << "��ѡ�����ڣ����������룻" << endl;
			break;
		}
	}
	}

}
