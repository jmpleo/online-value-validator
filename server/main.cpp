#include "../utils/params.h"

#include <bitset>
#include <boost/asio.hpp>
#include <iostream>
#include <ostream>

using namespace boost::asio::ip;


int main(int argc, char** argv)
{
    if (argc != 3 || std::string(argv[1]) != "-p") {
        std::cout << "Использование: " << argv[0] << " -p <номер порта>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[2]);

    boost::asio::io_context context;
    udp::socket socket(context, udp::endpoint(udp::v4(), port));

    static uint16_t packet[4];

    for (;;) {
        udp::endpoint remote_endpoint;
        socket.receive_from(boost::asio::buffer(packet), remote_endpoint);


        std::cout
            << std::bitset<16>(packet[0]) << '\n'
            << std::bitset<16>(packet[1]) << '\n'
            << std::bitset<16>(packet[2]) << '\n'
            << std::bitset<16>(packet[3]) << '\n';


        Parameters params = Parameters::unpack(packet);

        std::cout
            << "X: " << params.coord.x << ", Y: " << params.coord.y << std::endl
            << "Скорость: " << params.velocity << std::endl
            << "Режим работы: " << (
                params.workMod == Parameters::WorkMod::A ? 'A'
                : params.workMod == Parameters::WorkMod::B ? 'B'
                : 'C'
            ) << std::endl
            << "Состояние: " << (
                params.state == Parameters::State::A ? 'A'
                : params.state == Parameters::State::B ? 'B'
                : 'C'
            ) << std::endl
            << "Ускорение: " << (params.acceleration) << std::endl
            << "Мощность: " << (params.power) << std::endl
            << "Резерв:" << params.reserve << std::endl;


        boost::system::error_code ignored_error;
        socket.send_to(boost::asio::buffer("Hey!"), remote_endpoint, 0, ignored_error);
    }

    return 0;
}
