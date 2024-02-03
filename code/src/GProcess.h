//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GObject.h"
//===============================================
#define GPROCESS GProcess::Instance()
//===============================================
class GProcess : public GObject {
public:
    GProcess();
    ~GProcess();
    static GProcess* Instance();
    void init();
    void clean();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runServer(int _argc, char** _argv);
    void runExit();
    static void onExit();

private:
    static GProcess* m_instance;
};
//===============================================
#endif
//===============================================
