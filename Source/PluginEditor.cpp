/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandCompressorAudioProcessorEditor::MultibandCompressorAudioProcessorEditor (MultibandCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    // Low Band Knobs
    addAndMakeVisible(sliderLowThreshold = new Slider ("Low Gain Threshold"));
    (*sliderLowThreshold).setRange(-80, 0, 0);
    (*sliderLowThreshold).setSliderStyle (Slider::LinearVertical);
    (*sliderLowThreshold).setTextBoxStyle (Slider::TextBoxAbove, false, 40, 20);
    (*sliderLowThreshold).addListener (this);
    
    addAndMakeVisible(sliderLowRatio = new Slider ("Low Ratio Slider"));
    (*sliderLowRatio).setRange (1, 10, 0);
    (*sliderLowRatio).setSliderStyle (Slider::Rotary);
    (*sliderLowRatio).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderLowRatio).addListener (this);
    
    addAndMakeVisible(sliderLowAttack = new Slider ("Low Attack Slider"));
    (*sliderLowAttack).setRange (5, 100, 0);
    (*sliderLowAttack).setSliderStyle (Slider::Rotary);
    (*sliderLowAttack).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderLowAttack).addListener (this);
    
    addAndMakeVisible(sliderLowRelease = new Slider ("Low Release Slider"));
    (*sliderLowRelease).setRange (5, 100, 0);
    (*sliderLowRelease).setSliderStyle (Slider::Rotary);
    (*sliderLowRelease).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderLowRelease).addListener (this);
    
    addAndMakeVisible(sliderLowGain = new Slider ("Low Gain Slider"));
    (*sliderLowGain).setRange (-80, 40, 0);
    (*sliderLowGain).setSliderStyle (Slider::Rotary);
    (*sliderLowGain).setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    (*sliderLowGain).addListener (this);
    
    // Mid Band Knobs
    addAndMakeVisible(sliderMidThreshold = new Slider ("Mid Gain Threshold"));
    (*sliderMidThreshold).setRange (-80, 0, 0);
    (*sliderMidThreshold).setSliderStyle (Slider::LinearVertical);
    (*sliderMidThreshold).setTextBoxStyle (Slider::TextBoxAbove, false, 40, 20);
    (*sliderMidThreshold).addListener (this);
    
    addAndMakeVisible(sliderMidRatio = new Slider ("Mid Ratio Slider"));
    (*sliderMidRatio).setRange (1, 10, 0);
    (*sliderMidRatio).setSliderStyle (Slider::Rotary);
    (*sliderMidRatio).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderMidRatio).addListener (this);
    
    addAndMakeVisible (sliderMidAttack = new Slider ("Mid Attack Slider"));
    (*sliderMidAttack).setRange (5, 100, 0);
    (*sliderMidAttack).setSliderStyle (Slider::Rotary);
    (*sliderMidAttack).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderMidAttack).addListener (this);
    
    addAndMakeVisible (sliderMidRelease = new Slider ("Mid Release Slider"));
    (*sliderMidRelease).setRange (5, 100, 0);
    (*sliderMidRelease).setSliderStyle (Slider::Rotary);
    (*sliderMidRelease).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderMidRelease).addListener (this);
    
    addAndMakeVisible (sliderMidGain = new Slider ("Mid Gain Slider"));
    (*sliderMidGain).setRange (-80, 40, 0);
    (*sliderMidGain).setSliderStyle (Slider::Rotary);
    (*sliderMidGain).setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    (*sliderMidGain).addListener (this);
    
    // High Band Knobs
    addAndMakeVisible (sliderHighThreshold = new Slider ("High Gain Threshold"));
    (*sliderHighThreshold).setRange (-80, 0, 0);
    (*sliderHighThreshold).setSliderStyle (Slider::LinearVertical);
    (*sliderHighThreshold).setTextBoxStyle (Slider::TextBoxAbove, false, 40, 20);
    (*sliderHighThreshold).addListener (this);
    
    addAndMakeVisible (sliderHighRatio = new Slider ("High Ratio Slider"));
    (*sliderHighRatio).setRange (1, 10, 0);
    (*sliderHighRatio).setSliderStyle (Slider::Rotary);
    (*sliderHighRatio).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderHighRatio).addListener (this);
    
    addAndMakeVisible (sliderHighAttack = new Slider ("High Attack Slider"));
    (*sliderHighAttack).setRange (5, 100, 0);
    (*sliderHighAttack).setSliderStyle (Slider::Rotary);
    (*sliderHighAttack).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderHighAttack).addListener (this);
    
    addAndMakeVisible (sliderHighRelease = new Slider ("High Release Slider"));
    (*sliderHighRelease).setRange (5, 100, 0);
    (*sliderHighRelease).setSliderStyle (Slider::Rotary);
    (*sliderHighRelease).setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    (*sliderHighRelease).addListener (this);
    
    addAndMakeVisible (sliderHighGain = new Slider ("High Gain Slider"));
    (*sliderHighGain).setRange (-80, 40, 0);
    (*sliderHighGain).setSliderStyle (Slider::Rotary);
    (*sliderHighGain).setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    (*sliderHighGain).addListener (this);
    
    // Low Cutoff Frequency Slider
    addAndMakeVisible(sliderLowCutoff = new Slider ("Low Cutoff"));
    (*sliderLowCutoff).setRange (150, 600, 0);
    (*sliderLowCutoff).setSliderStyle (Slider::Rotary);
    (*sliderLowCutoff).setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    (*sliderLowCutoff).addListener (this);
    (*sliderLowCutoff).setSkewFactor (2);
    
     // High Cutoff Frequency Slider
    addAndMakeVisible(sliderHighCutoff = new Slider ("High Cutoff"));
    (*sliderHighCutoff).setRange (1000, 4000, 0);
    (*sliderHighCutoff).setSliderStyle (Slider::Rotary);
    (*sliderHighCutoff).setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    (*sliderHighCutoff).addListener (this);
    (*sliderHighCutoff).setSkewFactor (2);
    
    // Compressor State Buttons
    addAndMakeVisible(buttonLowCompressorState = new TextButton ("Low Compressor"));
    (*buttonLowCompressorState).setButtonText (TRANS("Low"));
    (*buttonLowCompressorState).setColour(TextButton::buttonOnColourId, Colours::lightblue);
    (*buttonLowCompressorState).setColour(TextButton::textColourOnId, Colours::black);
    (*buttonLowCompressorState).setColour(TextButton::textColourOffId, Colours::white);
    (*buttonLowCompressorState).addListener (this);
    
    addAndMakeVisible(buttonMidCompressorState = new TextButton ("Mid Compressor"));
    (*buttonMidCompressorState).setButtonText (TRANS("Mid"));
    (*buttonMidCompressorState).setColour(TextButton::buttonOnColourId, Colours::lightblue);
    (*buttonMidCompressorState).setColour(TextButton::textColourOnId, Colours::black);
    (*buttonMidCompressorState).setColour(TextButton::textColourOffId, Colours::white);
    (*buttonMidCompressorState).addListener (this);
    
    addAndMakeVisible(buttonHighCompressorState = new TextButton ("High Compressor"));
    (*buttonHighCompressorState).setButtonText (TRANS("High"));
    (*buttonHighCompressorState).setColour(TextButton::buttonOnColourId, Colours::lightblue);
    (*buttonHighCompressorState).setColour(TextButton::textColourOnId, Colours::black);
    (*buttonHighCompressorState).setColour(TextButton::textColourOffId, Colours::white);
    (*buttonHighCompressorState).addListener (this);
    
    (*buttonHighCompressorState).setClickingTogglesState(true);
    (*buttonMidCompressorState).setClickingTogglesState(true);
    (*buttonLowCompressorState).setClickingTogglesState(true);
    
    // Labels
    addAndMakeVisible(cutoffLabel = new Label ("Cutoff", TRANS("Cutoff:")));
    (*cutoffLabel).setFont (Font (15.00f, Font::plain));
    (*cutoffLabel).setJustificationType (Justification::centredLeft);
    (*cutoffLabel).setEditable (false, false, false);
    (*cutoffLabel).setColour(Label::textColourId, Colours::white);
    
    addAndMakeVisible(thresholdLabel = new Label ("Threshold", TRANS("Threshold:")));
    (*thresholdLabel).setFont (Font (15.00f, Font::plain));
    (*thresholdLabel).setJustificationType (Justification::centredLeft);
    (*thresholdLabel).setEditable (false, false, false);
    (*thresholdLabel).setColour(Label::textColourId, Colours::white);
    
    addAndMakeVisible(ratioLabel = new Label ("Ratio", TRANS("Ratio:")));
    (*ratioLabel).setFont (Font (15.00f, Font::plain));
    (*ratioLabel).setJustificationType (Justification::centredLeft);
    (*ratioLabel).setEditable (false, false, false);
    (*ratioLabel).setColour(Label::textColourId, Colours::white);
    
    addAndMakeVisible(attackLabel = new Label ("Attack", TRANS("Attack:")));
    (*attackLabel).setFont (Font (15.00f, Font::plain));
    (*attackLabel).setJustificationType (Justification::centredLeft);
    (*attackLabel).setEditable (false, false, false);
    (*attackLabel).setColour(Label::textColourId, Colours::white);
    
    addAndMakeVisible(releaseLabel = new Label ("Release", TRANS("Release:")));
    (*releaseLabel).setFont (Font (15.00f, Font::plain));
    (*releaseLabel).setJustificationType (Justification::centredLeft);
    (*releaseLabel).setEditable (false, false, false);
    (*releaseLabel).setColour(Label::textColourId, Colours::white);
    
    addAndMakeVisible(gainLabel = new Label ("Gain", TRANS("Gain:")));
    (*gainLabel).setFont (Font (15.00f, Font::plain));
    (*gainLabel).setJustificationType (Justification::centredLeft);
    (*gainLabel).setEditable (false, false, false);
    (*gainLabel).setColour(Label::textColourId, Colours::white);
    
    addAndMakeVisible (sliderKneeWidth = new Slider ("Knee Width"));
    (*sliderKneeWidth).setRange (0, 10, 0);
    (*sliderKneeWidth).setSliderStyle (Slider::Rotary);
    (*sliderKneeWidth).setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    (*sliderKneeWidth).addListener (this);
    
    addAndMakeVisible (sliderOverallGain = new Slider ("Overall Gain"));
    (*sliderOverallGain).setRange (-40, 10, 0);
    (*sliderOverallGain).setSliderStyle (Slider::Rotary);
    (*sliderOverallGain).setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    (*sliderOverallGain).addListener (this);
    
    addAndMakeVisible (kneeWidthLabel = new Label ("Kneewidth", TRANS("Knee Width:")));
    (*kneeWidthLabel).setFont (Font (15.00f, Font::plain));
    (*kneeWidthLabel).setJustificationType (Justification::centredLeft);
    (*kneeWidthLabel).setEditable (false, false, false);
    (*kneeWidthLabel).setColour (TextEditor::textColourId, Colours::black);
    (*kneeWidthLabel).setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (overallGainLabel = new Label ("OverallGain", TRANS("Overall Gain:")));
    (*overallGainLabel).setFont (Font (15.00f, Font::plain));
    (*overallGainLabel).setJustificationType (Justification::centredLeft);
    (*overallGainLabel).setEditable (false, false, false);
    (*overallGainLabel).setColour(Label::textColourId, Colours::white);
    
    setSize (800, 600);
    startTimer(100);
 
}

MultibandCompressorAudioProcessorEditor::~MultibandCompressorAudioProcessorEditor()
{
    sliderLowCutoff = nullptr;
    sliderHighCutoff = nullptr;
    
    buttonLowCompressorState = nullptr;
    buttonMidCompressorState = nullptr;
    buttonHighCompressorState = nullptr;
    
    sliderLowThreshold = nullptr;
    sliderLowRatio = nullptr;
    sliderLowAttack = nullptr;
    sliderLowRelease = nullptr;
    sliderLowGain = nullptr;
    
    sliderMidThreshold = nullptr;
    sliderMidRatio = nullptr;
    sliderMidAttack = nullptr;
    sliderMidRelease = nullptr;
    sliderMidGain = nullptr;
    
    sliderHighThreshold = nullptr;
    sliderHighRatio = nullptr;
    sliderHighAttack = nullptr;
    sliderHighRelease = nullptr;
    sliderHighGain = nullptr;
    
    cutoffLabel = nullptr;
    thresholdLabel = nullptr;
    ratioLabel = nullptr;
    attackLabel = nullptr;
    releaseLabel = nullptr;
    gainLabel = nullptr;
    
    kneeWidthLabel = nullptr;
    sliderKneeWidth = nullptr;
    
    overallGainLabel = nullptr;
    sliderOverallGain = nullptr;
}

//==============================================================================
void MultibandCompressorAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillAll(Colours::black);
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText("Multiband Compressor", getWidth()/2 - 75, 0, 150, 20, Justification::centred, 1);
}

void MultibandCompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // Cutoff Frequency Sliders
    (*sliderLowCutoff).setBounds (175, 31, 56, 64);
    (*sliderHighCutoff).setBounds (325, 31, 56, 64);
    
    // Compressor State Buttons
    (*buttonLowCompressorState).setBounds (110, 98, 50, 24);
    (*buttonMidCompressorState).setBounds (260, 98, 50, 24);
    (*buttonHighCompressorState).setBounds (410, 98, 50, 24);
    
    // Threshold Sliders
    (*sliderLowThreshold).setBounds (115, 128, 40, 112);
    (*sliderMidThreshold).setBounds (265, 128, 40, 112);
    (*sliderHighThreshold).setBounds (415, 128, 40, 112);
    
    // Labels
    (*cutoffLabel).setBounds(16, 60, 88, 24);
    (*thresholdLabel).setBounds (16, 160, 88, 24);
    (*ratioLabel).setBounds (16, 280, 48, 24);
    (*attackLabel).setBounds (16, 360, 64, 24);
    (*releaseLabel).setBounds (16, 440, 72, 24);
    (*gainLabel).setBounds (16, 520, 48, 24);
    
    // Low Band Knobs
    (*sliderLowRatio).setBounds (100, 260, 80, 64);
    (*sliderLowAttack).setBounds (100, 340, 80, 64);
    (*sliderLowRelease).setBounds (100, 420, 80, 64);
    (*sliderLowGain).setBounds (100, 500, 80, 64);
    
    // Mid Band Knobs
    (*sliderMidRatio).setBounds (250, 260, 80, 64);
    (*sliderMidAttack).setBounds (250, 340, 80, 64);
    (*sliderMidRelease).setBounds (250, 420, 80, 64);
    (*sliderMidGain).setBounds (250, 500, 80, 64);
    
    // High Band Knobs
    (*sliderHighRatio).setBounds (400, 260, 80, 64);
    (*sliderHighAttack).setBounds (400, 340, 80, 64);
    (*sliderHighRelease).setBounds (400, 420, 80, 64);
    (*sliderHighGain).setBounds (400, 500, 80, 64);
    
    // Knee Width
    (*kneeWidthLabel).setBounds (500, 360, 88, 24);
    (*sliderKneeWidth).setBounds (600, 340, 80, 64);
    
    // Overall Gain
    (*overallGainLabel).setBounds (500, 440, 88, 24);
    (*sliderOverallGain).setBounds (600, 420, 80, 64);

}

void MultibandCompressorAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    // Slider Changed Values for Low Compressor
    if (sliderThatWasMoved == sliderLowThreshold)
        processor.setLowThreshold((*sliderLowThreshold).getValue());
    else if (sliderThatWasMoved == sliderLowRatio)
        processor.setLowRatio((*sliderLowRatio).getValue());
    else if (sliderThatWasMoved == sliderLowAttack)
        processor.setLowAttack((*sliderLowAttack).getValue());
    else if (sliderThatWasMoved == sliderLowRelease)
        processor.setLowRelease((*sliderLowRelease).getValue());
    else if (sliderThatWasMoved == sliderLowGain)
        processor.setLowGain((*sliderLowGain).getValue());
    
    // Slider Changed Values for Mid Compressor
    else if (sliderThatWasMoved == sliderMidThreshold)
        processor.setMidThreshold((*sliderMidThreshold).getValue());
    else if (sliderThatWasMoved == sliderMidRatio)
        processor.setMidRatio((*sliderMidRatio).getValue());
    else if (sliderThatWasMoved == sliderMidAttack)
        processor.setMidAttack((*sliderMidAttack).getValue());
    else if (sliderThatWasMoved == sliderMidRelease)
        processor.setMidRelease((*sliderMidRelease).getValue());
    else if (sliderThatWasMoved == sliderMidGain)
        processor.setMidGain((*sliderMidGain).getValue());
    
    // Slider Changed Values for High Compressor
    else if (sliderThatWasMoved == sliderHighThreshold)
        processor.setHighThreshold((*sliderHighThreshold).getValue());
    else if (sliderThatWasMoved == sliderHighRatio)
        processor.setHighRatio((*sliderHighRatio).getValue());
    else if (sliderThatWasMoved == sliderHighAttack)
        processor.setHighAttack((*sliderHighAttack).getValue());
    else if (sliderThatWasMoved == sliderHighRelease)
        processor.setHighRelease((*sliderHighRelease).getValue());
    else if (sliderThatWasMoved == sliderHighGain)
        processor.setHighGain((*sliderHighGain).getValue());
    else if (sliderThatWasMoved == sliderKneeWidth)
        processor.setKneeWidth((*sliderKneeWidth).getValue());
    else if (sliderThatWasMoved == sliderOverallGain)
        processor.setOverallGain((*sliderOverallGain).getValue());
    
    // Slider Changed Values for Cut Off Frequencies
    else if (sliderThatWasMoved == sliderLowCutoff)
        processor.setLowCutoff((*sliderLowCutoff).getValue());
    else if (sliderThatWasMoved == sliderHighCutoff)
        processor.setHighCutoff((*sliderHighCutoff).getValue());
}

void MultibandCompressorAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == buttonLowCompressorState)
        processor.setLowCompressorState((*buttonLowCompressorState).getToggleState());
    else if (buttonThatWasClicked == buttonMidCompressorState)
        processor.setMidCompressorState((*buttonMidCompressorState).getToggleState());
    else if (buttonThatWasClicked == buttonHighCompressorState)
        processor.setHighCompressorState((*buttonHighCompressorState).getToggleState());
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MultibandCompressorAudioProcessorEditor::timerCallback() {
    
    (*sliderOverallGain).setValue(processor.getOverallGain());
    (*sliderKneeWidth).setValue(processor.getKneeWidth());
    
    (*sliderLowGain).setValue(processor.getLowGain());
    (*sliderLowThreshold).setValue(processor.getLowThreshold());
    (*sliderLowRatio).setValue(processor.getLowRatio());
    (*sliderLowAttack).setValue(processor.getLowAttack());
    (*sliderLowRelease).setValue(processor.getLowRelease());
    
    (*sliderMidGain).setValue(processor.getMidGain());
    (*sliderMidThreshold).setValue(processor.getMidThreshold());
    (*sliderMidRatio).setValue(processor.getMidRatio());
    (*sliderMidAttack).setValue(processor.getMidAttack());
    (*sliderMidRelease).setValue(processor.getMidRelease());
    
    (*sliderHighGain).setValue(processor.getHighGain());
    (*sliderHighThreshold).setValue(processor.getHighThreshold());
    (*sliderHighRatio).setValue(processor.getHighRatio());
    (*sliderHighAttack).setValue(processor.getHighAttack());
    (*sliderHighRelease).setValue(processor.getHighRelease());
    
    (*buttonLowCompressorState).setToggleState(processor.getLowCompressorState(), dontSendNotification);
    (*buttonMidCompressorState).setToggleState(processor.getMidCompressorState(), dontSendNotification);
    (*buttonHighCompressorState).setToggleState(processor.getHighCompressorState(), dontSendNotification);
    
    (*sliderLowCutoff).setValue(processor.getLowCutoff());
    (*sliderHighCutoff).setValue(processor.getHighCutoff());
    
}
