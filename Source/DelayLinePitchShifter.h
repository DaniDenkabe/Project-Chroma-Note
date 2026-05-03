/*
  ==============================================================================

    DenkabePitchShifter.h
    Created: 1 May 2026 11:18:42am
    Author:  denkabe

  ==============================================================================
*/

#include <JuceHeader.h>
#include <atomic>
#pragma once

namespace juce::dsp {

template <typename FloatType>



class DelayLinePitchShifter
  {
  public:
  DelayLinePitchShifter()  = default;
  ~DelayLinePitchShifter() = default;

// =========================================================================
void prepare (const juce::dsp::ProcessSpec& spec, int windowSamples = 512)
{
    sampleRate     = spec.sampleRate;
    numChannels    = (int)spec.numChannels;
    windowSize     = windowSamples;

    // Buffer must be large enough for the write head to lap the read head
    // at the maximum pitch ratio (4×) during one full crossfade window,
    // plus generous headroom.  2× windowSize × maxRatio + margin suffices.
    delayLen = windowSize * 12;
    buf.setSize (numChannels, delayLen, false, true, false);

    buildFadeTable();
    reset();
}

void reset()
{
    buf.clear();
    writePos = 0;

    // Head 0 starts active, sitting windowSize samples behind write.
    heads[0].pos      = (double)(delayLen - windowSize);
    heads[0].active   = true;
    heads[0].fadePh   = 0.0;   // not in a crossfade

    // Head 1 starts idle at the same safe offset; it will be repositioned
    // before it's ever faded in.
    heads[1].pos      = (double)(delayLen - windowSize);
    heads[1].active   = false;
    heads[1].fadePh   = 0.0;

    crossfading       = false;
    fadePhase         = 0.0;
}

// =========================================================================
/** 1.0 = unity, 2.0 = octave up, 0.5 = octave down. */
void setPitchRatio (float ratio)
{
    pitchRatio.store (juce::jlimit (0.125f, 4.0f, ratio),
                      std::memory_order_relaxed);
}

void setPitchShiftSemitones (float semitones)
{
    setPitchRatio (std::pow (2.0f, semitones / 12.0f));
}

float getPitchRatio()       const { return pitchRatio.load (std::memory_order_relaxed); }
int   getLatencyInSamples() const { return windowSize; }

// =========================================================================
void process (juce::dsp::AudioBlock<float>& block)
{
    const int   N     = (int)block.getNumSamples();
    const float ratio = pitchRatio.load (std::memory_order_relaxed);

    // Determine safe read range.
    // The active head must stay inside [writePos - (delayLen-1), writePos].
    // We trigger a crossfade when the lag (distance behind write) is about
    // to violate those bounds.
    //
    //   pitch up   (ratio > 1): head catches write → lag shrinks → crossfade when lag < windowSize
    //   pitch down (ratio < 1): head falls behind  → lag grows  → crossfade when lag > delayLen - windowSize
    const double minLag = (double)windowSize;
    const double maxLag = (double)(delayLen - windowSize);

    for (int ch = 0; ch < numChannels; ++ch)
    {
        float* data  = block.getChannelPointer (ch);
        float* d     = buf.getWritePointer (ch);

        // Restore per-channel state (heads are shared — same positions for
        // all channels keeps the stereo image mono-compatible).
        int    wp  = writePos;
        double p0  = heads[0].pos;
        double p1  = heads[1].pos;
        bool   xf  = crossfading;
        double fp  = fadePhase;

        for (int i = 0; i < N; ++i)
        {
            // 1. Write
            d[wp] = data[i];

            // 2. Compute lag of the active head (head 0)
            double lag = (double)wp - p0;
            if (lag < 0.0) lag += (double)delayLen;

            // 3. Trigger crossfade if head 0 is drifting out of safe zone
            if (!xf && (lag < minLag || lag > maxLag))
            {
                xf = true;
                fp = 0.0;

                // Park head 1 at the centre of the safe zone: lag = windowSize * 3
                // (well inside the buffer, independent of where head 0 has drifted)
                p1 = (double)wp - (double)windowSize * 3.0;
                if (p1 < 0.0) p1 += (double)delayLen;
            }

            // 4. Read
            float out;
            if (!xf)
            {
                // No crossfade — just read head 0
                out = hermite (d, p0);
            }
            else
            {
                // Crossfading: head 0 fades out, head 1 fades in
                const float fadeIn  = fadeTable[(int)fp];
                const float fadeOut = fadeTable[windowSize - 1 - (int)fp];

                out = hermite (d, p0) * fadeOut
                    + hermite (d, p1) * fadeIn;

                fp += 1.0;

                if (fp >= (double)windowSize)
                {
                    // Crossfade complete: head 1 becomes head 0
                    p0 = p1;
                    xf = false;
                    fp = 0.0;
                }
            }

            data[i] = out;

            // 5. Advance write
            wp = (wp + 1) % delayLen;

            // 6. Advance both read heads by pitchRatio
            p0 += (double)ratio;
            if (p0 >= (double)delayLen) p0 -= (double)delayLen;

            p1 += (double)ratio;
            if (p1 >= (double)delayLen) p1 -= (double)delayLen;
        }

        // Write back (channel 0 owns canonical state)
        if (ch == 0)
        {
            writePos      = wp;
            heads[0].pos  = p0;
            heads[1].pos  = p1;
            crossfading   = xf;
            fadePhase     = fp;
        }
    }
}

void processBlock (float** channelData, int numChans, int numSamples)
{
    juce::dsp::AudioBlock<float> block (channelData,
                                        (size_t)numChans,
                                        (size_t)numSamples);
    process (block);
}


private:
// =========================================================================
struct Head { double pos = 0.0; bool active = false; double fadePh = 0.0; };
double sampleRate   = 44100.0;
int    numChannels  = 2;
int    windowSize   = 512;
int    delayLen     = 6144;

std::atomic<float> pitchRatio { 1.0f };

juce::AudioBuffer<float> buf;
int    writePos   = 0;
Head   heads[2];

bool   crossfading = false;
double fadePhase   = 0.0;

std::vector<float> fadeTable;  // linear ramp 0 → 1, length = windowSize

// -------------------------------------------------------------------------
void buildFadeTable()
{
    fadeTable.resize ((size_t)windowSize);
    for (int n = 0; n < windowSize; ++n)
        fadeTable[(size_t)n] = (float)n / (float)(windowSize - 1);
}

// -------------------------------------------------------------------------
inline float hermite (const float* d, double pos) const noexcept
{
    // Wrap
    while (pos <  0.0)              pos += (double)delayLen;
    while (pos >= (double)delayLen) pos -= (double)delayLen;

    const int   i  = (int)pos;
    const float t  = (float)(pos - (double)i);

    const float xm1 = d[wrap(i-1)];
    const float x0  = d[wrap(i  )];
    const float x1  = d[wrap(i+1)];
    const float x2  = d[wrap(i+2)];

    const float a = 0.5f*(3.f*x0 - xm1 - 3.f*x1 + x2);
    const float b = xm1 - 2.5f*x0 + 2.f*x1 - 0.5f*x2;
    const float c = 0.5f*(x1 - xm1);

    return ((a*t + b)*t + c)*t + x0;
}

inline int wrap (int i) const noexcept
{
    return ((i % delayLen) + delayLen) % delayLen;
}

JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayLinePitchShifter)
};



}
