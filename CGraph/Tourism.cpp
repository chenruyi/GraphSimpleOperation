#include "Tourism.h"
#include<iostream>
#include<fstream>
using namespace std;

void CTourism::CreateGraph()
{
	Vex vex;	//景点信息
	Edge edge;	//道路信息
	
	ifstream filein;
	//获得景点信息,读取文件：Vex.txt
	
	char vex_num[20];//临时存放vex.num
	filein.open("Vex.txt", ios::in);
	if (!filein.eof())
	{
		char AllVexNum[20];
		filein.getline(AllVexNum, 20, '\n');
		//cout << "景区数目：" << AllVexNum << endl;
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
	//获得道路信息,读取文件：Edge.txt
	char edge_vex1[20];//临时存放edge.vex1;
	char edge_vex2[20];//临时存放edge.vex2;
	char edge_weight[20];//临时存放edge.weight;

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
	//获得所有的景点信息
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
		cout << "编号不存在" << endl;
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
		
		cout << "路线" << i << ": ";
		for (int j = 0; j<n; j++)
		{
			switch ((pList->vexs[j]))
			{
			case 0:
			{
				cout << "A区-->";
				break;
			}
			case 1:
			{
				cout << "B区-->";
				break;
			}
			case 2:
			{
				cout << "C区-->";
				break;
			}
			case 3:
			{
				cout << "D区-->";
				break;
			}
			case 4:
			{
				cout << "E区-->";
				break;
			}
			case 5:
			{
				cout << "F区-->";
				break;
			}
			case 6:
			{
				cout << "G区-->";
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
	cout << "0--A区" << "\n"
		<< "1--B区" << "\n"
		<< "2--C区" << "\n"
		<< "3--D区" << "\n"
		<< "4--E区" << "\n"
		<< "5--F区" << "\n"
		<< "6--G区" << endl;
	cout << "请输入起始点编号：" ;
	while (!(cin >> pos))
	{
		cout << "输入格式错误！！" << endl;
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
	cout << "0--A区" << "\n"
		<< "1--B区" << "\n"
		<< "2--C区" << "\n"
		<< "3--D区" << "\n"
		<< "4--E区" << "\n"
		<< "5--F区" << "\n"
		<< "6--G区" << endl;
	cout << "请输入起点的编号：";
	cin >> nVexStart;
	cout << "请输入终点的编号：";
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
