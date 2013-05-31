#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

#include "level_bar.h"
#include "led.h"

class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    virtual ~MainWindow();

    void set_level(double level);
    void set_led_state(bool state);

    unsigned char get_midi_note_active()
    {
        return midi_note_active;
    }
    unsigned char get_midi_note_inactive()
    {
        return midi_note_inactive;
    }

protected:
    // Signal handlers
    void on_threshold_update();
    void on_power_switch_change();
    void on_midi_note_change();

    double threshold;
    unsigned char midi_note_active;
    unsigned char midi_note_inactive;

    // Child widgets
    Gtk::VBox m_vbox;
    Gtk::HBox m_hbox;

    Gtk::SpinButton m_active_note_entry;
    Gtk::SpinButton m_inactive_note_entry;

    Gtk::VScale m_threshold_scale;
    Gtk::Switch m_power_switch;

    LevelBar m_level_bar;
    Led m_led;

// Signals
public:
    typedef sigc::signal<void, bool> type_signal_running_state_updated;
    typedef sigc::signal<void, double> type_signal_threshold_updated;

    type_signal_running_state_updated signal_running_state_updated()
    {
        return m_signal_running_state_updated;
    };
    type_signal_threshold_updated signal_threshold_updated()
    {
        return m_signal_threshold_updated;
    };

protected:
    type_signal_running_state_updated m_signal_running_state_updated;
    type_signal_threshold_updated m_signal_threshold_updated;

};

#endif // MAIN_WINDOW_H
