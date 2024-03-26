//===============================================
#include "GCommon.h"
#include "GSocket.h"
//===============================================
GCommon::GCommon()
: m_type(eGRequestType::REQ_TYPE_UNKNOWN)
, m_isContinue(false)
, m_isClose(false) {

}
//===============================================
GCommon::~GCommon() {

}
//===============================================
void GCommon::setCommon(const GCommon& _obj) {
    slog            = _obj.slog;
    m_type          = _obj.m_type;
    m_isContinue    = _obj.m_isContinue;
    m_isClose       = _obj.m_isClose;
}
//===============================================
