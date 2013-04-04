#include "main_window.h"

#include <glibmm.h>
#include <iostream>
#include <cmath>

MainWindow::MainWindow()
    : m_vbox()
    , m_hbox()
    , m_threshold_scale(0, 1, 0.05)
    , m_level_bar()
    , m_led()
    , threshold(0.75)
{

    m_threshold_scale.set_value(threshold);
    m_threshold_scale.set_inverted(true);
    m_threshold_scale.signal_value_changed().connect(sigc::mem_fun(*this, &MainWindow::on_threshold_change));
    m_hbox.pack_start(m_threshold_scale);

    m_level_bar.set_threshold_value(threshold);
    m_hbox.pack_start(m_level_bar);

    m_vbox.pack_start(m_hbox);

    m_vbox.pack_start(m_led);

    add(m_vbox);

    set_default_size(50,200);

    show_all();
    

    Glib::signal_timeout().connect(sigc::mem_fun(*this, &MainWindow::on_timeout), 10);
}

MainWindow::~MainWindow()
{
}

bool MainWindow::on_timeout()
{
    counter++;

    value = (1 + sin(counter / 10.0 / (2*M_PI))) / 2;

    m_level_bar.set_value(value);
    
    if (!state && value >= threshold) {
       m_signal_triggered.emit(); 
       state = true;
    }

    if (state && value < threshold) {
       m_signal_released.emit(); 
       state = false;
    }

    return true;
}

void MainWindow::on_threshold_change()
{
    threshold = m_threshold_scale.get_value();
    m_level_bar.set_threshold_value(threshold);
}

MainWindow::type_signal_triggered MainWindow::signal_triggered()
{
    return m_signal_triggered;
}

MainWindow::type_signal_released MainWindow::signal_released()
{
    return m_signal_released;
}
