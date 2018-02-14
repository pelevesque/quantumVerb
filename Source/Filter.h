/*
  ==============================================================================

    Filter.h

  ==============================================================================
*/

#pragma once

#include "Task.h"

#include <memory>

namespace reverb
{

	static float invdB(float dB) {
		return pow(10, dB / 10);
	}

    //==============================================================================
    /**
    * TODO: Description
    */
    class Filter : public Task,
                   public juce::dsp::IIR::Filter<float>
    {
    public:
        //==============================================================================
        Filter(juce::AudioProcessor * processor, float freq = 1000.0f, float q = 0.5f, float gain = 1.0f);

        //==============================================================================
        using Ptr = std::shared_ptr<Filter>;

        //==============================================================================
        virtual void exec(juce::AudioSampleBuffer& ir) override;

        //==============================================================================
        virtual void buildFilter() = 0;

        //==============================================================================

		void setFrequency(float);
		void setQ(float);
		void setGain(float);

	protected:
		bool assertValues();

		double frequency;
		double Q;
		double gainFactor;

    };

    
    //==============================================================================
    /**
    * TODO: Description
    */
    class LowShelfFilter : public Filter
    {
    public:
        //==============================================================================
        using Filter::Filter;   // Inherit constructor
        
        //==============================================================================
        virtual void buildFilter() override;
    };

    
    //==============================================================================
    /**
    * TODO: Description
    */
    class HighShelfFilter : public Filter
    {
    public:
        //==============================================================================
        using Filter::Filter;   // Inherit constructor
        
        //==============================================================================
        virtual void buildFilter() override;
    };


    //==============================================================================
    /**
    * TODO: Description
    */
    class PeakFilter : public Filter
    {
    public:
        //==============================================================================
        using Filter::Filter;   // Inherit constructor
        
        //==============================================================================
        virtual void buildFilter() override;
    };

}