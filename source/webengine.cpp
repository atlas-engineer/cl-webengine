#include "webengine.h"
#define UNUSED(x) (void)(x)

SharedLibrary::SharedLibrary() {
    argc = 0;
    argv = nullptr;
    app = NULL;

    if (QCoreApplication::instance() == NULL) {
        app = new QApplication(argc, argv);
        QPushButton button("Hello World");
        button.show();
        app->exec();
    }
}

void initialize() {
    new SharedLibrary();
    return;
}

int main (int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);
    new SharedLibrary();
    return 0;
}
