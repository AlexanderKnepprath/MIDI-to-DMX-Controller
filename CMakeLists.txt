cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "C:/Users/Alexander Knepprath/Desktop/VST/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(MIDI_to_DMX_Controller
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "MIDI_to_DMX_Controller VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(MIDI_to_DMX_Controller
    source/version.h
    source/MIDI_to_DMXcids.h
    source/MIDI_to_DMXprocessor.h
    source/MIDI_to_DMXprocessor.cpp
    source/MIDI_to_DMXcontroller.h
    source/MIDI_to_DMXcontroller.cpp
    source/MIDI_to_DMXentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
    target_sources(MIDI_to_DMX_Controller
        PRIVATE
            resource/MIDI_to_DMXeditor.uidesc
    )
    target_link_libraries(MIDI_to_DMX_Controller
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(MIDI_to_DMX_Controller
        RESOURCES
            "resource/MIDI_to_DMXeditor.uidesc"
    )
endif(SMTG_ADD_VSTGUI)
# -------------------

smtg_target_add_plugin_snapshots (MIDI_to_DMX_Controller
    RESOURCES
        resource/001C4CBA77B157EEA197F18D3434ED89_snapshot.png
        resource/001C4CBA77B157EEA197F18D3434ED89_snapshot_2.0x.png
)

target_link_libraries(MIDI_to_DMX_Controller
    PRIVATE
        sdk
)

smtg_target_configure_version_file(MIDI_to_DMX_Controller)

if(SMTG_MAC)
    smtg_target_set_bundle(MIDI_to_DMX_Controller
        BUNDLE_IDENTIFIER com.tikiaudio.mididmx
        COMPANY_NAME "Tiki Audio"
    )
    smtg_target_set_debug_executable(MIDI_to_DMX_Controller
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(MIDI_to_DMX_Controller PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MIDI_to_DMX_Controller)

        smtg_target_set_debug_executable(MIDI_to_DMX_Controller
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
