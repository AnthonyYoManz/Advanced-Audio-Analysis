#include "stdafx.h"
#include "AudioAnalysis.h"
#include <fstream>

void FrequencySelectedBeats::loadFromFile(const char* _filename)
{
	std::ifstream reader;
	reader.open(_filename);
	if (reader.is_open())
	{
		int beatCount = 0;
		reader >> beatCount;
		for (int i = 0; i < beatCount; i++)
		{
			FrequencyOutlier beat;
			reader >> beat.m_instant;

			int beatSubbandCount = 0;
			reader >> beatSubbandCount;
			for (int j = 0; j < beatSubbandCount; j++)
			{
				int subbandIndex = 0;
				reader >> subbandIndex;

				float threshold = 0;
				reader >> threshold;

				beat.m_subbands.push_back(subbandIndex);
				beat.m_thresholds.push_back(threshold);
			}

			m_beats.push_back(beat);
		}
		reader.close();
	}
}

unsigned int FrequencySelectedBeats::getBeatCount() const
{
	return m_beats.size();
}

FrequencyOutlier* FrequencySelectedBeats::getBeat(unsigned int _index)
{
	if (_index < getBeatCount())
	{
		return &(m_beats.at(_index));
	}
	return nullptr;
}

FrequencyOutlier* FrequencySelectedBeats::getLastBeatBefore(unsigned int _instant)
{
	FrequencyOutlier* result = getBeat(0);
	unsigned int curIndex = 0;
	for (unsigned int i=0; i<m_beats.size(); i++)
	{
		if (m_beats.at(i).m_instant > _instant)
		{
			break;
		}
		curIndex = i;
	}
	if (curIndex > 0)
	{
		result = getBeat(curIndex);
	}
	return result;
}
