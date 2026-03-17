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
      space = 1;
      spaceOffset = 0;
      feedback = 0;
      volOffset = 0;
      release = 0;
      releaseCount = 100000;
      isOn = true;
      for (int i = 0; i < 16; i++) {
        waitCounts[i] = (space + rand() % spaceOffset) * (i + 1);

        delayBuffers.push_back(new juce::AudioBuffers<float>);

        delayLines.push_back(new juce::dsp::DelayLine<float>);
        delayLines[i]->prepare(spec);
        delayLines[i]->setMaximumDelayInSamples(10000);
        delayLines[i]->setDelay((space + rand() % spaceOffset) * (i + 1));
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

    void setOnOff(bool isOn) {
      this->isOn = isOn;
    }

    bool isOn() {
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
		void process(const juce::AudioBuffer<FloatType>& buffer) {

			auto len = buffer.getNumSamples();
			auto numChannels = buffer.getNumChannels();

      for (int i = 0; i < delayBuffers.size(); i++) {
        delayBuffers[i]->setSize(buffer.getNumChanels(), buffer.getNumSamples());
        delayBuffers[i]->clear();
        for (int chan = 0; chan < buffer.getNumChannels(); chan++) {
          delayBuffers[i]->copyFrom(chan, 0, buffer, chan, 0, buffer.getNumSamples());
        }
        delayLines[i]->setDelay((space + rand() % spaceOffset) * (i + 1));
        delayLines[i]->process(delayBuffers[index]);
        float trackVolume = 0;
        if (isOn) {
          releaseCount = 0;
          trackVolume = std::max(std::min(feedback * i, 1), 0);
        }
        buffer.addFrom(chan, 0, *delayBuffers[i], chan, 0, buffer.getNumSamples(), trackVolume);
      }

			// for (int chan = 0; chan < numChannels; chan++) {

			// 	for (int j = 0; j < delayBuffers.size(); j++ ) {
      //     if (waitCount[j] <= 0) {
      //       for (int i = 0; i < len; i++) {   
      //         float trackVolume;
      //         if (isOn) {
      //           trackVolume = std::max(std::min(feedback * j, 1), 0);
      //         } else {
      //           trackVolume = std::max(1 - (releaseCount / release), 0);   
      //           releaseCount++;
      //         }
      //         dst[i] = src[i] + (delayBuffers[j].front()[i] * trackVolume);
      //       } 
      //       delayBuffers[j].pop();
      //     } else {
      //       waitCounts[j]--;
      //     } 
      //     delayBuffers[j].push(src);
			// 	}
			// }
		}

	private:
		int spaceOffset;
    int space;
    float width;
    float feedback;
    float volOffset;
    int releaseCount;
    float release;
    bool isOn;
    std::vector<juce::AudioBuffer<float>*> delayBuffers;
    std::vector<juce::dsp::DelayLine<float>*> delayLines;
    
    SmoothedValue<FloatType> volume;
	};
}
