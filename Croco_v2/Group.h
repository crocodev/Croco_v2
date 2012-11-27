#pragma once
#include "CrocoBoardGame.h"

#include <vector>
using namespace std;

class CGroup
{
public:

	CGroup(void)
	{
		curGroupPosition = 0;		
		nextGroupPtr = NULL;

		//groupNumber = 0;		
		//nextGroupPosition = 0;
		//curGroupPositionType = 0;
	}

	~CGroup(void)
	{
	}

	int ChangeCurGroupPos(int val)
	{
		curGroupPosition += val;
		return curGroupPosition;
	}

	bool operator!=(const CGroup & other)
	{
		if(curGroupPosition != other.CurGroupPosition() && nextGroupPtr == other.NextGroupPtr())
			return true;
		else
			return false;
	}

// fields
	CGroup * NextGroupPtr() const { return nextGroupPtr; }
	void NextGroupPtr(CGroup * val) { nextGroupPtr = val; }	
	int CurGroupPosition() const { return curGroupPosition; }
	void CurGroupPosition(int val) { curGroupPosition = val; }

	//	int NextGroupPosition() const { return nextGroupPosition; }
	//	void NextGroupPosition(int val) { nextGroupPosition = val; }
	// 	int CurGroupPositionType() const { return curGroupPositionType; }
	// 	void CurGroupPositionType(int val) { curGroupPositionType = val; }
	// 	int GroupNumber() const { return groupNumber; }
	//	void GroupNumber(int val) { groupNumber = val; }

private:
	int curGroupPosition;		// текущая позиция группы на поле		
	CGroup * nextGroupPtr;		// указатель на следующую команду

	//int curGroupPositionType;	// 0 - describe		1 - paint	2 - show		
	//int nextGroupPosition;	// позиция группы в результате следующего хода	
	//int groupNumber;			// номер группы по порядку	
	
};

class CGroupsSnapshot
{
public:
	CGroupsSnapshot(){ ind = -1;}

	CGroupsSnapshot(CGroup * grar)
	{
		for (int i = 0; i < 4; i++)
		{
			groupArray[i] = grar[i]; 
		}
		ind = -1;
	}

	int CompareSnapshots(CGroupsSnapshot* gs, int & retGroupNum)	// return delta position
	{
		for (ind++; ind < 4; ind++)
		{
			if(gs->groupArray[ind] != groupArray[ind])
			{
				retGroupNum = ind;				
				return (gs->groupArray[ind].CurGroupPosition() - groupArray[ind].CurGroupPosition());
			}
		}
		
		return 0;
	}

	CGroup groupArray[4];
private:
	int ind;
};

class CSnapshots
{
public:
	CSnapshots(){ind = 0; curActGlobal = 0;}
	~CSnapshots(){}

	void PushSnapshot(CGroupsSnapshot & gs)
	{
		if(vec.size() > ind)
		{
			vec.erase(vec.begin() + ind, vec.end());
			actNum.erase(actNum.begin() + ind, actNum.end());
		}
		
		vec.push_back(gs);
		actNum.push_back(curActGlobal);
		ind++;
	}

	void PopSnapshot(CGroupsSnapshot & gs)
	{
		if(ind > 1 && vec.size() > 1)
		{			
			//vec.pop_back();
			//gs = vec.back();
			
			ind--;			
			gs = vec.at(ind-1);
		}		
	}

	void GetSnapshot(CGroupsSnapshot & gs)
	{
		if(ind > 1 && vec.size() > 1)
		{			
			//vec.pop_back();
			//gs = vec.back();

			//ind--;			
			gs = vec.at(ind-1);
		}		
	}

	void PopFSnapshot(CGroupsSnapshot & gs)
	{
		if(vec.size() > ind)
		{			
			//vec.pop_back();		
			//gs = vec.back();
			
			ind++;
			gs = vec.at(ind-1);
		}		
	}

	void IncCurAct()
	{
		curActGlobal++;
	}

	int getCurActGlobal()
	{
		return actNum.at(ind-1);
	}

	int getFCurActGlobal()
	{
		if(actNum.size() > ind )
			return  actNum.at(ind);
		else
			return  actNum.at(ind-1);
	}

private:
	vector<CGroupsSnapshot> vec;
	vector<int> actNum;	
	unsigned int ind;
	int curActGlobal;
	//int tmpInd;
};

