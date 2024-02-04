//===============================================
#include "GResponseUnknown.h"
//===============================================
GResponseUnknown::GResponseUnknown()
: GResponse() {

}
//===============================================
GResponseUnknown::~GResponseUnknown() {

}
//===============================================
void GResponseUnknown::create() {
    m_response += sformat("Un problème a été rencontré.");
}
//===============================================
