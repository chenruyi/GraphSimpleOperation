#pragma once
#include<stack>

#include<queue>
#include<iostream>
#define MAX_VERTEX_NUM 20	//��󶥵���

#define MAX_NAME_LEN 20		//����������󳤶�
#define MAX_DESC_LEN 1024	//���������󳤶�
struct Vex
{
	int num;			//������
	char name[MAX_NAME_LEN];		//��������
	char desc[MAX_DESC_LEN];	//�������
};
struct Edge
{
	int vex1;	//�ߵĵ�һ������
	int vex2;	//�ߵĵڶ�������
	int weight; //Ȩֵ
};
typedef struct Path 
{
	int vexs[MAX_VERTEX_NUM];//����һ��·��
	Path *next;

}*PathList;


class CGraph
{
private:
	int m_aAdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//---------�ڽӾ���
	Vex m_aVexs[MAX_VERTEX_NUM];				//-----------��������
	int m_nVexNum;			//---------�������


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

