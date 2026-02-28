/*
  ==============================================================================

    Shifter.h
    Created: 26 Feb 2026 11:18:07am
    Author:  denkabe

  ==============================================================================
*/

#include <bungee/Stream.h>
#include "WangSoundTouch/WangSoundTouchPitchShifter.h"
#include "WubVocoder/WubPitchShifter.h"
#include "McPherson/McPhersonPitchShifter.h"
#include "Dysomni/DysomniPitchShifter.h"

#pragma once


namespace juce::dsp {
	template <typename FloatType>
	class Shifter {
	public:

		template <typename ProcessSpec>
		void prepare(const ProcessSpec& spec) noexcept
		{
      shifter.prepare(spec);
			sampleRate = spec.sampleRate;
      
			reset();
		}

		void reset() noexcept
		{
		}

    void setPitch(int pitch) {
      this->pitch = pitch;
    }

		template <typename ProcessContext>
		void process(const juce::AudioBuffer<float>& buffer) {
      auto&& inBlock = context.getInputBlock();
			auto&& outBlock = context.getOutputBlock();

			jassert(inBlock.getNumChannels() == outBlock.getNumChannels());
			jassert(inBlock.getNumSamples() == outBlock.getNumSamples());

			auto len = inBlock.getNumSamples();
			auto numChannels = inBlock.getNumChannels();

      const auto maxInputFrameCount = inBlock.getNumChannels(); 
      Bungee::Stretcher<Bungee::Basic> stretch(sampleRate, numChannels);
      stretcher.enableInstrumentation(true);
      Bungee::Stream<Bungee::Basic> stream(stretcher, maxInputFrameCount, numChannels);

      if (context.isBypassed)
			{

				if (context.usesSeparateInputAndOutputBlocks())
					outBlock.copyFrom(inBlock);

				return;
			}

      for (int chan = 0; i < numChannels; i++) {
        auto* src = inBlock.getChannelPointer(chan);
				auto* dst = outBlock.getChannelPointer(chan);
        const double outputFrameCountIdeal = (inputSampleCount * sampleRates.output) / (speed * sampleRates.input);

        const auto outputFrameCountActual = stream.process(src, dst, inBlock.getNumSamples(), outputFrameCountIdeal, pitch);
      }
      
    
		}

	private:
		double sampleRate;
    double rate;
    double blend;
    double reso;
    double pitch;
    double speed;
	};
}
