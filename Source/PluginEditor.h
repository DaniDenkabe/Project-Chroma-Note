/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Project_Chromatic_AberationAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Project_Chromatic_AberationAudioProcessorEditor (Project_Chromatic_AberationAudioProcessor&);
    ~Project_Chromatic_AberationAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Project_Chromatic_AberationAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project_Chromatic_AberationAudioProcessorEditor)
};
