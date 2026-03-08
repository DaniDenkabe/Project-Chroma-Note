/*
  ==============================================================================

    Stutter.h
    Created: 6 Mar 2026 11:55:32am
    Author:  denkabe

  ==============================================================================
*/

#pragma once

#include <ctime>

namespace juce::dsp {
	template <typename FloatType>
	class Stutter {
	public:

		template <typename ProcessSpec>
		void prepare(const ProcessSpec& spec) noexcept
		{

		}

		void reset() noexcept
		{
		}

    float volFunc(int count) {
      int funcValue = -pow((currSpace - count) - (currSpace / 2), 2) * (4 / pow(currSpace, 2));
      if (count >= currSpace / 2) {
        int finalVal = (funcValue * attack + (1 - attack));
      } else {
        int finalVal = (funcValue * release + (1 - attack));
      }
    }

		template <typename ProcessContext>
		void process(const ProcessContext& context) {
			auto&& inBlock = context.getInputBlock();
			auto&& outBlock = context.getOutputBlock();

			jassert(inBlock.getNumChannels() == outBlock.getNumChannels());
			jassert(inBlock.getNumSamples() == outBlock.getNumSamples());

			auto len = inBlock.getNumSamples();
			auto numChannels = inBlock.getNumChannels();

			if (context.isBypassed)
			{

				if (context.usesSeparateInputAndOutputBlocks())
					outBlock.copyFrom(inBlock);

				return;
			}

			for (int chan = 0; chan < numChannels; chan++) {
				auto* src = inBlock.getChannelPointer(chan);
				auto* dst = outBlock.getChannelPointer(chan);
			}
		}

	private:
    boolean isOn;
    int offSpace;
    int onSpace;
    int offOffset;
    int onOffset;
    int count;
    boolean passThru;
    float volume;
    float attack;
    float release;
    int currSpace;
	};
}
