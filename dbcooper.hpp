/*
    BEGIN_JUCE_MODULE_DECLARATION

        ID:             dbcooper
        vendor:         dBCooper Audio
        version:        0.0.0
        name:           dBCooper
        description:    dBCooper JUCE Module
        website:        github.com/dbcooperaudio
        license:        GPLv3
        dependencies:   juce_core, juce_audio_processors, juce_events, juce_graphics, juce_gui_basics

    END_JUCE_MODULE_DECLARATION
*/

#pragma once

#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace dB
{
    class Plugin;
    class PluginEditor;
}

#include "plugin/db_Plugin.hpp"
#include "plugin/db_PluginEditor.hpp"
