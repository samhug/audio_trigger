#include <iostream>
#include <gtkmm.h>
#include <glibmm.h>

#include "ui/main_window.h"
#include "config.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Print out application header
    cout << APPLICATION_NAME << " v" << VERSION << endl << endl;

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
        "org.samuelhug.audio_trigger");

    MainWindow window;


    return app->run(window);
}
