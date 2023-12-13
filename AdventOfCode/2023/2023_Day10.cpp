#include "2023_Day10.h"

#include <unordered_set>

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
    std::vector<std::vector<Tile*>> tiles = AdventOfCode::LoadDataFromFile<std::vector<Tile*>>(GetDataPath(), [this, &start](std::string line) {
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

    const Loop loop(start);
    printf("Max Dist: %ld", loop.len/2);
}

void AOC_2023_10::Part2() {
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
	
	Loop loop(start);

	//replace all unvisited tiles with ground
	for(int y = 0; y < tiles.size(); y++) {
		std::vector<Tile*>& row = tiles[y];
		for(int x = 0; x < row.size(); x++) {
			Tile* tile = row[x];
			if(loop.visitedTiles->find(std::pair<int, int>(tile->x, tile->y)) == loop.visitedTiles->end()) {
				tile->type = ConnectorType::NONE;
			}
		}
	}

	//creep from edges to fill space
	std::vector<Tile*> edgeTiles = getEdgeTiles(tiles);
	for(Tile* t : edgeTiles) {
		fillSpace(t);
	}

	long numEnclosed = 0;
	for(int y = 0; y < tiles.size(); y++) {
		std::vector<Tile*>& row = tiles[y];
		for(int x = 0; x < row.size(); x++) {
			Tile* tile = row[x];
			if(tile->type == ConnectorType::NONE) {
				numEnclosed++;
			}
		}
	}

	printf("Num Enclosed: %ld", numEnclosed);
}

AOC_2023_10::Tile* AOC_2023_10::Tile::getNext(const Tile* prev) {
	if(!prev) {
		if(north) {
			return north;
		}
		if(south) {
			return south;
		}
		if(east) {
			return east;
		}
		if(west) {
			return west;
		}
	} else if(prev == north) {
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

AOC_2023_10::Loop::Loop (Tile* start) {
	len = 2;
	visitedTiles = new std::set<std::pair<int, int>>();
	Tile* prev = start;
	Tile* next = start->getNext(NULL);
	visitedTiles->emplace(std::pair<int, int>(start->x, start->y));
	visitedTiles->emplace(std::pair<int, int>(next->x, next->y));
	while(next && next != start) {
		Tile* tmp = prev;
		prev = next;
		next = next->getNext(tmp);
		len++;
		visitedTiles->emplace(std::pair<int, int>(next->x, next->y));
	}
	if(next != start) {
		len = -1;
		visitedTiles->clear();
	}
}

void AOC_2023_10::connectTileMap(std::vector<std::vector<Tile*>>& map) {
    for(int y = 0; y < map.size(); y++) {
        std::vector<Tile*>& row = map[y];
        for(int x = 0; x < row.size(); x++) {
            Tile* tile = row[x];
        	tile->x = x;
        	tile->y = y;
            if(!tile->north && tile->shouldBeConnected(Direction::North)) {
                if(y != 0 && map[y-1][x]->shouldBeConnected(Direction::South)) {
                    tile->north = map[y-1][x];
                    map[y-1][x]->south = tile;
                }
            }
            if(!tile->south && tile->shouldBeConnected(Direction::South)) {
                if(y != map.size()-1 && map[y+1][x]->shouldBeConnected(Direction::North)) {
                    tile->south = map[y+1][x];
                    map[y+1][x]->north = tile;
                }
            }
            if(!tile->east && tile->shouldBeConnected(Direction::East)) {
                if(x != row.size()-1 && map[y][x+1]->shouldBeConnected(Direction::West)) {
                    tile->east = map[y][x+1];
                    map[y][x+1]->west = tile;
                }
            }
            if(!tile->west && tile->shouldBeConnected(Direction::West)) {
                if(x != 0 && map[y][x-1]->shouldBeConnected(Direction::East)) {
                    tile->west = map[y][x-1];
                    map[y][x-1]->east = tile;
                }
            }
        }
    }
}

void AOC_2023_10::fillSpace (Tile* src) {
	if(!src) {
		return;
	}
	if(src->type == ConnectorType::NONE) {
		src->type = ConnectorType::UNENCLOSED;
		fillSpace(src->north);
		fillSpace(src->south);
		fillSpace(src->east);
		fillSpace(src->west);
	}
}

std::vector<AOC_2023_10::Tile*> AOC_2023_10::getEdgeTiles (std::vector<std::vector<Tile*>> tiles) {
	const size_t rowCnt = tiles.size();
	const size_t colCnt = tiles[0].size();
	std::vector<Tile*> out;
	for(Tile* t : tiles[0]) {
		out.push_back(t);
	}
	for(Tile* t : tiles[rowCnt-1]) {
		out.push_back(t);
	}
	for(int i = 1; i < rowCnt-1; i++) {
		out.push_back(tiles[i][0]);
		out.push_back(tiles[i][colCnt-1]);
	}
	return out;
}
