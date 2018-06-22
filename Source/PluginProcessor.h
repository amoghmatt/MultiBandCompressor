/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Compressor.h"

//==============================================================================
/**
*/
class MultibandCompressorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MultibandCompressorAudioProcessor();
    ~MultibandCompressorAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // Appended by Amogh Matt
    //==============================================================================
    // Setter Functions for each parameter
    
    void setOverallGain(float overallGain) { pOverallGain = Decibels::decibelsToGain(overallGain); }
    void setKneeWidth(float kneeWidth) { pKneeWidth = kneeWidth; }
    
    // Cutoff Parameters
    void setLowCutoff(float lowCutoff) { pLowPassCutoff = lowCutoff; }
    void setHighCutoff(float highCutoff) { pHighPassCutoff = highCutoff; }
    
    // Low Compressor Parameters
    void setLowGain(float lowGain) { pLowGain = Decibels::decibelsToGain(lowGain); }
    void setLowThreshold(float lowThreshold) { pLowThreshold = lowThreshold; }
    void setLowRatio(float lowRatio) { pLowRatio = lowRatio; }
    void setLowAttack(float lowAttack) { pLowAttack = lowAttack; }
    void setLowRelease(float lowRelease) { pLowRelease = lowRelease; }
    
    // Mid Compressor Parameters
    void setMidGain(float midGain) { pMidGain = Decibels::decibelsToGain(midGain); }
    void setMidThreshold(float midThreshold) { pMidThreshold = midThreshold; }
    void setMidRatio(float midRatio) { pMidRatio = midRatio; }
    void setMidAttack(float midAttack) { pMidAttack = midAttack; }
    void setMidRelease(float midRelease) { pMidRelease = midRelease; }
    
    // High Compressor Parameters
    void setHighGain(float highGain) { pHighGain = Decibels::decibelsToGain(highGain); }
    void setHighThreshold(float highThreshold) { pHighThreshold = highThreshold; }
    void setHighRatio(float highRatio) { pHighRatio = highRatio; }
    void setHighAttack(float highAttack) { pHighAttack = highAttack; }
    void setHighRelease(float highRelease) { pHighRelease = highRelease; }
    
    // Compressor States
    void setLowCompressorState(int lowCompressorState) { pLowCompressorState = lowCompressorState;}
    void setMidCompressorState(int midCompressorState) { pMidCompressorState = midCompressorState;}
    void setHighCompressorState(int highCompressorState) { pHighCompressorState = highCompressorState;}
    
    //==============================================================================
    // Getter Functions for each parameter
    
    float getOverallGain() { return Decibels::gainToDecibels(pOverallGain); }
    float getKneeWidth() { return pKneeWidth; }
    
    // Cutoff Parameters
    float getLowCutoff() { return pLowPassCutoff; }
    float getHighCutoff() { return pHighPassCutoff; }
    
    // Low Compressor Parameters
    float getLowGain() { return Decibels::gainToDecibels(pLowGain); }
    float getLowThreshold() { return pLowThreshold; }
    float getLowRatio() { return pLowRatio; }
    float getLowAttack() { return pLowAttack; }
    float getLowRelease() { return pLowRelease ; }
    
    // Mid Compressor Parameters
    float getMidGain() { return Decibels::gainToDecibels(pMidGain); }
    float getMidThreshold() { return pMidThreshold; }
    float getMidRatio() { return pMidRatio; }
    float getMidAttack() { return pMidAttack; }
    float getMidRelease() { return pMidRelease; }
    
    // High Compressor Parameters
    float getHighGain() { return Decibels::gainToDecibels(pHighGain); }
    float getHighThreshold() { return pHighThreshold; }
    float getHighRatio() { return pHighRatio; }
    float getHighAttack() { return pHighAttack; }
    float getHighRelease() { return pHighRelease; }
    
    // Compressor States
    float getLowCompressorState() { return pLowCompressorState;}
    float getMidCompressorState() { return pMidCompressorState;}
    float getHighCompressorState() { return pHighCompressorState;}

private:
    //==============================================================================
    //Appended by Amogh Matt
    
    // Filter Definition
    IIRFilter lowBandFilterL1,lowBandFilterL2,lowBandFilterR1,lowBandFilterR2;
    IIRFilter lowMidBandFilterL1,lowMidBandFilterL2, lowMidBandFilterR1,lowMidBandFilterR2;
    IIRFilter highMidBandFilterL1, highMidBandFilterL2, highMidBandFilterR1, highMidBandFilterR2;
    IIRFilter highBandFilterL1, highBandFilterL2, highBandFilterR1, highBandFilterR2;
    IIRCoefficients coefficients;
    
    // Compressors
    ScopedPointer<Compressor> lowCompressor;
    ScopedPointer<Compressor> midCompressor;
    ScopedPointer<Compressor> highCompressor;

    // Parameters
    int numChannels;
    float pOverallGain;
    float pKneeWidth;

    // Cutoff Frequencies
    float pLowPassCutoff;
    float pHighPassCutoff;
    
    // Compressor Parameters
    float pLowGain, pLowThreshold, pLowRatio, pLowAttack, pLowRelease;
    float pMidGain, pMidThreshold, pMidRatio, pMidAttack, pMidRelease;
    float pHighGain, pHighThreshold, pHighRatio, pHighAttack, pHighRelease;
    
    // Compressor States
    int pLowCompressorState;
    int pMidCompressorState;
    int pHighCompressorState;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandCompressorAudioProcessor)
};
