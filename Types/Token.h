//Types/Token.h - Declaration of the Token class
// An object for breaking strings into delimited tokens

#define delimStringSize 64
#define tokenStringSize 256
#define maxLeadAntiTokenSize tokenStringSize

class Token	{
	public:
	char delims[delimStringSize];	char curtoken[tokenStringSize];	char*buffer;	char*p;
	char leadAntiToken[maxLeadAntiTokenSize];
	char curdelim;
	//operator >>: skip tokens
	int Skip(int ntokens);
	Token(char*sdelims,char*sbuffer);
	char*Next();
	char*Next(int skips);
	void Init(char*sdelims,char*sbuffer);
	bool DelimCheck();
	void	NewDelimSet(char*newdelims);
	char*ResetBufrPtr();
	};

