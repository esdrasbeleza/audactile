/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * player
 * Copyright (C)  2010  Esdras Beleza <linux@esdrasbeleza.com>
 * 
 * player is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * player is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "main-window.h"
#include <iostream>

MainWindow::MainWindow() {
	set_title("Player");
	set_size_request(800,600); // TODO: set this to a better dimension, so it can fit well to netbook screens
	set_border_width(10);
	maximize();

	
	Gtk::Label* LabelTeste = Gtk::manage(new Gtk::Label("asdf!"));

	// Obtain window size to help calc widgets size
	int main_window_width, main_window_height;
	get_size(main_window_width, main_window_height);

	add(main_hpaned);
	main_notebook.set_size_request(floor(0.25*main_window_width),-1);
	main_hpaned.add1(main_notebook);
	main_hpaned.add2(*LabelTeste);

	show_all_children();
	

}

MainWindow::~MainWindow() {
}