#include "2023_Day10.h"

#include "../AOCUtils.h"

const std::string test = "2023/Data/test.txt";

std::unordered_map<char, AOC_2023_10::ConnectorType> AOC_2023_10::CONNECTOR_MAP = {
    {'|', ConnectorType::NS},
    {'-', ConnectorType::EW},
    {'L', ConnectorType::NE},
    {'J', ConnectorType::NW},
    {'7', ConnectorType::SW},
    {'F', ConnectorType::SE},
    {'.', ConnectorType::NONE},
    {'S', ConnectorType::START}
};

void AOC_2023_10::Part1() {
    Tile* start = NULL;
    std::vector<std::vector<Tile*>> tiles = AdventOfCode::LoadDataFromFile<std::vector<Tile*>>(test, [this, &start](std::string line) {
        std::vector<Tile*> out;
        for(char c : line) {
            Tile* t = new Tile();
            t->type = CONNECTOR_MAP[c];
            out.push_back(t);
            if(t->type == ConnectorType::START) {
                start = t;
            }
        }
        return out;
    });

    connectTileMap(tiles);

    long loopLen = 2;
    Tile* prev = start;
    Tile* next = start->north;
    if(!next) {
        next = start->south;
    }
    if(!next) {
        next = start->east;
    }
    if(!next) {
        next = start->west;
    }
    while(next && next != start) {
        Tile* tmp = prev;
        prev = next;
        next = next->getNext(tmp);
        loopLen++;
    }
    printf("Max Dist: %ld", loopLen/2);
}

void AOC_2023_10::Part2() {
    
}

AOC_2023_10::Tile* AOC_2023_10::Tile::getNext(Tile* prev) {
    if(prev == north) {
        switch(type) {
        case ConnectorType::NS:
            return south;
        case ConnectorType::NE:
            return east;
        case ConnectorType::NW:
            return west;
        }
    } else if(prev == south) {
        switch(type) {
        case ConnectorType::NS:
            return north;
        case ConnectorType::SE:
            return east;
        case ConnectorType::SW:
            return west;
        }
    } else if(prev == east) {
        switch(type) {
        case ConnectorType::EW:
            return west;
        case ConnectorType::NE:
            return north;
        case ConnectorType::SE:
            return south;
        }
    } else if(prev == west) {
        switch(type) {
        case ConnectorType::EW:
            return east;
        case ConnectorType::NW:
            return north;
        case ConnectorType::SW:
            return south;
        }
    }
    return NULL;
}

bool AOC_2023_10::Tile::stronglyConnected() {
    switch(type) {
    case ConnectorType::NS:
        return north && south;
    case ConnectorType::EW:
        return east && west;
    case ConnectorType::NE:
        return north && east;
    case ConnectorType::NW:
        return north && west;
    case ConnectorType::SW:
        return south && west;
    case ConnectorType::SE:
        return south && east;
    case ConnectorType::NONE:
        return false;
    case ConnectorType::START:
        return true;
    }
    return false;
}

bool AOC_2023_10::Tile::shouldBeConnected(Direction d) {
    switch(d) {
    case Direction::North:
        return type == ConnectorType::NS || type == ConnectorType::NE || type == ConnectorType::NW || type == ConnectorType::START;
    case Direction::South:
        return type == ConnectorType::NS || type == ConnectorType::SE || type == ConnectorType::SW || type == ConnectorType::START;
    case Direction::East:
        return type == ConnectorType::EW || type == ConnectorType::NE || type == ConnectorType::SE || type == ConnectorType::START;
    case Direction::West:
        return type == ConnectorType::EW || type == ConnectorType::NW || type == ConnectorType::SW || type == ConnectorType::START;
    }
}

void AOC_2023_10::connectTileMap(std::vector<std::vector<Tile*>>& map) {
    for(int i = 0; i < map.size(); i++) {
        std::vector<Tile*>& row = map[i];
        for(int j = 0; j < row.size(); j++) {
            Tile* tile = row[j];
            if(!tile->north && tile->shouldBeConnected(Direction::North)) {
                if(i != 0 && map[i-1][j]->shouldBeConnected(Direction::South)) {
                    tile->north = map[i-1][j];
                    map[i-1][j]->south = tile;
                }
            }
            if(!tile->south && tile->shouldBeConnected(Direction::South)) {
                if(i != map.size()-1 && map[i+1][j]->shouldBeConnected(Direction::North)) {
                    tile->south = map[i+1][j];
                    map[i+1][j]->north = tile;
                }
            }
            if(!tile->east && tile->shouldBeConnected(Direction::East)) {
                if(j != 0 && map[i][j+1]->shouldBeConnected(Direction::West)) {
                    tile->east = map[i][j+1];
                    map[i][j+1]->west = tile;
                }
            }
            if(!tile->west && tile->shouldBeConnected(Direction::West)) {
                if(j != row.size()-1 && map[i][j-1]->shouldBeConnected(Direction::East)) {
                    tile->west = map[i][j-1];
                    map[i][j-1]->east = tile;
                }
            }
        }
    }
}
