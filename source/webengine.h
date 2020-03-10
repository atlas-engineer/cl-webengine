#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QThread>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void initialize();

#undef EXTERNC

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
