//===============================================
#include "GRegex.h"
//===============================================
GRegex::GRegex()
: GString() {

}
//===============================================
GRegex::GRegex(const char* _data)
: GString(_data) {

}
//===============================================
GRegex::GRegex(const std::string& _data)
: GString(_data) {

}
//===============================================
GRegex::GRegex(const GString& _data)
: GString(_data) {

}
//===============================================
GRegex::GRegex(const GRegex& _data)
: GString(_data) {

}
//===============================================
GRegex::~GRegex() {

}
//===============================================
bool GRegex::isMatch(const GString& _match) const {
    if(isEmpty()) return false;
    std::string lData(m_data, m_size);
    std::regex pattern(_match.c_str());
    return std::regex_match(lData, pattern);
}
//===============================================
int GRegex::countMatch(const GString& _match) const {
    if(isEmpty()) return 0;
    std::string lData(m_data, m_size);
    std::regex words_regex(_match.c_str());
    auto words_begin = std::sregex_iterator(lData.begin(), lData.end(), words_regex);
    auto words_end = std::sregex_iterator();
    return std::distance(words_begin, words_end);
}
//===============================================
GString GRegex::replaceMatch(const GString& _from, const GString& _to) const {
    if(isEmpty()) return "";
    std::string lData(m_data, m_size);
    std::regex reg(_from.c_str());
    lData = std::regex_replace(lData, reg, _to.c_str());
    return lData;
}
//===============================================
GString GRegex::searchMatch(const GString& _search, int _capture, int _pos) const {
    if(isEmpty()) return "";
    std::smatch sm1;
    std::string lData(m_data, m_size);
    std::regex lRegex(_search.c_str());
    int lCapture = 0;
    int lPos = 0;
    while(std::regex_search(lData, sm1, lRegex)) {
        if(lCapture++ == _capture) {
            for(auto x : sm1) {
                if(lPos++ == _pos) {
                    return std::string(x);
                }
            }
        }
        lData = sm1.suffix().str();
    }
    return "";
}
//===============================================
