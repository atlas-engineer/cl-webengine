#include <QObject>
#include <QVBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QWebEngineView>
#include <QThread>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void* newQApplication(int argc, char** argv);
EXTERNC int applicationExec(void* application);
EXTERNC void* newQWidget();
EXTERNC void* newQVBoxLayout();
EXTERNC void* newQWebEngineView();
EXTERNC void webEngineViewLoad(void* webEngineView, char* url);
EXTERNC void* webEngineViewPage(void* webEngineView);
EXTERNC void webEnginePageRunJavaScript(void* webEnginePage, char* javascript);
EXTERNC void layoutAddWidget(void* layout, void* widget);
EXTERNC void widgetSetLayout(void* widget, void* layout);
EXTERNC void widgetShow(void* widget);
EXTERNC void widgetResize(void* widget, int width, int height);
EXTERNC void widgetSetFixedHeight(void* widget, int height);
EXTERNC void windowSetWindowTitle(void* window, char* title);
EXTERNC void layoutSetContentsMargins(void* layout, int left, int top, int right, int bottom);
EXTERNC void layoutSetSpacing(void* layout, int spacing);
EXTERNC void layoutInsertWidget(void* layout, int index, void* widget);

#undef EXTERNC



