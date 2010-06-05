//NameListTree.h - A class for organizing and searching name lists by location

#pragma once

#include "../People/PeepNames.h"
#include "../People/locations.h"

//includes for implementation
#include <string.h>
#include <stdlib.h>
//#include <iostream>
// ! includes for implementation


struct NameListTreeEntry	{
	short nchildren;
	union	{	NameGenerator*namegen;	NameGenerator*ng;	}	;
	NameListTreeEntry**children;	//array of pointers to children
	NameListTreeEntry*parent;
	inline NameListTreeEntry**Siblings()	{	return(parent/* !=NULL */?parent->children:NULL);	}
	inline short nsiblings(){	return(parent?parent->nchildren-1:0);	}	//number of parent's children not including itself
	//constructor
	void Init(	NameListTreeEntry*sparent,NameGenerator*sng	)	{
		parent=sparent;	children=NULL;	ng=sng;	nchildren=0;
		}
	NameListTreeEntry(	NameListTreeEntry*sparent,NameGenerator*sng	)	{
		Init(sparent,sng);
		}
	NameListTreeEntry()	{
		Init(NULL,NULL);
		}
	// ! constructor
	inline unsigned long ChildrenSize(){	return(sizeof(*children)*nchildren);	}
	void AddChild(	NameListTreeEntry*child	)	{
		if(nchildren)	{	++nchildren;	children=(NameListTreeEntry**)realloc(children,ChildrenSize());	}
		else if(children=(NameListTreeEntry**)malloc(ChildrenSize()))	++nchildren;
		if(nchildren)	{
			children[nchildren-1]=child;
			if(child){	children[nchildren-1]->parent=this;	}
		}
		}//AddChild()
	void UnlinkChild(	short childIndex	)	{	//make it an orphan
		if(children&&childIndex<nchildren)	{
			if(children[childIndex]){
				memmove(&children[childIndex],&children[childIndex+1],(nchildren-1-childIndex)*sizeof(*children));
				--nchildren;
				}
			}
		}//AddChild()
	};//NameListTreeEntry;

#define nnameListTreeStackEntries	0x1000l

class NameListTree	{
	public:
	NameListTreeEntry*root;
	union	{	WorldLocations*locations;	WorldLocations*locs;	};
	NameListTreeEntry**stack;	short stacki;
	//constructor
	NameListTree(WorldLocations*slocs,NameListTreeEntry*sroot){
		locs=slocs;	root=sroot;	stack=NULL;	stacki=-1;
		}
	NameListTree(){
		locs=NULL;	root=NULL;	stack=NULL;	stacki=-1;
		}
	NameListTreeEntry*FindNode(short location){
		NameListTreeEntry*node=NULL;
		if(node=root)	{
			//search tree
			StartStack();
			Push(root);
			while(node=this->Pop()){	//assignment
				if(location==node->ng->location){		// this is the node we are looking for
					KillStack();
					return(node);
					}
				else	{	this->PushChildren(node);	}
				}//while
			KillStack();
			return(node=NULL);
			}//if(rp==root)
		else	{
			return((NameListTreeEntry*)NULL);
			}
		return(node);
		}	//FindNode()
	void StartStack()	{
		if(stack)	free(stack);	stacki=-1;
		stack=(NameListTreeEntry**)malloc(sizeof(root)*nnameListTreeStackEntries);
		}	//StartStack()
	NameListTreeEntry*Pop(){
		if(stacki>=0)	return(stack[stacki--]);
		else			return	NULL;
		}
	bool Push(	NameListTreeEntry*entry	){
		bool rv=stacki<nnameListTreeStackEntries;
		if(rv)	{
			++stacki;
			stack[stacki]=entry;
			}
		return(rv);
		}
	// PushChildren(): Push all the children of an entry onto the stack
	bool PushChildren(NameListTreeEntry*entry){
		bool rv=entry->nchildren>0&&entry->children;
		if(rv)	{
			for(int i=0;i<entry->nchildren&&rv;i++){
				rv=Push(entry->children[i]);
				}
			}
		return(rv);
		}
	void KillStack()	{
		if(stack) free(stack);	stack=NULL;	stacki=-1;
		}
	void AddList(short parentId,NameListTreeEntry*newEntry)	{
		NameListTreeEntry*parentnode;
		if(parentnode=FindNode(parentId))	{	//that is supposed to be an assignment = sign
			parentnode->AddChild(newEntry);		}
		}//AddList()
	void MakeLineageString(char*lineagestr,short bufsz){

		}
	};//NameListTree
