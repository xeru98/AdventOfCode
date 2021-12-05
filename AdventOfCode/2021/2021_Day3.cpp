#include "2021_Day3.h"
#include "../AOCUtils.h"

void AOC_2021_3::Part1 () {
	std::vector<BitArray> data = AdventOfCode::LoadDataFromFile<BitArray>(GetDataPath(), [](std::string in) {
		BitArray out;
		for(int i = 0; i < 12; i += 1) {
			out.data[i] = (in[i] == '1');
		}
		return out;
	});

	int trueArray[12] = {};
	for(BitArray ba : data) {
		for(int i = 0; i < 12; i += 1) {
			trueArray[i] += ba[i];
		}
	}
	int gammaRate = 0;
	int epsilonRate = 0;
	for(int i = 0; i < 12; i += 1) {
		bool posValue = trueArray[i] > (data.size()/2);
		gammaRate <<= 1;
		epsilonRate <<= 1;
		gammaRate += posValue;
		epsilonRate += !posValue;
	}
	std::printf("Gamma: %i, Epsilon: %i, Total: %i", gammaRate, epsilonRate, gammaRate*epsilonRate);
}

void AOC_2021_3::Part2 () {
	std::vector<BitArray> data = AdventOfCode::LoadDataFromFile<BitArray>(GetDataPath(), [](std::string in) {
		BitArray out;
		for(int i = 0; i < 12; i += 1) {
			out.data[i] = (in[i] == '1');
		}
		return out;
	});

	

	std::vector<BitArray> workingdata = data;
	int o2 = 0;
	int co2 = 0;
	
	//Calculate O2
	for(int i = 0; i < 12; i += 1) {

		//store the size since we are erasing from the data to filter
		const float dataHalfSize = workingdata.size() / 2.0;
		
		//at the beginning of each loop recount the number of values in each place
		int onVotes[12] = {};
		for(BitArray ba : workingdata) {
			for(int j = 0; j < 12; j += 1) {
				onVotes[j] += ba[j];
			}
		}
		
		for(std::vector<BitArray>::iterator it = workingdata.begin(); it != workingdata.end();) {
			//if our bit in the i place doesn't match the bit in the trueArray erase it
			if((*it)[i] != (onVotes[i] >= dataHalfSize)) { 
				it = workingdata.erase(it);
			} else {
				++it;
			}
		}
		
		//Assumption: at some point our data will be exactly 1
		if(workingdata.size() == 1) {
			o2 = workingdata[0].toInt();
			break;
		}
	}

	//Calculate CO2
	workingdata = data; //reset working data
	for(int i = 0; i < 12; i += 1) {

		//store the size since we are erasing from the data to filter
		const float dataHalfSize = workingdata.size() / 2.0;
		
		//at the beginning of each loop recount the number of values in each place
		int onVotes[12] = {};
		for(BitArray ba : workingdata) {
			for(int j = 0; j < 12; j += 1) {
				onVotes[j] += ba[j];
			}
		}
		
		for(std::vector<BitArray>::iterator it = workingdata.begin(); it != workingdata.end();) {
			//if our bit in the i place doesn't match the bit in the trueArray erase it
			if((*it)[i] != (onVotes[i] < dataHalfSize)) { 
				it = workingdata.erase(it);
			} else {
				++it;
			}
		}
		
		//Assumption: at some point our data will be exactly 1
		if(workingdata.size() == 1) {
			co2 = workingdata[0].toInt();
			break;
		}
	}

	std::printf("O2 Level: %i, CO2 Level: %i, Life Support Total: %i", o2, co2, o2 * co2);
}
