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


inline void ShowEdge(Edge eg)
{
	char V1 = (char)eg.vex1 + 'A', V2 = (char)eg.vex2 + 'A';
	cout << V1 << "区->" << V2 << "区" << "\t" << eg.weight << "米" << endl;

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
		ShowEdge(edge[j]);
		//cout << "<" << edge[j].vex1 << "," << edge[j].vex2 << ">  =" << edge[j].weight << endl;
	}

}
inline void ShowPathList(PathList pList,const int n)
{		
	char ch[MAX_VERTEX_NUM];
	for (int i = 0; i < n; i++)
	{
		ch[i] = pList->vexs[i] + 'A';
		cout << ch[i] << "区-->";
	}
	cout << "\b\b\b     \n";
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

	int i = 1, n = this->m_Graph.GetVexNum();
	while ( plist->next != NULL)
	{		
		cout << "路线" << i << ":";
		ShowPathList(plist,n);
		plist = plist->next;
		i++;
	}
}

void CTourism::FindShortPath(void)
{
	int nVexStart, nVexEnd, pathLength=0;
	
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
	
	Edge edge[MAX_VERTEX_NUM];	
	int n = m_Graph.FindShortPath(nVexStart, nVexEnd, edge);	
	if (n > 0)
	{
		for (int i = 0; i < n; i++)
		{
			ShowEdge(edge[i]);
			pathLength += edge[i].weight;
		}
		cout << "最短路径长度为：" << pathLength << endl;
	}
	else 
	{
		
		cout << "未查到，请确定是否输入错误" << endl;
	}
	
}


void CTourism::DesignPath(void)
{
	Edge edge[MAX_VERTEX_NUM];
	int k=m_Graph.MiniSpanTree(edge);
	cout << "在以下景点之间铺设电路：" << endl;
	for (int i=0;i<k; i++)
	{
		ShowEdge(edge[i]);
	}	
}

CTourism::CTourism()
{
	
}


CTourism::~CTourism()
{
}
