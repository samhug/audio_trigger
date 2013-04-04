#include "level_bar.h"

LevelBar::LevelBar()
    : value(0.00)
{
    override_background_color(Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
}

LevelBar::~LevelBar()
{
}

bool LevelBar::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height(); 


    /***********************************
     * Draw gradiant
     **********************************/
    Gdk::Color color1("red");
    Gdk::Color color2("yellow");
    Gdk::Color color3("green");

    Cairo::RefPtr<Cairo::LinearGradient> background_gradient_ptr = Cairo::LinearGradient::create(
            0, 0, 0, height);

    // Set grandient colors
    background_gradient_ptr->add_color_stop_rgb(0.0, 
            color1.get_red_p(), color1.get_green_p(), color1.get_blue_p());

    background_gradient_ptr->add_color_stop_rgb(0.5, 
            color2.get_red_p(), color2.get_green_p(), color2.get_blue_p());

    background_gradient_ptr->add_color_stop_rgb(1.0, 
            color3.get_red_p(), color3.get_green_p(), color3.get_blue_p());

    cr->save();
    cr->set_source(background_gradient_ptr);
    cr->rectangle(0, height, width, -height * value);
    cr->fill();
    cr->restore();


    /***********************************
     * Draw Threshold
     **********************************/
    double y = height * (1-threshold_value);
    cr->save();
    cr->set_source_rgba(0.0, 0.0, 1.0, 1.0);
    cr->move_to(0, y);
    cr->line_to(width, y);
    cr->stroke();
    cr->restore();

    return true;
}

void LevelBar::set_value(double value)
{
    this->value = value;
    
    // Force Redraw of the widget
    queue_draw();
}

void LevelBar::set_threshold_value(double value)
{
    this->threshold_value = value;
    
    // Force Redraw of the widget
    queue_draw();
}
