#pragma once
#include <vector>
#include "FrequencyOutlier.h"

class FrequencySelectedBeats
{
private:
	std::vector<FrequencyOutlier> m_beats;
public:
	//Loads beat data from the file specified in _filename
	void loadFromFile(const char* _filename);
	
	//Gets total number of detected beats
	unsigned int getBeatCount() const;

	//Gets beat data at specified index
	FrequencyOutlier* getBeat(unsigned int _index);

	//Gets latest beat data from before the specified instant
	FrequencyOutlier* getLastBeatBefore(unsigned int _instant);
};