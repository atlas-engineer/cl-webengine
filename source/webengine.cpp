#include "webengine.h"
#define UNUSED(x) (void)(x)

SharedLibrary::SharedLibrary() {
    int argc = 1;
    char* argv[] = { (char*)"sharedlibrary.lib", NULL };
    app = new QApplication(argc, argv);
}

int SharedLibrary::exec() {
    return app->exec();
}

void* initialize() {
    return new SharedLibrary();
}

void* newQWidget() {
    QWidget *widget = new QWidget;
    return widget;
}

void* newQVBoxLayout() {
    QVBoxLayout *layout = new QVBoxLayout;
    return layout;
}

void layoutAddWidget(void* layout, void* widget) {
    QLayout *_layout = reinterpret_cast<QLayout*>(layout);
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _layout->addWidget(_widget);
}

void widgetSetLayout(void *widget, void* layout) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    QLayout *_layout = reinterpret_cast<QLayout*>(layout);
    _widget->setLayout(_layout);
}

void widgetShow(void *widget) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->show();
}

int main (int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);
    SharedLibrary *instance = reinterpret_cast<SharedLibrary*>(initialize());

    QWidget *window = reinterpret_cast<QWidget*>(newQWidget());
    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    QVBoxLayout *layout = reinterpret_cast<QVBoxLayout*>(newQVBoxLayout());
    layoutAddWidget(layout, button1);
    layoutAddWidget(layout, button2);
    widgetSetLayout(window, layout);
    widgetShow(window);
    
    window->setWindowTitle("New Title");
    return instance->exec();
}
