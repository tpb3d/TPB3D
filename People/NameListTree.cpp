//People/NameListTree.cpp

#include "../People/NameListTree.h"

NameListTreeEntry::NameListTreeEntry()
{
   Init(NULL,NULL);
}

NameListTreeEntry::NameListTreeEntry(	NameListTreeEntry*sparent,NameGenerator*sng	)
{
   Init(sparent,sng);
}
// ! constructor

void NameListTreeEntry::Init(	NameListTreeEntry*sparent,NameGenerator*sng	)
{
   parent=sparent;
   mChildren.clear();
   ng = sng;
   //nchildren = 0;
}

void NameListTreeEntry::AddChild(NameListTreeEntry* child)
{
   //if(nchildren)
   //{
   //   ++nchildren;
   //   children=(NameListTreeEntry**)realloc(children,ChildrenSize());
   //}
   //else if(children= new NameListTreeEntry[ChildrenSize()])
   //{
   //   ++nchildren;
   //}
   //if(nchildren)
   //{
   //   children[nchildren-1] = child;
   //   if(child)
   //   {
   //      child->parent = this;
   //   }
   //}
   mChildren.insert(mChildren.end(), child);
   child->parent = this;
}//AddChild()

void NameListTreeEntry::UnlinkChild(NameListTreeEntry* child)
{	//make it an orphan
   //if(children&&childIndex<nchildren)
   //{
   //   if(children[childIndex])
   //   {
   //      memmove(&children[childIndex],&children[childIndex+1],(nchildren-1-childIndex)*sizeof(*children));
   //      --nchildren;
   //   }
   //}
   if( mChildren.size() > 0)
   {
      mChildren.remove (child);
   }
   // else throw new TPBException ("error");
}//AddChild()


NameListTree::NameListTree(WorldLocations*slocs,NameListTreeEntry*sroot)
{
   locs=slocs;
   root=sroot;
   //stack=NULL;
   //stacki=-1;
}

NameListTree::NameListTree()
{
   locs=NULL;
   root=NULL;
   //stack=NULL; mStack's ctor clears it's own
   //stacki=-1;
}

NameListTreeEntry* NameListTree::FindNode(short location)
{
   NameListTreeEntry*node=NULL;
   if(node=root)
   {
      //search tree
      StartStack();
      Push(root);
      while(node=this->Pop())
      {	//assignment
         if(location==node->ng->location){		// this is the node we are looking for
            KillStack();
            return(node);
         }
         else
         {
            this->PushChildren(node);
         }
      }//while

      KillStack();
      return (node=NULL);
   }//if(rp==root)
   else
   {
      return ((NameListTreeEntry*)NULL);
   }
   return(node);
}	//FindNode()

void NameListTree::StartStack()
{
   //if(stack) delete [] stack;
   //stacki=-1;
   //stack= new NameListTreeEntry*[nnameListTreeStackEntries];
   KillStack();
}	//StartStack()

NameListTreeEntry* NameListTree::Pop()
{
//   if(stacki>=0)
//      return stack[stacki--];
//   else
//      return NULL;
   NameListTreeEntry* pChild = NULL;
   if (!mStack.empty())
   {
      pChild = mStack.top();
      mStack.pop();  // remove pCHild
   }
   return pChild;
}

bool NameListTree::Push(NameListTreeEntry* entry)
{
   //bool rv=stacki<nnameListTreeStackEntries;
   //if(rv)
   //{
   //   ++stacki;
   //   stack[stacki]=entry;
   //}
   //return(rv);
   bool bResult = (entry->mChildren.size() > 0);
   if (bResult)
   {
      mStack.push (entry);
   }
   return bResult;
}

// PushChildren(): Push all the children of an entry onto the stack
bool NameListTree::PushChildren(NameListTreeEntry* entry)
{
   //bool rv = entry->mChildren.size>0 && entry->children;
   bool bResult = false;
   if( !entry->mChildren.empty()) //rv)
   {
//      for(int i=0;i<entry->nchildren&&rv;i++)
      std::list<NameListTreeEntry*>::iterator i;
      for (i=entry->mChildren.begin(); i!=entry->mChildren.end(); i++)
      {
         //rv=Push(entry->children[i]);
         Push (*i);
      }
      bResult = true;
   }
   return bResult; // (rv);
}

void NameListTree::KillStack()
{
   //if(stack)
   //   delete [] stack;

   //stack=NULL;
   //stacki=-1;
   while (!mStack.empty())
      mStack.pop();
}

void NameListTree::AddList(short parentId,NameListTreeEntry*newEntry)
{
   NameListTreeEntry* parentnode;
   if(parentnode = FindNode(parentId))
   {	//that is supposed to be an assignment = sign
      parentnode->AddChild(newEntry);
   }
}//AddList()

void NameListTree::MakeLineageString(char*lineagestr,short bufsz)
{
}

