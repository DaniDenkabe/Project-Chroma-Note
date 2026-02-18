/*
  ==============================================================================

    Looper.h
    Created: 26 Jan 2026 8:54:15am
    Author:  alpha

  ==============================================================================
*/

#pragma once

namespace juce::dsp {
    template <typename FloatType>
    class Looper {
    public:
        Looper(ProcessSpec& spec) {
            numChannels = spec.numChannels;
            sampleRate = spec.sampleRate;
            loopSize = 0;
        }

        void setLoopLength(int seconds, FloatType b) {
            int prevSize = loopSize;
            loopSize = (int)(sampleRate * seconds);
            if (prevSize > loopSize) {
                for (int i = 0; i < prevSize - loopSize; i++) {
                    circularBuffer.pop_back();
                    loopBuffer.pop_back();
                }
            }
            else if (prevSize < loopSize) {
                for (int i = 0; i  < loopSize - prevSize; i++) {
                    circularBuffer.push_back(b);
                    loopBuffer.push_back(b);
                }
            }
        }

        int getLoopLength() {
            return loopSize;
        }

        void setLooping(bool looping) {
            if (looping && !isLooping) {
                // Capture the most recent loopSize samples into loopBuffer
                for (int i = 0; i < loopSize; i++) {
                    int index = (writeIndex - loopSize + i + loopSize) % loopSize;
                    loopBuffer[i] = circularBuffer[index];
                }
                readIndex = 0;
                hasLoop = true;
            }
            isLooping = looping;
        }

        bool isRunning() {
            return isLooping;
        }

        void process(AudioBuffer<FloatType>& buffer) {
            int bufferSize = buffer.getNumSamples();
            for (int ch = 0; ch < buffer.getNumChannels(); ch++) {
                for (int i = 0; i < bufferSize; i++) {
                    if (!isLooping) {
                        // Record incoming samples into the circular buffer
                        circularBuffer.at(writeIndex) = buffer.getSample(0, i);
                        writeIndex = (writeIndex + 1) % loopSize;
                    }
                    else if (hasLoop) {
                        // Replace live audio with loop playback
                        buffer.setSample(0, i, loopBuffer[readIndex]);
                        readIndex = (readIndex + 1) % loopSize;
                    }
                }
            }
        }

    private:
        std::vector<FloatType> circularBuffer;
        std::vector<FloatType> loopBuffer;
        int loopSize;
        int sampleRate;
        int writeIndex = 0;
        int readIndex = 0;
        int numChannels;
        bool isLooping = false;
        bool hasLoop = false;
    };
}
