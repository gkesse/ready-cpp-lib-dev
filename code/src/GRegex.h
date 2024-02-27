//===============================================
#ifndef _GRegex_
#define _GRegex_
//===============================================
#include "GString.h"
//===============================================
class GRegex : public GString {
public:
    GRegex();
    GRegex(const char* _data);
    GRegex(const std::string& _data);
    GRegex(const GString& _data);
    GRegex(const GRegex& _data);
    ~GRegex();
    bool isMatch(const GString& _match) const;
    int countMatch(const GString& _match) const;
    GString replaceMatch(const GString& _from, const GString& _to) const;
    GString searchMatch(const GString& _search, int _capture, int _pos) const;
};
//===============================================
#endif
//===============================================
