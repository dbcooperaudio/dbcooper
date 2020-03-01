dB::PluginEditor::PluginEditor(
    dB::Plugin& plugin) :
        juce::AudioProcessorEditor(plugin),
        processor(plugin)
{

}


void
dB::PluginEditor::attachControl(
    juce::Slider& slider,
    const juce::String& paramID)
{
    const auto* const param = processor.state.getParameter(paramID);

    if (not param)
    {
        jassertfalse;
        return;
    }

    slider.setComponentID(paramID);

    if (slider.getName().isEmpty())
        slider.setName(param->getName(128));

    if (slider.getTooltip().isEmpty())
        slider.setTooltip(param->getName(128));

    sliderAttachments.add(new SliderAttachment(
        processor.state, paramID, slider
    ));
}


void
dB::PluginEditor::attachControl(
    juce::Button& button,
    const juce::String& paramID)
{
    const auto* const param = processor.state.getParameter(paramID);

    if (not param)
    {
        jassertfalse;
        return;
    }

    button.setComponentID(paramID);

    if (button.getName().isEmpty())
        button.setName(param->getName(128));

    if (button.getTooltip().isEmpty())
        button.setTooltip(param->getName(128));

    buttonAttachments.add(new ButtonAttachment(
       processor.state, paramID, button
    ));
}


void
dB::PluginEditor::attachControl(
    juce::ComboBox& comboBox,
    const juce::String& paramID)
{
    const auto* const param = processor.state.getParameter(paramID);

    if (not param)
    {
        jassertfalse;
        return;
    }

    comboBox.setComponentID(paramID);

    if (comboBox.getName().isEmpty())
        comboBox.setName(param->getName(128));

    if (comboBox.getTooltip().isEmpty())
        comboBox.setTooltip(param->getName(128));

    if (param->isDiscrete())
        comboBox.addItemList(param->getAllValueStrings(), 1);

    comboBoxAttachments.add(new ComboBoxAttachment(
       processor.state, paramID, comboBox
    ));
}


static juce::Component* const
findComponentWithID(
          juce::Component& parent,
    const juce::String&    componentID)
{
    for (auto* const child : parent.getChildren())
    {
        if (child->getComponentID() == componentID)
            return child;

        if (auto* const result = findComponentWithID(*child, componentID))
            return result;
    }

    return nullptr;
}


void
dB::PluginEditor::setControlHighlight(
    const juce::AudioProcessorEditor::ParameterControlHighlightInfo info)
{
    const auto params = processor.getParameters();

    if (info.parameterIndex >= params.size())
        return;

    const auto* const param = dynamic_cast<juce::AudioProcessorParameterWithID*>(
        processor.getParameters()[info.parameterIndex]
    );

    jassert(param); // Parameter should be juce::AudioProcessorParameterWithID!
    if (not param)
        return;

    if (auto* const target = findComponentWithID(*this, param->paramID))
    {
        if (info.isHighlighted)
            target->setColour(controlHighlightColourId, info.suggestedColour);
        else
            target->removeColour(controlHighlightColourId);
    }
}


int
dB::PluginEditor::getControlParameterIndex(
    juce::Component& component)
{
    const auto& ID = component.getComponentID();

    if (ID.isNotEmpty())
        if (const auto* const param = processor.state.getParameter(ID))
            return param->getParameterIndex();

    return -1;
}
