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

#include <iostream>
#include "music.h"

using namespace Glib;
using namespace TagLib;

Music::Music(ustring music_file_path) {
	this->file_path = music_file_path;
	this->file      = FileRef(file_path.c_str());
	this->artist    = this->file.tag()->artist().toCString(true); // returns artist with Unicode = true!
	this->title     = this->file.tag()->title().toCString(true);
	this->album     = this->file.tag()->album().toCString(true);
	

}

Music::~Music() {
}


void Music::set_title(ustring new_title) {
	this->file.tag()->setTitle(new_title.c_str());	
	this->file.save();
}



void Music::set_artist(ustring new_artist) {
	this->file.tag()->setArtist(new_artist.c_str());	
	this->file.save();
}



void Music::set_album(ustring new_album) {
	this->file.tag()->setAlbum(new_album.c_str());	
	this->file.save();
}


ustring Music::get_title()  { return this->title;  }
ustring Music::get_artist() { return this->artist; }
ustring Music::get_album()  { return this->album;  } 




