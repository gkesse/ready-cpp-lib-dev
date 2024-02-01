//===============================================
#ifndef _GDate_
#define _GDate_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
#define DATE_FORMAT_LOG "%d/%m/%Y %H:%M:%S"
//===============================================
#define GDATE   GDate::Instance()
#define sdate   GDATE->getDate
//===============================================
class GDate {
public:
    GDate();
    ~GDate();
    static GDate* Instance();
    GString getDate(const GString& _format = DATE_FORMAT_LOG) const;

private:
    static GDate* m_instance;
};
//===============================================
#endif
//===============================================
