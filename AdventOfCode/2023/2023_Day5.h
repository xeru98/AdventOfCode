#pragma once
#include <vector>

#include "../AOC.h"

class AOC_2023_5 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day5.txt"; }
	
    void Part1() override;
    void Part2() override;

private:

    struct Interval {
        unsigned long start;
        unsigned long end;

        bool covers(Interval other) {
            return start <= other.start && end >= other.end;
        }

        void shift(unsigned long diff) {
            start += diff;
            end += diff;
        }
    };

    struct Intersection {
        bool intersects;
        Interval interval;
    };

    struct TargetMap {
        unsigned long src;
        unsigned long dst;
        unsigned long cnt;

        bool isIn(unsigned long val) {
            return val >= src && val <= src+cnt;
        }

        unsigned long getDiff() {
            return dst-src;
        }

        unsigned long getDst(unsigned long val) {
            if(!isIn(val)) {
                return -1;
            } else {
                return val+dst-src;
            }
        }

        Interval getSrcInterval() {
            Interval i;
            i.start = src;
            i.end = src+cnt;
            return i;
        }

        Interval toDstInterval(Interval srcInterval) {
            unsigned long diff = dst-src;
            srcInterval.start += diff;
            srcInterval.end += diff;
            return srcInterval;
        }
    };

    class TreeNode {
    public:
        std::vector<TreeNode*> children;
        Interval src;
        long shift;
        Interval getDstInterval() {
            Interval out;
            out.start = src.start + shift;
            out.end = src.end + shift;
            return out;
        }

        bool isLeaf() {
            return children.size() == 0;
        }
    };

    unsigned long getDst(unsigned long src, std::vector<TargetMap*>*& targets);

    Intersection getIntersection(Interval a, Interval b);

    std::vector<Interval> removeIntersection(Interval src, Interval remove);
    std::vector<Interval> removeIntersection(std::vector<Interval> src, Interval remove);
    

    TreeNode* createNode(Interval interval, long shift, std::vector<std::vector<TargetMap*>*>& almanac, size_t index);
    unsigned long getMinLocation(TreeNode* node);
};
