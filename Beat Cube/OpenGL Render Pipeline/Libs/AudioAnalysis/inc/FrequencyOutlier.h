#pragma once
#include <vector>

struct FrequencyOutlier
{
	unsigned int m_instant;
	std::vector<unsigned int> m_subbands;
	std::vector<float> m_thresholds;
};
