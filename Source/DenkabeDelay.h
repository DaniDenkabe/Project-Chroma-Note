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
          feedback = 2;
          damp = 1;
          magnitude = 3000;
          for (int ch = 0; ch < spec.numChannels; ch++) {
              delayBuffers.push_back(new std::vector<std::deque<long double>*>);
              for (int voice = 0; voice < feedback; voice++) {
                  delayBuffers[ch]->push_back(new std::deque<long double>);
                  for (int j = 0; j < (magnitude - 1) * (voice + 1); j++) {
                      delayBuffers[ch]->at(voice)->push_front(0);
                  }
              }
          }

          isOn = false;
		  }


      void setOnOff(bool isOn) {
          this->isOn = isOn;
      }

      void setDamp(int newDamp) {
          damp = newDamp;
      }


      void setMagnitude(int newMagnitude) {
          for (int ch = 0; ch < delayBuffers.size(); ch++) {
              for (int i = 0; i < feedback; i++) {
                  int diff = newMagnitude * (i + 1) - magnitude * (i + 1);
                  if (diff > 0) {
                      for (int j = 0; j < diff; j++) {
                          delayBuffers[ch]->at(i)->push_back(delayBuffers[ch]->at(i)->back());
                      }
                  } else if (diff < 0) {
                      for (int j = 0; j < -1 * diff; j++) {
                          delayBuffers[ch]->at(i)->pop_back();
                      }
                  }
              }
          }
          this->magnitude = newMagnitude;
      }

		  void reset() noexcept
		  {
      }


		  void process(AudioBuffer<FloatType>& buffer) {

			    auto len = buffer.getNumSamples();
			    auto numChannels = buffer.getNumChannels();
          for (int ch = 0; ch < delayBuffers.size(); ch++) {
              for (int i = 0; i < len; i++) {
                      
                  for (int j = 0; j < feedback; j++) {
                      // Add the sample to the delay list
                      delayBuffers[ch]->at(j)->push_front(buffer.getSample(ch, i));
                          
                      // Add the last sample to the dst list
                      if (isOn) {
                          float newSample = delayBuffers[ch]->at(j)->back() * (1 - damp * j) * 0.5;
                          buffer.setSample(ch, i, newSample + buffer.getSample(ch, i)); 
                      } 

                      // Remove the last sample from the delayBuffer
                      delayBuffers[ch]->at(j)->pop_back();
                  }
              }   
          }
      } 

	  

	private:

      std::vector<std::vector<std::deque<long double>*>*> delayBuffers;
      
      bool isOn;
      int magnitude;
      int feedback;
      float damp;
	};
}
