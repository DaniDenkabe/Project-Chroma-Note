/*
  ==============================================================================

    NoiseGen.h
    Created: 28 Apr 2026 11:14:14am
    Author:  denkabe

  ==============================================================================
*/

#pragma once

namespace juce::dsp {
	template <typename FloatType>
	class NoiseGen {
	public:

		  template <typename ProcessSpec>
		  void prepare(const ProcessSpec& spec) noexcept
		  {
          volume = 0;
		  }

      void setVolume(float volume) {
          this->volume = volume;
      }
 
		  void reset() noexcept
		  {
      }


		  void process(AudioBuffer<FloatType>& buffer) {

			    auto len = buffer.getNumSamples();
			    auto numChannels = buffer.getNumChannels();
          for (int ch = 0; ch < numChannels; ch++) {
              for (int i = 0; i < len; i++) {
                  buffer.setSample(ch, i, buffer.getSample(ch, i) + rand() * volume * 0.00001);
              }
          }
      } 

	  

	private:

      float volume;

	};
}
