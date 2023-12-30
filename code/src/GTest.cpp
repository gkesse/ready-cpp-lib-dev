//===============================================
#include "GTest.h"
#include "GString.h"
//===============================================
GTest::GTest()
: GObject() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
    std::string lMethod = "";
    if(_argc > 2) lMethod = _argv[2];

    if(lMethod == "") {
        printf("La méthode est obligatoire.\n");
    }
    else if(lMethod == "string") {
        runString(_argc, _argv);
    }
    else {
        printf("La méthode est inconnue.\n");
    }
}
//===============================================
void GTest::runString(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);

    GString lData;
    lData.print();

    GString lData2("Bonjour tout le monde.");
    lData2.print();

    GString lData3 = "Bonjour tout le monde (2).";
    lData3.print();

    GString lData4 = GString("Bonjour tout le monde (3).");
    lData3.print();
}
//===============================================
