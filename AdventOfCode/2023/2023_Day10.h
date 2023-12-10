#pragma once

#include <unordered_map>

#include "../AOC.h"

class AOC_2023_10 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day10.txt"; }
	
    void Part1() override;
    void Part2() override;

private:
    enum class Direction : uint8_t {
        North,
        South,
        East,
        West
    };

    enum class ConnectorType: uint8_t {
        NS,
        EW,
        NE,
        NW,
        SW,
        SE,
        NONE,
        START
    };

    static std::unordered_map<char, ConnectorType> CONNECTOR_MAP;
    
    struct Tile {
        ConnectorType type;
        Tile* north;
        Tile* south;
        Tile* east;
        Tile* west;

        Tile* getNext(Tile* prev);
        bool stronglyConnected();
        bool shouldBeConnected(Direction d);
    };

    void connectTileMap(std::vector<std::vector<Tile*>>& map);
    
};
