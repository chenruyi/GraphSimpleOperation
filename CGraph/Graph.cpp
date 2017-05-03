#include "Graph.h"
#include<stack>

#include<queue>
#include<iostream>
using namespace std;

void CGraph::Init(void)
{
	m_nVexNum = 0;
for (int i = 0; i < MAX_VERTEX_NUM; i++)
{
	for (int j = 0; j < MAX_VERTEX_NUM; j++)
	{
		m_aAdjMatrix[i][j] = 0;
	}
}
}

bool CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == MAX_VERTEX_NUM)
	{
		return false;//已达到最大值
	}
	m_aVexs[m_nVexNum++] = sVex;
	return true;
}

bool CGraph::InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex2 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex1 >= m_nVexNum)
	{
		return false;//越界
	}
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

Vex CGraph::GetVex(int x)
{

	return m_aVexs[x];
}

int CGraph::FindEdge(int v, Edge* &aEdge)
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_aAdjMatrix[v][i] != 0)
		{
			aEdge[k].vex1 = v;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_aAdjMatrix[v][i];
			k++;
		}
	}
	return k;
}

int CGraph::GetVexNum(void)
{
	int num = this->m_nVexNum;
	return num;
}
///改进的DFS方法
void CGraph::DFS(int v, bool bVisited[], PathList &pList, int &index,int aPath[])
{
	
	
	bVisited[v] = true;
	aPath[index++] = v;
	//for (int i = 0; i < this->m_nVexNum; i++)
	//{
	//	if (bVisted[i] != true && (m_aAdjMatrix[i][v] != 0 || m_aAdjMatrix[v][i] != 0))
	//	{
	//		DFS(i, bVisted, pList,index);
	//	}
	//}
	////查找多条路线
	bool flag = true;//所有顶点是否都被访问
	for (int j = 0; j < this->m_nVexNum; j++)
	{
		if (bVisited[j] == false)
		{
			flag = false; break;
		}
	}
	if (flag)
	{	
		for (int j = 0; j < this->m_nVexNum; ++j)
		{
			pList->vexs[j] = aPath[j];
		}
		pList->next = (PathList)malloc(sizeof(Path));
		pList->next->next = NULL;
		pList = pList->next;
	}
	else
	{
		for (int i = 0; i < this->m_nVexNum; i++)
		{			
			if (bVisited[i] != true && (m_aAdjMatrix[i][v] != 0|| m_aAdjMatrix[v][i] != 0))
			{	
				DFS(i, bVisited, pList,index,aPath);
				bVisited[i] = false;
				index--;
			}
		}
	}
}

void CGraph::DFSTraverse(int nVex, PathList & pList)
{
	int nIndex = 0;
	PathList listhead = pList;	
	bool bVisited[MAX_VERTEX_NUM] = { false };
	//DFS(nVex, aVisted, nIndex, listhead);

	int aPath[MAX_VERTEX_NUM];
	//查找多条路径
	//正确输出
	//DFS(nVex, bVisited, aPath, nIndex, listhead);
	
	
	DFS(nVex, bVisited, listhead, nIndex,aPath);
}

int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge *& aPath)
{
	int min=INT16_MAX;
	int i = 0, w = 0, v;
	bool aVisited[MAX_VERTEX_NUM] = { false };
	v = nVexStart;
	for (i = 0; i < this->m_nVexNum; i++)
	{
		if (m_aAdjMatrix[v][i] !=0 )
		{
			min =min< m_aAdjMatrix[v][i] ? min: m_aAdjMatrix[v][i];
			aVisited[i] = true;
			aVisited[v] = true;		
		}
	}	
	
	for (i = 0; i < this->m_nVexNum; i++)
	{
		for (w = 0; w < this->m_nVexNum; w++)
		{
			if (this->m_aAdjMatrix[v][w] != 0 && (!aVisited[i]))
				if (min > m_aAdjMatrix[nVexStart][w])
				{
					aVisited[w] = true;
					min = m_aAdjMatrix[nVexStart][w];
				}
		}
		if (min + m_aAdjMatrix[i][w] < min)
		{
			min = min + m_aAdjMatrix[i][w];
		}

	}
	return min;
}

CGraph::CGraph()
{
	Init();
}


CGraph::~CGraph()
{
}
