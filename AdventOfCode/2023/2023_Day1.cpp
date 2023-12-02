//
// Created by Xeru on 12/1/2021.
//
#include "2023_Day1.h"
#include "../AOCUtils.h"

void AOC_2023_1::Part1() {
	//Load text file into list of integers
	std::vector<long int> data = AdventOfCode::LoadDataFromFile<long int>(GetDataPath(), [this](std::string in){
		char values[2] = {'\0', '\0'};
		int i = 0;
		while(true) {
			char c = in[i++];
			if(isInt(c)) {
				values[0] = c;
				break;
			}
		}
		i = in.size()-1;
		while(true) {
			char c = in[i--];
			if(isInt(c)) {
				values[1] = c;
				break;
			}
		}

		return strtol(values, NULL, 10);
	});
	long int sum = 0;
	for(long int li : data) {
		sum += li;
	}
	printf("Sum: %ld", sum);
}

void AOC_2023_1::Part2() {
	long int sum = 0;
	AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &sum](std::string in)mutable {
		int i = 0;
		while(true) {
			std::string sub = in.substr(i, std::min((size_t)5, in.length()-i));
			if(isInt(sub[0])) {
				sum += ((sub[0]-'0') * 10);
				break;
			}
			long int v = findNumStr(sub);
			if(v != -1) {
				sum += v * 10;
				break;
			}
			i++;
		}
		i = in.size()-1;
		while(true) {
			std::string sub = in.substr(i, std::min((size_t)5, in.length()-i));
			if(isInt(sub[0])) {
				sum += (sub[0]-'0');
				break;
			}
			long int v = findNumStr(sub);
			if(v != -1) {
				sum += v;
				break;
			}
			i--;
		}
	});
	printf("Sum: %ld", sum);
}

long int AOC_2023_1::findNumStr(std::string s) {
	std::unordered_map<std::string, int>::const_iterator it;
	size_t len = s.length();
	do {
		it = NUM_STR.find(s.substr(0, len));
		if(it == NUM_STR.end()) {
			len--;
		} else {
			break;
		}
	} while(len >= 3);
	return it == NUM_STR.end() ? -1 : it->second;
}
