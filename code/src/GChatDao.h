//===============================================
#ifndef _GChatDao_
#define _GChatDao_
//===============================================
#include "GMySQL.h"
//===============================================
class GChatUser;
//===============================================
class GChatDao : public GObject {
public:
    GChatDao();
    ~GChatDao();
    bool createUser(GChatUser& _obj);
    bool updateUuid(GChatUser& _obj);
    bool connectUser(GChatUser& _obj);

private:
    GMySQL m_dbSQL;
};
//===============================================
#endif
//===============================================
