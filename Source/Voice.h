/*
  ==============================================================================

    Voice.h
    Created: 4 Jan 2026 4:59:21pm
    Author:  Denkabe

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "signalsmith-stretch.h"
#include "Saturator.h"
#include "DownSampler.h"
#include <string>
#include <thread>
//Luther Standing Bear, Life at boarding school
//Saum Song Bo, Chinese American protest

class Voice {
public:

    Voice() {}

    void prepare(double sampleRate, int samplesPerBlock, int totalNumInputChannels, int totalNumOutputChannels, juce::AudioProcessorValueTreeState& apvts, int index) {

        this->sampleRate = sampleRate;
        juce::dsp::ProcessSpec spec;
        spec.maximumBlockSize = samplesPerBlock;
        spec.numChannels = totalNumInputChannels;
        spec.sampleRate = sampleRate;
        leftChain.prepare(spec);
        rightChain.prepare(spec);

        gainAmount = apvts.getRawParameterValue("Gain" + std::to_string(index))->load();

        pitchSemi = apvts.getRawParameterValue("Pitch" + std::to_string(index))->load();
        freq = apvts.getRawParameterValue("Freq" + std::to_string(index))->load();
        amplitude = apvts.getRawParameterValue("Amplitude" + std::to_string(index))->load();
        lfo = apvts.getRawParameterValue("LFO" + std::to_string(index))->load();

        saturation = apvts.getRawParameterValue("Saturation" + std::to_string(index))->load();

        highFreq = apvts.getRawParameterValue("High Pass" + std::to_string(index))->load();
        lowFreq = apvts.getRawParameterValue("Low Pass" + std::to_string(index))->load();

        params.wetLevel = apvts.getRawParameterValue("Reverb Mix" + std::to_string(index))->load();
        params.dryLevel = 1 - params.wetLevel;
        params.damping = apvts.getRawParameterValue("Damping" + std::to_string(index))->load();
        params.width = apvts.getRawParameterValue("Width" + std::to_string(index))->load();
        params.roomSize = apvts.getRawParameterValue("Room Size" + std::to_string(index))->load();

        sampleFactor = apvts.getRawParameterValue("Sample Rate" + std::to_string(index))->load();

        compMix = apvts.getRawParameterValue("Mix" + std::to_string(index))->load();
        thresh = apvts.getRawParameterValue("Threshold" + std::to_string(index))->load();
        ratio = apvts.getRawParameterValue("Ratio" + std::to_string(index))->load();
        attack = apvts.getRawParameterValue("Attack" + std::to_string(index))->load();
        release = apvts.getRawParameterValue("Release" + std::to_string(index))->load();

        //Gain
        gain.prepare(spec);
        gain.setGainDecibels(gainAmount);

        // Pitch Shifter / Wobble
        stretch.presetDefault(totalNumInputChannels, static_cast<int>(sampleRate), true);
        stretch.reset();

        stretchInput.setSize(totalNumInputChannels, fifoSize);
        stretchOutput.setSize(totalNumInputChannels, fifoSize);

        pitchShifter.prepare(spec);

        //Saturator
        saturator.prepare(spec);
        saturator.setSaturation(saturation);

        //Band Cuts
        leftHpFilter.prepare(spec);
        leftHpFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highFreq);
        leftLpFilter.prepare(spec);
        leftLpFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowFreq);

        rightHpFilter.prepare(spec);
        rightHpFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highFreq);
        rightLpFilter.prepare(spec);
        rightLpFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowFreq);

        //Reverb
        reverb.prepare(spec);
        reverb.setParameters(params);
        leftReverb.prepare(spec);
        rightReverb.prepare(spec);
        leftReverb.setParameters(params);
        rightReverb.setParameters(params);

        //Down Sampler
        downSampler.prepare(spec);
        downSampler.setSampleRate(sampleFactor);

        // Compressor
        leftCompressor.reset();
        leftCompressor.prepare(spec);
        leftCompressor.setThreshold(thresh);
        leftCompressor.setRatio(ratio);
        leftCompressor.setAttack(attack);
        leftCompressor.setRelease(release);

        rightCompressor.reset();
        rightCompressor.prepare(spec);
        rightCompressor.setThreshold(thresh);
        rightCompressor.setRatio(ratio);
        rightCompressor.setAttack(attack);
        rightCompressor.setRelease(release);

        leftCompMixer.prepare(spec);
        leftCompMixer.setWetMixProportion(compMix);
        rightCompMixer.prepare(spec);
        rightCompMixer.setWetMixProportion(compMix);

        counter = 0;
        randCount = 0;
    }

    void process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer midiMessages, int totalNumInputChannels, int totalNumOutputChannels, juce::AudioProcessorValueTreeState& apvts, int index) {
        juce::ScopedNoDenormals noDenormals;

        // In case we have more outputs than inputs, this code clears any output
        // channels that didn't contain input data, (because these aren't
        // guaranteed to be empty - they may contain garbage).
        // This is here to avoid people getting screaming feedback
        // when they first compile a plugin, but obviously you don't need to keep
        // this code if your algorithm always overwrites all the output channels.
        for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear(i, 0, buffer.getNumSamples());

        gainAmount = apvts.getRawParameterValue("Gain" + std::to_string(index))->load();

        pitchSemi = apvts.getRawParameterValue("Pitch" + std::to_string(index))->load();
        freq = apvts.getRawParameterValue("Freq" + std::to_string(index))->load();
        amplitude = apvts.getRawParameterValue("Amplitude" + std::to_string(index))->load();
        lfo = apvts.getRawParameterValue("LFO" + std::to_string(index))->load();

        counter += freq;
        float shift = sin(counter);
        if (lfo < 1) {
            shift *= amplitude;
        }
        else if (lfo < 2) {
            shift = (abs(1 / shift) * shift) * amplitude;
        }
        else {
            randCount++;
            if (randCount == freq + 3) {
                randCount = 0;
                srand(time(0));
                shift = (((rand() % 201) - 100) / 100) * amplitude;
            }
        }

        saturation = apvts.getRawParameterValue("Saturation" + std::to_string(index))->load();

        highFreq = apvts.getRawParameterValue("High Pass" + std::to_string(index))->load();
        lowFreq = apvts.getRawParameterValue("Low Pass" + std::to_string(index))->load();

        params.wetLevel = apvts.getRawParameterValue("Reverb Mix" + std::to_string(index))->load();
        params.dryLevel = 1 - params.wetLevel;
        params.damping = apvts.getRawParameterValue("Damping" + std::to_string(index))->load();
        params.width = apvts.getRawParameterValue("Width" + std::to_string(index))->load();
        params.roomSize = apvts.getRawParameterValue("Room Size" + std::to_string(index))->load();

        sampleFactor = apvts.getRawParameterValue("Sample Rate" + std::to_string(index))->load();

        compMix = apvts.getRawParameterValue("Mix" + std::to_string(index))->load();
        thresh = apvts.getRawParameterValue("Threshold" + std::to_string(index))->load();
        ratio = apvts.getRawParameterValue("Ratio" + std::to_string(index))->load();
        attack = apvts.getRawParameterValue("Attack" + std::to_string(index))->load();
        release = apvts.getRawParameterValue("Release" + std::to_string(index))->load();


        const int numChannels = buffer.getNumChannels();
        const int numSamples = buffer.getNumSamples();

        if (numChannels == 0 || numSamples == 0)
            return;

        /*stretchBuffer.setSize(numChannels, numSamples, false, false, true);
        stretch.setTransposeSemitones(pitchSemi + shift);

        for (int ch = 0; ch < numChannels; ++ch)
        {
            inBuffers[ch] = const_cast<float*>(buffer.getReadPointer(ch));
            outBuffers[ch] = stretchBuffer.getWritePointer(ch);
        }

        int inputSamples = numSamples;
        int outputSamples = numSamples;

        // Process with Signalsmith Stretch
        #if PERFETTO
        TRACE_EVENT_BEGIN("dsp", "signalsmith-stretch");
        #endif

        //stretch.process(inBuffers.data(), inputSamples, outBuffers.data(), outputSamples);

        #if PERFETTO
        TRACE_EVENT_END("dsp");
        #endif

        // Copy processed audio back into JUCE buffer
        const int copySamples = std::min(numSamples, outputSamples);

        #if PERFETTO
        TRACE_EVENT_BEGIN("dsp", "buffer-copy");
        #endif

        for (int ch = 0; ch < numChannels; ++ch)
        {
            //buffer.clear(ch, 0, numSamples);
            buffer.copyFrom(ch, 0, stretchBuffer, ch, 0, numSamples);
        }         */

        /*struct StretchIO
        {
            juce::AudioBuffer<float>& buffer;

            float* operator[](int channel)
            {
                return buffer.getWritePointer(channel);
            }
        };


        // 1. Render DRY voice into output buffer first
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            auto* out = buffer.getWritePointer(ch, 0);
        }

        // 2. Create a temp view pointing at JUST this voice's region
        juce::AudioBuffer<float> voiceView(
            buffer.getArrayOfWritePointers(),
            buffer.getNumChannels(),
            0,
            numSamples
        );

        StretchIO io{ voiceView };

        // 3. Configure pitch (do NOT do this per-sample)
        stretch.setTransposeSemitones(pitchSemi + shift);

        // 4. STREAMING process (in-place)
        stretch.process(io, numSamples, io, numSamples); */

        /*pitchShifter.setSemitones(pitchSemi + shift);
        pitchShifter.process(buffer);*/



        juce::dsp::AudioBlock<float> block(buffer);

        auto leftBlock = block.getSingleChannelBlock(0);
        auto rightBlock = block.getSingleChannelBlock(1);

        juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
        juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

        //Gain
        gain.setGainDecibels(gainAmount);
        gain.process(leftContext);
        gain.process(rightContext);

        //Saturation
        saturator.setSaturation(saturation);
        saturator.process(leftContext);
        saturator.process(rightContext);

        //Frequency Filters
        leftHpFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highFreq);
        leftLpFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowFreq);
        rightHpFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highFreq);
        rightLpFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowFreq);
        leftHpFilter.process(leftContext);
        rightHpFilter.process(rightContext);
        leftLpFilter.process(leftContext);
        rightLpFilter.process(rightContext);

        //Reverb
        reverb.setParameters(params);
        leftReverb.setParameters(params);
        rightReverb.setParameters(params);
        leftReverb.process(leftContext);
        rightReverb.process(rightContext);

        //Down Sampler
        downSampler.setSampleRate(sampleFactor);
        downSampler.process(leftContext);
        downSampler.process(rightContext);

        //Compressor
        leftCompMixer.pushDrySamples(block);
        rightCompMixer.pushDrySamples(block);

        leftCompressor.setThreshold(thresh);
        leftCompressor.setRatio(ratio);
        leftCompressor.setAttack(attack);
        leftCompressor.setRelease(release);
        leftCompressor.process(leftContext);

        rightCompressor.setThreshold(thresh);
        rightCompressor.setRatio(ratio);
        rightCompressor.setAttack(attack);
        rightCompressor.setRelease(release);
        rightCompressor.process(rightContext);

        leftCompMixer.setWetMixProportion(compMix);
        rightCompMixer.setWetMixProportion(compMix);
        leftCompMixer.mixWetSamples(block);
        rightCompMixer.mixWetSamples(block);




        //juce::dsp::AudioBlock<float> block(buffer);

        //auto leftBlock = block.getSingleChannelBlock(0);
        //auto rightBlock = block.getSingleChannelBlock(1);

        //juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
        //juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

        //rightChain.process(rightContext);

        //newThread.join();
    }

    void stretchProcess(std::vector<float*>& inBuffers, int inputSamples, std::vector<float*>& outBuffers, int outputSamples) {
        stretch.process(inBuffers.data(), inputSamples, outBuffers.data(), outputSamples);
    }

private:
    using Filter = juce::dsp::IIR::Filter<float>;
    signalsmith::stretch::SignalsmithStretch<float> stretch;
    WangSoundTouchPitchShifter pitchShifter;
    juce::AudioBuffer<float> stretchBuffer;

    juce::AudioBuffer<float> stretchInput;
    juce::AudioBuffer<float> stretchOutput;

    int fifoWrite = 0;
    int fifoRead = 0;
    static constexpr int fifoSize = 8192;

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

    juce::dsp::Reverb reverb;
    juce::dsp::Reverb leftReverb;
    juce::dsp::Reverb rightReverb;
    juce::Reverb::Reverb::Parameters params;

    juce::dsp::DownSampler<float> downSampler;

    float pitchSemi, freq, amplitude, counter, lfo, randCount, thresh, ratio, attack, release, highFreq, lowFreq,
        compMix, gainAmount, damping, roomSize, revMix, width, saturation, sampleFactor;
    double sampleRate;
    int totalNumInputChannels;
    int totalNumOutputChannels;

    using MonoChain = juce::dsp::ProcessorChain<Filter>;
    MonoChain leftChain, rightChain;
    std::vector<float*> inBuffers, outBuffers;

};
