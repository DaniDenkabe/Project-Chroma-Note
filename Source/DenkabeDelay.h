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
            space = 1;
            spaceOffset = 0;
            feedback = 0;
            volOffset = 0;
            release = 1;
            releaseCount = 0;
            isOn = false;
            for (int i = 0; i < numOfVoices; i++) {
                delayBuffers.push_back(new juce::AudioBuffer<float>);

                delayLines.push_back(new juce::dsp::DelayLine<float>);
                delayLines[i]->prepare(spec);
                delayLines[i]->setMaximumDelayInSamples(40000);
                if (spaceOffset == 0) {
                    delayLines[i]->setDelay(space * (i + 1));
                }
                else {
                    delayLines[i]->setDelay((space + rand() % spaceOffset) * (i + 1));
                }
            }
		}

        void switchOnOff() {
            isOn = !isOn;
            if (isOn) {
                releaseCount = 0;
            }
        }

        void setOnOff(bool isOn) {
            this->isOn = isOn;
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

        void setRelease(float release) {
            this->release = release;
        }

		void reset() noexcept
		{
            for (int i = 0; i < numOfVoices; i++) {
                delayBuffers.push_back(new juce::AudioBuffer<float>);
            }
		}

		void process(juce::AudioBuffer<FloatType>& buffer) {

			auto len = buffer.getNumSamples();
			auto numChannels = buffer.getNumChannels();

            for (int i = 0; i < delayBuffers.size(); i++) {
                delayBuffers[i]->setSize(buffer.getNumChannels(), buffer.getNumSamples());
                delayBuffers[i]->clear();
                for (int chan = 0; chan < buffer.getNumChannels(); chan++) {
                    delayBuffers[i]->copyFrom(chan, 0, buffer, chan, 0, buffer.getNumSamples());
                }
                if (spaceOffset == 0) {
                    delayLines[i]->setDelay(space * (i + 1));
                }
                else {
                    delayLines[i]->setDelay((space + rand() % spaceOffset) * (i + 1));
                }
                juce::dsp::AudioBlock<float> block(buffer);
                juce::dsp::ProcessContextReplacing<float> ctx(block);
                delayLines[i]->process(ctx);
                float trackVolume = 0;
                if (isOn) {
                    releaseCount = 0;
                    trackVolume = feedback / (i + 1);
                    for (int chan = 0; chan < buffer.getNumChannels(); chan++) {
                        buffer.addFrom(chan, 0, *delayBuffers.at(i), chan, 0, buffer.getNumSamples(), trackVolume);
                    }
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
        float release;
        bool isOn;
        int numOfVoices = 4;
        std::vector<juce::AudioBuffer<float>*> delayBuffers;
        std::vector<juce::dsp::DelayLine<float>*> delayLines;
    
        SmoothedValue<FloatType> volume;
	};
}
