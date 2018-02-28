/*
==============================================================================

Equalizer.cpp

==============================================================================
*/

#include "Equalizer.h"

namespace reverb {

	Equalizer::Equalizer(juce::AudioProcessor * processor)
		: Task(processor) {

		filterSet.add(new LowShelfFilter(processor));
		filterSet.add(new PeakFilter(processor));
		filterSet.add(new PeakFilter(processor));
		filterSet.add(new PeakFilter(processor));
		filterSet.add(new PeakFilter(processor));
		filterSet.add(new HighShelfFilter(processor));

		for (int i = 0; i < filterSet.size(); i++) {
			EQGains.push_back(1.0f);
		}

		setFilterFrequency(1000, LOW);
		setFilterGain(2, LOW);
		setFilterQ(0.71, LOW);

		setFilterFrequency(2000, PEAK1);
		setFilterGain(2, PEAK1);
		setFilterQ(4, PEAK1);

		setFilterFrequency(3000, PEAK2);
		setFilterGain(2, PEAK2);
		setFilterQ(4, PEAK2);

		setFilterFrequency(4000, HIGH);
		setFilterGain(2, HIGH);
		setFilterQ(4, HIGH);

		setFilterFrequency(5000, 4);
		setFilterGain(2, 4);
		setFilterQ(4, 4);

		setFilterFrequency(6000, 5);
		setFilterGain(2, 5);
		setFilterQ(0.71, 5);
	}

	void Equalizer::exec(juce::AudioSampleBuffer& ir) {
		updateFilters();

		for (int i = 0; i < filterSet.size(); i++) {
			filterSet[i]->exec(ir);
		}
	}

	void Equalizer::updateFilters() {

		//Update filter parameters before gain normalization

		const int dim = filterSet.size();

		float * evalFrequencies = new float[dim];

		//Set evaluation frequencies

		evalFrequencies[0] = 0;

		for (int i = 1; i < dim - 1; i++) {
			evalFrequencies[i] = filterSet[i]->frequency;
		}

		evalFrequencies[(dim - 1)] = FMAX;

		//Create Matrix objects

		juce::dsp::Matrix<float> B(dim, dim);
		juce::dsp::Matrix<float> gamma(dim, 1);
		juce::dsp::Matrix<float> lambda(dim, 1);

		float * B_data = B.getRawDataPointer();
		float * gamma_data = gamma.getRawDataPointer();
		float * lambda_data = lambda.getRawDataPointer();

		//Compute gamma column

		for (int i = 0; i < filterSet.size(); i++) {
			gamma_data[i] = filterSet[i]->getdBAmplitude(evalFrequencies[i]);
		}

		//Set gains to 1 dB for B matrix
		for (int i = 0; i < filterSet.size(); i++) {
			filterSet[i]->setGain(Filter::invdB(1.0f));
		}
		


		//Correction algorithm (5 iterations)

		for (int k = 0; k < 5; k++) {

			memcpy(lambda_data, gamma_data, dim * sizeof(float));

			//Compute B matrix with new gains
			for (int i = 0; i < dim; i++) {

				for (int j = 0; j < filterSet.size(); j++) {

					B_data[j + B.getNumColumns() * i] = filterSet[j]->getdBAmplitude(evalFrequencies[i]);
				}
			}

			B.solve(lambda);

			for (int i = 0; i < dim; i++) {

				filterSet[i]->setGain(Filter::invdB(lambda_data[i] * Filter::todB(filterSet[i]->gainFactor)));
			}
		}

		delete[] evalFrequencies;


	}

	float Equalizer::getdBAmplitude(float freq) {
		float dBAmplitude = 0;

		for (int i = 0; i < filterSet.size(); i++) {
			dBAmplitude += filterSet[i]->getdBAmplitude(freq);
		}

		return dBAmplitude;

	}

	void Equalizer::setFilterFrequency(float freq, int num) {
		if (num < 0 || num >= filterSet.size())
			throw InvalidFilterException();

			filterSet[num]->setFrequency(freq);
	}
	void Equalizer::setFilterGain(float gain, int num) {
		if (num < 0 || num >= filterSet.size())
			throw InvalidFilterException();

			EQGains[num] = gain;

			filterSet[num]->setGain(gain);

	}
	void Equalizer::setFilterQ(float Q, int num) {
		if (num < 0 || num >= filterSet.size())
			throw InvalidFilterException();

			filterSet[num]->setQ(Q);
	}

	float Equalizer::getFilterFrequency(int num) {
		if (num < 0 || num >= filterSet.size())
			throw InvalidFilterException();

		return filterSet[num]->frequency;
	}

	float Equalizer::getFilterGain(int num) {
		if (num < 0 || num >= filterSet.size())
			throw InvalidFilterException();

		return filterSet[num]->gainFactor;
	}

	float Equalizer::getFilterQ(int num) {
		if (num < 0 || num >= filterSet.size())
			throw InvalidFilterException();

		return filterSet[num]->gainFactor;
	}

	float Equalizer::getEQGain(int num) {
		if (num < 0 || num >= filterSet.size())
			throw InvalidFilterException();

		return EQGains[num];
	}

	int Equalizer::getNumFilters() {
		return filterSet.size();
	}
}