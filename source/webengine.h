#include <QObject>
#include <QVBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QThread>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void* initialize();

#undef EXTERNC

class SharedLibrary :public QObject {
    Q_OBJECT

public:
    SharedLibrary();
    int exec();

private:
    QCoreApplication * app;
};
