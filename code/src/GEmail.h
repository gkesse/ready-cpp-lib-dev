//===============================================
#ifndef _GEmail_
#define _GEmail_
//===============================================
#include "GString.h"
//===============================================
class GEmail : public GString {
public:
    GEmail();
    GEmail(const char* _data);
    GEmail(const std::string& _data);
    GEmail(const GString& _data);
    GEmail(const GEmail& _data);
    ~GEmail();
    bool isValid() const;
};
//===============================================
#endif
//===============================================
