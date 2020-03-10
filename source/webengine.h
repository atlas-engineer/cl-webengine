#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QThread>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC int add(int x, int y);
EXTERNC void initialize();

#undef EXTERNC

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget();

signals:
    void buttonClicked();

private:
    QPushButton *myButton;
};
