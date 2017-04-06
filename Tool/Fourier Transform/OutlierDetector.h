#pragma once
#include "Aliases.h"
#include "LoopedQueue.h"
#include <vector>

class OutlierDetector
{
private:
	LoopedList<real>* m_history;
	std::vector<unsigned int> m_outlierIndexes;
	std::vector<real> m_outlierThresholds;
public:
	OutlierDetector();
	~OutlierDetector();
	void detectOutliers(const real* _samples, unsigned int _sampleCount, unsigned int _instantSize, unsigned int _recordedHistory);
	const std::vector<unsigned int>& getOutlierIndexes() const;
	const std::vector<real>& getOutlierThresholds() const;
};