//
//  Compressor.cpp
//  MultibandCompressor - VST
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

#include "Compressor.h"
#include <stdio.h>

void Compressor::processBlock(AudioSampleBuffer &buffer)
{
    int bufferSize = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels(); // number of channels
    int M = round(numChannels/2); // number of stereo channels
    
    // create blank input buffer to add to
    AudioSampleBuffer inputBuffer(M, bufferSize);
    inputBuffer.clear();
    
    for (int m = 0 ; m < M ; ++m) //For each channel pair of channels
    {
        if (compressorState) // check if compressor is active
        {
            if ( (cThreshold < 0) ) // check if compressor threshold is non-zero
            {
                // Mix down left-right to analyse the input
                inputBuffer.addFrom(m,0,buffer,m*2,0,bufferSize,0.5);
                inputBuffer.addFrom(m,0,buffer,m*2+1,0,bufferSize,0.5);
                
                // compression : calculates the control voltage
                float alphaAttack = exp(-1/(0.001 * cSampleRate * cAttack));
                float alphaRelease= exp(-1/(0.001 * cSampleRate * cRelease));
                for (int i = 0 ; i < bufferSize ; ++i)
                {
                    //Level detection- estimate level using peak detector
                    if (fabs(buffer.getWritePointer(m)[i]) < 0.000001)
                    {
                        inputGain =-120;
                    }
                    else
                    {
                        inputGain =20*log10(fabs(buffer.getWritePointer(m)[i]));
                    }
                    
                    // Gain computer - apply input/output curve with kneewidth
                    // Incorporating the SOFT KNEE
                    if (2 * (inputGain-cThreshold) >= cKneeWidth)
                    {
                        // above knee
                        outputGain = cThreshold+ (inputGain - cThreshold) / cRatio;
                    }
                    else if (2 * fabs(inputGain - cThreshold) <= cKneeWidth)
                    {
                        // in knee
                        outputGain = inputGain + (1/cRatio - 1) * pow(inputGain - cThreshold + cKneeWidth/2, 2)/(2 * cKneeWidth);
                    }
                    else {
                        // below knee
                        outputGain = inputGain;
                    }
                    
                    inputLevel = inputGain - outputGain;
                    
                    //Ballistics- smoothing of the gain
                    if (inputLevel>previousOutputLevel)
                        outputLevel=alphaAttack * previousOutputLevel+(1 - alphaAttack ) * inputLevel;
                    else
                        outputLevel=alphaRelease* previousOutputLevel+(1 - alphaRelease) * inputLevel;
                    
                    //find control voltage
                    controlVoltage = pow(10,(cMakeUpGain - outputLevel)/20);
                    previousOutputLevel=outputLevel;
                    
                    // apply control voltage to both channels
                    buffer.getWritePointer(2*m+0)[i] *= controlVoltage;
                    buffer.getWritePointer(2*m+1)[i] *= controlVoltage;
                }
            }
            else
            {
                // if threshold = 0, still apply make up gain.
                buffer.applyGain(pow(10,(cMakeUpGain)/20));
            }
        }
    }
}

void Compressor::setParameters(float ratio, float threshold, float attack, float release, float makeUpGain, float kneeWidth)
{
    cRatio = ratio;
    cThreshold = threshold;
    cAttack = attack;
    cRelease = release;
    cMakeUpGain = Decibels::gainToDecibels(makeUpGain);
    cKneeWidth = kneeWidth;
}

void Compressor::prepareToPlay(double samplerate, int samplesPerBlock, int numInputChannels)
{
    cSampleRate = samplerate;
    previousOutputLevel = 0;
}
