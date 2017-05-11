#include "Graph.h"
#include<string>
#include<iostream>
using namespace std;

void CGraph::Init(void)
{
	m_nVexNum = 0;
for (int i = 0; i < MAX_VERTEX_NUM; i++)
{
	for (int j = 0; j < MAX_VERTEX_NUM; j++)
	{
		m_aAdjMatrix[i][j] = INT16_MAX;
	
	}
	m_aAdjMatrix[i][i] = 0;
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
		if (i == v) continue;
		if (m_aAdjMatrix[v][i] <INT16_MAX)
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
			if ((m_aAdjMatrix[v][i] <INT16_MAX || m_aAdjMatrix[i][v] < INT16_MAX) && !bVisited[i])
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
	
	
	
	DFS(nVex, bVisited, listhead, nIndex,aPath);
}


inline string Int2Str(int v)
{
	string str="";
	int i = 0;
	while(i=v/10)
	{
		str += '0' + i;
	}
	str+='0'+v  ;	
	return str;
}

int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int v = 0, w = 0, u = 0, i = 0;
	int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	aPath[i++].vex1 = nVexStart;
	string Ph[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	
	for (v = 0; v < this->m_nVexNum; v++)
	{
		for (w = 0; w < this->m_nVexNum; w++)
		{
			D[v][w] = this->m_aAdjMatrix[v][w];
			if (D[v][w] < INT16_MAX)
			{
				if (v == w) continue;
				//v到w有直接路径
				Ph[v][w]= Int2Str(v)+Int2Str(w);
				Ph[w][v]= Int2Str(w)+ Int2Str(v);
			}			
		}		
	}
	for (u = 0; u < this->m_nVexNum; u++)
	{
		for (v = 0; v < this->m_nVexNum; v++)
		{
			for (w = 0; w < this->m_nVexNum; w++)
			{
				if (D[v][u] + D[u][w] < D[v][w])//v经u到w更短
				{
					D[v][w] = D[v][u] + D[u][w];	
					Ph[v][w] = Ph[v][u];
					Ph[v][w] += Ph[u][w];
				}
			}
		}		
	}	
	//Ph为所有最短路径信息	
	string str = Ph[nVexStart][nVexEnd];
	int m,z,n = str.length() - 1;
	for ( m = 0,z=0; m <= n;m+=2,z++ )
	{
		aPath[z].vex1 = str[m] - '0';
		aPath[z].vex2 = str[m+1] - '0';
		aPath[z].weight = this->m_aAdjMatrix[aPath[z].vex1][aPath[z].vex2];		
	}	
	return z;
}

int CGraph::FindShortPath(int nVexStart, int nVexEnd, int Path[])
{
	
	int v = 0, w = 0, u = 0, i = 0;
	int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	
	string Ph[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	for (v = 0; v < this->m_nVexNum; v++)
	{
		for (w = 0; w < this->m_nVexNum; w++)
		{
			D[v][w] = this->m_aAdjMatrix[v][w];
			if (D[v][w] < INT16_MAX)
			{
				if (v == w) continue;
				//v到w有直接路径
				Ph[v][w] = Int2Str(v);
				Ph[w][v] = Int2Str(w);
			}

		}

	}

	for (u = 0; u < this->m_nVexNum; u++)
	{
		for (v = 0; v < this->m_nVexNum; v++)
		{
			for (w = 0; w < this->m_nVexNum; w++)
			{
				if (D[v][u] + D[u][w] < D[v][w])//v经u到w更短
				{
					D[v][w] = D[v][u] + D[u][w];
					Ph[v][w] = Ph[v][u];
					Ph[v][w] += Ph[u][w];

				}
			}
		}
	}
	for (v = 0; v < this->m_nVexNum; v++)
		for (w = 0; w < this->m_nVexNum; w++)
		{
			Ph[v][w] += Int2Str(w);
		}

	//Ph为所有最短路径信息	
	string str = Ph[nVexStart][nVexEnd];
	int n = Ph[nVexStart][nVexEnd].length() - 1;
	while (n >= 0)
	{
		Path[n] = str[n] - '0';
		n--;
	}
	return D[nVexStart][nVexEnd];
}

int CGraph::MiniSpanTree(Edge aPath[])
{
	//标志数组
	bool bVisited[MAX_VERTEX_NUM] = { false };
	int min = INT16_MAX;
	int k = 0;
	//V0加入集合
	bVisited[0] = true;
	int nVex1, nVex2,n=0;
	for ( k = 0; k < this->m_nVexNum-1; k++)
	{
		min = INT16_MAX;
		for (int i = 0; i < this->m_nVexNum; i++)
		{
			if (bVisited[i])
			{
				n++;
				for (int j = 0; j < this->m_nVexNum; j++)
				{
					if( (!bVisited[j])&& (this->m_aAdjMatrix[i][j] < min) && (this->m_aAdjMatrix[j][i] < min))	
						{
							min = this->m_aAdjMatrix[i][j];	
							nVex1 = i; nVex2 = j;
						}					
				}
			}
		}
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = min;
		
		bVisited[nVex1] = true;
		bVisited[nVex2] = true;


	}
	return k;
}

CGraph::CGraph()
{
	Init();
}


CGraph::~CGraph()
{
}
