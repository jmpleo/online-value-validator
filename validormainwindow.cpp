#include "validormainwindow.h"
#include "./ui_validormainwindow.h"
#include <boost/asio/ip/address.hpp>
#include <cstddef>
#include <ios>
#include <qregexp.h>
#include <qregularexpression.h>
#include <qmessagebox.h>
#include <boost/asio.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include <bitset>

using namespace boost::asio::ip;

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

void ValidorMainWindow::pack(uint16_t packet[4])
{
    packet[0] = (
        (0x3f & static_cast <uint8_t> (ui->coordXSpinBox->value())) // 0 - 5
        ^
        ((0x3f & static_cast <uint8_t> (ui->coordYSpinBox->value())) << 8) // 8 - 13
    );

    packet[1] = (
        (0xff & static_cast <uint8_t> (ui->velocitySpinBox->value())) // 0 - 7
        ^
        ((0x3 & (
            (ui->workModBRadioButton->isChecked()) // 8
            ^
            (ui->workModCRadioButton->isChecked() << 1) // 9
        )) << 8) // 8 - 11
        ^
        ((0x3 & (
            (ui->stateBRadioButton->isChecked()) // 12
            ^
            (ui->stateCRadioButton->isChecked() << 1) // 13
        )) << 12) // 12 - 15
    );

    packet[2] = (
        (0xff & static_cast <uint8_t> (ui->accelerationDoubleSpinBox->value() * 10.0)) // 0 - 7
        ^
        ((0xff & static_cast <uint8_t> (ui->powerSpinBox->value())) << 8) // 8 - 15
    );

    packet[3] = (
          (ui->reserveBit0->isChecked() << 0)
        ^ (ui->reserveBit1->isChecked() << 1)
        ^ (ui->reserveBit2->isChecked() << 2)
        ^ (ui->reserveBit3->isChecked() << 3)
        ^ (ui->reserveBit4->isChecked() << 4)
        ^ (ui->reserveBit5->isChecked() << 5)
        ^ (ui->reserveBit6->isChecked() << 6)
        ^ (ui->reserveBit7->isChecked() << 7)
        ^ (ui->reserveBit8->isChecked() << 8)
        ^ (ui->reserveBit9->isChecked() << 9)
        ^ (ui->reserveBit10->isChecked() << 10)
        ^ (ui->reserveBit11->isChecked() << 11)
        ^ (ui->reserveBit12->isChecked() << 12)
        ^ (ui->reserveBit13->isChecked() << 13)
        ^ (ui->reserveBit14->isChecked() << 14)
        ^ (ui->reserveBit15->isChecked() << 15)
    );
}

void ValidorMainWindow::on_sendValuesButton_clicked()
{
    static QRegExp hostaddressExp("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    static uint16_t packet[4];

    if (hostaddressExp.exactMatch(ui->hostaddressLineEdit->text()) == false) {
        QMessageBox::warning(this, "Некорректный адрес сервера", "Проверьте введнный Вами адрес соединения");
    }

    std::string ipaddr = ui->hostaddressLineEdit->text().toStdString();

    boost::asio::io_context context;
    udp::socket socket(context);
    udp::endpoint senderEndpoint(address::from_string(ipaddr), ui->portSpinBox->value());
    socket.open(udp::v4());

    pack(packet);

    std::cout
        << std::bitset<16>(packet[0]) << '\n'
        << std::bitset<16>(packet[1]) << '\n'
        << std::bitset<16>(packet[2]) << '\n'
        << std::bitset<16>(packet[3]) << '\n';

    boost::system::error_code err;
    size_t lenght = socket.send_to(boost::asio::buffer(packet), senderEndpoint, 0, err);
    socket.close();
    std::cout << "Sent Payload --- " << lenght << std::endl;
}


