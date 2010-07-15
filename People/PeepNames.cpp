//People/PeepNames.cpp - Classes for generating peep names - surname and first names

#include "../People/PeepNames.h"
#include <iostream>
#include <stdio.h>
#include "../Types/Token.h"
#include "../People/Locations.h"
#include "../People/NameListTree.h"

//  NameString method implementations

char* NameString::Text()
{
   return(&buffer[0]);
}

NameString::NameString()
{
   memset(&buffer[0],0,sizeof(buffer));
}

void NameString::	operator =(char*s)
{
   strncpy(&buffer[0],s,personNameMaxSize);
}

// ! NameString method implementations

// NameEntry method implementations

void NameEntry::Init(char*n,long w)
{
   name = n;
   weight= (short)w;
}

NameEntry::NameEntry(char*n,long w)
{
   Init(n,w);
}

void NameEntry::Init(char*n,long w,Name2Features a1,Name2Features a2,Name2Features a3,Name2Features a4)
{
#define a(n) appearances[n-1]=a##n
   a(1);	a(2);	a(3);	a(4);
#undef a
   Init(n,w);
}

NameEntry::NameEntry(char*n,long w,Name2Features a,Name2Features b,Name2Features c,Name2Features d)
{
   Init(n,w,a,b,c,d);
}

NameEntry::NameEntry(char*n,long w,Name2Features a,Name2Features b,Name2Features c)
{
   Name2Features d(0,0,false);
   Init(n,w,a,b,d,d);
}

NameEntry::NameEntry(char*n,long w,Name2Features a,Name2Features b)
{
   Name2Features d(0,0,false);
   Init(n,w,a,b,d,d);
}

NameEntry::NameEntry(char*n,long w,Name2Features a)
{
   Name2Features d(0,0,false);
   Init(n,w,a,d,d,d);
}

NameEntry::NameEntry(char*n,long w,Name2Features a[])
{
   short nentries=sizeof(a)/sizeof(Name2Features);
   Name2Features b[4];
   for(int i=0;i<4;i++)
   {
      b[i]=i>=nentries?Name2Features(false):a[i];
   }
   Init(n,w,b[0],b[1],b[2],b[3]);
}

// ! NameEntry method implementations

// NameGenerator method implementation

void NameGenerator::Init(short slocation)
{
   Init("",slocation);
}

NameGenerator::NameGenerator(short slocation)
{
   Init(slocation);
}

void NameGenerator::Destroy()
{
//   int rv;
   //ResizeList(0);
   //list=NULL;
   mList.clear();
}

NameGenerator::~NameGenerator()
{
   Destroy();
}

NameGenerator::NameGenerator(char*file,short slocation)
{
   Init(file,slocation);
}

NameGenerator::NameGenerator()
{
   Init("",locIndexWorld);
}

void NameGenerator::ReadListFromFile(char*file)
{
   NameGenFileParser ngfp(file,*this);
   ngfp.ReadWholeFile();
#define testTokenParser 0
#if testTokenParser
   FILE*f=fopen("data/TokenTestData.txt","r+");
   if(f){
      char delims[delimStringSize];
      char buffer[256];
      fscanf(f," %[^\t\n] %[^\t\n] ",delims,buffer);
      Token t(delims,buffer);
      t.ResetBufrPtr();
      t.Next();
      t.Next();
      t.Next();
      t.Next();
      t.Next();
      t.Next();
      fclose(f);
   }
#endif
}

void NameGenerator::Init(char*file,short slocation)
{
   location=slocation;
   //list=NULL;
   //numEntries=0;
   if(file[0]==0)	/*""*/
   {
   }
   else
   {
      ReadListFromFile(file);
   }
}

//void NameGenerator::GrowList()
//{
//   GrowList(1);
//}
//
//void NameGenerator::GrowList(short nnewentries)
//{
//   ResizeList(numEntries+nnewentries);
//}
//
//void NameGenerator::ResizeList(short snentries)
//{
//   if(snentries==0)
//   {
//      delete list;
//      list = new NameEntry[1];
//   }
//   else
//   {
//      delete list;
//      list = new NameEntry[snentries];
//   }
//   numEntries=snentries;
//}

void NameGenerator::Add2List(NameEntry* n)
{
   mList.push_back (n);
   //GrowList();
   //list[numEntries-1]=n;
}

void NameGenerator::Add2List(char*name,long weight)
{
   Add2List (new NameEntry (name, weight));
   // GrowList();
   //list[numEntries-1].weight = (short)weight;
   //list[numEntries-1].name = name;
}

void NameGenerator::CleanList()
{
   //delete [] list;
   while (mList.size() > 0)
   {
      NameEntry* p = mList.back();
      delete p;
      mList.pop_back();
   }
   Init(location);
}

long NameGenerator::GetTotNameWeight()
{
   long tw=0;
   /*for(int i=0;i<numEntries;i++)
   {
      tw+=list[i].weight;
   }*/
   std::list<NameEntry*>::iterator i = mList.begin();
   for (; i != mList.end(); i++)
   {
      NameEntry* n = *(i);
      tw += n->weight;
   }
   return tw;
}

long NameGenerator::InRange(long n,long l,long h)
{
   return ((n>=l)&&(n<=h));
}

NameString NameGenerator::GetListName()
{
   NameEntry errorEntry("(ERROR)",-1);
   long lrv=rand()%GetTotNameWeight();
   long lo = 0;
   long hi = 0;

//   for(int i=0,lo=0,hi=-1;i<numEntries;i++)
//   {
   std::list<NameEntry*>::iterator i = mList.begin();
   for (; i != mList.end(); i++)
   {
      NameEntry* n = *(i);
      lo = hi+1;
      hi = lo+ n->weight;
      if(InRange(lrv,lo,hi))
      {
         return n->name;
      }
   }
   return errorEntry.name;
}

// Optimization
//void NameGenerator::LessThanSwap(short i,short j)
//{
//   if(list[i].weight<list[j].weight)
//      SwapEntries(i,j);
//}
//
//void NameGenerator::SwapEntries(short i,short j)
//{
//   NameEntry tmp("",0);
//   tmp=list[i];	list[i]=list[j];	list[j]=tmp;
//}

void NameGenerator::OptimizeList()
{
   //put the heaviest entry first, with a simple bubble sort algorithm
   //for(int i=0;i<numEntries-1;i++)
   //{
   //   for(int j=i+1;j<numEntries;j++)
   //   {
   //      LessThanSwap(i,j);
   //   }
   //}//for j and i
   mList.sort (NameEntry::Compare);
}//OptimizeList()

// ! NameGenerator method implementation

#if doAmericanTest

void TestAmericanNames()
{

#if 0
#endif //	#if 0
   //usnames.Add2List(NameEntry("Smith",110,Name2Features(/*1*/(short)hfNEurope,11,true)/*0*//*0*//*0*/,Name2Features(/*2*/(short)hfAfrican,3,true)/*0*//*0*//*0*//*0*/));

   //output
   NameGenerator countrynames;
   char*nameoutfile;

   //std::cout<<"==== American surname generator test ====\r\n";
   for(int pass=0;pass<2;pass++)
   {
      switch(pass)
      {
      case 0:
         countrynames=NameGenerator("data/NameLists/surnames/USAmerican-All.pnl",locIndexUnitedStates);
         nameoutfile="output/usnames.txt";
         break;
      case 1:
         countrynames=NameGenerator("data/NameLists/surnames/Canada-All.pnl",locIndexCanada);
         nameoutfile="output/canadanames.txt";
         break;
      }
      countrynames.OptimizeList();
      FILE*f=fopen(nameoutfile,"w+");
      int nnames=3000;
      NameString name;
      if(f)
      {
         std::cout<<"(Check file: "<<nameoutfile<<")\r\n";
         fprintf(f,"==== American surname generator test ====\r\n");
      }
#ifdef NAMES
      for(int i=0;i<nnames;i++)
      {
         name=countrynames.GetListName();
         if(f)	fprintf(f,"%d\t%s\r\n",i,name.Text());
         else	std::cout<<name.Text()<<", ";

      }//for i
#endif
      if(f)	fclose(f);
      else	std::cout<<name.Text()<<"\r\n";

      countrynames.Destroy();
   } //step through passes (for loop)


}//TestAmerican()

#endif

#if doTestNameTree
void TestNameTree(){
   //NameGenerator usnames("data/tpb3dpnl-American-All.pnl",locIndexUnitedStates);
   WorldLocations wloc;
   //add first node
   //NameGenerator worldnames("data/tpb3dpnl-American-All.pnl",locIndexWorld);
   NameGenerator worldnames("",locIndexWorld);
   NameListTreeEntry root(NULL,&worldnames);
   NameListTree nmtree(&wloc,&root);
   //NameListTreeEntry*rootp=nmtree.FindNode(locIndexWorld);
   //Add all nodes
   NameListTreeEntry listnodes[locIndexFirstCustom];
   NameGenerator list[locIndexFirstCustom];
   NameGenerator*curNameList=&worldnames;
   //dump output
   std::cout<<"======== TestNameTree() ========\r\n";
   for(int pass=0;pass<2;pass++)	{
      for(int i=locIndexAngloNorthAmerica;i<locIndexFirstCustom;++i){
         if(pass==0){
            list[i]=NameGenerator(i);	curNameList=&list[i];
            listnodes[i]=NameListTreeEntry(NULL,curNameList);
            nmtree.AddList(wloc.locations[i].parentindex,&listnodes[i]);
            //dump output
         }
         else	{
            char outs[128];	char*llsp;
            NameListTreeEntry*findp=nmtree.FindNode(i);
            LocationLineageString lls(&wloc,"");
            llsp=lls.BuildLineageString(i," -> ");
            sprintf(outs,"Index: %hd\tRetptr: 0x%lx\r\n\tLocstr: %s\r\n",(short)i,findp,llsp);
            std::cout<<outs;
         }
      }//for i
   }//for pass
   //dump output
   std::cout<<"======== ! TestNameTree() ========\r\n";
}
#endif
// NameGenFileParser implementation

NameGenFileParser::NameGenFileParser(char*file,NameGenerator&sng)
{
   f=fopen(file,"r+");
   this->ng=&sng;
}

NameGenFileParser::~NameGenFileParser()
{
   if(f)	fclose(f);

   this->ng=NULL;
}

bool NameGenFileParser::ReadLine()
{
   char rawreadline[ngfpMaxLineSize*2];
   readline[0]=comment[0]=0;
   int nscans;
   if(f)
   {
      fpos=ftell(f);
      fgets(rawreadline,ngfpMaxLineSize*2,f);
      fpos=ftell(f);
      if(rawreadline[0]==';')
         nscans=sscanf(rawreadline,";%[^\n]",comment);
      else
         nscans=sscanf(rawreadline,"%[^;\n]%;[^\n]",readline,comment);
   }//if f open
   return(nscans>0);
}

bool NameGenFileParser::ReadEntry()
{
   if(f)
   {
      ReadNextUsedLine();
      if(Eof())return false;

      char name[64];
      short weight;
      char aprnames[4][32];
      short aprtypes[4];
      short aprwts[4];
      int nscans;
      bool aprused[4];
      nscans=sscanf(readline," \"%64[^\"]\" %hd %32s %hd %32s %hd %32s %hd %32s %hd "
         ,name,&weight,&aprnames[0],&aprwts[0],&aprnames[1],&aprwts[1],&aprnames[2],&aprwts[2],&aprnames[3],&aprwts[3]);

      for(int i=0;i<4;i++)
      {
         aprtypes[i]=(short)ConvTypeString(aprnames[i]);
         aprused[i]=aprwts[i]!=0;
      }

      if(nscans>=10)
         ng->Add2List(new NameEntry(name,weight,Name2Features(aprwts[0],aprtypes[0],aprused[0]),Name2Features(aprwts[1],aprtypes[1],aprused[1]),Name2Features(aprwts[2],aprtypes[2],aprused[2]),Name2Features(aprwts[3],aprtypes[3],aprused[3])));
      else if(nscans>=8)
         ng->Add2List(new NameEntry(name,weight,Name2Features(aprwts[0],aprtypes[0],aprused[0]),Name2Features(aprwts[1],aprtypes[1],aprused[1]),Name2Features(aprwts[2],aprtypes[2],aprused[2])));
      else if(nscans>=6)
         ng->Add2List(new NameEntry(name,weight,Name2Features(aprwts[0],aprtypes[0],aprused[0]),Name2Features(aprwts[1],aprtypes[1],aprused[1])));
      else if(nscans>=4)
         ng->Add2List(new NameEntry(name,weight,Name2Features(aprwts[0],aprtypes[0],aprused[0])));
      else if(nscans>=2)
         ng->Add2List(new NameEntry(name,weight));
      else 	{
         return(false);
      }
      return(true);
   }//if f open
   else
   {
      return(false);
   }
}

humanFeatureTypes NameGenFileParser::ConvTypeString(char*s)
{
   humanFeatureTypes rv=hfUnk;
   struct
   {
      char name[16];
      humanFeatureTypes ftype;
   }
   typetable[nhumanFeatureTypes]
   =	{
      {	"hfNEurope"	,	hfNEurope	}	,
      {	"hfMeditrn"	,	hfMeditrn	}	,
      {	"hfEAsian"	,	hfEAsian	}	,
      {	"hfSAsian"	,	hfSAsian	}	,
      {	"hfAfrican"	,	hfAfrican	}	,
      {	"hfMEast"	,	hfMEast	}	,
      {	"hfAmerind"	,	hfAmerind	}	,
      {	"hfPacIsld"	,	hfPacIsld	}	,
      {	"hfLatAmr"	,	hfLatAmr	}
   };
   for(int i=0;i<nhumanFeatureTypes;i++)
   {
      if(strcmp(typetable[i].name,s)==0)	rv=(humanFeatureTypes)i;
   }
   return(rv);
}//NameGenFileParser::ConvTypeString()

bool NameGenFileParser::Eof()
{
   return (feof(f) != 0);
}

void NameGenFileParser::ReadNextUsedLine()
{
   bool done=false;
   while(!done)
   {
      done=Eof();
      if(!done)	ReadLine();
      done=done||readline[0]!='\0';
   }
}

bool NameGenFileParser::ReadFileSig()
{
   ReadNextUsedLine();
   int scmpres;
   if(Eof())
      return(false);
   char sig[32];
   sscanf(readline," %32s ",sig);
   scmpres=strcmp(sig,"TPB3DpeepNameList");
   return(scmpres==0);
}//ReadWholeFile()

// ! NameGenFileParser implementation
bool NameGenFileParser::ReadListName()
{
   ReadNextUsedLine();
   bool rv=false;
   int nscans;
   nscans=sscanf(readline,"%32s",ng->listname);
   return(nscans>=0);
}//NameGenFileParser::ReadListName()

void NameGenFileParser::ReadWholeFile()
{
   if(ReadFileSig())
   {
      ReadListName();
      while(!Eof())
      {
         ReadEntry();
      }//while not eof
   }
}//NameGenFileParser::ReadWholeFile()

// ! NameGenFileParser implementation




