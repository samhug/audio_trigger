#include <iostream>
#include <gtkmm.h>
#include <glibmm.h>

#include "ui/main_window.h"
#include "audio_trigger_client.h"
#include "config.h"

// Trigger states
#define TRIGGER_INACTIVE false
#define TRIGGER_ACTIVE true
#define RELEASE_TIME 4

using namespace std;

MainWindow *main_window;
AudioTriggerClient *audio_client;

double level;
int release_timer = 0;
double threshold = DEFAULT_THRESHOLD;
bool state = TRIGGER_INACTIVE;

// Forward Declarations
void on_running_state_update(bool);
void on_threshold_update(double);
void on_level_update(double);

int main(int argc, char *argv[])
{
    // Print out application header
    cout << APPLICATION_NAME << " v" << VERSION << endl << endl;

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
        "org.samuelhug.audio_trigger");

    main_window = new MainWindow;
    audio_client = new AudioTriggerClient;

    // Connect signal handlers
    main_window->signal_running_state_updated().connect(sigc::ptr_fun(&on_running_state_update));
    main_window->signal_threshold_updated().connect(sigc::ptr_fun(&on_threshold_update));
    audio_client->signal_level_updated().connect(sigc::ptr_fun(&on_level_update));

    return app->run(*main_window);
}

void on_running_state_update(bool state)
{
    if (state) {
        audio_client->start();
    } else {
        audio_client->stop();
    }
}

void on_threshold_update(double value)
{
    threshold = value;
}

void on_level_update(double value)
{
    level = value;

    main_window->set_level(value);

    //midi_note_event_t event;

    if (level >= threshold) {
        release_timer = RELEASE_TIME;
    } else {
        release_timer--;
    }

    if (state == TRIGGER_INACTIVE && level >= threshold) {
        state = TRIGGER_ACTIVE;
        main_window->set_led_state(true);

        midi_note_event_t m_event(true, 1, main_window->get_midi_note_inactive(), 0x50);
        audio_client->send_midi_note(m_event);

    }
    else if (state == TRIGGER_ACTIVE && level < threshold) {
        if (release_timer <= 0) {
            state = TRIGGER_INACTIVE;
            main_window->set_led_state(false);

            midi_note_event_t m_event(true, 1, main_window->get_midi_note_active(), 0x50);
            audio_client->send_midi_note(m_event);
        }

    }
}

