#pragma once
#include "../AOC.h"

class  AOC_2021_3 : public AdventOfCodeDay {
public:
	std::string GetDataPath () override {return "2021/Data/Day3.txt"; }
	void Part1 () override;
	void Part2 () override;

private:
	struct BitArray {
		bool data[12];
		
		int operator[](size_t index) const {
			return data[index];
		}

		int toInt() const {
			int out = 0;
			for(int i = 0; i < 12; i += 1) {
				out <<= 1;
				out += data[i];
			}
			return out;
		}
	};
};
