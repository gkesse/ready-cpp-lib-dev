//===============================================
#ifndef _GCarpoolEmail_
#define _GCarpoolEmail_
//===============================================
#include "GManager.h"
//===============================================
class GCarpoolEmail : public GManager {
public:
    GCarpoolEmail();
    ~GCarpoolEmail();
    GString serialize(const GString& _code = "email") const;
    void deserialize(const GString& _data, const GString& _code = "email");
    void run();
    void runInscription();
    bool insertEmail();
    bool updateUuid(const GString& _uuid);
    bool updateStatus(char _status);
    bool loadEmail();

protected:
    int m_id;
    GString m_uuid;
    GString m_email;
    GString m_password;
    GString m_confirm;
    bool m_isNewsletter;
    char m_status;
};
//===============================================
#endif
//===============================================
