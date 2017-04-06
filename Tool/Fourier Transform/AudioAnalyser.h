#pragma once
#include "Aliases.h"
#include "FourierTransform.h"
#include "AudioSpectrum.h"
#include "OutlierDetector.h"
#include "FFTOutlierDetector.h"

struct AudioInstantData
{
	const real* m_samples;
	unsigned int m_sampleSize;
	const real* m_frequencyMagnitudes;
	unsigned int m_binCount;
	const AudioSpectrumInstant* m_audioSpectrum;
	bool m_potentialBeat;
};

class AudioAnalyser
{
private:
	OutlierDetector m_beatDetector;
	FFTOutlierDetector m_frequencyBeatDetector;
	FFTResult m_fftResult;
	FFTResult* m_normalisedFFTResult;
	AudioSpectrum m_audioSpectrum;
	real* m_srcSamples;	//original samples
	unsigned int m_srcSampleCount;
	real* m_samples;	//normalised/modified samples
	unsigned int m_sampleCount;
public:
	AudioAnalyser();
	~AudioAnalyser();
	void setSamples(real* _samples, unsigned int _sampleCount);
	void cleanup();
	void analyseAudio(unsigned int _instantSize);
	void analyseAudio(unsigned int _binCount, unsigned int _instantSize);
	void saveFrequencySelectedBeats();

	const real* getSourceSamples();
	unsigned int getSourceSampleCount();
	const real* getSamples();
	unsigned int getSampleCount();
	const FFTResult& getFFTResult() const;
	const FFTResult& getNormalisedFFTResult();
	const AudioSpectrum& getAudioSpectrum();
	const OutlierDetector& getOutlierDetector() const;
	const FFTOutlierDetector& getFFTOutlierDetector() const;
	AudioInstantData getInstantDataAtIndex(unsigned int _index);
};

