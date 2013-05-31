#include <string.h>
#include <cmath>

#include "audio_trigger_client.h"
#include "config.h"

AudioTriggerClient::AudioTriggerClient() : JackClient(APPLICATION_NAME)
{
    add_audio_in_port("input");
    add_midi_out_port("output");
}

int AudioTriggerClient::process_callback(jack_nframes_t nframes, vector<void*> input_buffers,
        vector<void*> output_buffers)
{

    // MIDI event output
    void *out_buffer = output_buffers[0];

    jack_midi_clear_buffer(out_buffer);

    if (!midi_send_queue.empty()) {
        unsigned char buffer[3];
        midi_note_event_t e = midi_send_queue.front(); 
        if (e.state)
            buffer[0] = MIDI_ON_EVENT;
        else
            buffer[0] = MIDI_OFF_EVENT;

        buffer[1] = e.note;
        buffer[2] = e.velocity;

        jack_midi_event_write(out_buffer, 0, buffer, 3);

        midi_send_queue.pop();
    }

    // Audio Level Monitoring
    float *in_buffer = static_cast<float*>(input_buffers[0]);

    double a = 0;
    for (unsigned int i=0; i<nframes; i++) {
        a += abs(in_buffer[i]);
    }

    level = a / nframes;

    m_signal_level_updated.emit(level);

    return 0;
}

void AudioTriggerClient::send_midi_note(midi_note_event_t event)
{
    midi_send_queue.push(event);
}
