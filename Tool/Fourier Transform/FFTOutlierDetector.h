#pragma once
#include "Aliases.h"
#include <vector>
#include "OutlierDetector.h"

struct FrequencyOutlier
{
	unsigned int m_instant;
	std::vector<unsigned int> m_subbands;
	std::vector<real> m_thresholds;
};

class FFTOutlierDetector
{
private:
	unsigned int m_outlierDetectorCount;
	std::vector<FrequencyOutlier> m_outliers;
public:
	FFTOutlierDetector();
	~FFTOutlierDetector();
	void detectOutliers(const std::vector<real*>& _magnitudes, unsigned int _instantSize, 
						unsigned int _recordedHistory, unsigned int _subbandCount);
	const std::vector<FrequencyOutlier>& getOutliers() const;
};
