#include "led.h"

#include <algorithm>
#include <cmath>

using namespace std;

Led::Led()
    : state(false)
    , color_on("green")
    , color_off("red")
{
}

Led::~Led()
{
}

bool Led::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height(); 

    double xc = width / 2.0;
    double yc = height / 2.0;
    double radius = min(xc, yc) * 0.9;

    cr->save();
    cr->arc(xc, xc, radius, 0, 2*M_PI);

    /***********************************
     * Draw Light
     **********************************/
    if (state)
        cr->set_source_rgb(color_on.get_red_p(), color_on.get_green_p(), color_on.get_blue_p());
    else
        cr->set_source_rgb(color_off.get_red_p(), color_off.get_green_p(), color_off.get_blue_p());


    cr->fill_preserve();


    /***********************************
     * Draw Border
     **********************************/
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->set_line_width(1);
    cr->stroke();

    cr->restore();

    return true;
}

void Led::set_state(bool state)
{
    this->state = state;
    
    // Force Redraw of the widget
    queue_draw();
}
bool Led::get_state()
{
    return this->state;
}

bool Led::toggle_state()
{
    this->state = !state;
    
    // Force Redraw of the widget
    queue_draw();

    return this->state;
}
