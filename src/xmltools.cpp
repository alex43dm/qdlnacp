#include <string.h>
#include <stdlib.h>
#include <upnp/ixml.h>
#include <string>

// Returns the value of a child element, or 0 on error
const char* xml_getChildElementValue( IXML_Element* parent, const char* tagName )
{
    if ( !parent ) return 0;
    if ( !tagName ) return 0;

    char* s = strdup( tagName );
    IXML_NodeList* nodeList = ixmlElement_getElementsByTagName( parent, s );
    free( s );
    if ( !nodeList ) return 0;

    IXML_Node* element = ixmlNodeList_item( nodeList, 0 );
    ixmlNodeList_free( nodeList );
    if ( !element ) return 0;

    IXML_Node* textNode = ixmlNode_getFirstChild( element );
    if ( !textNode ) return 0;

    return ixmlNode_getNodeValue( textNode );
}

const char* xml_getChildElement( IXML_Element* parent, const char* tagName )
{
    if ( !parent ) return 0;
    if ( !tagName ) return 0;

    char* s = strdup( tagName );
    IXML_NodeList* nodeList = ixmlElement_getElementsByTagName( parent, s );
    free( s );

    IXML_Node* element = ixmlNodeList_item( nodeList, 0 );
    ixmlNodeList_free( nodeList );
    if ( !element ) return 0;

    IXML_Node* textNode = ixmlNode_getFirstChild( element );
    if ( !textNode ) return 0;

    return ixmlNodetoString( textNode );
}

// Extracts the result document from a SOAP response
IXML_Document* parseBrowseResult( IXML_Document* doc )
{
    if ( !doc ) return 0;

    IXML_NodeList* resultList = ixmlDocument_getElementsByTagName( doc, "Result" );
    if ( !resultList ) return 0;

    IXML_Node* resultNode = ixmlNodeList_item( resultList, 0 );

    ixmlNodeList_free( resultList );

    if ( !resultNode ) return 0;

    IXML_Node* textNode = ixmlNode_getFirstChild( resultNode );
    if ( !textNode ) return 0;

    const char* resultString = ixmlNode_getNodeValue( textNode );
    char* resultXML = strdup( resultString );

    //resolve_xml_special_chars( resultXML );

    IXML_Document* browseDoc = ixmlParseBuffer( resultXML );

    free( resultXML );

    return browseDoc;
}


// Returns the value of a child element, or 0 on error
const char* xml_getElementValue( IXML_Element* parent, const char* tagName )
{
    if ( !parent ) return 0;
    if ( !tagName ) return 0;

    char* s = strdup( tagName );
    IXML_NodeList* nodeList = ixmlElement_getElementsByTagName( parent, s );
    free( s );
    if ( !nodeList ) return 0;

    IXML_Node* element = ixmlNodeList_item( nodeList, 0 );
    ixmlNodeList_free( nodeList );
    if ( !element ) return 0;

    return ixmlNode_getNodeValue( element );
}

void Replace(std::string& str, const std::string& oldStr, const std::string& newStr)
{
    size_t pos = 0;
    while((pos = str.find(oldStr, pos)) != std::string::npos)
    {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}


IXML_Document*  clearXmlDoc(IXML_Document* doc)
{
    std::string ss = ixmlDocumenttoString(doc);
    Replace(ss,"&quot;","\"");
    Replace(ss,"&lt;","<");
    Replace(ss,"&gt;",">");

   return ixmlParseBuffer( ss.c_str() );
}

void clearXmlString(std::string &str)
{
    Replace(str,"&quot;","\"");
    Replace(str,"&lt;","<");
    Replace(str,"&gt;",">");
}
