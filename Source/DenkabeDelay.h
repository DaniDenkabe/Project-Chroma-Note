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
          feedback = 4;
          damp = 1;
          magnitude = 12;
          for (int i = 0; i < feedback; i++) {
              delayHeads.push_back(new Node(0));
              delayLasts.push_back(new Node(0));
              Node* currNode = delayHeads[i];
              for (int j = 0; j < (magnitude - 1) * (i + 1); j++) {
                  currNode->next = new Node(0, nullptr, currNode);
                  currNode = currNode->next;
                  delayLasts[i] = currNode;
              }
          }
          isOn = false;
		  }


      void setOnOff(bool isOn) {
          this->isOn = isOn;
      }

      void setMagnitude(int newMagnitude) {
          for (int i = 0; i < feedback; i++) {
              int diff = newMagnitude * (i + 1) - magnitude * (i + 1);
              Node* currNode = delayLasts[i];
              if (diff > 0) {
                  for (int j = 0; j < diff; j++) {
                      currNode->next = new Node(delayLasts[i]->data, nullptr, currNode);
                      currNode = currNode->next;
                  }
              } else if (diff < 0) {
                  for (int j = 0; j < -1 * diff; j++) {
                      currNode = currNode->prev;
                      currNode->next = nullptr;
                  }
              }
              delayLasts[i] = currNode;
          }
          this->magnitude = newMagnitude;
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
                  
                  for (int j = 0; j < feedback; j++) {
                      // Add the sample to the delay list
                      Node* pastHead = delayHeads[j];
                      delayHeads[j] = new Node(src[i], pastHead);
                      pastHead->prev = delayHeads[j];

                      // Add the last sample to the dst list
                      if (isOn) {
                          if (j == 0) {
                              dst[i] = src[i];
                          }
                          dst[i] += delayLasts[j]->data * (1 - ((1/feedback) * damp) * (j + 1));
                      }

                      // Remove the last sample from the delayBuffer
                      delayLasts[j] = delayLasts[j]->prev;
                      delayLasts[j]->next = nullptr;
                  }
              }
			    }

		  }

	  

	private:
      struct Node {
          float data;
          Node* next;
          Node* prev;

          Node(float val) : data(val), next(nullptr), prev(nullptr) {}
          Node(float val, Node* nextNode) : data(val), next(nextNode), prev(nullptr){}
          Node(float val, Node* nextNode, Node* prevNode) : data(val), next(nextNode), prev(prevNode){}

      };

      Node* delayHead;
      Node* delayLast;

      std::vector<Node*> delayHeads;
      std::vector<Node*> delayLasts;
      bool isOn;
      int magnitude;
      int feedback;
      float damp;
	};
}
