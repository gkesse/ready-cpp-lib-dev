//===============================================
#ifndef _GMimeType_
#define _GMimeType_
//===============================================
#include "GObject.h"
//===============================================
#define GMIMETYPE   GMimeType::Instance()
#define smimetype   GMIMETYPE->getMimeType
//===============================================
class GMimeType : public GObject {
public:
    struct sGMimeType {
        bool flag;
        const char* extension;
        const char* mimeType;
    };

public:
    GMimeType();
    ~GMimeType();
    static GMimeType* Instance();
    GString getMimeType(const GString& _extension) const;

private:
    static GMimeType* m_instance;
};
//===============================================
#endif
//===============================================
