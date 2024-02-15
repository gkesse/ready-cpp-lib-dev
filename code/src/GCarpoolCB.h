//===============================================
#ifndef _GCarpoolCB_
#define _GCarpoolCB_
//===============================================
#include "GManager.h"
//===============================================
class GCarpoolCB : public GManager {
public:
    GCarpoolCB();
    ~GCarpoolCB();
    GString serialize(const GString& _code = "carpool") const;
    void deserialize(const GString& _data, const GString& _code = "carpool");
    void run();
    void runCarpool();
    void runHelloWorld();
    void runInscriptionEmail();

private:
    GString m_email;
    GString m_password;
};
//===============================================
#endif
//===============================================
