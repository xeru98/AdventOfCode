#include "2023_Day3.h"

#include <set>
#include <vector>

#include "../AOCUtils.h"

void AOC_2023_3::Part1() {
    int lineNum = 0;
    std::vector<PartNumber*> numbers;
    std::vector<PartSymbol*> symbols;

    AdventOfCode::ProcessDataFromFileInline("2023/Data/d3tst.txt", [this, &numbers, &symbols, &lineNum](std::string line) mutable {
        PartNumber* nextNum = NULL;
        for(int i = 0; i < line.length(); i++) {
            char c = line[i];
            if(isSymbol(c)) {
                symbols.push_back(new PartSymbol(lineNum, i));
            }
            
            if(nextNum == NULL) {
                if(isNumber(c)) {
                    nextNum = new PartNumber(lineNum, i, -1);
                    nextNum->valStr += c;
                }
            } else {
                if(isNumber(c)) {
                    nextNum->valStr += c;
                }
                if(!isNumber(c)) {
                    nextNum->endCol = i-1;
                    numbers.push_back(nextNum);
                    nextNum = NULL;
                }
            }
        }
        if(nextNum != NULL) {
            nextNum->endCol = line.length()-1;
            numbers.push_back(nextNum);
        }

        lineNum++;
    });
    std::vector<PartNumber*> adjPN;
    for(PartNumber* pn : numbers) {
        for(PartSymbol* ps : symbols) {
            if(isAdjacent(pn, ps)) {
                adjPN.push_back(pn);
            }
        }
    }
    long sum = 0;
    for(PartNumber* pn : adjPN) {
        sum += pn->val();
    }
    printf("PN Sum: %ld", sum);
}

void AOC_2023_3::Part2() {
    int lineNum = 0;
    std::vector<PartNumber*> numbers;
    std::vector<Gear*> gears;

    AdventOfCode::ProcessDataFromFileInline("2023/Data/d3tst.txt", [this, &numbers, &gears, &lineNum](std::string line) mutable {
        PartNumber* nextNum = NULL;
        for(int i = 0; i < line.length(); i++) {
            char c = line[i];
            if(c == '*') {
                gears.push_back(new Gear(lineNum, i));
            }
            
            if(nextNum == NULL) {
                if(isNumber(c)) {
                    nextNum = new PartNumber(lineNum, i, -1);
                    nextNum->valStr += c;
                }
            } else {
                if(isNumber(c)) {
                    nextNum->valStr += c;
                }
                if(!isNumber(c)) {
                    nextNum->endCol = i-1;
                    numbers.push_back(nextNum);
                    nextNum = NULL;
                }
            }
        }
        if(nextNum != NULL) {
            nextNum->endCol = line.length()-1;
            numbers.push_back(nextNum);
        }

        lineNum++;
    });
    for(PartNumber* pn : numbers) {
        for(Gear* g : gears) {
            if(isAdjacent(pn, g)) {
                g->numbers.push_back(pn);
            }
        }
    }
    long sum = 0;
    for(Gear* g : gears) {
        if(g->numbers.size() == 2) {
            sum += g->ratio();
        }
    }
    printf("Gear Ratio Sum: %ld", sum);
}

bool AOC_2023_3::isAdjacent(PartNumber* pn, PartSymbol* ps) {
    bool adjCol = pn->startCol-1 <= ps->col && pn->endCol+1 >= ps->col;
    bool adjRow = pn->row-1 <= ps->row && pn->row + 1 >= ps->row;
    return adjCol && adjRow;
}
