#ifndef VALIDORMAINWINDOW_H
#define VALIDORMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ValidorMainWindow; }
QT_END_NAMESPACE

class ValidorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ValidorMainWindow(QWidget *parent = nullptr);
    ~ValidorMainWindow();

private:
    Ui::ValidorMainWindow *ui;
};
#endif // VALIDORMAINWINDOW_H
