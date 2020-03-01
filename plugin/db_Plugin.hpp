#pragma once


/** A subclass of juce::AudioProcessor that provides some helpful things
    utilized in all of the dBCooper plugins, such as:

        - Default behaviors for certain juce::AudioProcessor pure virtuals
        - An instance of juce::AudioProcessorValueTreeState
**/
class dB::Plugin : public juce::AudioProcessor
{
    using ParameterLayout = juce::AudioProcessorValueTreeState::ParameterLayout;

public:
    /** Constructor.

        Creates a plugin with a default stereo IO.
    **/
    Plugin(ParameterLayout&&);

    /** Constructor.

        Creates a plugin with a specified IO configuration.
    **/
    Plugin(juce::AudioProcessor::BusesProperties&&, ParameterLayout&&);

    /** Default destructor.
    **/
    ~Plugin() = default;

    /** Returns the name set by the JucePlugin_Name preprocessor definition.
    **/
    const juce::String getName() const final override;

    /** Returns the boolean state of the JucePlugin_WantsMidiInput preprocessor
        definition.
    **/
    bool acceptsMidi() const final override;

    /** Returns the boolean state of the JucePlugin_ProducesMidiOutput
        preprocessor definition.
    **/
    bool producesMidi() const final override;

    /** Returns the boolean state of the JucePlugin_IsMidiEffect
        preprocessor definition.
    **/
    bool isMidiEffect() const final override;

    /** Returns a default tail length of 0.0.
    **/
    double getTailLengthSeconds() const override;

    /** Returns a default program count of 1.
    **/
    int getNumPrograms() override;

    /** Returns a default current program of 0.
    **/
    int getCurrentProgram() override;

    /** Provides a default behavior; does nothing.
    **/
    void setCurrentProgram(int) override;

    /** Provides a default behavior; returns an empty string.
    **/
    const juce::String getProgramName(int) override;

    /** Provides a default behavior; does nothing.
    **/
    void changeProgramName(int, const juce::String&) override;

    /** Provides a default behavior; does nothing.
    **/
    void prepareToPlay(double, int) override;

    /** Provides a default behavior; does nothing.
    **/
    void releaseResources() override;

    /** Provides a default implementation for saving state by saving the
        AudioProcessorValueTreeState state as XML.
    **/
    void getStateInformation(juce::MemoryBlock&) override;

    /** Provides a default implementation for restoring state by restoring XML
        for the AudioProcessorValueTreeState state from the supplied data.
    **/
    void setStateInformation(const void*, int) override;

    /** The state for the plugin. This will handle parameters, but can also be
        used to store other things like GUI state.
    **/
    juce::AudioProcessorValueTreeState state;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Plugin)
};
