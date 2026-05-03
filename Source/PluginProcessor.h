/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


#include "signalsmith-stretch.h"
#include "Saturator.h"
#include "DownSampler.h"
#include "Looper.h"
#include "Stutter.h"
#include <vector>

#include "DenkabeDelay.h"
#include "NoiseGen.h"
#include "PitchBend.h"
#include "DelayLinePitchShifter.h"


//==============================================================================
/**
*/
class Project_Chromatic_AberationAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Project_Chromatic_AberationAudioProcessor();
    ~Project_Chromatic_AberationAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setVariables(int index, bool set);
    void processGain(int index, juce::AudioBuffer<float>& buffer);
    void processGain(int index, juce::dsp::ProcessSpec spec);
    void processPitch(int index, juce::AudioBuffer<float>& buffer);
    void processPitch(int index, juce::dsp::ProcessSpec spec);
    void processSaturator(int index, juce::AudioBuffer<float>& buffer);
    void processSaturator(int index, juce::dsp::ProcessSpec spec);
    void processFreqCuts(int index, juce::AudioBuffer<float>& buffer);
    void processFreqCuts(int index, juce::dsp::ProcessSpec spec);
    void processDownSampler(int index, juce::AudioBuffer<float>& buffer);
    void processDownSampler(int index, juce::dsp::ProcessSpec spec);
    void processCompressor(int index, juce::AudioBuffer<float>& buffer);
    void processCompressor(int index, juce::dsp::ProcessSpec spec);
    void processDelayLine(int index, juce::AudioBuffer<float>& buffer);
    void processDelayLine(int index, juce::dsp::ProcessSpec spec);
    void processLooper(int index, juce::AudioBuffer<float>& buffer);
    void processLooper(int index, juce::dsp::ProcessSpec spec);
    void processDelay(int index, juce::AudioBuffer<float>& buffer);
    void processDelay(int index, juce::dsp::ProcessSpec spec);
    void processStutter(int index, juce::AudioBuffer<float>& buffer);
    void processStutter(int index, juce::dsp::ProcessSpec spec);
    void processNoise(int index, juce::AudioBuffer<float>& buffer);
    void processNoise(int index, juce::dsp::ProcessSpec spec);
    void processBend(int index, juce::AudioBuffer<float>& buffer);
    void processBend(int index, juce::dsp::ProcessSpec spec);
    void processPan(int index, juce::AudioBuffer<float>& buffer);
    void processPan(int index, juce::dsp::ProcessSpec spec);

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    

    juce::AudioProcessorValueTreeState apvts{*this, nullptr, "Parameters", createParameterLayout()};

private:
    std::vector<juce::dsp::Saturator<float>*> saturatorList;
    std::vector <juce::dsp::IIR::Filter<float>*> leftHpFilterList, leftLpFilterList,
      rightHpFilterList, rightLpFilterList;
    std::vector <juce::dsp::Compressor<float>*> compressorList;
    std::vector <juce::dsp::Gain<float>*> gainList;
    std::vector <juce::dsp::DownSampler<float>*> downSamplerList;
    std::vector <juce::dsp::DelayLine<float>*> delayLineList;
    std::vector <juce::dsp::DenkabeDelay<float>*> delayList;


    std::vector <juce::dsp::DelayLinePitchShifter<float>*> pitchShifters;

    std::vector <juce::dsp::NoiseGen<float>*> noiseList;

    std::vector <juce::dsp::Stutter<float>*> stutterList;

    std::vector <juce::dsp::Looper<float>*> looperList;

    std::vector <juce::dsp::PitchBend<float>*> bendsList;

    std::vector <juce::dsp::Panner<float>*> panList;

    std::vector <float> pitchSemis, freqs, amplitudes, counters, lfos, randCounts,
      threshs, ratios, attacks, releases, highFreqs, lowFreqs, compMixes,
      gainAmounts, dampings, roomSizes, revMixes, widths, saturations, sampleFactors,
      rates, depths, centreDelays, feedbacks, chorusMixes, delayAmounts, loopLengths,
      loopIsOn, bitDepths, wows, delayFeedbacks, delayReleases, stutterAttacks,
      stutterReleases, noiseMags, bends, pans;

    std::vector <int> delayVolOffsets, delaySpaceOffsets, delaySpaces, onSpaces,
      offSpaces, onOffsets, offOffsets;

    std::vector <bool> delayIsOn, stutterIsOn;

    std::vector <juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear>*> wowAmps;
    using Filter = juce::dsp::IIR::Filter<float>;
    int selected;
    int numOfVoices;

    std::vector <juce::AudioBuffer<float>*> copyBuffers;

    //std::vector<float*> inBuffers, outBuffers;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project_Chromatic_AberationAudioProcessor)
};
