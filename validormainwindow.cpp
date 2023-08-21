#include "validormainwindow.h"
#include "./ui_validormainwindow.h"
#include <qregexp.h>
#include <qregularexpression.h>
#include <qmessagebox.h>
#include <boost/asio.hpp>
#include <sstream>
#include <iostream>

using namespace boost::asio;

ValidorMainWindow::ValidorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ValidorMainWindow)
{
    ui->setupUi(this);
    ui->hostaddressLineEdit->setText("127.0.0.1");
}

ValidorMainWindow::~ValidorMainWindow()
{
    delete ui;
}

void ValidorMainWindow::on_sendValuesButton_clicked()
{
    static QRegExp hostaddressExp("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    if (hostaddressExp.exactMatch(ui->hostaddressLineEdit->text()) == false) {
        QMessageBox::warning(this, "Некорректный адрес сервера", "Проверьте введнный Вами адрес соединения");
    }

    /*
    io_context io_context;
    ip::udp::socket socket(io_context, ip::udp::endpoint(ip::udp::v4(), ui->portSpinBox->value()));

    char data[1024];
    ip::udp::endpoint sender_endpoint;
    size_t length = socket.receive_from(buffer(data, sizeof(data)), sender_endpoint);

    std::cout << "Received message from " << sender_endpoint.address() << ": " << data << std::endl;

    socket.send_to(boost::asio::buffer(data, length), sender_endpoint);
    */
}


