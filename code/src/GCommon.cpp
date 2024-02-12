//===============================================
#include "GCommon.h"
#include "GSocket.h"
//===============================================
GCommon::GCommon() {

}
//===============================================
GCommon::~GCommon() {

}
//===============================================
void GCommon::setCommon(const GCommon& _obj) {
    slog = _obj.slog;
}
//===============================================
void GCommon::setDebug(const GDebug& _obj) {
    slog = _obj;
}
//===============================================
void GCommon::setSocket(const GSocket& _obj) {
    slog = _obj.getDebug();
}
//===============================================
