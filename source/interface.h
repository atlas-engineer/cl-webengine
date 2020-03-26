#include <QObject>
#include <QVBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QWebEngineView>
#include <QThread>

typedef void (*fp)(int arg);

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC int windowIsActiveWindow(void* window);
EXTERNC QApplication* newQApplication(int argc, char** argv);
EXTERNC void* newLoadStartedListener(int id, fp callback);
EXTERNC void loadStartedListenerConnect(void* loadStartedListener, void* webEngineView);
EXTERNC int applicationExec(void* application);
EXTERNC void applicationQuit(void* application);
EXTERNC QPushButton* newQPushButton(char* label);
EXTERNC QWidget* newQWidget();
EXTERNC QHBoxLayout* newQHBoxLayout();
EXTERNC QVBoxLayout* newQVBoxLayout();
EXTERNC QWebEngineView* newQWebEngineView();
EXTERNC void webEngineViewLoad(void* webEngineView, char* url);
EXTERNC void* webEngineViewPage(void* webEngineView);
EXTERNC void webEnginePageSetHtml(void* webEnginePage, char* html);
EXTERNC void webEnginePageRunJavaScript(void* webEnginePage, char* javascript);
EXTERNC void layoutAddWidget(void* layout, void* widget);
EXTERNC void widgetSetLayout(void* widget, void* layout);
EXTERNC void widgetSetParent(void* widget, void* parent);
EXTERNC void widgetShow(void* widget);
EXTERNC void widgetResize(void* widget, int width, int height);
EXTERNC void widgetSetFixedHeight(void* widget, int height);
EXTERNC void widgetSetFixedSize(void* widget, int width, int height);
EXTERNC void windowSetWindowTitle(void* window, char* title);
EXTERNC void windowShowFullScreen(void* window);
EXTERNC void windowShowNormal(void* window);
EXTERNC void layoutSetContentsMargins(void* layout, int left, int top, int right, int bottom);
EXTERNC void layoutSetSpacing(void* layout, int spacing);
EXTERNC void layoutInsertWidget(void* layout, int index, void* widget);

#undef EXTERNC

class LoadStartedListener :public QObject {
    Q_OBJECT

public:
    LoadStartedListener();
    int id;
    fp callback;

public slots:
    void loadStarted();
};
