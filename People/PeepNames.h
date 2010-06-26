//People/PeepNames.h - Classes for generating peep names - surname and first names

#pragma once

#include "../Types/MathStuff.h"
#include <string>
#include <list>
#include <cstdlib>
//#include <time.h>
//#include <stdio.h>

#define personNameMaxSize 10

struct NameString
{
	char buffer[personNameMaxSize];
	//NameString method declarations
	NameString();
	void operator=(char*s);
	char*Text();
	//NameString(char*s)	{	(*this)=s;	}
};

//feature (proto)types for human peeps.  Maybe eventually custom types like alien or fantasy races may be added, but these are the default ones
	//	how these convert to actual peep appearance will be defined later
	//	this may also need to be moved to a peep appearance code file for better code organization
typedef	enum	{
	hfNEurope	=	0	,
	hfMeditrn	=	1	,
	hfEAsian	=	2	,
	hfSAsian	=	3	,
	hfAfrican	=	4	,
	hfMEast	=	5	,
	hfAmerind	=	6	,
	hfPacIsld	=	7	,
	hfLatAmr	=	8	,
	hfUnk		=	9
	}	humanFeatureTypes	;

#define nhumanFeatureTypes (hfUnk)

//Name2PeepAppearanceStruct: a 1-byte mini-structure for determining peep features from the selected name
	//note: appearancetype should be defined elsewhere; it should be an identifier
	//		in a set of appearance prototypes.  It should be a range of appearances more than an exact set
	//		of physical features.  (skin color, hair color, height,	etc).  Think of it as a simplified
	//		genetic selector.  This is more important for surnames than given names.  Peep location
	//		should also be taken into account when determining appearance.  This can be ignored if it takes
	//		too many resources or comp. time - it's mostly for a realism.  Appearances and names can be randomly assigned
	//		without regards to one another.
struct Name2PeepAppearanceStruct
{
	unsigned char weight:4,	appearancetype:3,	usedflag:1;
	void Init(unsigned char sweight,unsigned char sappearancetype, bool sused)	{
		weight=sweight;	appearancetype=sappearancetype; usedflag=sused?1:0;
		}
	Name2PeepAppearanceStruct(unsigned char sweight,unsigned char sappearancetype, bool sused)	{
		Init(sweight,sappearancetype,sused);
		}
	Name2PeepAppearanceStruct(bool sused=false)	{
		Init(0,0,sused);
		}
	bool IsUsed(){	return(usedflag==1);	}
	//unary operator *: Answers "Is this structure being used?"
	bool operator*(){	this->IsUsed();	}
};

typedef Name2PeepAppearanceStruct Name2Features;

// NameEntry: This should be aligned to 16 or 32 bytes
#define nameEntryTargetSize 16
#define nname2appearTypes	4
#define nameEntryFillSize	(nameEntryTargetSize-nname2appearTypes-2-personNameMaxSize)

struct NameEntry
{
	NameString name;//("");
	short weight;
	Name2PeepAppearanceStruct appearances[nname2appearTypes];
	#if(nameEntryFillSize>0)
	unsigned char fill[nameEntryFillSize];
	#endif
	//NameEntry method declarations
	void Init(char*n,long w);
   NameEntry()
   {
      name = "";
      weight = 0;
   }
	NameEntry(char*n,long w);
	void Init(char*n,long w,Name2Features a1,Name2Features a2,Name2Features a3,Name2Features a4);
	NameEntry(char*n,long w,Name2Features a,Name2Features b,Name2Features c,Name2Features d);
	NameEntry(char*n,long w,Name2Features a,Name2Features b,Name2Features c);
	NameEntry(char*n,long w,Name2Features a,Name2Features b);
	NameEntry(char*n,long w,Name2Features a);
	NameEntry(char*n,long w,Name2Features a[]);
public:
   static int Compare (NameEntry* a, NameEntry* b)
   {
      return (a->weight < b->weight);
   }
};

//class RandomNameMaker;  //defined later

#define listnameMaxSize 32

class NameGenerator
{
	public:
	//NameEntry*list;
      std::list<NameEntry*> mList;
	//union{	short numEntries;	short nentries;	};
	char listname[listnameMaxSize];
	short location;
	//RandomNameMaker randGen;
	//NameGenerator method declaration
	void Init(short slocation)		;
	NameGenerator(short slocation)	;
	NameGenerator()	;
	void Destroy();
	~NameGenerator()	;
	void ReadListFromFile(char*file)	;
	NameGenerator(char*file,short slocation)	;
	void Init(char*file,short slocation)	;
	//void ResizeList(short snentries);
	//void GrowList();
	//void GrowList(short nnewentries);
	void Add2List(char*name,long weight)	;
	void Add2List(NameEntry* n);
	void CleanList()	;
	long GetTotNameWeight()	;
	long InRange(long n,long l,long h)  ;
	NameString GetListName()	;
	// Optimization
	void LessThanSwap(short i,short j)	;
	void SwapEntries(short i,short j)	;
	void OptimizeList()	;
	};//SurnameGenerator

#define ngfpMaxLineSize 512
class NameGenFileParser{
	public:
	FILE*f;	unsigned long fpos;
	char readline[ngfpMaxLineSize];
	char comment[ngfpMaxLineSize];
	NameGenerator*ng;
	NameGenFileParser(char*file,NameGenerator&sng);
	~NameGenFileParser();
	bool ReadEntry();
	void ReadNextUsedLine();
	bool ReadLine();
	humanFeatureTypes ConvTypeString(char*s);
	bool ReadFileSig();
	bool ReadListName();
	bool Eof();
	void 	ReadWholeFile();
	};

#define doAmericanTest 1
#if doAmericanTest
void TestAmericanNames();
#endif
#define doTestNameTree 0
#if doTestNameTree
void TestNameTree();
#endif
