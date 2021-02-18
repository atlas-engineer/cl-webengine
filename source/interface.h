#include <QObject>
#include <QHBoxLayout>
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
EXTERNC int widgetIsActiveWindow(void* widget);
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
EXTERNC void webEnginePageSetLivecycleState(void* webEnginePage, int state);
EXTERNC int webEnginePageLivecycleState(void* webEnginePage);
EXTERNC void webEnginePageTriggerAction(void* webEnginePage, int action, int checked);
EXTERNC void* webEnginePageAction(void* webEnginePage, int action);
EXTERNC void* webEnginePageHistory(void* webEnginePage);
EXTERNC void webEnginePageSetUrlRequestInterceptor(void* webEnginePage, void* interceptor);
EXTERNC char* webEnginePageUrl(void* webEnginePage);
EXTERNC int webEnginePageIsAudioMuted(void* webEnginePage);
EXTERNC void webEnginePageSetAudioMuted(void* webEnginePage, int muted);
EXTERNC void layoutAddWidget(void* layout, void* widget);
EXTERNC void windowShow(void* window);
EXTERNC void windowPresent(void* window);
EXTERNC void windowSetTitle(void* window, char* title);
EXTERNC char* windowTitle(void* window);
EXTERNC int windowIsActive(void* window);
EXTERNC void widgetSetLayout(void* widget, void* layout);
EXTERNC void widgetSetParent(void* widget, void* parent);
EXTERNC void widgetShow(void* widget);
EXTERNC void widgetHide(void* widget);
EXTERNC void widgetDelete(void* object);
EXTERNC void widgetResize(void* widget, int width, int height);
EXTERNC void widgetSetFixedHeight(void* widget, int height);
EXTERNC void widgetSetFixedSize(void* widget, int width, int height);
EXTERNC void widgetSetWindowTitle(void* widget, char* title);
EXTERNC void widgetShowFullScreen(void* widget);
EXTERNC void widgetShowNormal(void* widget);
EXTERNC void widgetPresent(void* widget);
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
