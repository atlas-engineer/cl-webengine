#include "interface.h"

void* newKeyPressFilter(int id, fpKeyPress callback) {
    KeyPressFilter *keyPressFilter = new KeyPressFilter();
    keyPressFilter->id = id;
    keyPressFilter->callback = callback;
    return keyPressFilter;
}

void widgetInstallKeyPressFilter(void* widget, void* keyPressFilter) {
    KeyPressFilter *_keyPressFilter = reinterpret_cast<KeyPressFilter*>(keyPressFilter);
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->installEventFilter(_keyPressFilter);
}

bool KeyPressFilter::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int keyCode = keyEvent->key();
        QString text;
        if (keyEvent->text().isEmpty()) {
            text = QKeySequence(keyEvent->key()).toString();
        } else {
            text = keyEvent->text();
        }
        QByteArray keyStringArray = text.toUtf8();
        char* keyString = keyStringArray.data();
        int modifierFlags = keyEvent->modifiers();
        // -31 emitted as keystring when only modifiers pressed
        if ((int)keyString[0] == -31) {
            keyString = (char*)"";
        }
        callback(id, keyCode, keyString, modifierFlags);
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}

void* newLoadFinishedListener(int id, fpInt callback) {
    LoadFinishedListener *listener = new LoadFinishedListener();
    listener->id = id;
    listener->callback = callback;
    return listener;
}

void loadFinishedListenerConnect(void* loadFinishedListener, void* webEngineView) {
    LoadFinishedListener *_loadFinishedListener = reinterpret_cast<LoadFinishedListener*>(loadFinishedListener);
    QWebEngineView *_webEngineView = reinterpret_cast<QWebEngineView*>(webEngineView);
    QObject::connect(_webEngineView, &QWebEngineView::loadFinished,
                     _loadFinishedListener, &LoadFinishedListener::loadFinished);
}

void LoadFinishedListener::loadFinished(bool ok) {
    UNUSED(ok);
    callback(id);
    return;
}

void* newLoadStartedListener(int id, fpInt callback) {
    LoadStartedListener *listener = new LoadStartedListener();
    listener->id = id;
    listener->callback = callback;
    return listener;
}

void loadStartedListenerConnect(void* loadStartedListener, void* webEngineView) {
    LoadStartedListener *_loadStartedListener = reinterpret_cast<LoadStartedListener*>(loadStartedListener);
    QWebEngineView *_webEngineView = reinterpret_cast<QWebEngineView*>(webEngineView);
    QObject::connect(_webEngineView, &QWebEngineView::loadStarted,
                     _loadStartedListener, &LoadStartedListener::loadStarted);
}

void LoadStartedListener::loadStarted() {
    callback(id);
    return;
}

QApplication* newQApplication(int argc, char** argv) {
    return new QApplication(argc, argv);
}

int applicationExec(void* application) {
    QApplication *_application = reinterpret_cast<QApplication*>(application);
    return _application->exec();
}

void applicationQuit(void* application) {
    QApplication *_application = reinterpret_cast<QApplication*>(application);
    _application->quit();
    return;
}

QWidget* newQWidget() {
    QWidget *widget = new QWidget;
    return widget;
}

QWindow* newQWindow() {
    QWindow *window = new QWindow;
    return window;
}

QVBoxLayout* newQVBoxLayout() {
    QVBoxLayout *layout = new QVBoxLayout;
    return layout;
}

QHBoxLayout* newQHBoxLayout() {
    QHBoxLayout *layout = new QHBoxLayout;
    return layout;
}

QPushButton* newQPushButton(char* label){
    QPushButton *pushButton = new QPushButton(label);
    return pushButton;
}

QWebEngineView* newQWebEngineView() {
    QWebEngineView *webEngineView = new QWebEngineView();
    return webEngineView;
}

void webEngineViewLoad(void* webEngineView, char* url) {
    QWebEngineView *_webEngineView = reinterpret_cast<QWebEngineView*>(webEngineView);
    _webEngineView->setUrl(QUrl(url));
}

char* webEngineViewUrl(void* webEngineView) {
    QWebEngineView *_webEngineView = reinterpret_cast<QWebEngineView*>(webEngineView);
    return _webEngineView->url().toString().toUtf8().data();
}

void* webEngineViewPage(void* webEngineView) {
    QWebEngineView *_webEngineView = reinterpret_cast<QWebEngineView*>(webEngineView);
    return _webEngineView->page();
}

void webEnginePageSetHtml(void* webEnginePage, char* html) {
    QWebEnginePage *_webEnginePage = reinterpret_cast<QWebEnginePage*>(webEnginePage);
    _webEnginePage->setHtml(html);
}

void webEnginePageRunJavaScript(void* webEnginePage, char* javascript, int id, fpIntChar callback) {
    QWebEnginePage *_webEnginePage = reinterpret_cast<QWebEnginePage*>(webEnginePage);
    _webEnginePage->runJavaScript(javascript, [id, callback](const QVariant &v) { callback(id, v.toString().toUtf8().data()); });
}

void webEnginePageSetLivecycleState(void* webEnginePage, int state) {
    QWebEnginePage *_webEnginePage = reinterpret_cast<QWebEnginePage*>(webEnginePage);
    _webEnginePage->setLifecycleState(static_cast<QWebEnginePage::LifecycleState>(state));
}

int webEnginePageLivecycleState(void* webEnginePage) {
    QWebEnginePage *_webEnginePage = reinterpret_cast<QWebEnginePage*>(webEnginePage);
    return (int)_webEnginePage->lifecycleState();
}

void webEnginePageTriggerAction(void* webEnginePage, int action, int checked) {
    QWebEnginePage *_webEnginePage = reinterpret_cast<QWebEnginePage*>(webEnginePage);
    _webEnginePage->triggerAction(static_cast<QWebEnginePage::WebAction>(action), checked);
}

void* webEnginePageAction(void* webEnginePage, int action) {
    QWebEnginePage *_webEnginePage = reinterpret_cast<QWebEnginePage*>(webEnginePage);
    return _webEnginePage->action(static_cast<QWebEnginePage::WebAction>(action));
}

void* webEnginePageHistory(void* webEnginePage) {
    QWebEnginePage *_webEnginePage = reinterpret_cast<QWebEnginePage*>(webEnginePage);
    return _webEnginePage->history();
}

void webEnginePageSetUrlRequestInterceptor(void* webEnginePage, void* interceptor) {
    QWebEnginePage *_webEnginePage = reinterpret_cast<QWebEnginePage*>(webEnginePage);
    QWebEngineUrlRequestInterceptor *_interceptor
      = reinterpret_cast<QWebEngineUrlRequestInterceptor*>(interceptor);
    _webEnginePage->setUrlRequestInterceptor(_interceptor);
}

void layoutAddWidget(void* layout, void* widget) {
    QLayout *_layout = reinterpret_cast<QLayout*>(layout);
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _layout->addWidget(_widget);
}

void windowShow(void* window){
    QWindow *_window = reinterpret_cast<QWindow*>(window);
    _window->show();
}

void windowPresent(void* window) {
    QWindow *_window = reinterpret_cast<QWindow*>(window);
    _window->show();
    _window->raise();
 }

void windowSetTitle(void* window, char* title){
    QWindow *_window = reinterpret_cast<QWindow*>(window);
    _window->setTitle(title);
}

char* windowTitle(void* window){
    QWindow *_window = reinterpret_cast<QWindow*>(window);
    return _window->title().toUtf8().data();
}

int windowIsActive(void* window) {
    QWindow *_window = reinterpret_cast<QWindow*>(window);
    return _window->isActive();
}

void widgetSetLayout(void* widget, void* layout) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    QLayout *_layout = reinterpret_cast<QLayout*>(layout);
    _widget->setLayout(_layout);
}

void widgetSetParent(void* widget, void* parent) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    QWidget *_parent = reinterpret_cast<QWidget*>(parent);
    _widget->setParent(_parent);
}

void widgetShow(void* widget) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->show();
}

void widgetHide(void* widget) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->hide();
}

void widgetDelete(void* widget) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    delete _widget;
}

void widgetResize(void* widget, int width, int height) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->resize(width, height);
}

void widgetSetFixedHeight(void* widget, int height) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->setFixedHeight(height);
}

void widgetSetFixedSize(void* widget, int width, int height) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->setFixedSize(width, height);
}

void widgetSetWindowTitle(void* widget, char* title) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->setWindowTitle(title);
}

int widgetIsActiveWindow(void* widget) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    return _widget->isActiveWindow();
}

void widgetShowFullScreen(void* widget) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->showFullScreen();
}

void widgetShowNormal(void* widget) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->showNormal();
}

void widgetPresent(void* widget) {
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _widget->show();
    _widget->raise();
}

void layoutSetContentsMargins(void* layout, int left, int top, int right, int bottom) {
    QLayout *_layout = reinterpret_cast<QLayout*>(layout);
    _layout->setContentsMargins(left, top, right, bottom);
}

void layoutSetSpacing(void* layout, int spacing) {
    QLayout *_layout = reinterpret_cast<QLayout*>(layout);
    _layout->setSpacing(spacing);
}

void layoutInsertWidget(void* layout, int index, void* widget) {
    QBoxLayout *_layout = reinterpret_cast<QBoxLayout*>(layout);
    QWidget *_widget = reinterpret_cast<QWidget*>(widget);
    _layout->insertWidget(index, _widget);
}

int main (int argc, char** argv) {
    QApplication* app = new QApplication(argc, argv);
    QWidget *window = reinterpret_cast<QWidget*>(newQWidget());
    QVBoxLayout *layout = reinterpret_cast<QVBoxLayout*>(newQVBoxLayout());
    QWebEngineView *web = reinterpret_cast<QWebEngineView*>(newQWebEngineView());
    KeyPressFilter *keyPressFilter = new KeyPressFilter();
    webEngineViewLoad(web, (char*)"https://www.duckduckgo.com");
    layoutAddWidget(layout, web);
    widgetSetLayout(window, layout);
    widgetShow(window);
    window->installEventFilter(keyPressFilter);
    return app->exec();
}
