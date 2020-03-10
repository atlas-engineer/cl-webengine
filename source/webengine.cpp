#include "webengine.h"
#define UNUSED(x) (void)(x)

SharedLibrary::SharedLibrary() {
    argc = 0;
    argv = nullptr;
    app = NULL;
    thread = NULL;
    if (thread == NULL) {
        thread = new QThread();
        connect(thread, SIGNAL(started()), this, SLOT(onStarted()), Qt::DirectConnection);
        thread->start();
    }
}

void SharedLibrary::onStarted() {
    if (QCoreApplication::instance() == NULL) {
        app = new QCoreApplication(argc, argv);
        QPushButton button("Hello World");
        button.show();
        app->exec();
    }
    return;
}

void initialize() {
    new SharedLibrary();
    return;
}

int main (int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);
    new SharedLibrary();
    while(1) {}
    return 0;
}
