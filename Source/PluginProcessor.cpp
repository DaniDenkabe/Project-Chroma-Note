/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <cmath>
#include <cstdlib>
#include <thread>

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
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    

    stretchBuffers[index]->setSize(numChannels, numSamples, false, false, true);

    if (numChannels == 0 || numSamples == 0)
        return;

    stretchList[index]->setTransposeSemitones(pitchSemis[index]);

    for (int ch = 0; ch < numChannels; ++ch)
    {
        inBuffers[index][ch] = const_cast<float*>(buffer.getReadPointer(ch));
        outBuffers[index][ch] = stretchBuffers[index]->getWritePointer(ch);
    }

    int inputSamples = numSamples;  
    int outputSamples = numSamples;

    // Process with Signalsmith Stretch
    stretchList[index]->process(inBuffers[index].data(), numSamples, outBuffers[index].data(), numSamples);

    // Copy processed audio back into JUCE buffer
    const int copySamples = std::min(numSamples, outputSamples);

    for (int ch = 0; ch < numChannels; ++ch)
    {
        buffer.copyFrom(ch, 0, *stretchBuffers[index], ch, 0, copySamples);
    }
}

void Project_Chromatic_AberationAudioProcessor::processPitch(int index, juce::dsp::ProcessSpec spec) {
    stretchList.push_back(new signalsmith::stretch::SignalsmithStretch<float>);
    stretchList[index]->presetDefault(spec.numChannels, spec.sampleRate, true);
    stretchList[index]->reset();
    stretchBuffers.push_back(new juce::AudioBuffer<float>);
    stretchBuffers[index]->setSize(getNumInputChannels(), spec.sampleRate, false, true, true);
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





void Project_Chromatic_AberationAudioProcessor::processReverb(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    leftReverbList[index]->setParameters(*paramList[index]);
    rightReverbList[index]->setParameters(*paramList[index]);
    leftReverbList[index]->process(leftContext);
    rightReverbList[index]->process(rightContext);
}


void Project_Chromatic_AberationAudioProcessor::processReverb(int index, juce::dsp::ProcessSpec spec) {
    leftReverbList.push_back(new juce::dsp::Reverb);
    rightReverbList.push_back(new juce::dsp::Reverb);
    leftReverbList[index]->prepare(spec);
    rightReverbList[index]->prepare(spec);
    leftReverbList[index]->setParameters(*paramList[index]);
    rightReverbList[index]->setParameters(*paramList[index]);
}





void Project_Chromatic_AberationAudioProcessor::processDownSampler(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    downSamplerList[index]->setSampleRate(sampleFactors[index]);
    downSamplerList[index]->setBitDepth(bitDepths[index]);
    downSamplerList[index]->process(leftContext);
    downSamplerList[index]->process(rightContext);
}


void Project_Chromatic_AberationAudioProcessor::processDownSampler(int index, juce::dsp::ProcessSpec spec) {
    downSamplerList.push_back(new juce::dsp::DownSampler<float>);
    downSamplerList[index]->prepare(spec);
    downSamplerList[index]->setSampleRate(sampleFactors[index]);
    downSamplerList[index]->setBitDepth(bitDepths[index]);
}





void Project_Chromatic_AberationAudioProcessor::processCompressor(int index, juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    leftCompMixerList[index]->pushDrySamples(block);
    rightCompMixerList[index]->pushDrySamples(block);

    leftCompressorList[index]->setThreshold(threshs[index]);
    leftCompressorList[index]->setRatio(ratios[index]);
    leftCompressorList[index]->setAttack(attacks[index]);
    leftCompressorList[index]->setRelease(releases[index]);
    leftCompressorList[index]->process(leftContext);

    rightCompressorList[index]->setThreshold(threshs[index]);
    rightCompressorList[index]->setRatio(ratios[index]);
    rightCompressorList[index]->setAttack(attacks[index]);
    rightCompressorList[index]->setRelease(releases[index]);
    rightCompressorList[index]->process(rightContext);

    leftCompMixerList[index]->setWetMixProportion(compMixes[index]);
    rightCompMixerList[index]->setWetMixProportion(compMixes[index]);
    leftCompMixerList[index]->mixWetSamples(block);
    rightCompMixerList[index]->mixWetSamples(block);
}


void Project_Chromatic_AberationAudioProcessor::processCompressor(int index, juce::dsp::ProcessSpec spec) {
    leftCompressorList.push_back(new juce::dsp::Compressor<float>);
    leftCompressorList[index]->reset();
    leftCompressorList[index]->prepare(spec);
    leftCompressorList[index]->setThreshold(threshs[index]);
    leftCompressorList[index]->setRatio(ratios[index]);
    leftCompressorList[index]->setAttack(attacks[index]);
    leftCompressorList[index]->setRelease(releases[index]);

    rightCompressorList.push_back(new juce::dsp::Compressor<float>);
    rightCompressorList[index]->reset();
    rightCompressorList[index]->prepare(spec);
    rightCompressorList[index]->setThreshold(threshs[index]);
    rightCompressorList[index]->setRatio(ratios[index]);
    rightCompressorList[index]->setAttack(attacks[index]);
    rightCompressorList[index]->setRelease(releases[index]);

    leftCompMixerList.push_back(new juce::dsp::DryWetMixer<float>);
    rightCompMixerList.push_back(new juce::dsp::DryWetMixer<float>);
    leftCompMixerList[index]->prepare(spec);
    leftCompMixerList[index]->setWetMixProportion(compMixes[index]);
    rightCompMixerList[index]->prepare(spec);
    rightCompMixerList[index]->setWetMixProportion(compMixes[index]);
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
    delayLineList[index]->setMaximumDelayInSamples(10000);
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

        processReverb(i, spec);

        processDownSampler(i, spec);

        processCompressor(i, spec);

        processDelayLine(i, spec);

        processLooper(i, spec);

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

    float voiceGain = 0.000005;

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    for (int i = 0; i < copyBuffers.size(); i++) {
        copyBuffers.at(i)->setSize(buffer.getNumChannels(), buffer.getNumSamples());
        for (int chan = 0; chan < buffer.getNumChannels(); chan++) {
            copyBuffers.at(i)->copyFrom(chan, 0, buffer, chan, 0, buffer.getNumSamples());
        }
    }
    buffer.clear();
    for (int i = 0; i < copyBuffers.size(); i++) {
        for (int chan = 0; chan < getTotalNumOutputChannels(); chan++) {
            buffer.addFrom(chan, 0, *copyBuffers.at(i), chan, 0, buffer.getNumSamples(), voiceGain);
        }
    }

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.

    for (int i = 0; i < copyBuffers.size() + 1; i++) {

        setVariables(i, false);

        if (i != copyBuffers.size()) {

            processGain(i, *copyBuffers[i]);

            //When I comment out this line everything works fine
            //processPitch(i, *copyBuffers[i]);

            processSaturator(i, *copyBuffers[i]);

            processFreqCuts(i, *copyBuffers[i]);

            processReverb(i, *copyBuffers[i]);

            processDownSampler(i, *copyBuffers[i]);

            processCompressor(i, *copyBuffers[i]);

            processDelayLine(i, *copyBuffers[i]);

            //processLooper(i, *copyBuffers[i]);

        }
        else {
            processGain(i, buffer);

            processPitch(i, buffer);

            processSaturator(i, buffer);

            processFreqCuts(i, buffer);

            processReverb(i, buffer);

            processDownSampler(i, buffer);

            processCompressor(i, buffer);

            processDelayLine(i, buffer);

            processLooper(i, buffer);
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

        std::vector<float*> inList;
        inList.resize(100);
        inBuffers.push_back(inList);

        std::vector<float*> outList;
        outList.resize(100);
        outBuffers.push_back(outList);

        saturations.push_back(apvts.getRawParameterValue("Saturation" + num)->load());

        /*chorusMixes.push_back(apvts.getRawParameterValue("Chorus Mix" + num)->load());
        rates.push_back(apvts.getRawParameterValue("Rate" + num)->load());
        depths.push_back(apvts.getRawParameterValue("Depth" + num)->load());
        centreDelays.push_back(apvts.getRawParameterValue("Center Delay" + num)->load());
        feedbacks.push_back(apvts.getRawParameterValue("Feedback" + num)->load());*/

        highFreqs.push_back(apvts.getRawParameterValue("High Pass" + num)->load());
        lowFreqs.push_back(apvts.getRawParameterValue("Low Pass" + num)->load());

        paramList.push_back(new  juce::Reverb::Reverb::Parameters);
        paramList[index]->wetLevel = apvts.getRawParameterValue("Reverb Mix" + num)->load();
        paramList[index]->dryLevel = 1 - paramList[index]->wetLevel;
        paramList[index]->damping = apvts.getRawParameterValue("Damping" + num)->load();
        paramList[index]->width = apvts.getRawParameterValue("Width" + num)->load();
        paramList[index]->roomSize = apvts.getRawParameterValue("Room Size" + num)->load();

        sampleFactors.push_back(apvts.getRawParameterValue("Sample Rate" + num)->load());
        bitDepths.push_back(apvts.getRawParameterValue("Bit Depth" + num)->load());

        compMixes.push_back(apvts.getRawParameterValue("Mix" + num)->load());
        threshs.push_back(apvts.getRawParameterValue("Threshold" + num)->load());
        ratios.push_back(apvts.getRawParameterValue("Ratio" + num)->load());
        attacks.push_back(apvts.getRawParameterValue("Attack" + num)->load());
        releases.push_back(apvts.getRawParameterValue("Release" + num)->load());

        delayAmounts.push_back(apvts.getRawParameterValue("Delay Mag" + num)->load());

        loopLengths.push_back(apvts.getRawParameterValue("Loop Length" + num)->load());
        loopIsOn.push_back(apvts.getRawParameterValue("Loop On/Off" + num)->load());
    }
    else {
        gainAmounts[index] = apvts.getRawParameterValue("Gain" + num)->load();

        pitchSemis[index] = apvts.getRawParameterValue("Pitch" + num)->load();
        freqs[index] = apvts.getRawParameterValue("Freq" + num)->load();
        amplitudes[index] = apvts.getRawParameterValue("Amplitude" + num)->load();
        lfos[index] = apvts.getRawParameterValue("LFO" + num)->load();

        counters[index] += freqs[index];
        float shift = sin(counters[index]);
        if (lfo < 1) {
            shift *= amplitudes[index];
        }
        else if (lfo < 2) {
            shift = (abs(1 / shift) * shift) * amplitudes[index];
        }
        else {
            randCounts[index]++;
            if (randCounts[index] == freqs[index] + 3) {
                randCounts[index] = 0;
                srand(time(0));
                shift = (((rand() % 201) - 100) / 100) * amplitudes[index];
            }
        }
        pitchSemis[index] += shift;

        saturations[index] = apvts.getRawParameterValue("Saturation" + num)->load();

        /*chorusMixes[index] = apvts.getRawParameterValue("Chorus Mix" + num)->load();
        rates[index] = apvts.getRawParameterValue("Rate" + num)->load();
        depths[index] = apvts.getRawParameterValue("Depth" + num)->load();
        centreDelays[index] = apvts.getRawParameterValue("Center Delay" + num)->load();
        chorusMixes[index] = apvts.getRawParameterValue("Feedback" + num)->load();*/

        highFreqs[index] = apvts.getRawParameterValue("High Pass" + num)->load();
        lowFreqs[index] = apvts.getRawParameterValue("Low Pass" + num)->load();

        paramList[index]->wetLevel = apvts.getRawParameterValue("Reverb Mix" + num)->load();
        paramList[index]->dryLevel = 1 - paramList[index]->wetLevel;
        paramList[index]->damping = apvts.getRawParameterValue("Damping" + num)->load();
        paramList[index]->width = apvts.getRawParameterValue("Width" + num)->load();
        paramList[index]->roomSize = apvts.getRawParameterValue("Room Size" + num)->load();

        sampleFactors[index] = apvts.getRawParameterValue("Sample Rate" + num)->load();
        bitDepths[index] = apvts.getRawParameterValue("Bit Depth" + num)->load();

        compMixes[index] = apvts.getRawParameterValue("Mix" + num)->load();
        threshs[index] = apvts.getRawParameterValue("Threshold" + num)->load();
        ratios[index] = apvts.getRawParameterValue("Ratio" + num)->load();
        attacks[index] = apvts.getRawParameterValue("Attack" + num)->load();
        releases[index] = apvts.getRawParameterValue("Release" + num)->load();

        delayAmounts[index] = apvts.getRawParameterValue("Delay Mag" + num)->load();

        loopLengths[index] = apvts.getRawParameterValue("Loop Length" + num)->load();
        loopIsOn[index] = apvts.getRawParameterValue("Loop On/Off" + num)->load();
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

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts) {
    ChainSettings settings;

    return settings;
}

juce::AudioProcessorValueTreeState::ParameterLayout Project_Chromatic_AberationAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    for (int i = 0; i < 5; i++) {
        std::string num = std::to_string(i);
        layout.add(std::make_unique<juce::AudioParameterFloat>("Gain" + num, "Gain" + num, juce::NormalisableRange<float>(-100.f, 100.f, 0.5, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Pitch" + num, "Pitch" + num, juce::NormalisableRange<float>(-10.f, 10.f, 0.5, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Freq" + num, "Freq" + num, juce::NormalisableRange<float>(0.0001, 2.f, 0.0001, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Amplitude" + num, "Amplitude" + num, juce::NormalisableRange<float>(0, 5.f, 0.005, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("LFO" + num, "LFO" + num, juce::NormalisableRange<float>(0, 3.f, 0.05, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("High Pass" + num, "High Pass" + num, juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 20.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Low Pass" + num, "Low Pass" + num, juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 20000.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Mix" + num, "Mix" + num, juce::NormalisableRange<float>(0.f, 1.f, 0.1, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Threshold" + num, "Threshold" + num, juce::NormalisableRange<float>(-24.f, 0.f, 0.5, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Ratio" + num, "Ratio" + num, juce::NormalisableRange<float>(1, 20.f, 0.5, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Attack" + num, "Attack" + num, juce::NormalisableRange<float>(0, 100.f, 1.f, 1.f), 12.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Release" + num, "Release" + num, juce::NormalisableRange<float>(0, 100.f, 1.f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Reverb Mix" + num, "Reverb Mix" + num, juce::NormalisableRange<float>(0, 1.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Damping" + num, "Damping" + num, juce::NormalisableRange<float>(0, 1.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Width" + num, "Width" + num, juce::NormalisableRange<float>(0, 1.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Room Size" + num, "Room Size" + num, juce::NormalisableRange<float>(0, 1.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Saturation" + num, "Saturation" + num, juce::NormalisableRange<float>(0, 10.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Sample Mix" + num, "Sample Mix" + num, juce::NormalisableRange<float>(0, 1.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Sample Rate" + num, "Sample Rate" + num, juce::NormalisableRange<float>(0, 100.f, 1.f, 1.f), 0)); 
        layout.add(std::make_unique<juce::AudioParameterFloat>("Bit Depth" + num, "Bit Depth" + num, juce::NormalisableRange<float>(6, 16, 1.f, 1.f), 16));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Chorus Mix" + num, "Chorus Mix" + num, juce::NormalisableRange<float>(0, 1.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Depth" + num, "Depth" + num, juce::NormalisableRange<float>(0, 1.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Center Delay" + num, "Center Delay" + num, juce::NormalisableRange<float>(0, 100.f, 1.f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Rate" + num, "Rate" + num, juce::NormalisableRange<float>(0, 100.f, 1.f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Feedback" + num, "Feedback" + num, juce::NormalisableRange<float>(-1, 1.f, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Delay Mag" + num, "Delay Mag" + num, juce::NormalisableRange<float>(0, 10000, 0.1f, 1.f), 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Loop Length" + num, "Loop Length" + num, juce::NormalisableRange<float>(1, 20, 0.1f, 1.f), 1));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Loop On/Off" + num, "Loop On/Off" + num, juce::NormalisableRange<float>(0, 1, 1.f, 1.f), 0));
    }

    return layout; 
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Project_Chromatic_AberationAudioProcessor();
}
