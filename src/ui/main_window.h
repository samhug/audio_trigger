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

    typedef sigc::signal<void> type_signal_triggered;
    typedef sigc::signal<void> type_signal_released;

    type_signal_triggered signal_triggered();
    type_signal_released signal_released();

protected:
    // Signal handlers
    bool on_timeout();
    void on_threshold_change();

    int counter;
    bool state;

    double value;
    double threshold;

    // Child widgets
    Gtk::VBox m_vbox;
    Gtk::HBox m_hbox;

    Gtk::VScale m_threshold_scale;

    LevelBar m_level_bar;
    Led m_led;

    type_signal_triggered m_signal_triggered;
    type_signal_released m_signal_released;
};

#endif // MAIN_WINDOW_H
