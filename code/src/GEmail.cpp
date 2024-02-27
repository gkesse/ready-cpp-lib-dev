//===============================================
#include "GEmail.h"
#include "GRegex.h"
//===============================================
GEmail::GEmail()
: GString() {

}
//===============================================
GEmail::GEmail(const char* _data)
: GString(_data) {

}
//===============================================
GEmail::GEmail(const std::string& _data)
: GString(_data) {

}
//===============================================
GEmail::GEmail(const GString& _data)
: GString(_data) {

}
//===============================================
GEmail::GEmail(const GEmail& _data)
: GString(_data) {

}
//===============================================
GEmail::~GEmail() {

}
//===============================================
bool GEmail::isValid() const {
    if(isEmpty()) return false;
    GRegex lRegex = *this;
    GString lPattern = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+";
    return lRegex.isMatch(lPattern);
}
//===============================================
