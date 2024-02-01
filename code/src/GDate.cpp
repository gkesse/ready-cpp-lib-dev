//===============================================
#include "GDate.h"
//===============================================
GDate* GDate::m_instance = 0;
//===============================================
GDate::GDate() {

}
//===============================================
GDate::~GDate() {

}
//===============================================
GDate* GDate::Instance() {
    if(m_instance == 0) {
        m_instance = new GDate;
    }
    return m_instance;
}
//===============================================
GString GDate::getDate(const GString& _format) const {
    time_t lTime;
    struct tm* lTimeInfo;
    char lBuffer[80];
    time(&lTime);
    lTimeInfo = localtime(&lTime);
    strftime(lBuffer, sizeof(lBuffer), _format.c_str(), lTimeInfo);
    return lBuffer;
}
//===============================================
