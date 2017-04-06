#include "FFTOutlierDetector.h"
#include <iostream>
#include "LoopedQueue.h"

FFTOutlierDetector::FFTOutlierDetector()
{
}

FFTOutlierDetector::~FFTOutlierDetector()
{
}

void FFTOutlierDetector::detectOutliers(const std::vector<real*>& _magnitudes, unsigned int _instantSize,
										unsigned int _recordedHistory, unsigned int _subbandCount)
{
	unsigned int instantCount = _magnitudes.size();
	real* subbandTotals = new real[_subbandCount * instantCount];
	unsigned int binsPerInstant = _instantSize / 2;
	unsigned int binsPerSubband = binsPerInstant / _subbandCount;
	bool extraBin = ((real)binsPerSubband < ((real)binsPerInstant / _subbandCount));
	for (unsigned int i = 0; i < _subbandCount; i++)
	{
		for (unsigned int k = 0; k < instantCount; k++)
		{
			subbandTotals[i * instantCount + k] = 0;
			unsigned int mod = 0;
			if (extraBin && i == _subbandCount - 1)
			{
				mod = 1;
			}
			for (unsigned int j = 0; j < binsPerSubband + mod; j++)
			{
				real mag = _magnitudes.at(k)[j + i * binsPerSubband];
				subbandTotals[i * instantCount + k] += mag;
			}
			subbandTotals[i * instantCount + k] /= (binsPerSubband + mod);
		}
	}

	for (unsigned int i = 0; i < _subbandCount; i++)
	{
		OutlierDetector detector;
		detector.detectOutliers(&(subbandTotals[i* instantCount]), instantCount, 1, _recordedHistory);
		for (unsigned int j = 0; j< detector.getOutlierIndexes().size(); j++)
		{
			bool newOutlier = true;
			for (auto& out : m_outliers)
			{
				if (out.m_instant == detector.getOutlierIndexes().at(j))
				{
					newOutlier = false;
					out.m_subbands.push_back(i);
					out.m_thresholds.push_back(detector.getOutlierThresholds().at(j));
					break;
				}
			}
			if (newOutlier)
			{
				FrequencyOutlier outlier;
				outlier.m_instant = detector.getOutlierIndexes().at(j);
				outlier.m_subbands.push_back(i);
				outlier .m_thresholds.push_back(detector.getOutlierThresholds().at(j));
				m_outliers.push_back(outlier);
			}
		}
	}
}

const std::vector<FrequencyOutlier>& FFTOutlierDetector::getOutliers() const
{
	return m_outliers;
}
