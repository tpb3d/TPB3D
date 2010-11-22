//NameListTree.h - A class for organizing and searching name lists by location

#pragma once

#include "../People/PeepNames.h"
#include "../People/Locations.h"

//includes for implementation
#include <string>
#include <list>
#include <stack>
#include <cstdlib>
//#include <iostream>
// ! includes for implementation


struct NameListTreeEntry
{
   // implementation
	//unsigned short nchildren;
	union	{	NameGenerator*namegen;	NameGenerator*ng;	}	;

	//NameListTreeEntry**children;	//array of pointers to children
   std::list<NameListTreeEntry*> mChildren;
	NameListTreeEntry* parent;

   // properties
	//inline NameListTreeEntry** Siblings()	{	return(parent/* !=NULL */? parent->mChildren : NULL);	}
	inline short nsiblings(){	return(parent ? (short)(parent->mChildren.size()-1) : 0);	}	//number of parent's children not including itself
   //inline unsigned long ChildrenSize(){	return(sizeof(*children)*nchildren);	}

	//constructor
	NameListTreeEntry(	NameListTreeEntry*sparent,NameGenerator*sng	);
	NameListTreeEntry();
	// ! constructor

	void Init(	NameListTreeEntry*sparent,NameGenerator*sng	);
	void AddChild(	NameListTreeEntry*child	);

   //AddChild()
	void UnlinkChild(NameListTreeEntry* child);		//make it an orphan
};//NameListTreeEntry;

#define nnameListTreeStackEntries	0x1000l

class NameListTree
{
	public:
	NameListTreeEntry*root;
	union	{	WorldLocations*locations;	WorldLocations*locs;	};

	//NameListTreeEntry**stack;	short stacki;
   std::stack<NameListTreeEntry*> mStack;

	//constructor
	NameListTree(WorldLocations*slocs,NameListTreeEntry*sroot);
	NameListTree();

	NameListTreeEntry* FindNode(short location);
	void StartStack ();
	NameListTreeEntry* Pop();
	bool Push (NameListTreeEntry*entry);
	// PushChildren(): Push all the children of an entry onto the stack
	bool PushChildren (NameListTreeEntry*entry);
	void KillStack ();
	void AddList (short parentId,NameListTreeEntry*newEntry);
	void MakeLineageString (char*lineagestr,short bufsz);
};//NameListTree
