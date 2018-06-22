//
//  Compressor.h
//  MultibandCompressor
//
//  Created by Amogh Matt on 03/03/2018.
//
//  Based on the compressor example plug-in by Reiss and McPherson
//  ---
//
//  Compressor: dynamic range compression effect
//  See textbook Chapter 6: Dynamics Processing
//
//  Code by Joshua Reiss, Brecht de Man and Andrew McPherson
//
//  ---

#ifndef Compressor_h
#define Compressor_h
#include "../JuceLibraryCode/JuceHeader.h"

class Compressor
{
public:
    Compressor() {}
    ~Compressor() {}
    
    void prepareToPlay (double samplerate, int samplesPerBlock, int numInputChannels);
    void processBlock(AudioSampleBuffer &buffer);
    void setParameters(float ratio, float threshold, float attack, float release, float makeUpGain, float kneeWidth);

private:
    // Parameters
    float cRatio;
    float cThreshold;
    float cAttack;
    float cRelease;
    float cMakeUpGain;
    float cKneeWidth;
    float cSampleRate;

    // Compressor ON-OFF state
    int compressorState = 1;

    // Gain and Levels
    float inputGain;
    float inputLevel;
    float outputGain;
    float outputLevel;

    float previousOutputLevel;
    
    float controlVoltage;
};

#endif /* Compressor_h */
