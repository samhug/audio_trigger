#ifndef LEVEL_BAR_H
#define LEVEL_BAR_H

#include <gtkmm.h>

class LevelBar : public Gtk::DrawingArea
{
public:
    LevelBar();
    virtual ~LevelBar();

    void set_value(double value);
    void set_threshold_value(double value);

protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

    double value;
    double threshold_value;
};

#endif // LEVEL_BAR_H
