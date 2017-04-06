#include "OutlierDetector.h"
#include <iostream>

OutlierDetector::OutlierDetector()
{
	m_history = nullptr;
}

OutlierDetector::~OutlierDetector()
{
	if (m_history)
	{
		delete m_history;
		m_history = nullptr;
	}
}

void OutlierDetector::detectOutliers(const real * _samples, unsigned int _sampleCount, unsigned int _instantSize, unsigned int _recordedHistory)
{
	real sensitivity = 0.1f;

	if (m_history)
	{
		delete m_history;
		m_history = nullptr;
	}
	unsigned int instantCount = _sampleCount / _instantSize;
	if ((float)_sampleCount / _instantSize != (float)((int)(_sampleCount / _instantSize)))
	{
		instantCount++;
	}

	m_history = new LoopedList<real>(_recordedHistory);

	//for each instant
	for (unsigned int i = 0; i < instantCount; i++)
	{ 
		real instantEnergySquared = 0;
		//for each sample in instant
		unsigned int samplesCovered = 0;
		for (unsigned int s = 0; s < _instantSize; s++)
		{
			real sample = 0;
			unsigned int index = i * _instantSize + s;
			if (index < _sampleCount)
			{
				sample = _samples[index];
				samplesCovered++;
			}
			instantEnergySquared += sample * sample;
		}
		real historyAverage = 0;
		int historyValuesCovered = 0;
		unsigned int historySize = m_history->getSize();
		for (int h = 0; h < historySize; h++)
		{
			real curHistoryValue = m_history->getRelative(-1 - h);
			historyAverage += curHistoryValue;// *curHistoryValue;	//maybe not squared here
			historyValuesCovered++;
		}
		if (historyValuesCovered > 0)
		{
			historyAverage /= (float)historyValuesCovered;
		}
		real energyDifference = instantEnergySquared - historyAverage;
		energyDifference *= energyDifference;
		real variance = (1.0 / _recordedHistory)  * energyDifference;
		sensitivity = (-0.0025714 * variance) + 1.5142857;

		if (instantEnergySquared > sensitivity * historyAverage)
		{
			m_outlierIndexes.push_back(i);
			m_outlierThresholds.push_back(instantEnergySquared - (sensitivity * historyAverage));
		}
		/*if(fabs(instantEnergySquared) - fabs(historyAverage) >= sensitivity)
		{
			m_outlierIndexes.push_back(i);
		}*/

		m_history->add(instantEnergySquared);
	}
}

const std::vector<unsigned int>& OutlierDetector::getOutlierIndexes() const
{
	return m_outlierIndexes;
}

const std::vector<real>& OutlierDetector::getOutlierThresholds() const
{
	return m_outlierThresholds;
}
