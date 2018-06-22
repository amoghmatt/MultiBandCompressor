/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandCompressorAudioProcessor::MultibandCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Default Low Band Values
    pLowGain = 1.0;
    pLowThreshold = 0.0;
    pLowRatio = 1.0;
    pLowAttack =  5.0;
    pLowRelease = 5.0;
    
    // Default Mid Band Values
    pMidGain = 1.0;
    pMidThreshold = 0.0;
    pMidRatio = 1.0;
    pMidAttack = 5.0;
    pMidRelease = 5.0;
    
    // Default High Band Values
    pHighGain = 1.0;
    pHighThreshold = 0.0;
    pHighRatio = 1.0;
    pHighAttack = 5.0;
    pHighRelease = 5.0;
    
    // Default Compressor States
    pLowCompressorState = 1;
    pMidCompressorState = 1;
    pHighCompressorState = 1;
    
    pOverallGain = 10.0;
    pKneeWidth = 0.0;

    // Default Cutoff Frequencies
    pLowPassCutoff = 500;
    pHighPassCutoff = 3000;

    // Initialise the Compressors
    lowCompressor = new Compressor;
    midCompressor = new Compressor;
    highCompressor = new Compressor;
    
}

MultibandCompressorAudioProcessor::~MultibandCompressorAudioProcessor()
{
}

//==============================================================================
const String MultibandCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultibandCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultibandCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultibandCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultibandCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultibandCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultibandCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultibandCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const String MultibandCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultibandCompressorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MultibandCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    numChannels = getTotalNumInputChannels();
    
    // Calculate Filter Coefficients
    //==============================
    // First Left Channel Filters
    lowBandFilterL1.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
    lowMidBandFilterL1.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
    highMidBandFilterL1.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
    highBandFilterL1.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));

    // First Right Channel Filters
    lowBandFilterR1.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
    lowMidBandFilterR1.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
    highMidBandFilterR1.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
    highBandFilterR1.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));

    // Second Left Channel Filters
    lowBandFilterL2.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
    lowMidBandFilterL2.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
    highMidBandFilterL2.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
    highBandFilterL2.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));

    // Second Right Channel Filters
    lowBandFilterR2.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
    lowMidBandFilterR2.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
    highMidBandFilterR2.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
    highBandFilterR2.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));

    // Prepare the Compressors
     (*lowCompressor).prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());
     (*midCompressor).prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());
     (*highCompressor).prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    
    // Initialise the Compressor Parameters
    (*lowCompressor).setParameters(pLowRatio, pLowThreshold, pLowAttack, pLowRelease, pLowGain, pKneeWidth);
    (*midCompressor).setParameters(pMidRatio, pMidThreshold, pMidAttack, pMidRelease, pMidGain, pKneeWidth);
    (*highCompressor).setParameters(pHighRatio, pHighThreshold, pHighAttack, pHighRelease, pHighGain, pKneeWidth);
}

void MultibandCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultibandCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void MultibandCompressorAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();

    // Initialise Buffer for Each Band
    AudioSampleBuffer lowOutput;
    AudioSampleBuffer midOutput;
    AudioSampleBuffer highOutput;
    
    // Set each buffer to an input
    lowOutput.makeCopyOf(buffer);
    midOutput.makeCopyOf(buffer);
    highOutput.makeCopyOf(buffer);
    
    float sampleRate = getSampleRate();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    // Recalculate the coefficients in case the cutoffs are altered
    // First Left Channel Filters
    lowBandFilterL1.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
    lowMidBandFilterL1.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
    highMidBandFilterL1.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
    highBandFilterL1.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));
    
    // First Right Channel Filters
    lowBandFilterR1.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
    lowMidBandFilterR1.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
    highMidBandFilterR1.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
    highBandFilterR1.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));
    
    // Second Left Channel Filters
    lowBandFilterL2.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
    lowMidBandFilterL2.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
    highMidBandFilterL2.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
    highBandFilterL2.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));
    
    // Second Right Channel Filters
    lowBandFilterR2.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
    lowMidBandFilterR2.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
    highMidBandFilterR2.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
    highBandFilterR2.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));
    
    // Apply Filter onto the buffer
    //==============================
    // First Low Band Filtering Stage
    lowBandFilterL1.processSamples(lowOutput.getWritePointer(0), numSamples);
    lowBandFilterR1.processSamples(lowOutput.getWritePointer(1), numSamples);
    // Second Low Band Filtering Stage
    lowBandFilterL2.processSamples(lowOutput.getWritePointer(0), numSamples);
    lowBandFilterR2.processSamples(lowOutput.getWritePointer(1), numSamples);
    
    // First Low - Mid Band Filtering Stage
    lowMidBandFilterL1.processSamples(midOutput.getWritePointer(0), numSamples);
    lowMidBandFilterR1.processSamples(midOutput.getWritePointer(1), numSamples);
    // Second Low - Mid Band Filtering Stage
    lowMidBandFilterL2.processSamples(midOutput.getWritePointer(0), numSamples);
    lowMidBandFilterR2.processSamples(midOutput.getWritePointer(1), numSamples);
    
    //First High - Mid Band Filtering Stage
    highMidBandFilterL1.processSamples(midOutput.getWritePointer(0), numSamples);
    highMidBandFilterR1.processSamples(midOutput.getWritePointer(1), numSamples);
    // Second High - Mid Band Filtering Stage
    highMidBandFilterL2.processSamples(midOutput.getWritePointer(0), numSamples);
    highMidBandFilterR2.processSamples(midOutput.getWritePointer(1), numSamples);
    
    // First High Band Filtering Stage
    highBandFilterL1.processSamples(highOutput.getWritePointer(0), numSamples);
    highBandFilterR1.processSamples(highOutput.getWritePointer(1), numSamples);
    // Second High Band Filtering Stage
    highBandFilterL2.processSamples(highOutput.getWritePointer(0), numSamples);
    highBandFilterR2.processSamples(highOutput.getWritePointer(1), numSamples);
    
    // Set the Compressor Parameters
    (*lowCompressor).setParameters(pLowRatio, pLowThreshold, pLowAttack, pLowRelease, pLowGain, pKneeWidth);
    (*midCompressor).setParameters(pMidRatio, pMidThreshold, pMidAttack, pMidRelease, pMidGain, pKneeWidth);
    (*highCompressor).setParameters(pHighRatio, pHighThreshold, pHighAttack, pHighRelease, pHighGain, pKneeWidth);

    // Compress Each Band
    if(pLowCompressorState)
        (*lowCompressor).processBlock(lowOutput);
    if(pMidCompressorState)
        (*midCompressor).processBlock(midOutput);
    if(pHighCompressorState)
        (*highCompressor).processBlock(highOutput);
    
    // Sum Each Band
    buffer.clear();
    for (int channel = 0; channel < totalNumInputChannels; channel++)
    {
        buffer.addFrom(channel, 0, lowOutput, channel, 0, numSamples, 1.0/3.0);
        buffer.addFrom(channel, 0, midOutput, channel, 0, numSamples, 1.0/3.0);
        buffer.addFrom(channel, 0, highOutput, channel, 0, numSamples, 1.0/3.0);
    }
    
    // Apply the Overall Gain
    buffer.applyGain(pOverallGain);
}

//==============================================================================
bool MultibandCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MultibandCompressorAudioProcessor::createEditor()
{
    return new MultibandCompressorAudioProcessorEditor (*this);
}

//==============================================================================
void MultibandCompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MultibandCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultibandCompressorAudioProcessor();
}
