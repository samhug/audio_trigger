#ifndef AUDIO_TRIGGER_CLIENT_H
#define AUDIO_TRIGGER_CLIENT_H

#include <jack_client/jack_client.h>
#include <sigc++/sigc++.h>

#include <queue>
#include <stdexcept>

#define MIDI_ON_EVENT 0x90
#define MIDI_OFF_EVENT 0x80

struct midi_note_event_t {
    midi_note_event_t(bool state, unsigned char channel, unsigned char note, unsigned char velocity)
    {
        if (channel < 1 || channel > 31) {
            throw new std::range_error("MIDI channel must be between 1 and 31 inclusive.");
        }

        if (note > 127) {
            throw new std::range_error("MIDI note number must be less then 127.");
        }

        if (velocity > 127) {
            throw new std::range_error("MIDI note velocity must be less then 127.");
        }

        this->state = state;
        this->channel = channel;
        this->note = note;
        this->velocity = velocity;
    }

    bool state;
    unsigned char channel;
    unsigned char note;
    unsigned char velocity;
};

class AudioTriggerClient : public JackClient
{
public:
    AudioTriggerClient();

    double get_level()
    {
        return level;
    };
    
    void send_midi_note(midi_note_event_t event);

private:
    int process_callback(jack_nframes_t nframes, vector<void*> input_buffers, vector<void*> output_buffers);

    double level;
    std::queue<midi_note_event_t> midi_send_queue;
    

// Signals
public:
    typedef sigc::signal<void, double> type_signal_level_updated;
    type_signal_level_updated signal_level_updated()
    {
        return m_signal_level_updated;
    };

protected:
    type_signal_level_updated m_signal_level_updated;
};

#endif // AUDIO_TRIGGER_CLIENT_H
