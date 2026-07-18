/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <thread> 
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>

//==============================================================================
Project_Chromatic_AberationAudioProcessor::Project_Chromatic_AberationAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    for (int i = 0; i < 4; i++) {
        copyBuffers.push_back(new juce::AudioBuffer<float>);
    }
}

Project_Chromatic_AberationAudioProcessor::~Project_Chromatic_AberationAudioProcessor()
{
}

//==============================================================================
const juce::String Project_Chromatic_AberationAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Project_Chromatic_AberationAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Project_Chromatic_AberationAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Project_Chromatic_AberationAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Project_Chromatic_AberationAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Project_Chromatic_AberationAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Project_Chromatic_AberationAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Project_Chromatic_AberationAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Project_Chromatic_AberationAudioProcessor::getProgramName (int index)
{
    return {};
}

void Project_Chromatic_AberationAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}






void Project_Chromatic_AberationAudioProcessor::processGain(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    gainList[index]->setGainDecibels(gainAmounts[index]);
    gainList[index]->process(leftContext);
    gainList[index]->process(rightContext);
}

void Project_Chromatic_AberationAudioProcessor::processGain(int index, juce::dsp::ProcessSpec spec) {
    gainList.push_back(new juce::dsp::Gain<float>);
    gainList[index]->prepare(spec);
    gainList[index]->setGainDecibels(gainAmounts[index]);
}





void Project_Chromatic_AberationAudioProcessor::processPitch(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);

    pitchShifters[index]->setPitchShiftSemitones(pitchSemis[index]);
    pitchShifters[index]->process(block);

}

void Project_Chromatic_AberationAudioProcessor::processPitch(int index, juce::dsp::ProcessSpec spec) {
   
    pitchShifters.push_back(new juce::dsp::DelayLinePitchShifter<float>);
    pitchShifters[index]->prepare(spec);
}







void Project_Chromatic_AberationAudioProcessor::processSaturator(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    saturatorList[index]->setSaturation(saturations[index]);
    saturatorList[index]->process(leftContext);
    saturatorList[index]->process(rightContext);
}

void Project_Chromatic_AberationAudioProcessor::processSaturator(int index, juce::dsp::ProcessSpec spec) {
    saturatorList.push_back(new juce::dsp::Saturator<float>);
    saturatorList[index]->prepare(spec);
    saturatorList[index]->setSaturation(saturations[index]);
}





void Project_Chromatic_AberationAudioProcessor::processFreqCuts(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    leftHpFilterList[index]->coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), highFreqs[index]);
    leftLpFilterList[index]->coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), lowFreqs[index]);
    rightHpFilterList[index]->coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), highFreqs[index]);
    rightLpFilterList[index]->coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), lowFreqs[index]);
    leftHpFilterList[index]->process(leftContext);
    rightHpFilterList[index]->process(rightContext);
    leftLpFilterList[index]->process(leftContext);
    rightLpFilterList[index]->process(rightContext);
}

void Project_Chromatic_AberationAudioProcessor::processFreqCuts(int index, juce::dsp::ProcessSpec spec) {
    leftHpFilterList.push_back(new juce::dsp::IIR::Filter<float>);
    leftLpFilterList.push_back(new juce::dsp::IIR::Filter<float>);
    leftHpFilterList[index]->prepare(spec);
    leftHpFilterList[index]->coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate, highFreqs[index]);
    leftLpFilterList[index]->prepare(spec);
    leftLpFilterList[index]->coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(spec.sampleRate, lowFreqs[index]);

    rightHpFilterList.push_back(new juce::dsp::IIR::Filter<float>);
    rightLpFilterList.push_back(new juce::dsp::IIR::Filter<float>);
    rightHpFilterList[index]->prepare(spec);
    rightHpFilterList[index]->coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate, highFreqs[index]);
    rightLpFilterList[index]->prepare(spec);
    rightLpFilterList[index]->coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(spec.sampleRate, lowFreqs[index]);
}



void Project_Chromatic_AberationAudioProcessor::processDownSampler(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);

    downSamplerList[index]->setSampleRate(sampleFactors[index]);
    downSamplerList[index]->setBitDepth(bitDepths[index]);
    downSamplerList[index]->process(ctx);
}


void Project_Chromatic_AberationAudioProcessor::processDownSampler(int index, juce::dsp::ProcessSpec spec) {
    downSamplerList.push_back(new juce::dsp::DownSampler<float>);
    downSamplerList[index]->prepare(spec);
    downSamplerList[index]->setSampleRate(sampleFactors[index]);
    downSamplerList[index]->setBitDepth(bitDepths[index]);
}





void Project_Chromatic_AberationAudioProcessor::processCompressor(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);

    compressorList[index]->setThreshold(threshs[index]);
    compressorList[index]->setRatio(ratios[index]);
    compressorList[index]->setAttack(attacks[index]);
    compressorList[index]->setRelease(releases[index]);
    compressorList[index]->process(ctx);
}


void Project_Chromatic_AberationAudioProcessor::processCompressor(int index, juce::dsp::ProcessSpec spec) {
    compressorList.push_back(new juce::dsp::Compressor<float>);
    compressorList[index]->prepare(spec);
    compressorList[index]->setThreshold(threshs[index]);
    compressorList[index]->setRatio(ratios[index]);
    compressorList[index]->setAttack(attacks[index]);
    compressorList[index]->setRelease(releases[index]);
}





void Project_Chromatic_AberationAudioProcessor::processDelayLine(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);
    delayLineList[index]->setDelay(delayAmounts[index]);
    delayLineList[index]->process(ctx);
}


void Project_Chromatic_AberationAudioProcessor::processDelayLine(int index, juce::dsp::ProcessSpec spec) {
    delayLineList.push_back(new juce::dsp::DelayLine<float>);
    delayLineList[index]->prepare(spec);
    delayLineList[index]->setMaximumDelayInSamples(100000);
}





void Project_Chromatic_AberationAudioProcessor::processLooper(int index, juce::AudioBuffer<float>& buffer) {
    looperList[index]->setLoopLength(loopLengths[index], 0);
    looperList[index]->setLooping(loopIsOn[index]);
    looperList[index]->process(buffer);
}

void Project_Chromatic_AberationAudioProcessor::processLooper(int index, juce::dsp::ProcessSpec spec) {
    looperList.push_back(new juce::dsp::Looper<float>(spec));
    looperList[index]->setLoopLength(loopLengths[index], 0);
    looperList[index]->setLooping(false);
}



void Project_Chromatic_AberationAudioProcessor::processDelay(int index, juce::AudioBuffer<float>& buffer) {
    delayList[index]->setDamp(delayFeedbacks[index]);
    delayList[index]->setMagnitude(delaySpaces[index]);
    delayList[index]->setOnOff(delayIsOn[index]);
    delayList[index]->process(buffer);
}

void Project_Chromatic_AberationAudioProcessor::processDelay(int index, juce::dsp::ProcessSpec spec) {
    delayList.push_back(new juce::dsp::DenkabeDelay<float>);
    delayList[index]->prepare(spec);
    delayList[index]->setDamp(delayFeedbacks[index]);
    delayList[index]->setMagnitude(delaySpaces[index]);
    delayList[index]->setOnOff(delayIsOn[index]);
}


void Project_Chromatic_AberationAudioProcessor::processStutter(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);
    stutterList[index]->setOnOff(stutterIsOn[index]);
    stutterList[index]->setOnSpace(onSpaces[index]);
    stutterList[index]->setOffSpace(offSpaces[index]);
    stutterList[index]->setOnOffset(onOffsets[index]);
    stutterList[index]->setOffOffset(offOffsets[index]);
    stutterList[index]->setAttack(stutterAttacks[index]);
    stutterList[index]->setRelease(stutterReleases[index]);   
    stutterList[index]->process(ctx);
}

void Project_Chromatic_AberationAudioProcessor::processStutter(int index, juce::dsp::ProcessSpec spec) {
    stutterList.push_back(new juce::dsp::Stutter<float>);
    stutterList[index]->prepare(spec);
    stutterList[index]->setOnOff(stutterIsOn[index]);
    stutterList[index]->setOnSpace(onSpaces[index]);
    stutterList[index]->setOffSpace(offSpaces[index]);
    stutterList[index]->setOnOffset(onOffsets[index]);
    stutterList[index]->setOffOffset(offOffsets[index]);
    stutterList[index]->setAttack(stutterAttacks[index]);
    stutterList[index]->setRelease(stutterReleases[index]);   
}


void Project_Chromatic_AberationAudioProcessor::processNoise(int index, juce::AudioBuffer<float>& buffer) {
    noiseList[index]->setVolume(noiseMags[index]);
    noiseList[index]->process(buffer);
}

void Project_Chromatic_AberationAudioProcessor::processNoise(int index, juce::dsp::ProcessSpec spec) {
    noiseList.push_back(new juce::dsp::NoiseGen<float>);
    noiseList[index]->prepare(spec);
    noiseList[index]->setVolume(noiseMags[index]);
}


void Project_Chromatic_AberationAudioProcessor::processBend(int index, juce::AudioBuffer<float>& buffer) {

     bendsList[index]->setRate(bends[index]);
     bendsList[index]->process(buffer);
}

void Project_Chromatic_AberationAudioProcessor::processBend(int index, juce::dsp::ProcessSpec spec) {

    bendsList.push_back(new juce::dsp::PitchBend<float>); 
    bendsList[index]->prepare(spec);
    bendsList[index]->setRate(bends[index]);
}


void Project_Chromatic_AberationAudioProcessor::processPan(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);

    panList[index]->setPan(pans[index]);
    panList[index]->process(ctx);
}

void Project_Chromatic_AberationAudioProcessor::processPan(int index, juce::dsp::ProcessSpec spec) {
    panList.push_back(new juce::dsp::Panner<float>);
    panList[index]->setPan(pans[index]);
    panList[index]->prepare(spec);
}

//==============================================================================
void Project_Chromatic_AberationAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    for (int i = 0; i < copyBuffers.size(); i++) {
        copyBuffers.at(i)->setSize(getNumInputChannels(), samplesPerBlock);
    }

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    spec.sampleRate = sampleRate;


    for (int i = 0; i < copyBuffers.size() + 1; i++) {  
        setVariables(i, true);

        processGain(i, spec);

        processPitch(i, spec);

        processSaturator(i, spec);

        processFreqCuts(i, spec);

        processDownSampler(i, spec);

        processCompressor(i, spec);

        processDelayLine(i, spec);

        processLooper(i, spec);

        processDelay(i, spec);

        processStutter(i, spec);

        processNoise(i, spec);

        processBend(i, spec);
        
        processPan(i, spec);

        counters.push_back(0);
        randCounts.push_back(0);
    } 
}

void Project_Chromatic_AberationAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Project_Chromatic_AberationAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Project_Chromatic_AberationAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    float voiceGain = 0.05;

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    for (int i = 0; i < copyBuffers.size(); i++) {
        copyBuffers.at(i)->setSize(buffer.getNumChannels(), buffer.getNumSamples());
        for (int chan = 0; chan < buffer.getNumChannels(); chan++) {
            copyBuffers.at(i)->copyFrom(chan, 0, buffer, chan, 0, buffer.getNumSamples());
        }
    }
    buffer.clear();
    /*for (int i = 0; i < copyBuffers.size(); i++) {
        for (int chan = 0; chan < getTotalNumOutputChannels(); chan++) {
            buffer.addFrom(chan, 0, *copyBuffers.at(i), chan, 0, buffer.getNumSamples(), voiceGain);
        }
    }*/

    

    for (int i = 0; i < copyBuffers.size() + 1; i++) {

        setVariables(i, false);

        if (i != copyBuffers.size()) {

            processNoise(i, *copyBuffers[i]);

            processPitch(i, *copyBuffers[i]);

            processSaturator(i, *copyBuffers[i]);

            processDownSampler(i, *copyBuffers[i]);

            processFreqCuts(i, *copyBuffers[i]);

            processCompressor(i, *copyBuffers[i]);

            processDelayLine(i, *copyBuffers[i]);

            processLooper(i, *copyBuffers[i]);

            processDelay(i, *copyBuffers[i]);
            
            processStutter(i, *copyBuffers[i]);

            processBend(i, *copyBuffers[i]);

            processGain(i, *copyBuffers[i]);

            processPan(i, *copyBuffers[i]);


        }
        else {

            processNoise(i, buffer);

            processPitch(i, buffer);

            processSaturator(i, buffer);

            processDownSampler(i, buffer);

            processFreqCuts(i, buffer);

            processCompressor(i, buffer);

            processDelayLine(i, buffer);

            processLooper(i, buffer);

            processDelay(i, buffer);
            
            processStutter(i, buffer);

            processBend(i, buffer);

            processGain(i, buffer);

            processPan(i, buffer);

        }

        if (i != copyBuffers.size()) {
            for (int chan = 0; chan < getTotalNumOutputChannels(); chan++) {
                buffer.addFrom(chan, 0, *copyBuffers.at(i), chan, 0, buffer.getNumSamples(), voiceGain);
            }
        }
    }
}


void Project_Chromatic_AberationAudioProcessor::setVariables(int index, bool set) {
    std::string num = std::to_string(index);
    if (set) {
        gainAmounts.push_back(apvts.getRawParameterValue("Gain" + num)->load());

        pitchSemis.push_back(apvts.getRawParameterValue("Pitch" + num)->load());
        freqs.push_back(apvts.getRawParameterValue("Freq" + num)->load());
        amplitudes.push_back(apvts.getRawParameterValue("Amplitude" + num)->load());
        lfos.push_back(apvts.getRawParameterValue("LFO" + num)->load());
        wows.push_back(apvts.getRawParameterValue("WOW" + num)->load());
        wowAmps.push_back(new juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear>);

        saturations.push_back(apvts.getRawParameterValue("Saturation" + num)->load());

        highFreqs.push_back(apvts.getRawParameterValue("High Pass" + num)->load());
        lowFreqs.push_back(apvts.getRawParameterValue("Low Pass" + num)->load());

        sampleFactors.push_back(apvts.getRawParameterValue("Sample Rate" + num)->load());
        bitDepths.push_back(apvts.getRawParameterValue("Bit Depth" + num)->load());

        threshs.push_back(apvts.getRawParameterValue("Threshold" + num)->load());
        ratios.push_back(apvts.getRawParameterValue("Ratio" + num)->load());
        attacks.push_back(apvts.getRawParameterValue("Attack" + num)->load());
        releases.push_back(apvts.getRawParameterValue("Release" + num)->load());

        delayAmounts.push_back(apvts.getRawParameterValue("Delay Mag" + num)->load());

        loopLengths.push_back(apvts.getRawParameterValue("Loop Length" + num)->load());
        loopIsOn.push_back(apvts.getRawParameterValue("Loop On/Off" + num)->load());

        delaySpaces.push_back(apvts.getRawParameterValue("Delay Space" + num)->load());
        delayFeedbacks.push_back(apvts.getRawParameterValue("Delay Feedback" + num)->load());
        delayIsOn.push_back(apvts.getRawParameterValue("Delay ON/OFF" + num)->load());

        onSpaces.push_back(apvts.getRawParameterValue("Stutter On Space" + num)->load());
        offSpaces.push_back(apvts.getRawParameterValue("Stutter Off Space" + num)->load());
        onOffsets.push_back(apvts.getRawParameterValue("Stutter On Offset" + num)->load());
        offOffsets.push_back(apvts.getRawParameterValue("Stutter Off Offset" + num)->load());
        stutterAttacks.push_back(apvts.getRawParameterValue("Stutter Attack" + num)->load());
        stutterReleases.push_back(apvts.getRawParameterValue("Stutter Release" + num)->load());
        stutterIsOn.push_back(apvts.getRawParameterValue("Stutter ON/OFF" + num)->load());

        noiseMags.push_back(apvts.getRawParameterValue("Noise" + num)->load());

        bends.push_back(apvts.getRawParameterValue("Bend" + num)->load());

        pans.push_back(apvts.getRawParameterValue("Pan" + num)->load());

    }
    else {


        const char* home = std::getenv("HOME");
std::ifstream file(std::string(home) + "/data.txt");
        std::string strVoice;
        std::string strParam;
        std::string data;

        if (file.is_open()) {

            std::getline(file, strVoice);
            std::getline(file, strParam);
            std::getline(file, data);

            try { 
                int voice = std::stof(strVoice);
                float input = std::stof(data);
                int param = std::stof(strParam);
                bool negative = input < 0;

//                std::cout << "voice: " << voice << " input: " << input << " param: " << param << "\n";
                switch (param) {
                    case 0:
                        gainAmounts[voice] = input; 
                        break;
                        
                       
                    case 1:
                        pitchSemis[voice] = input / 2;         
                        break;

                    case 2:
                        if (!negative) {
                            freqs[voice] = input / 100;
                        }
                        break;

                    case 3:
                        if (!negative) {
                            wows[voice] = input;         
                        }
                        break;

                    case 4:
                        amplitudes[voice] = input / 100;                
                        break;

                    case 5:
                        if (!negative) {
                            lfos[voice] = input / 1000; 
                        } 
                        break;

                    case 6:
                          saturations[voice] = std::clamp((10.f/100.f) * input, 0.f, 10.f); 
                          break;

                      case 7:
                          highFreqs[voice] = std::clamp((100.f/1.f) * input, 20.f, 20000.f);        
                          break;

                      case 8:
                          lowFreqs[voice] =  std::clamp((100.f/1.f) * input, 20.f, 20000.f);    
                          break;

                      case 9:
                          sampleFactors[voice] =  std::clamp((12.f/12.f) * input, 0.f, 12.f);
                          break;

                      case 10:
                          bitDepths[voice] =  std::clamp((1.f/1.f) * input, 6.f, 16.f);         
                          break;

                      case 11:
                          threshs[voice] = std::clamp((1.f/2.f) * input, -50.f, 0.f);          
                          break;

                      case 12:
                          ratios[voice] =  std::clamp((1.f/1.f) * input, 1.f, 100.f);  
                          break;

                      case 13:
                          attacks[voice] =  std::clamp((2.f/1.f) * input, 0.f, 200.f);       
                          break;

                      case 14:
                          releases[voice] = std::clamp((2.f/1.f) * input, 0.f, 200.f);              
                          break;

                      case 15:
                          delayAmounts[voice] = std::clamp((100.f/1.f) * input, 0.f, 100000.f);        
                          break;

                      case 16:
                          loopLengths[voice] = std::clamp((1.f/10.f) * input, 1.f, 20.f);          
                          break;

                      case 17:
                          loopIsOn[voice] = std::clamp((1.f/1.f) * input, 0.f, 1.f); 
                          break;

                      case 18:
                          delaySpaces[voice] = std::clamp((100.f/1.f) * input, 3.f, 10000.f);             
                          break;

                      case 19:
                          delayFeedbacks[voice] = std::clamp((0.1f/1.f) * input, 0.f, 1.f);    
                          break;

                      case 20:
                          delayIsOn[voice] = std::clamp((1.f/1.f) * input, 0.f, 1.f);             
                          break;

                      case 21:
                          onSpaces[voice] = std::clamp((1000.f/1.f) * input, 1.f, 50000.f);            
                          break;

                      case 22:
                          offSpaces[voice] = std::clamp((1000.f/1.f) * input, 1.f, 50000.f);             
                          break;

                      case 23:
                          onOffsets[voice] = std::clamp((1000.f/1.f) * input, 1.f, 50000.f); 
                          break;

                      case 24:
                          offOffsets[voice] = std::clamp((1000.f/1.f) * input, 1.f, 50000.f);
                          break;

                      case 25:
                          stutterAttacks[voice] = std::clamp((1.f/50.f) * input, 0.f, 1.f);  
                          break;

                      case 26:
                          stutterReleases[voice] = std::clamp((1.f/50.f) * input, 0.f, 1.f);
                          break;

                      case 27:
                          stutterIsOn[voice] = std::clamp((1.f/1.f) * input, 0.f, 1.f);
                          break;

                      case 28:
                          noiseMags[voice] = std::clamp((1.f/10000.f) * input, 0.f, 0.0001f);     
                          break;

                      case 29:
                          bends[voice] = std::clamp((1.f/15.f) * input, 0.f, 1.f);  
                          break;

                      case 30:
                          pans[voice] = std::clamp((1.f/10.f) * input, -1.f, 1.f);             
                          break;
                      }
                
                  
            } catch (const std::invalid_argument& e) {
                
            } 
        } 
        
        if ((sin(counters[index] * (4 + (wows[index] / 5))) <= 0 && sin((counters[index] + freqs[index]) * (4 + (wows[index] / 5))) > 0) 
        || (sin(counters[index] * (4 + (wows[index] / 5))) > 0 && sin((counters[index] + freqs[index]) * (4 + (wows[index] / 5))) < 0)) {
            wowAmps[index]->setTargetValue((rand() % (int) wows[index]) / 10000);
        }

        counters[index] += freqs[index];

        
        float shift = (wowAmps[index]->getNextValue()) * sin(counters[index] * (4 + (wows[index] / 5))) + amplitudes[index] * sin(counters[index] * freqs[index]);
        if (shift > 0) {
            shift = ((100 - lfos[index]) * shift + lfos[index] * amplitudes[index]) / 100;
        } else if (shift < 0) {
            shift = ((100 - lfos[index]) * shift + lfos[index] * -amplitudes[index]) / 100;
        }
        pitchSemis[index] += shift;
    }
}


//==============================================================================
bool Project_Chromatic_AberationAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Project_Chromatic_AberationAudioProcessor::createEditor()
{
    //return new Project_Chromatic_AberationAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void Project_Chromatic_AberationAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Project_Chromatic_AberationAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}



juce::AudioProcessorValueTreeState::ParameterLayout Project_Chromatic_AberationAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    for (int i = 0; i < 5; i++) {
        std::string num = std::to_string(i);
        layout.add(std::make_unique<juce::AudioParameterFloat>("Gain" + num, "Gain" + num, juce::NormalisableRange<float>(-20.f, 20.f, 0.5, 1.f), 0));

        layout.add(std::make_unique<juce::AudioParameterFloat>("Pitch" + num, "Pitch" + num, juce::NormalisableRange<float>(-10.f, 10.f, 0.1f, 1.f), 1));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Freq" + num, "Freq" + num, juce::NormalisableRange<float>(0.0001, 5.f, 0.0001, 1.f), 0.1f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("WOW" + num, "WOW" + num, juce::NormalisableRange<float>(1, 50000.f, 1.f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Amplitude" + num, "Amplitude" + num, juce::NormalisableRange<float>(0, 5.f, 0.005, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("LFO" + num, "LFO" + num, juce::NormalisableRange<float>(0, 100.f, 0.05, 1.f), 0));
        
        layout.add(std::make_unique<juce::AudioParameterFloat>("High Pass" + num, "High Pass" + num, juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 20.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Low Pass" + num, "Low Pass" + num, juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 20000.f));

        layout.add(std::make_unique<juce::AudioParameterFloat>("Threshold" + num, "Threshold" + num, juce::NormalisableRange<float>(-44.f, 0.f, 0.5, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Ratio" + num, "Ratio" + num, juce::NormalisableRange<float>(1, 100.f, 0.5, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Attack" + num, "Attack" + num, juce::NormalisableRange<float>(0, 200.f, 1.f, 1.f), 12.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Release" + num, "Release" + num, juce::NormalisableRange<float>(0, 200.f, 1.f, 1.f), 0));


        layout.add(std::make_unique<juce::AudioParameterFloat>("Saturation" + num, "Saturation" + num, juce::NormalisableRange<float>(0, 10.f, 0.1f, 1.f), 0));

        layout.add(std::make_unique<juce::AudioParameterFloat>("Sample Rate" + num, "Sample Rate" + num, juce::NormalisableRange<float>(0, 12.f, 1.f, 1.f), 0)); 
        layout.add(std::make_unique<juce::AudioParameterFloat>("Bit Depth" + num, "Bit Depth" + num, juce::NormalisableRange<float>(6, 16, 1.f, 1.f), 16));

        layout.add(std::make_unique<juce::AudioParameterFloat>("Delay Mag" + num, "Delay Mag" + num, juce::NormalisableRange<float>(0, 100000, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Loop Length" + num, "Loop Length" + num, juce::NormalisableRange<float>(1, 20, 0.1f, 1.f), 1));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Loop On/Off" + num, "Loop On/Off" + num, juce::NormalisableRange<float>(0, 1, 1.f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Delay Space" + num, "Delay Space" + num, juce::NormalisableRange<float>(3, 10000, 1.f, 1.f), 3000));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Delay Feedback" + num, "Delay Feedback" + num, juce::NormalisableRange<float>(0.1, 1.f, 0.000001f, 1.f), 1));
        layout.add(std::make_unique<juce::AudioParameterBool>("Delay ON/OFF" + num, "Delay ON/OFF" + num, false, juce::AudioParameterBoolAttributes()));


        layout.add(std::make_unique<juce::AudioParameterFloat>("Stutter On Space" + num, "Stutter On Space" + num, juce::NormalisableRange<float>(1, 50000, 1.f, 1.f), 20));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Stutter Off Space" + num, "Stutter Off Space" + num, juce::NormalisableRange<float>(1, 50000, 1.f, 1.f), 20));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Stutter On Offset" + num, "Stutter On Offset" + num, juce::NormalisableRange<float>(1, 50000, 1.f, 1.f), 20));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Stutter Off Offset" + num, "Stutter Off Offset" + num, juce::NormalisableRange<float>(1, 50000, 1.f, 1.f), 20));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Stutter Attack" + num, "Stutter Attack" + num, juce::NormalisableRange<float>(0.f, 1.f, 0.01f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Stutter Release" + num, "Stutter Release" + num, juce::NormalisableRange<float>(0.f, 1.f, 0.01f, 1.f), 0.f));
         layout.add(std::make_unique<juce::AudioParameterBool>("Stutter ON/OFF" + num, "Stutter ON/OFF" + num, false, juce::AudioParameterBoolAttributes()));       

        layout.add(std::make_unique<juce::AudioParameterFloat>("Noise" + num, "Noise" + num, juce::NormalisableRange<float>(0.f, 0.0001f, 0.00001f, 1.f), 0.f));

        layout.add(std::make_unique<juce::AudioParameterFloat>("Bend" + num, "Bend" + num, juce::NormalisableRange<float>(0.f, 1.f, 0.01f, 1.f), 1.f));

        layout.add(std::make_unique<juce::AudioParameterFloat>("Pan" + num, "Pan" + num, juce::NormalisableRange<float>(-1.f, 1.f, 0.01f, 1.f), 0.f));

    }

    return layout; 
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Project_Chromatic_AberationAudioProcessor();
}
