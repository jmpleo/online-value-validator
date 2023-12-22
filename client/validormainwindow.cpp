#include "validormainwindow.h"
#include "./ui_validormainwindow.h"
#include "../utils/params.h"

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


void ValidorMainWindow::proccessForm(Parameters &params)
{
    params.coord.x = ui->coordXSpinBox->value();
    params.coord.y = ui->coordYSpinBox->value();

    params.velocity = ui->velocitySpinBox->value();

    params.workMod
        = ui->workModARadioButton->isChecked() ?
            Parameters::WorkMod::A

        : ui->workModBRadioButton->isChecked() ?
            Parameters::WorkMod::B
        :
            Parameters::WorkMod::C;

    params.state
        = ui->stateARadioButton->isChecked() ?
            Parameters::State::A
        : ui->stateBRadioButton->isChecked() ?
            Parameters::State::B
        :
            Parameters::State::C;


    params.acceleration = ui->accelerationDoubleSpinBox->value();
    params.power = ui->powerSpinBox->value();

    params.reserve.set(0, ui->reserveBit0->isChecked());
    params.reserve.set(1, ui->reserveBit1->isChecked());
    params.reserve.set(2, ui->reserveBit2->isChecked());
    params.reserve.set(3, ui->reserveBit3->isChecked());
    params.reserve.set(4, ui->reserveBit4->isChecked());
    params.reserve.set(5, ui->reserveBit5->isChecked());
    params.reserve.set(6, ui->reserveBit6->isChecked());
    params.reserve.set(7, ui->reserveBit7->isChecked());
    params.reserve.set(8, ui->reserveBit8->isChecked());
    params.reserve.set(9, ui->reserveBit9->isChecked());
    params.reserve.set(10, ui->reserveBit10->isChecked());
    params.reserve.set(11, ui->reserveBit11->isChecked());
    params.reserve.set(12, ui->reserveBit12->isChecked());
    params.reserve.set(13, ui->reserveBit13->isChecked());
    params.reserve.set(14, ui->reserveBit14->isChecked());
    params.reserve.set(15, ui->reserveBit15->isChecked());
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

    Parameters params;
    proccessForm(params);
    params.packTo(packet);

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


