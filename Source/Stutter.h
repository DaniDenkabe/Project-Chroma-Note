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
          passThru = false;
          isOn = false;
          onSpace = 1;
          offSpace = 0;
          onOffset = 0;
          offOffset = 0;
          count = 0;
          attack = 0;
          release = 0;
          currSpace = 0;
      }

      void setOnSpace(int onSpace) {
          this->onSpace = onSpace;
      }


      void setOnOff(bool onOff) {
          this->isOn = onOff;
      }


      void setOffSpace(int offSpace) {
          this->offSpace = offSpace;
      }

      void setOnOffset(int onOffset) {
          this->onOffset = onOffset;
      }

      void setOffOffset(int offOffset) {
          this->offOffset = offOffset;
      }

      void setAttack(float attack) {
          this->attack = attack;
      }

      void setRelease(float release) {
          this->release = release;
      }

      void reset() noexcept
      {
      }

      float volFunc() {
          float finalVal = 0;
          float funcValue = -pow((currSpace - count) - (currSpace / 2), 2) * (4 / pow(currSpace, 2));
          if (count >= currSpace / 2) {
              finalVal = (funcValue * attack + (1 - attack));
          } else {
              finalVal = (funcValue * release + (1 - release));
          }
          return finalVal;
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
                   if (isOn) {
                      if (passThru) {
                          dst[i] = src[i] * volFunc();
                      } else {
                          dst[i] = 0;
                      }
                      count--;
                      if (count <= 0) {
                          if (passThru) {
                              count = offSpace + rand() % offOffset;
                          } else {
                              count = onSpace + rand() % onOffset;
                          }
                          currSpace = count;
                          passThru = !passThru;
                      }
                  }                 
              }
          }
      }

	private:
      bool isOn;
      int offSpace;
      int onSpace;
      int offOffset;
      int onOffset;
      int count;
      bool passThru;
      float volume;
      float attack;
      float release;
      int currSpace;
	};
}
