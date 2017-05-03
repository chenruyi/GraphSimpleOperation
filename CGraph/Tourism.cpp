#include "Tourism.h"
#include<iostream>
#include<fstream>
using namespace std;

void CTourism::CreateGraph()
{
	Vex vex;	//������Ϣ
	Edge edge;	//��·��Ϣ
	
	ifstream filein;
	//��þ�����Ϣ,��ȡ�ļ���Vex.txt
	
	char vex_num[20];//��ʱ���vex.num
	filein.open("Vex.txt", ios::in);
	if (!filein.eof())
	{
		char AllVexNum[20];
		filein.getline(AllVexNum, 20, '\n');
		//cout << "������Ŀ��" << AllVexNum << endl;
	}
	while (!filein.eof())
	{
		filein.getline(vex_num, 20, '\n');
		sscanf_s(vex_num, "%d", &(vex.num));
		filein.getline(vex.name, MAX_NAME_LEN, '\n');
		filein.getline(vex.desc, MAX_DESC_LEN, '\n');
		m_Graph.InsertVex(vex);

		//cout << vex.num<<"\t" <<vex.name<< "\t" << vex.desc << endl;
	}

	filein.clear();
	filein.close();
//	ifstream filein;
	//��õ�·��Ϣ,��ȡ�ļ���Edge.txt
	char edge_vex1[20];//��ʱ���edge.vex1;
	char edge_vex2[20];//��ʱ���edge.vex2;
	char edge_weight[20];//��ʱ���edge.weight;

	filein.open("Edge.txt", ios::in);
	while (!filein.eof())
	{
		filein.getline(edge_vex1, 20, '\t');
		sscanf_s(edge_vex1, "%d", &(edge.vex1));
		filein.getline(edge_vex2, 20, '\t');
		sscanf_s(edge_vex2, "%d", &(edge.vex2));
		filein.getline(edge_weight, 20, '\n');
		sscanf_s(edge_weight, "%d", &(edge.weight));
		//cout <<"<" <<edge.vex1<<","<<edge.vex2<<">"<<"\t"<<edge.weight << endl;
		m_Graph.InsertEdge(edge);

	}
	filein.clear();
	filein.close();

}



void CTourism::GetSpotInfo(void) 
{
	//������еľ�����Ϣ
	int i, j = m_Graph.GetVexNum();
	for (i = 0; i < j; i++)
	{
		Vex vex= m_Graph.GetVex(i);
		cout << vex.num<<"\t" <<vex.name<< "\t" << vex.desc << endl;
	}
	
}

void CTourism::GetSpotInfo(int ch)
{
	int i = m_Graph.GetVexNum();
	if (ch >=i)
	{
		cout << "��Ų�����" << endl;
	}
	
	Edge *edge = (Edge*)malloc( i* sizeof(Edge));
	i = m_Graph.FindEdge(ch, edge);
	for (int j = 0; j <i; j++)
	{
		cout << "<" << edge[j].vex1 << "," << edge[j].vex2 << ">  =" << edge[j].weight << endl;
	}

}
inline void ShowPathList(PathList pList)
{
	
	for (int i = 1; pList!= NULL; i++)
	{
		int n = 7;
		
		cout << "·��" << i << ": ";
		for (int j = 0; j<n; j++)
		{
			switch ((pList->vexs[j]))
			{
			case 0:
			{
				cout << "A��-->";
				break;
			}
			case 1:
			{
				cout << "B��-->";
				break;
			}
			case 2:
			{
				cout << "C��-->";
				break;
			}
			case 3:
			{
				cout << "D��-->";
				break;
			}
			case 4:
			{
				cout << "E��-->";
				break;
			}
			case 5:
			{
				cout << "F��-->";
				break;
			}
			case 6:
			{
				cout << "G��-->";
				break;
			}
			default:
			{
				cout << "\b\b\b\b\b\b\b          "; 
			}
			}
		}
		cout << "\b\b\b     \n";
		pList = pList->next;
	}

}
void CTourism::TravelPath()
{
	int pos;
	cout << "0--A��" << "\n"
		<< "1--B��" << "\n"
		<< "2--C��" << "\n"
		<< "3--D��" << "\n"
		<< "4--E��" << "\n"
		<< "5--F��" << "\n"
		<< "6--G��" << endl;
	cout << "��������ʼ���ţ�" ;
	while (!(cin >> pos))
	{
		cout << "�����ʽ���󣡣�" << endl;
		cin.clear();
		while (cin.get() != '\n')
			continue;
	}
	PathList plist = (PathList)malloc(sizeof(PathList));
	plist->next = NULL;
	
	m_Graph.DFSTraverse(pos, plist);
	
	if (plist != NULL)
	{
		ShowPathList(plist);
	}
	
}

void CTourism::FindShortPath(void)
{
	int nVexStart, nVexEnd, pathLength;
	Edge *edge = (Edge*)malloc(sizeof(Edge)*m_Graph.GetVexNum());
	cout << "0--A��" << "\n"
		<< "1--B��" << "\n"
		<< "2--C��" << "\n"
		<< "3--D��" << "\n"
		<< "4--E��" << "\n"
		<< "5--F��" << "\n"
		<< "6--G��" << endl;
	cout << "���������ı�ţ�";
	cin >> nVexStart;
	cout << "�������յ�ı�ţ�";
	cin >> nVexEnd;
	 pathLength=m_Graph.FindShortPath(nVexStart, nVexEnd,edge);
	 
	 //ShowPathList();
}

CTourism::CTourism()
{
	
}


CTourism::~CTourism()
{
}
