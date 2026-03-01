/*
  ==============================================================================

    DownSampler.h
    Created: 4 Jan 2026 2:53:24pm
    Author:  alpha

  ==============================================================================
*/

#pragma once

namespace juce::dsp {
	template <typename FloatType>
	class DownSampler {
	public:
		void setSampleRate(float sampleFactor) { 
			this->sampleFactor.setTargetValue(sampleFactor);
		}

		float getSampleRate() {
			return sampleFactor.getTargetValue();
		}

		void setBitDepth(int depth) {
			bitDepth = depth;
		}

		int getBitDepth() {
			return bitDepth;
		}

		template <typename ProcessSpec>
		void prepare(const ProcessSpec& spec) noexcept
		{
			sampleRate = spec.sampleRate;
			reset();
		}

		void reset() noexcept
		{
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

				for (int i = 0; i < len; i++) {
					whiteNoiseValue = std::rand() % 10;
					whiteNoiseValue *= ((16 - bitDepth) / 17);
					dst[i] += whiteNoiseValue;
				}
				
				for (int i = 0; i < len; i++) {

					float totalQLevels = powf(2, bitDepth);
					float val = dst[i];
					float remainder = fmodf(val, 1 / totalQLevels);

					dst[i] = val - remainder;
				}

				for (int i = 0; i < len; i++) {
					if (sampleFactor.getNextValue() == 0) {
						currentSample = src[i];
					} else if (i % (int) sampleFactor.getNextValue() == 0) {
						currentSample = src[i];
					}

					dst[i] = currentSample;
				}
			}

		}

	private:
		SmoothedValue<FloatType> sampleFactor;
		int bitDepth;
		double sampleRate = 0;
		float currentSample;
		float whiteNoiseValue = 0;
	};
}
