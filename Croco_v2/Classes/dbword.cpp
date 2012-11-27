#include "dbword.h"

DBWord::DBWord(const char* dbfile)
{
	//Load XML document
    xmlDocument = xmlParseFile(dbfile);
	//Create xpath evaluation context
	xpathContext = xmlXPathNewContext(xmlDocument);
	lastCheckedWordID=0;
}

DBWord::~DBWord()
{
	//Cleanup of XPath data
	xmlFreeDoc(xmlDocument);
    xmlXPathFreeContext(xpathContext); 
}

unsigned char* DBWord::getWord(int CardDigit, const char* Activity)
{
    xmlXPathObjectPtr xpathObj; 
	char eval[255] = "/Cards/Card[@cost='";
	char buf[8]; sprintf(buf,"%i",CardDigit);
	strcat(eval, buf);
	strcat(eval,"' and @act='");
	strcat(eval, Activity);
    strcat(eval,"']/Word");
	xpathObj = xmlXPathEvalExpression((xmlChar*)eval,xpathContext);
    
	xmlNodePtr xxx;
    
	//randomize
	srand((unsigned)time(NULL));
	xxx=xpathObj->nodesetval->nodeTab[rand()%xpathObj->nodesetval->nodeNr];
    
	xmlChar* cont = xmlNodeGetContent(xxx);
	
	lastCheckedWordID = atoi((const char*)xmlGetProp(xxx->parent,(xmlChar*)"id"));
    
	//free the document
    xmlXPathFreeObject(xpathObj);
	return cont;
    
    /*
	//Evaluate xpath expression
	xmlXPathObjectPtr xpathObj; 
	char eval[255] = "/Cards/Card[@cardvalue='";
	char buf[8]; sprintf(buf,"%i",CardDigit);
	strcat(eval, buf);
	strcat(eval,"']/");
	strcat(eval, Activity);
	xpathObj = xmlXPathEvalExpression((xmlChar*)eval,xpathContext);

	xmlNodePtr xxx;

	//randomize
	srand((unsigned)time(NULL));
	xxx=xpathObj->nodesetval->nodeTab[rand()%xpathObj->nodesetval->nodeNr];
	xmlChar* attr = xmlGetProp(xxx,(xmlChar*)"red");
	isRed = atoi((const char*)attr);

	xmlChar* cont = xmlNodeGetContent(xxx);
	
	lastCheckedWordID = atoi((const char*)xmlGetProp(xxx->parent,(xmlChar*)"id"));

	//free the document
    xmlXPathFreeObject(xpathObj);
	return cont;
    */
}