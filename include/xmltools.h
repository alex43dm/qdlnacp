#ifndef XMLTOOLS_H_INCLUDED
#define XMLTOOLS_H_INCLUDED

const char* xml_getChildElementValue( IXML_Element* parent, const char* tagName );
IXML_Document* parseBrowseResult( IXML_Document* doc );
const char* xml_getChildElement( IXML_Element* parent, const char* tagName );
const char* xml_getElementValue( IXML_Element* parent, const char* tagName );
IXML_Document*  clearXmlDoc(IXML_Document* doc);
void clearXmlString(std::string &doc);

#endif // XMLTOOLS_H_INCLUDED
