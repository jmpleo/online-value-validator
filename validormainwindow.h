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

public slots:
    void on_sendValuesButton_clicked();

private:
    void pack(uint16_t packet[4]);

private:
    Ui::ValidorMainWindow *ui;
};
#endif // VALIDORMAINWINDOW_H
