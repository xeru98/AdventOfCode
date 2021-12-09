#include "2021_Day8.h"

#include <algorithm>

#include "../AOCUtils.h"

void AOC_2021_8::Part1 () {
	int numOne = 0;
	int numFour = 0;
	int numSeven = 0;
	int numEight = 0;
	AdventOfCode::LoadDataFromFile<void*>(GetDataPath(), [&numOne, &numFour, &numSeven, &numEight](std::string in) mutable {
		std::string input = AdventOfCode::splitString(in, " | ")[1];
		std::vector<std::string> values = AdventOfCode::splitString(input, " ");
		for(std::string s : values) {
			if(s.length() == 2) {
				numOne += 1;
			} else if (s.length() == 4) {
				numFour += 1;
			} else if (s.length() == 3) {
				numSeven += 1;
			} else if (s.length() == 7) {
				numEight += 1;
			}
		}
		return nullptr;
	});
	std::printf("1: %i | 4: %i | 7: %i | 8: %i | Total: %i", numOne, numFour, numSeven, numEight, numOne+numFour+numSeven+numEight);
}

void AOC_2021_8::Part2 () {
	int sum = 0;
	AdventOfCode::LoadDataFromFile<void*>(GetDataPath(), [this, &sum](std::string in) mutable {
		std::vector<std::string> parts = AdventOfCode::splitString(in, " | ");
		std::vector<std::string> config = AdventOfCode::splitString(parts[0], " ");
		std::vector<std::string> encodedValues = AdventOfCode::splitString(parts[1], " ");
		std::sort(config.begin(), config.end(), [](std::string lhs, std::string rhs) {
			if(lhs.length() != rhs.length()) {
				return lhs.length() < rhs.length();
			}
			for(int i = 0; i < lhs.size(); i += 1) {
				if(lhs[i] != rhs[i]) {
					return lhs[i] < rhs[i];
				}
			}
			return true;
		});
		/* Store the possible flags for each position
		 * 0: Top Center
		 * 1: Top Left
		 * 2: Top Right
		 * 3: Center
		 * 4: Bottom Left
		 * 5: Bottom Right
		 * 6: Bottom Center
		 */
		int positionDecode[7] = {127, 127, 127, 127, 127, 127, 127}; //stored as candidate flags 
		int valueDecode[10] = {0, 0, 0, 0, 0, 0, 0, 0, 127, 0}; //8 will always be 0111 1111 which is 127

		//decode the known numbers and positions from sorting
		//1 (len 2) determines pair 2,5 0010010
		valueDecode[1] = stringToInt(config[0]);
		setPositionCandidates(&positionDecode[0], 0b0100100,valueDecode[1]);

		//7 (len 3) determines 0 0000001
		valueDecode[7] = stringToInt(config[1]);
		setPositionCandidates(&positionDecode[0], 0b0000001, valueDecode[7]-valueDecode[1]);

		//4 (len 4) determines pair 1,3 0001010
		valueDecode[4] = stringToInt(config[2]);
		setPositionCandidates(&positionDecode[0], 0b0001010, valueDecode[4]-valueDecode[1]);

		//6, 9, & 0 (len 6)
		//find 9 to fill in position 6 (and 4 by process of elimination)
		//9 uses panels 0,1,2,3,5, & 6. so we look to see if 9 - (0 + 2,5 + 1,3) is a power of 2
		for(int i = 6; i < 9; i += 1) {
			int checkRaw = stringToInt(config[i]);
			int base = positionDecode[0] + positionDecode[1] + positionDecode[2]; //remember 1 and 2 current contain pair data
			if(isNumberPow2(checkRaw - base)) {
				valueDecode[9] = checkRaw;
				setPositionCandidates(&positionDecode[0], 0b1000000, (checkRaw - base));
			}
		}
		
		//2, 3, & 5 (len 5)
		//find 2 to fill in positions 2 and 3 (and 1 and 5 by process of elimination)
		for(int i = 3; i < 6; i += 1) {
			int checkRaw = stringToInt(config[i]);
			int base = positionDecode[0] + positionDecode[4] + positionDecode[6]; //2 is the only number that contains 0,4 and 6
			if((checkRaw & base) == base) {
				valueDecode[2] = checkRaw;
				setPositionCandidates(&positionDecode[0], 0b0001000, (checkRaw & positionDecode[3]));
				setPositionCandidates(&positionDecode[0], 0b0000100, (checkRaw & positionDecode[2]));
			}
		}

		//solve 0, 3, 5, 6
		valueDecode[0] = positionDecode[0] + positionDecode[1] + positionDecode[2] + positionDecode[4] + positionDecode[5] + positionDecode[6];
		valueDecode[3] = positionDecode[0] + positionDecode[2] + positionDecode[3] + positionDecode[5] + positionDecode[6];
		valueDecode[5] = positionDecode[0] + positionDecode[1] + positionDecode[3] + positionDecode[5] + positionDecode[6];
		valueDecode[6] = positionDecode[0] + positionDecode[1] + positionDecode[3] + positionDecode[4] + positionDecode[5] + positionDecode[6];

		int values[4];
		for(int i = 0; i < 4; i += 1) {
			values[i] = getDecodedDigit(&valueDecode[0], encodedValues[i]);
		}
		sum += (1000 * values[0]) + (100 * values[1]) + (10 * values[2]) + values[3];
		return nullptr;
	});

	printf("Total sum: %i", sum);
}

int AOC_2021_8::letterToInt (char c) {
	if(c >= 'a' && c <= 'g') {
		return 1 << (c-'a');
	}
	return 0;
}

int AOC_2021_8::stringToInt (std::string s) {
	int sum = 0;
	for(char c : s) {
		sum += letterToInt(c);
	}
	return sum;
}

int AOC_2021_8::getDecodedDigit (const int values[10], std::string encodedDigit) {
	int encodedValue = stringToInt(encodedDigit);
	for(int i = 0; i < 10; i += 1) {
		if(values[i] == encodedValue) {
			return i;
		}
	}
	return -1;
}

void AOC_2021_8::setPositionCandidates (int positions[7], int positionFlags, int candidateFlags) {
	for(int i = 0; i < 7; i += 1) {
		int checkFlag = 1 << i;
		if((checkFlag & positionFlags) == checkFlag) {
			positions[i] = candidateFlags;
		} else {
			positions[i] = (positions[i] | candidateFlags) - candidateFlags;
		}
	}
}

bool AOC_2021_8::isNumberPow2 (int n) {
	int bitCount = 0;
	while(n > 0) {
		if(n%2 == 1) {
			bitCount += 1;
		}
		n >>= 1;
	}
	return bitCount == 1;
}
