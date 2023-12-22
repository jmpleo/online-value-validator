#include "params.h"
#include <cstdint>


//
// | | |y|y|y|y|y|y| | |x|x|x|x|x|x|
// | | |s|s| | |m|m|v|v|v|v|v|v|v|v|
// |p|p|p|p|p|p|p|p|a|a|a|a|a|a|a|a|
// |r|r|r|r|r|r|r|r|r|r|r|r|r|r|r|r|
//
Parameters Parameters::unpack(uint16_t packet[4])
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

void Parameters::packTo(uint16_t packet[4])
{
    packet[0] = (
        (0x3f & coord.x) // 0 - 5
        ^
        ((0x3f & coord.y) << 8) // 8 - 13
    );

    packet[1] = (
        (0xff & velocity) // 0 - 7
        ^
        ((0x3 & static_cast <int> (workMod)) << 8) // 8 - 11
        ^
        ((0x3 & static_cast <int> (state)) << 12) // 12 - 15
    );

    packet[2] = (
        (0xff & static_cast <uint8_t> (acceleration * 10.0)) // 0 - 7
        ^
        ((0xff & power) << 8) // 8 - 15
    );

    packet[3] = static_cast <uint16_t> (reserve.to_ulong());
}

