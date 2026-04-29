/*
  ==============================================================================

    PitchBend.h
    Created: 29 Apr 2026 12:39:08am
    Author:  denkabe

  ==============================================================================
*/

#pragma once

namespace juce::dsp {
	template <typename FloatType>
	class PitchBend {
	public:

		  template <typename ProcessSpec>
		  void prepare(const ProcessSpec& spec) noexcept
		  {
          for (int i = 0; i < 2; i++) {
              stretchedQueues.push_back(new std::queue<float>);
          }
          rate = 1;

		  }

      void setRate(float rate) {
          if (rate <= 1) 
              this->rate = rate;
      }
 
		  void reset() noexcept
		  {
      }


		  void process(AudioBuffer<FloatType>& buffer) {

			    auto len = buffer.getNumSamples();
			    auto numChannels = buffer.getNumChannels();
          for (int ch = 0; ch < numChannels; ch++) {

              float* channelData = buffer.getWritePointer (ch);
              if (rate != 1) {
                  for (int i = 0; i < len / rate; i++)
                  {
                      double srcIndex = i * rate;

                      int index0 = (int)srcIndex;
                      int index1 = index0 + 1;

                      if (index1 >= len)
                      {
                          stretchedQueues[ch]->push(buffer.getSample(ch, len - 1));
                      } else {
                          float frac = (float)(srcIndex - index0);

                          float s0 = buffer.getSample(ch, index0);
                          float s1 = buffer.getSample(ch, index1);

                          stretchedQueues[ch]->push(s0 + frac * (s1 - s0));
                      }
                  }

                  for (int i = 0; i < len; i++) {
                      buffer.setSample(ch, i, stretchedQueues[ch]->front());
                      stretchedQueues[ch]->pop();
                  }                 
              } else {
                  for (int i = 0; i < stretchedQueues[ch]->size(); i++) {
                      stretchedQueues[ch]->pop();
                  }
              }
          } 
      } 

	  

	private:
      std::vector<std::queue<float>*> stretchedQueues;
      float rate;

	};
}
