//------------------------------------------------------------------------
// Copyright(c) 2024 Tiki Audio.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace Tiki {
//------------------------------------------------------------------------
static const Steinberg::FUID kMIDI_to_DMXProcessorUID (0x001C4CBA, 0x77B157EE, 0xA197F18D, 0x3434ED89);
static const Steinberg::FUID kMIDI_to_DMXControllerUID (0x69522479, 0x21D9507D, 0x949D913D, 0x91D16E10);

#define MIDI_to_DMXVST3Category "Instrument"

//------------------------------------------------------------------------
} // namespace Tiki
