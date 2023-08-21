#include "validormainwindow.h"
#include "./ui_validormainwindow.h"

ValidorMainWindow::ValidorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ValidorMainWindow)
{
    ui->setupUi(this);
}

ValidorMainWindow::~ValidorMainWindow()
{
    delete ui;
}

