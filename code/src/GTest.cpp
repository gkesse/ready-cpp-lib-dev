//===============================================
#include "GTest.h"
//===============================================
GTest::GTest()
: GObject() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
    GString lMethod = "";
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
    lData4.print();

    lData = lData2;
    lData.print();

    if(lData == lData2) {
        printf("Les valeurs sont identiques.\n");
    }

    lData = "Bonjour tout le monde (4).";
    lData.print();

    if(lData != lData2) {
        printf("Les valeurs sont différentes.\n");
    }

    GString lData5 = 'A';
    lData5.print();

    GString lData6 = 10000;
    lData6.print();

    GString lData7 = 3.14;
    lData7.print();

    if(GString("cat") < GString("categorie")) {
        printf("(cat < categorie) est vrai.\n");
    }
    if(!(GString("cat") < GString("cat"))) {
        printf("(cat < cat) est faux.\n");
    }
    if(GString("cat") <= GString("cat")) {
        printf("(cat <= cat) est vrai.\n");
    }
    if(!(GString("cat") <= GString("cas"))) {
        printf("(cat <= cas) est faux.\n");
    }

    lData = "Bonjour tout le monde : ";
    lData += 2024;
    lData.print();

    lData = "Bonjour tout le monde : ";
    lData += GString() + 2024 + " - " + 'P' + 3.14;
    lData.print();
}
//===============================================
