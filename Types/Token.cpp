//Types/Token.cpp - Implementation of the Token class

#include <string.h>
#include "../Types/Token.h"

#define useSscanf 1

#if useSscanf
#include <stdio.h>
#endif

//Token implementation

void
Token::
	Init(char*sdelims,char*sbuffer)	{
		buffer=sbuffer;		p=sbuffer;	strncpy(delims,sdelims,delimStringSize);
		memset(curtoken,0,tokenStringSize);
		}
Token::
	Token(char*sdelims,char*sbuffer)	{
		Init(sdelims,sbuffer);
		}
//	Token::Skip(): skip tokens
//		par: number of tokens to skip
//		ret: actual amt of tokens skipped
int
Token::
	Skip(int ntokens)	{
		Token t=*this;
		for(int i=0;i<ntokens;i++){	this->Next();	}
		*this=t;	//revert to the original state before the Next() calls;
		return(ntokens);	//later: check how many tokens were skipped
		}
//	Token::DelimCheck(): Check for a delimiter at the current position
bool
Token::
	DelimCheck()	{
		char&c=*p;	char*dp=&delims[0];		char*sdp=dp;
		bool inverted=false;	bool dcheck=false;	bool done=false;
		bool invdcheck=true;
		while(!done)	{
			if(*dp=='^')	{
				inverted=!inverted;	++dp;
				//treat 2 consecutive carets a literal caret character
				if(*dp=='^')	{	inverted=!inverted;	}
				}
			else if(dp[0]=='.'&&dp[1]=='.'&&dp>sdp&&dp[2]!=0)	{
				//two consecutive dots with non-nulls at each end = range
				bool rangedone=false;
				--dp;
				unsigned char lo=dp[0];	unsigned char	hi=dp[3];
				if(lo>hi){	lo=dp[3];	hi=dp[0];	}
				rangedone=hi-lo>1;
				for(char ci=lo+1;rangedone||ci<hi;ci++){
					if(!inverted)	dcheck=dcheck||ci==c;
					else			invdcheck=invdcheck&&ci!=c;
					rangedone=dcheck&&invdcheck;
					}
				++dp;//reset the position to that of the first dot
				++dp;//skip the next dot
				++dp;//skip the hi char
				}
			if(!inverted)	dcheck=dcheck||*dp==c;
			else			invdcheck=invdcheck&&*dp!=c;
			done=dcheck&&invdcheck;
			if(done)	curdelim=*dp;			else	curdelim='\0';
			++dp;
			done=done||!*dp;
			}//while not done
		return(dcheck&&invdcheck);
		}
//	Token::Next(): Get next token after skipping initial delims
//		par: number of tokens to skip
//		ret: pointer to the curtoken,
char*
Token::
	Next(int skips)	{
		if(skips>0)		Skip(skips);
		bool dc;		char*retp=&curtoken[0];		char*ctp=retp;		bool done=false;	int nchars;
		#if useSscanf
			*retp=0;
			char ssfdelims[delimStringSize];
			char ssfantidelims[delimStringSize];
			char ssformat[delimStringSize*2];
			char*dp;
			int retv;
			//set up antiToken and token delims
			dp=&delims[0];
			strcpy(ssfdelims,"%[");	strcpy(ssfantidelims,"%[");
			if(*dp!='^'){	strcat(ssfdelims,"^");	}
			else	{	strcat(ssfantidelims,"^");	++dp;	}
			strcat(ssfantidelims,dp);	strcat(ssfdelims,dp);
			strcat(ssfantidelims,"]");	strcat(ssfdelims,"]");
			sprintf(ssformat,"%s%s",ssfantidelims,ssfdelims);
			//get antitoken and token
			retv=sscanf(p,ssformat,leadAntiToken,curtoken);
			if(retv<2)	{	leadAntiToken[0]=0;	retv=sscanf(p,ssfdelims,curtoken);	}
			if(retv>0)	p=&p[strlen(leadAntiToken)+strlen(curtoken)];
			return(retp);
		#else
			while(dc=DelimCheck())	{	++p;	}
			while(!(dc=DelimCheck())&&!done)	{
				*(ctp++)=*(p++);
				if(++nchars>=tokenStringSize-1)	{
					done=true;
					}//if
				}//while
			*ctp=0;
			return(retp);
			#endif
		}//Token::Next()
char*
Token::
	Next()	{	return(this->Next(0));	}
void
Token::
	NewDelimSet(char*newdelims)	{	strncpy(delims,newdelims,delimStringSize);	}
char*
Token::
	ResetBufrPtr(){	p=buffer;	}

// ! Token implementation

