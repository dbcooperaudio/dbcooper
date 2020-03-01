#pragma once


/** A simple juce::AudioProcessorEditor subclass that provides an implementation
    for easy parameter control attachment and highlighting.
**/
class dB::PluginEditor : juce::AudioProcessorEditor
{
    using AudioProcessorValueTreeState = juce::AudioProcessorValueTreeState;
    using SliderAttachment   = AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment   = AudioProcessorValueTreeState::ButtonAttachment;
    using ComboBoxAttachment = AudioProcessorValueTreeState::ComboBoxAttachment;

public:

    enum ColourIds
    {
        controlHighlightColourId = 0xDBC00,
    };

    /** Constructor.
    **/
    PluginEditor(dB::Plugin&);

    /** Destructor.
    **/
    virtual ~PluginEditor() = default;

    /** Creates a SliderAttachment to manage syncing the slider with a
        parameter.

        This function will also set the slider's component ID to match the given
        parameter ID.
    **/
    void attachControl(juce::Slider&, const juce::String&);

    /** Creates a ButtonAttachment to manage syncing the button with a
        parameter.

        This function will also set the button's component ID to match the given
        parameter ID.
    **/
    void attachControl(juce::Button&, const juce::String&);

    /** Creates a ComboBoxAttachment to manage syncing the button with a
        parameter.

        This function will also set the combo-box's component ID to match the
        given parameter ID.
    **/
    void attachControl(juce::ComboBox&, const juce::String&);

    /** Finds and sets the highlight for a component based off of parameter
        information.

        The parameter's ID will be to used to find the component, using
        juce::Component::findChildWithID() recursively.
    **/
    void setControlHighlight(ParameterControlHighlightInfo) override;

    /** Determines the parameter attached to a component based off the
        component's ID.

        If you override this method, you may want to still call this base class
        version as well to fallback on using component ID.
    **/
    int getControlParameterIndex(juce::Component&) override;

private:
    dB::Plugin& processor;

    juce::OwnedArray<SliderAttachment>   sliderAttachments;
    juce::OwnedArray<ButtonAttachment>   buttonAttachments;
    juce::OwnedArray<ComboBoxAttachment> comboBoxAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
