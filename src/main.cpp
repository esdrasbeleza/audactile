/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) 2010 Esdras Beleza <linux@esdrasbeleza.com>
 *
 * Player is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Player is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include <gtkmm.h>
#include <iostream>
#include "main-window.h"
#include "base/music.h"

int main (int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);
    MainWindow window;
    Gtk::Main::run(window);



    Music* teste = new Music("/tmp/teste.mp3");
    std::cout << teste->get_artist().c_str() << "\n";
    
    return 0;
}
