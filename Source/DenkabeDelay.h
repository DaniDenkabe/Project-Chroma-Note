/*
  ==============================================================================

    DenkabeDelay.h
    Created: 3 Mar 2026 11:28:28am
    Author:  denkabe

  ==============================================================================
*/

#pragma once
#include <ctime>

namespace juce::dsp {
	template <typename FloatType>
	class DenkabeDelay {
	public:

		template <typename ProcessSpec>
		void prepare(const ProcessSpec& spec) noexcept
		{
			sampleRate = spec.sampleRate;
      waitCount = 0;
      space = 0;
      spaceOffset = 0;
      feedback = 0;
      volOffset = 0;
      release = 0;
      releaseCount = 100000;
      isOn = false;
      for (int i = 0; i < 16; i++) {
        waitCounts[j] = (space + rand() % spaceOffset) * (j + 1);
        delayBuffers.push_back(new std::queue<float*>);
      }
		}

    void switchOnOff() {
      isOn = !isOn;
      if (isOn) {
        // for (int i = 0; i < 16; i++) {
        //   waitCounts[j] = space * (j + 1);
        // }
        releaseCount = 0;
      }
    }

    boolean isOn() {
      return isOn;
    }

    void setSpaceOffset(int spaceOffset) {
      this->spaceOffset = spaceOffset;
    } 

    void setVolOffset(int volOffset) {
      this->volOffset = volOffset;
    } 

    void setWidth(float width) {
      this->width = width;
    }

    void setSpace(int space) {
      this->space = space;
    }

    void setFeedback(float feedback) {
      this->feedback = feedback;
    }

		void reset() noexcept
		{
      for (int i = 0; i < 16; i++) {
        waitCounts[j] = (space + rand() % spaceOffset) * (j + 1);
        delayBuffers.push_back(new std::queue<float*>);
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

				for (int j = 0; j < delayBuffers.size(); j++ ) {
          if (waitCount[j] <= 0) {
            for (int i = 0; i < len; i++) {   
              float trackVolume;
              if (isOn) {
                trackVolume = std::max(std::min(feedback * j, 1), 0);
              } else {
                trackVolume = std::max(1 - (releaseCount / release), 0);   
                releaseCount++;
              }
              dst[i] = src[i] + (delayBuffers[j].front()[i] * trackVolume);
            } 
            delayBuffers[j].pop();
          } else {
            waitCounts[j]--;
          } 
          delayBuffers[j].push(src);
				}
			}
		}

	private:
		int spaceOffset;
    int space;
    float width;
    float feedback;
    float volOffset;
    int releaseCount;
    std::vector<int> waitCounts;
    float release;
    boolean isOn;
    std::vector<std::queue<float*>> delayBuffers;
    
    SmoothedValue<FloatType> volume;
	};
}
