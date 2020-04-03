#include <QObject>
#include <QVBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QWebEngineView>
#include <QThread>
#include <QWindow>
#include <QKeyEvent>

typedef void (*fpInt)(int arg);
typedef void (*fpIntChar)(int arg, char* str);
typedef void (*fpKeyPress)(int id, int keyCode, char* keyString, int modifierFlags);

#define UNUSED(x) (void)(x)
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void* newKeyPressFilter(int id, fpKeyPress callback);
EXTERNC void widgetInstallKeyPressFilter(void* widget, void* keyPressFilter);
EXTERNC int windowIsActiveWindow(void* window);
EXTERNC QApplication* newQApplication(int argc, char** argv);
EXTERNC void* newLoadFinishedListener(int id, fpInt callback);
EXTERNC void loadFinishedListenerConnect(void* loadStartedListener, void* webEngineView);
EXTERNC void* newLoadStartedListener(int id, fpInt callback);
EXTERNC void loadStartedListenerConnect(void* loadStartedListener, void* webEngineView);
EXTERNC int applicationExec(void* application);
EXTERNC void applicationQuit(void* application);
EXTERNC QPushButton* newQPushButton(char* label);
EXTERNC QWindow* newQWindow();
EXTERNC QWidget* newQWidget();
EXTERNC QHBoxLayout* newQHBoxLayout();
EXTERNC QVBoxLayout* newQVBoxLayout();
EXTERNC QWebEngineView* newQWebEngineView();
EXTERNC char* webEngineViewUrl(void* webEngineView);
EXTERNC void webEngineViewLoad(void* webEngineView, char* url);
EXTERNC void* webEngineViewPage(void* webEngineView);
EXTERNC void webEnginePageSetHtml(void* webEnginePage, char* html);
EXTERNC void webEnginePageRunJavaScript(void* webEnginePage, char* javascript, int id, fpIntChar callback);
EXTERNC void layoutAddWidget(void* layout, void* widget);
EXTERNC void widgetSetLayout(void* widget, void* layout);
EXTERNC void widgetSetParent(void* widget, void* parent);
EXTERNC void widgetShow(void* widget);
EXTERNC void widgetHide(void* widget);
EXTERNC void widgetResize(void* widget, int width, int height);
EXTERNC void widgetSetFixedHeight(void* widget, int height);
EXTERNC void widgetSetFixedSize(void* widget, int width, int height);
EXTERNC void windowSetWindowTitle(void* window, char* title);
EXTERNC void windowShowFullScreen(void* window);
EXTERNC void windowShowNormal(void* window);
EXTERNC void windowPresent(void* window);
EXTERNC void layoutSetContentsMargins(void* layout, int left, int top, int right, int bottom);
EXTERNC void layoutSetSpacing(void* layout, int spacing);
EXTERNC void layoutInsertWidget(void* layout, int index, void* widget);

#undef EXTERNC

class Listener :public QObject {
    Q_OBJECT
public:
    int id;
    fpInt callback;
};

class LoadStartedListener :public Listener {
    Q_OBJECT
public slots:
    void loadStarted();
};

class LoadFinishedListener :public Listener {
    Q_OBJECT
public slots:
    void loadFinished(bool ok);
};

class KeyPressFilter : public QObject
{
    Q_OBJECT
public:
    int id;
    fpKeyPress callback;
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};
