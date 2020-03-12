#include "webengine.h"
#define UNUSED(x) (void)(x)

SharedLibrary::SharedLibrary() {
    int argc = 1;
    char* argv[] = { (char*)"sharedlibrary.lib", NULL };
    app = new QApplication(argc, argv);
}

void SharedLibrary::exec() {
    app->exec();
}

void SharedLibrary::windowMake() {
    QWidget *window = new QWidget;
    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);
    
    window->setLayout(layout);
    window->show();
}

void SharedLibrary::windowDelete() {
    
}

void SharedLibrary::windowFullscreen() {
    
}

void SharedLibrary::windowUnfullscreen() {
    
}

void initialize() {
    new SharedLibrary();
    return;
}

int main (int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);
    SharedLibrary *instance = new SharedLibrary();
    instance->windowMake();
    instance->windowMake();
    instance->exec();
    return 0;
}
