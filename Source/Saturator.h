/*
  ==============================================================================

    Saturator.h
    Created: 4 Jan 2026 1:58:35pm
    Author:  Denkabe

  ==============================================================================
*/

#pragma once


namespace juce::dsp {
	template <typename FloatType>
	class Saturator {
	public:
		void setSaturation(float saturation) {
			this->saturation.setTargetValue(saturation);
		}

		float getSaturation() {
			return saturation.getTargetValue();
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
					dst[i] = saturation.getNextValue() == 0 ? src[i] : tanhf(src[i] * saturation.getNextValue() * 10) / (saturation.getNextValue() * 10);
					dst[i] *= saturation.getNextValue() * 0.9 + 1;
				}
			}

		}

	private:
		SmoothedValue<FloatType> saturation;
		double sampleRate = 0;
	};
}