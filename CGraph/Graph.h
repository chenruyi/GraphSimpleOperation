#pragma once
#include<stack>

#include<queue>
#include<iostream>
#define MAX_VERTEX_NUM 20	//最大顶点数

#define MAX_NAME_LEN 20		//景点名字最大长度
#define MAX_DESC_LEN 1024	//景点介绍最大长度
struct Vex
{
	int num;			//景点编号
	char name[MAX_NAME_LEN];		//景点名字
	char desc[MAX_DESC_LEN];	//景点介绍
};
struct Edge
{
	int vex1;	//边的第一个顶点
	int vex2;	//边的第二个顶点
	int weight; //权值
};
typedef struct Path 
{
	int vexs[MAX_VERTEX_NUM];//保存一条路径
	Path *next;

}*PathList;


class CGraph
{
private:
	int m_aAdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//---------邻接矩阵
	Vex m_aVexs[MAX_VERTEX_NUM];				//-----------顶点数组
	int m_nVexNum;			//---------顶点个数


public:
	void Init(void);
	bool InsertVex(Vex sVex);
	bool InsertEdge(Edge sEdge);
	Vex GetVex(int x);
	
	int FindEdge(int v, Edge* &aEdge);
	int GetVexNum(void);
	
	//void DFS(int nVex, bool bVisted[], PathList &pList, int &index);//
	void DFS(int nVex, bool bVisted[], PathList &pList, int &index,int aPath[]);//
	void DFSTraverse(int nVex, PathList &pList);
	int FindShortPath(int nVexStart, int nVexEnd, Edge* &aPath);
	CGraph();
	~CGraph();
};

