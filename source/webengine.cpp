#include "webengine.h"
#include <QApplication>
#include <QPushButton>
#include <QThread>

int add(int x, int y) {
    return x + y;
}

class Q_DECL_EXPORT SharedLibrary :public QObject {
    Q_OBJECT

public:
    SharedLibrary();

private slots:
    void onStarted();

private:
    int argc;
    QCoreApplication * app;
    QThread * thread;
    char ** argv;
};

SharedLibrary::SharedLibrary() {
    argc = 0;
    argv = nullptr;
    app = NULL;
    thread = NULL;

    if (thread == NULL)
    {
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
