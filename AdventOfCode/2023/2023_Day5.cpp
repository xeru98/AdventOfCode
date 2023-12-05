#include "2023_Day5.h"

#include <set>
#include <unordered_set>
#include <vector>

#include "../AOCUtils.h"

const std::string test = "2023/Data/test.txt";

void AOC_2023_5::Part1() {
    std::vector<unsigned long> seeds;
    std::vector<std::vector<TargetMap*>*> maps;
    AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &seeds, &maps](std::string line) {
        if(line.length() == 0) {
            maps.push_back(new std::vector<TargetMap*>());
            return;
        }
        std::vector<std::string> parts = AdventOfCode::splitString(line, " ");
        if(seeds.size() == 0) {
            
            for(int i = 1; i < parts.size(); i+=1) {
                seeds.push_back(strtoul(parts[i].c_str(), NULL, 10));
            }
            return;
        }

        if(parts.size() != 3) {
            return;
        }

        TargetMap* newMap = new TargetMap();
        newMap->dst = strtoul(parts[0].c_str(), NULL, 10);
        newMap->src = strtoul(parts[1].c_str(), NULL, 10);
        newMap->cnt = strtoul(parts[2].c_str(), NULL, 10);
        (*(maps.end()-1))->push_back(newMap);
    });

    unsigned long minLoc = NULL;
    for(unsigned long seed : seeds) {
        unsigned long next = seed;
        for(std::vector<TargetMap*>* tmap : maps) {
            next = getDst(next, tmap);
        }
        if(minLoc == NULL) {
            minLoc = next;
        } else {
            minLoc = std::min(minLoc, next);
        }
    }

    printf("Minimum Location: %ld", minLoc);
}

void AOC_2023_5::Part2() {
    std::vector<Interval> seedIntervals;
    std::vector<std::vector<TargetMap*>*> almanac;
    AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &seedIntervals, &almanac](std::string line) {
        if(line.length() == 0) {
            almanac.push_back(new std::vector<TargetMap*>());
            return;
        }
        std::vector<std::string> parts = AdventOfCode::splitString(line, " ");
        if(seedIntervals.size() == 0) {
            
            for(int i = 1; i < parts.size(); i+=2) {
                Interval interval;
                interval.start = strtoul(parts[i].c_str(), NULL, 10);
                interval.end = interval.start + strtoul(parts[i+1].c_str(), NULL, 10)-1;
                seedIntervals.push_back(interval);
            }
            return;
        }

        if(parts.size() != 3) {
            return;
        }

        TargetMap* newMap = new TargetMap();
        newMap->dst = strtoul(parts[0].c_str(), NULL, 10);
        newMap->src = strtoul(parts[1].c_str(), NULL, 10);
        newMap->cnt = strtoul(parts[2].c_str(), NULL, 10);
        (*(almanac.end()-1))->push_back(newMap);
    });

    unsigned long minLoc = NULL;
    for(Interval seedInt : seedIntervals) {
        TreeNode* root = createNode(seedInt, 0, almanac, 0);
        if(minLoc == NULL) {
            minLoc = getMinLocation(root);
        } else {
            minLoc = std::min(minLoc, getMinLocation(root));
        }
    }
    

    printf("Minimum Location: %ld", minLoc);
}

unsigned long AOC_2023_5::getDst(unsigned long src, std::vector<TargetMap*>*& targets) {
    for(TargetMap* tmap : (*targets)) {
        unsigned long dst = tmap->getDst(src);
        if(dst != -1) {
            return dst;
        }
    }
    return src;
}

AOC_2023_5::Intersection AOC_2023_5::getIntersection(Interval a, Interval b) {
    Intersection i;
    if(a.end < b.start || a.start > b.end) {
        i.intersects = false;
        return i;
    }

    i.intersects = true;
    i.interval.start = std::max(a.start, b.start);
    i.interval.end = std::min(a.end, b.end);
}

std::vector<AOC_2023_5::Interval> AOC_2023_5::removeIntersection(Interval src, Interval remove) {
    std::vector<Interval> out;
    Intersection intersect = getIntersection(src, remove);
    if(!intersect.intersects) {
        out.push_back(src);
        return out;
    }

    //in this case there is nothing left
    // src [.........]
    // int [.........]
    // rem 
    if(intersect.interval.covers(src)) {
        return out;
    }

    // src [.........]
    // int [....]
    // rem      [....]
    if(intersect.interval.start <= src.start) {
        Interval remaining = src;
        remaining.start = intersect.interval.end+1;
        out.push_back(remaining);
        return out;
    }

    // src [.........]
    // int      [....]
    // rem [....]
    if(intersect.interval.end >= src.end) {
        Interval remaining = src;
        remaining.end = intersect.interval.start-1;
        out.push_back(remaining);
        return out;
    }


    //if we have 2 left then the remaining looks like
    // src [.........]
    // int    [....]
    // rem [..]    [.]
    Interval left = src;
    left.end = intersect.interval.start-1;
    out.push_back(left);
    Interval right = src;
    right.start = intersect.interval.end+1;
    out.push_back(right);
    return out;
}

std::vector<AOC_2023_5::Interval> AOC_2023_5::removeIntersection(std::vector<Interval> src, Interval remove) {
    std::vector<Interval> out;
    for(Interval sI : src) {
        std::vector<Interval> parts = removeIntersection(sI, remove);
        for(Interval pI : parts) {
            out.push_back(pI);
        }
    }
    return out;
}

AOC_2023_5::TreeNode* AOC_2023_5::createNode(Interval interval, long shift, std::vector<std::vector<TargetMap*>*>& almanac, size_t index) {
    TreeNode* out = new TreeNode();
    out->src = interval;
    out->shift = shift;
    if(index >= almanac.size()) {
        return out;
    }
    Interval dst = out->getDstInterval();
    std::vector<TargetMap*> tMaps = *almanac[index];
    std::vector<Interval> unmatched;
    unmatched.push_back(dst);
    for(TargetMap* tmap : tMaps) {
        if(unmatched.size() == 0) {
            break; //we have already checked everything
        }
        Intersection intersection = getIntersection(dst, tmap->getSrcInterval());
        if(!intersection.intersects) {
            continue;
        }
        //create child node for matched interval
        out->children.push_back(createNode(intersection.interval, tmap->getDiff(), almanac, index+1));

        // keep track of what is still unmatched
        unmatched = removeIntersection(unmatched, intersection.interval);
    }

    //create children for each unmatched
    for(Interval i : unmatched) {
        out->children.push_back(createNode(i, 0, almanac, index+1));
    }
    return out;
}

unsigned long AOC_2023_5::getMinLocation(TreeNode* node) {
    if(node->isLeaf()) {
        return node->getDstInterval().start;
    }
    unsigned long minLoc = getMinLocation(node->children[0]);
    for(int i = 1; i < node->children.size(); i++) {
        minLoc = std::min(minLoc, getMinLocation(node->children[i]));
    }
    return minLoc;
}



