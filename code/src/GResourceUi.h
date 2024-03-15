//===============================================
#ifndef _GResourceUi_
#define _GResourceUi_
//===============================================
#include "GPage.h"
//===============================================
class GResourceUi : public GPage {
public:
    GResourceUi();
    ~GResourceUi();
    bool loadResource();
    bool isResource() const;
};
//===============================================
#endif
//===============================================
