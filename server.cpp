#include <bitset>
#include <boost/asio.hpp>
#include <iostream>
#include <ostream>

using namespace boost::asio::ip;


struct Parameters
{
    enum class WorkMod {A = 0x0, B = 0x1, C = 0x2};
    enum class State   {A = 0x0, B = 0x1, C = 0x2};

    struct Coordinate { int x; int y; };

    Coordinate coord;
    int velocity;
    int power;
    float acceleration;
    std::bitset<16> reserve;

    WorkMod workMod;
    State state;
};

//
// | | |y|y|y|y|y|y| | |x|x|x|x|x|x|
// | | |s|s| | |m|m|v|v|v|v|v|v|v|v|
// |p|p|p|p|p|p|p|p|a|a|a|a|a|a|a|a|
// |r|r|r|r|r|r|r|r|r|r|r|r|r|r|r|r|
//
Parameters unpack(uint16_t packet[4])
{
    Parameters params;

    params.coord.x = static_cast <int> ((packet[0]) & 0x3f);
    params.coord.y = static_cast <int> ((packet[0] >> 8) & 0x3f);

    params.workMod = static_cast <Parameters::WorkMod> ((packet[1] >> 8) & 0x3);
    params.state = static_cast <Parameters::State> ((packet[1] >> 12) & 0x3);

    params.velocity = static_cast <int> ((packet[1]) & 0xff);

    params.acceleration = static_cast <float> (static_cast <int> (packet[2] & 0xff)) / 10;
    params.power = static_cast <int> ((packet[2] >> 8) & 0xff);

    params.reserve = packet[3];

    return params;
}


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

        /*
        std::cout
            << std::bitset<16>(packet[0]) << '\n'
            << std::bitset<16>(packet[1]) << '\n'
            << std::bitset<16>(packet[2]) << '\n'
            << std::bitset<16>(packet[3]) << '\n';
        */

        Parameters params = unpack(packet);

        std::cout
            << "X: " << params.coord.x << ", Y: " << params.coord.y << std::endl
            << "Скорость: " << params.velocity << std::endl
            << "Режим работы: " << (params.workMod == Parameters::WorkMod::A ? "A" : "other") << std::endl
            << "Состояние: " << (params.state == Parameters::State::A ? "A" : "other") << std::endl
            << "Ускорение: " << (params.acceleration) << std::endl
            << "Мощность: " << (params.power) << std::endl
            << "Резерв:" << params.reserve << std::endl;


        boost::system::error_code ignored_error;
        socket.send_to(boost::asio::buffer("Hey!"), remote_endpoint, 0, ignored_error);
    }

    return 0;
}
