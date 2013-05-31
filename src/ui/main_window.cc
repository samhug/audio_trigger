#include "main_window.h"
#include "config.h"

#include <glibmm.h>
#include <iostream>
#include <cmath>

MainWindow::MainWindow()
    : m_threshold_scale(0, 1, 0.05)
    , threshold(0.75)
    , midi_note_active(DEFAULT_MIDI_NOTE_ACTIVE)
    , midi_note_inactive(DEFAULT_MIDI_NOTE_INACTIVE)
{
    // MIDI Note Active control
    m_active_note_entry.set_range(0, 127);
    m_active_note_entry.set_increments(1, 10);
    m_active_note_entry.set_value(static_cast<unsigned int>(midi_note_active));
    m_active_note_entry.signal_value_changed().connect(sigc::mem_fun(*this,
                &MainWindow::on_midi_note_change));
    m_vbox.pack_start(m_active_note_entry, false, false);

    // MIDI Note Inactive control
    m_inactive_note_entry.set_range(0, 127);
    m_inactive_note_entry.set_increments(1, 10);
    m_inactive_note_entry.set_value(static_cast<unsigned int>(midi_note_inactive));
    m_inactive_note_entry.signal_value_changed().connect(sigc::mem_fun(*this,
                &MainWindow::on_midi_note_change));
    m_vbox.pack_start(m_inactive_note_entry, false, false);

    m_power_switch.property_active().signal_changed().connect(sigc::mem_fun(*this,
                &MainWindow::on_power_switch_change));
    m_vbox.pack_start(m_power_switch, false, false);

    m_threshold_scale.set_value(threshold);
    m_threshold_scale.set_inverted(true);
    m_threshold_scale.signal_value_changed().connect(sigc::mem_fun(*this,
                &MainWindow::on_threshold_update));
    m_hbox.pack_start(m_threshold_scale);

    m_level_bar.set_threshold_value(threshold);
    m_hbox.pack_start(m_level_bar);

    m_vbox.pack_start(m_hbox);

    m_vbox.pack_start(m_led);

    add(m_vbox);

    set_default_size(50,330);

    show_all();
}

MainWindow::~MainWindow()
{
}

void MainWindow::set_level(double level)
{
    m_level_bar.set_value(level);
}

void MainWindow::set_led_state(bool state)
{
    m_led.set_state(state);
}

void MainWindow::on_threshold_update()
{
    threshold = m_threshold_scale.get_value();
    m_level_bar.set_threshold_value(threshold);

    m_signal_threshold_updated.emit(threshold);
}

void MainWindow::on_power_switch_change()
{
    m_signal_running_state_updated.emit(m_power_switch.get_active());
}

void MainWindow::on_midi_note_change()
{
    midi_note_active = static_cast<unsigned char>(m_active_note_entry.get_value_as_int());
    midi_note_inactive = static_cast<unsigned char>(m_inactive_note_entry.get_value_as_int());
}
