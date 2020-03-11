#include "webengine.h"

SharedLibrary::SharedLibrary() {
    int argc = 1;
    char* argv[] = { (char*)"sharedlibrary.lib", NULL };

    app = new QApplication(argc, argv);
    QPushButton button("Hello World");
    button.show();
    app->exec();
}

void initialize() {
    new SharedLibrary();
    return;
}
