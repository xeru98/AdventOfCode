#pragma once

#include <unordered_map>
#include <set>

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
    	UNENCLOSED,
    	ENCLOSED,
        START
    };

    static std::unordered_map<char, ConnectorType> CONNECTOR_MAP;
    
    struct Tile {
        ConnectorType type;
        Tile* north;
        Tile* south;
        Tile* east;
        Tile* west;
    	int x;
    	int y;

        Tile* getNext(const Tile* prev);
        bool stronglyConnected();
        bool shouldBeConnected(Direction d);
    };

	struct Loop {
		long len;
		std::set<std::pair<int, int>>* visitedTiles;

		Loop(Tile* start);
	};

    void connectTileMap(std::vector<std::vector<Tile*>>& map);
    void fillSpace(Tile* src);

	std::vector<Tile*> getEdgeTiles(std::vector<std::vector<Tile*>> tiles);
};
