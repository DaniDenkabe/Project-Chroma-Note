/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WangSoundTouch/WangSoundTouchPitchShifter.h"
#include "WubVocoder/WubPitchShifter.h"
#include "McPherson/McPhersonPitchShifter.h"
#include "Dysomni/DysomniPitchShifter.h"
#include "stk/PitShift.h"

#include "signalsmith-stretch.h"
#include "Saturator.h"
#include "DownSampler.h"
#include "Looper.h"
#include "Voice.h"
#include <vector>

struct ChainSettings {
    float pitchTransposition{ 0 }; 
};

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);

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
    void processReverb(int index, juce::AudioBuffer<float>& buffer);
    void processReverb(int index, juce::dsp::ProcessSpec spec);
    void processDownSampler(int index, juce::AudioBuffer<float>& buffer);
    void processDownSampler(int index, juce::dsp::ProcessSpec spec);
    void processCompressor(int index, juce::AudioBuffer<float>& buffer);
    void processCompressor(int index, juce::dsp::ProcessSpec spec);
    void processDelayLine(int index, juce::AudioBuffer<float>& buffer);
    void processDelayLine(int index, juce::dsp::ProcessSpec spec);
    void processLooper(int index, juce::AudioBuffer<float>& buffer);
    void processLooper(int index, juce::dsp::ProcessSpec spec);


    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    

    juce::AudioProcessorValueTreeState apvts{*this, nullptr, "Parameters", createParameterLayout()};

private:
    std::vector<juce::dsp::Saturator<float>*> saturatorList;
    std::vector <juce::dsp::IIR::Filter<float>*> leftHpFilterList, leftLpFilterList, rightHpFilterList, rightLpFilterList;
    std::vector <juce::dsp::Compressor<float>*> leftCompressorList, rightCompressorList;
    std::vector <juce::dsp::DryWetMixer<float>*> leftCompMixerList, rightCompMixerList;
    std::vector <juce::dsp::Gain<float>*> gainList;
    std::vector <juce::dsp::Reverb*> leftReverbList, rightReverbList;
    std::vector <juce::Reverb::Reverb::Parameters*> paramList;
    std::vector <juce::dsp::DownSampler<float>*> downSamplerList;
    std::vector <juce::dsp::DelayLine<float>*> delayLineList;

    std::vector <signalsmith::stretch::SignalsmithStretch<float>*> stretchList;
    std::vector <juce::AudioBuffer<float>*> stretchBuffers;
    std::vector <std::vector<float*>> inBuffers;
    std::vector <std::vector<float*>> outBuffers;

    std::vector <DysomniPitchShifter*> dysmoniList;



    std::vector <juce::dsp::Looper<float>*> looperList;

    std::vector <float> pitchSemis, freqs, amplitudes, counters, lfos, randCounts, threshs, ratios, attacks, releases, highFreqs, lowFreqs,
        compMixes, gainAmounts, dampings, roomSizes, revMixes, widths, saturations, sampleFactors, rates, depths, centreDelays, feedbacks, 
        chorusMixes, delayAmounts, loopLengths, loopIsOn, bitDepths;


    using Filter = juce::dsp::IIR::Filter<float>;
    signalsmith::stretch::SignalsmithStretch<float> stretch;


    juce::AudioBuffer<float> stretchBuffer;


    juce::dsp::Saturator<float> saturator;

    juce::dsp::IIR::Filter<float> leftHpFilter;
    juce::dsp::IIR::Filter<float> leftLpFilter;
    juce::dsp::IIR::Filter<float> rightHpFilter;
    juce::dsp::IIR::Filter<float> rightLpFilter;

    juce::dsp::Compressor<float> leftCompressor;
    juce::dsp::Compressor<float> rightCompressor;

    juce::dsp::DryWetMixer<float> leftCompMixer;
    juce::dsp::DryWetMixer<float> rightCompMixer;

    juce::dsp::Gain<float> gain;

    juce::dsp::Reverb leftReverb;
    juce::dsp::Reverb rightReverb;
    juce::dsp::Chorus<float> chorus;
    juce::Reverb::Reverb::Parameters params;


    juce::dsp::DownSampler<float> downSampler;

    float pitchSemi, freq, amplitude, counter, lfo, randCount, thresh, ratio, attack, release, highFreq, lowFreq, 
        compMix, gainAmount, damping, roomSize, revMix, width, saturation, sampleFactor, rate, depth, centreDelay, feedback, chorusMix;
    double currSampleRate;

    std::vector<juce::AudioBuffer<float>*> copyBuffers;
    int selected;
    int numOfVoices;

    //std::vector<float*> inBuffers, outBuffers;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project_Chromatic_AberationAudioProcessor)
};
