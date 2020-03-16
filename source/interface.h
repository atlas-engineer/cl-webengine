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

EXTERNC void* initialize();

#undef EXTERNC

