#ifndef LED_H
#define LED_H

#include <gtkmm.h>

class Led : public Gtk::DrawingArea
{
public:
    Led();
    virtual ~Led();

    void set_state(bool state);
    bool get_state();

    bool toggle_state();

protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

    Gdk::Color color_on;
    Gdk::Color color_off;

    bool state;
};

#endif // LED_H
