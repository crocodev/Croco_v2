#include <stdlib.h>
#include <time.h>
#include <cstring>

//Attach XML
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <libxml/xpathInternals.h>
#include <libxml/tree.h>

class DBWord
{
	xmlDocPtr xmlDocument;
	xmlXPathContextPtr xpathContext;
	int lastCheckedWordID;
public:
	DBWord(const char* dbfile);
	~DBWord();

	//Get card from DBCards
	//isRed=1 if Red
	unsigned char* getWord(int CardDigit, const char* Activity);
	void removeWordFromDB(int idWord);
};