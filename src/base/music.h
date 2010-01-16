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

#ifndef _MUSIC_H_
#define _MUSIC_H_
#include <gtkmm.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>

using namespace Glib;
using namespace TagLib;

class Music 
{
public:
	Music(ustring music_file_path);
	virtual ~Music();
	void set_title(ustring title);
	void set_artist(ustring artist);
	void set_album(ustring album);
	ustring get_title();
	ustring get_artist();
	ustring get_album();
	 

protected:
	FileRef file;
	ustring file_path;
	ustring artist;
	ustring title;
	ustring album;
	

private:

};

#endif // _MUSIC_H_
