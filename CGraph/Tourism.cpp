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


inline void ShowEdge(Edge eg)
{
	char V1 = (char)eg.vex1 + 'A', V2 = (char)eg.vex2 + 'A';
	cout << V1 << "��->" << V2 << "��" << "\t" << eg.weight << "��" << endl;

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
		cout << ch[i] << "��-->";
	}
	cout << "\b\b\b     \n";
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

	int i = 1, n = this->m_Graph.GetVexNum();
	while ( plist->next != NULL)
	{		
		cout << "·��" << i << ":";
		ShowPathList(plist,n);
		plist = plist->next;
		i++;
	}
}

void CTourism::FindShortPath(void)
{
	int nVexStart, nVexEnd, pathLength=0;
	
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
	
	Edge edge[MAX_VERTEX_NUM];	
	int n = m_Graph.FindShortPath(nVexStart, nVexEnd, edge);	
	if (n > 0)
	{
		for (int i = 0; i < n; i++)
		{
			ShowEdge(edge[i]);
			pathLength += edge[i].weight;
		}
		cout << "���·������Ϊ��" << pathLength << endl;
	}
	else 
	{
		
		cout << "δ�鵽����ȷ���Ƿ��������" << endl;
	}
	
}


void CTourism::DesignPath(void)
{
	Edge edge[MAX_VERTEX_NUM];
	int k=m_Graph.MiniSpanTree(edge);
	cout << "�����¾���֮�������·��" << endl;
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
