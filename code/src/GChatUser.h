//===============================================
#ifndef _GChatUser_
#define _GChatUser_
//===============================================
#include "GChatCB.h"
//===============================================
class GChatUser : public GChatCB {
public:
    GChatUser();
    ~GChatUser();
    GString serializeXml() const;
    void deserializeXml();
    void run();
    void runCreate();
    void runConnect();

    void setUuid(const GString& _uuid)  {m_uuid = _uuid;}
    const GString& getUuid() const      {return m_uuid;}
    const GString& getPseudo() const    {return m_pseudo;}

protected:
    GString m_uuid;
    GString m_pseudo;
};
//===============================================
#endif
//===============================================
