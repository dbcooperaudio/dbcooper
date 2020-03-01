dB::Plugin::Plugin(
    ParameterLayout&& parameters) :
        juce::AudioProcessor(),
        state(
            *this,
            nullptr,
            juce::Identifier(JucePlugin_Name),
            std::move(parameters)
        )
{

}


dB::Plugin::Plugin(
    juce::AudioProcessor::BusesProperties&& io,
    ParameterLayout&& parameters) :
        juce::AudioProcessor(io),
        state(
            *this,
            nullptr,
            juce::Identifier(JucePlugin_Name),
            std::move(parameters)
        )
{

}


const juce::String
dB::Plugin::getName() const
{
    return JucePlugin_Name;
}


bool
dB::Plugin::acceptsMidi() const
{
    #if JucePlugin_WantsMidi
        return true;
    #else
        return false;
    #endif
}


bool
dB::Plugin::producesMidi() const
{
    #if JucePlugin_ProducesMidiOutput
        return true;
    #else
        return false;
    #endif
}


bool
dB::Plugin::isMidiEffect() const
{
    #if JucePlugin_isMidiEffect
        return true;
    #else
        return false;
    #endif
}


double
dB::Plugin::getTailLengthSeconds() const
{
    return 0.0;
}


int
dB::Plugin::getNumPrograms()
{
    return 1;
}


int
dB::Plugin::getCurrentProgram()
{
    return 0;
}


void
dB::Plugin::setCurrentProgram(
    int)
{

}


const juce::String
dB::Plugin::getProgramName(
    int)
{
    return "";
}


void
dB::Plugin::changeProgramName(
    int,
    const juce::String&)
{

}


void
dB::Plugin::prepareToPlay(
    double,
    int)
{

}


void
dB::Plugin::releaseResources()
{

}


void
dB::Plugin::getStateInformation(
    juce::MemoryBlock& data)
{
    auto currentState = state.copyState();
    currentState.setProperty("version", {JucePlugin_VersionString}, nullptr);

    if (auto xmlDocument = currentState.createXml())
        copyXmlToBinary(*xmlDocument.get(), data);
    else
        juce::Logger::writeToLog("Unable to write state");
}


void
dB::Plugin::setStateInformation(
    const void* data,
    const int   size)
{
    auto xmlDocument = getXmlFromBinary(data, (int)size);

    if (not xmlDocument)
    {
        juce::Logger::writeToLog("setStateInformation() failed to read data");
        return;
    }

    auto newState = juce::ValueTree::fromXml(*xmlDocument);

    if (not newState.isValid())
    {
        juce::Logger::writeToLog("setStateInformation() received invalid data");
        return;
    }

    state.replaceState(newState);
}
