/*
  ==============================================================================

    Gain.h

  ==============================================================================
*/

#pragma once

#include "Task.h"

namespace reverb
{

    //==============================================================================
    /**
    * TODO: Description
    */
    class Gain : public Task
    {
    public:
        //==============================================================================
        Gain(juce::AudioProcessor * processor);
		~Gain ();

        //==============================================================================
        using Ptr = std::shared_ptr<Gain>;

        //==============================================================================
        virtual void exec(juce::AudioSampleBuffer& buffer) override;

        //==============================================================================
        double gainFactor;
    };

}