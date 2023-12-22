#pragma once
#include <bitset>
#include <cstdint>
#include <map>

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

    void              packTo(uint16_t packet[4]);
    static Parameters unpack(uint16_t packet[4]);
};



