#pragma once
#include"Graph.h"
#include<stack>
#include<queue>
class CTourism
{
private:
		CGraph m_Graph;

public:
	void CreateGraph(void);
	void GetSpotInfo(void);
	void GetSpotInfo(int ch);
	void TravelPath();
	void FindShortPath(void);
	void DesignPath(void);
	CTourism();
	~CTourism();
};

