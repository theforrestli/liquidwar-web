/*
  Liquid War 6 is a unique multiplayer wargame.
  Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015  Christian Mauduit <ufoot@ufoot.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.


  Liquid War 6 homepage : http://www.gnu.org/software/liquidwar6/
  Contact author        : ufoot@ufoot.org
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "map.h"

#define _CORNER_SIZE 3

/*
 * This is the "world-sat" map downscaled and transformed to ASCII.
 * We need this to have a real world, ever-the-same, example of
 * a map, without needing to load a bazillion libs to handle jpegs
 * and pngs. This might sound exagerated but it's just convenient
 * to have an instant-loaded yet nice to play and interesting to
 * test map. Additionnally it can be used, for instance, for demos,
 * splash screen, and the rest.
 */
#define _LAYER_DEFAULT_SOURCE_FG '.'
#define _LAYER_DEFAULT_SOURCE_BG '@'
static char *_LAYER_DEFAULT_SOURCE[LW6MAP_BUILTIN_DEFAULT_HEIGHT + 1] = {
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@.............@@@@@@@@@....................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@...@..@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@................@@@@@..................................@@@@@@@@@@@@@@@@@@@@@..........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@@@@..@@..@@.@.........@@@......................................@@@@@@@@@@@@@@@@@@@@@@@...@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@.@@.@.......@@@@@@....................................@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......@@@@@....@.........@@@@@@@@@@@@@@@............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@@@@@@@@@@@@@@@@@...................@@@@@@@@@@@@@@@@@.....@...@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@.@...@@@@@@@@@@@@@@@@@@@@@@@@@..........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@@@.....................@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............@@@.....@@@...........@@@@@@@@@@@@@........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@@@...@...@...................................@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@",
  ".@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........@@@@@...@@..............@@@@@@@@@@@@.......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@............................................@@..............@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@................@@@@......@...@@@...........@@.....@@@@.............@@@@@@@@@......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........@@@@@@@@@@@@@@@@@@@@..@@@..................................................................@@.@@.@.....@@",
  "..@@@@@@@@........................................................@..............@@@@@@@@@..................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................@@@@..@@@............@...............................................................................",
  "......@@@@@@.........................................................@@@............@@@@@@..............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@@.................................................................................................",
  "@@@...@@@.........................................................@..@@@........@@.@@@@@@@..........@@@@@@@@@@@@......@@@@@@@@@@@@@@@@@@@.......@@.......@@@....................................................................................................",
  "@@@@@@@@@@......................................................@@@..@@@@@@@......@@@@@@@@@........@@@@@@@@@@@@@@...@@@@@@@@@@@@@@@@@@@........@@..............................................................................................................@",
  "@@@@@@@@@@.....................................................@@@@@@.@@@@@@@@...@@@@@@@@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........@@................................................................................................................@",
  "@@@@@@@@@....................................................@@@@@@@@@@@@....@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........@@@................................................................................................@@@.........@@@@@",
  "@@@@@@@@@.@........@..@@@@@..................................@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........@@@@@@@@.........................................................................................@@@@@.@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@....@@@@@@@@@@@................................@@@@@@@@@@@.......@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@....@@@@@...................................................................................@@@@@@@@@@@@@...@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@.................................@@@@@@@@@..........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@..@...@@@....................................................................................@@@@@@@@@@@@.....@@@@@@@@@@@@",
  "@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@@..................................@@@@@@............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@.@..@@@@@..................................................................................@@@@@@@@@@@@@@....@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................................@@...............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@..@@@@@@....@.......................................................................................@@@@@@@@@@@@@...@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..................................@@................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@....@@...................................................................................................@@@@@@@@@..@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@..................................................................................................@.@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............................................@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................................................................................................@.@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........................................@@@@....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......................................................................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........................................@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....................................................................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.............................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................@@...@.......................................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........................................@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........@@..........@@@@@@......................................................................@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........@@@@@@..@@........@@@@@@@@@..................................................................@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........@@@@@@@...@@......@@@...@@@@..............................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@@.@@@@.@@...@@........................................................................@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......@@@@@@@@@@@.@@@..@@...................................................................@@@..@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@..@@@@..@@...................................................................@@@...@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........@@@@@@@@@@@@@@@@@@............................................................@@@@..@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.............@@@@@@@@@@@@@@@@@@...........................................................@@@@@.@@@....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............@@@@@@@@@@@@@@@@@..............................................................@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..................@@@....@@@@@@@..............................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............................................................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........................................@...................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@..........@@@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................................@..........@@.................................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@.........@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..................................@@..........@@@@@............................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@........@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................................@...........@@.@@@@@@@......................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................................@@@..............@@@@@@...................................@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@@@@@..@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................................@@..............@@@@@@@................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@..@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................................@@..............@@@@@@@@@...........@@@@..........@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@...@@@@@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......................................@@............@@@@@@@@@@@........@@@@@@@........@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......................................@@.........@@@@@@@@@@@@@.......@@@@@@@@.........@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........................................@@.......@@@@@@@@@@@@@@@......@@@@@@@@@.@........@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........................................@......@@@@@@@@@@@@@@@@@....@@@@@@@@@@@@........@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........................................@...@@@@@@@@@@@@@@@@@@@....@@@@@@@@@@@@@........@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........................................@@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@@@@@@@.@@.....@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........................................@@...@@@@@@@@@@@@@@@@@@...@@@@@@@@@@@@@.@@....@@@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@...........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............................................@@@@@@@@@@@@@@@@@@...@@@@@@@@@@@@@.@@@..@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@..............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.............................................@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@.@@@@@@@@@@@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........................................@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@.@@@@@@@@@@@.@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@.@@@@@..............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@..@@@@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@.@@@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@.....@@..@@@@@@@.@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@..@@..@@@@@@@........@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@@@.@.@@@@@@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@@.@@.......@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@.......@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@..@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@.@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........@@@...@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................@@@....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........@@...@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@@@@....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................@@@@@....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..................@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@................@@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....................@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........................@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........................@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........................@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.............................@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............................@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............................@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........................@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........................@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......@@@@@@.............@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@@@@@...........@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........@@@@@@@@@@@@@@@@.@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........@@@@@@@@@@@@@@@@@.@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@@@@@@@@@@@@@@@@@@...@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@@..@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@.@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@..@@@@@.......@@@@..@@@@@@@.........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................@@@@@@@@...............................................@@@@@@@@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@.....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@........................@@@........................................................@@@@@@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........................................................................................................................@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@@@@@@@@@@..........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..................................................................................................................................@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@.............@@...............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................................................................................................................................@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...................@..@@..............................@@@@@@@@@@@@@@@@@@@@@@@@@.......................................................................................................................................@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@@@@@@@@...................................................................@@@@@@@@@@@@@@@@@@@@.......................................................................................................................................@@@@@@@@@@@@",
  "@@@@@@@@@@@@@@@...............................................................................@@@@@.@@@@.............................................................................................................................................@.......@@@",
  "................................................................................................................................................................................................................................................................",
  "................................................................................................................................................................................................................................................................",
  "................................................................................................................................................................................................................................................................",
  "................................................................................................................................................................................................................................................................",
  "................................................................................................................................................................................................................................................................",
  "................................................................................................................................................................................................................................................................",
  "................................................................................................................................................................................................................................................................",
  "................................................................................................................................................................................................................................................................",
  NULL
};

static int
_default_source (lw6sys_context_t * sys_context, lw6map_layer_t * layer, int width, int height)
{
  int ret = 0;
  int x, y;
  int source_x, source_y;
  char c;

  layer->shape.w = width;
  layer->shape.h = height;
  layer->shape.d = 1;		// allways 1
  layer->data = (unsigned char *) LW6SYS_CALLOC (sys_context, layer->shape.w * layer->shape.h * sizeof (unsigned char));

  if (layer->data)
    {
      ret = 1;
      for (y = 0; y < height; ++y)
	{
	  for (x = 0; x < width; ++x)
	    {
	      source_x = lw6sys_imax (0, lw6sys_imin ((x * LW6MAP_BUILTIN_DEFAULT_WIDTH) / width, LW6MAP_BUILTIN_DEFAULT_WIDTH - 1));
	      source_y = lw6sys_imax (0, lw6sys_imin ((y * LW6MAP_BUILTIN_DEFAULT_HEIGHT) / height, LW6MAP_BUILTIN_DEFAULT_HEIGHT - 1));
	      c = _LAYER_DEFAULT_SOURCE[source_y][source_x];
	      switch (c)
		{
		case _LAYER_DEFAULT_SOURCE_BG:
		  lw6map_layer_set (layer, x, y, 1);
		  break;
		case _LAYER_DEFAULT_SOURCE_FG:
		  lw6map_layer_set (layer, x, y, 0);
		  break;
		default:
		  lw6sys_log (sys_context, LW6SYS_LOG_WARNING,
			      _x_ ("inconsistent default source layer data '%c' at %d,%d for %d,%d"), c, source_x, source_y, x, y);
		  ret = 0;
		}
	    }
	}
    }

  if (!ret)
    {
      if (layer->data)
	{
	  LW6SYS_FREE (sys_context, layer->data);
	  layer->data = NULL;
	}
    }

  return ret;
}

/**
 * lw6map_layer_builtin_custom
 *
 * @sys_context: global system context
 * @layer: the layer to init
 * @w: width
 * @h: height
 *
 * Creates a default layer. This is mostly for testing purposes, the default
 * layer is not empty, it contains a simplified map of the world.
 *
 * Return value: none
 */
void
lw6map_layer_builtin_custom (lw6sys_context_t * sys_context, lw6map_layer_t * layer, int w, int h)
{
  lw6map_layer_clear (sys_context, layer);

  if (!_default_source (sys_context, layer, w, h))
    {
      lw6sys_log (sys_context, LW6SYS_LOG_WARNING, _x_ ("unable to construct default map layer"));
      layer->shape.w = 0;
      layer->shape.h = 0;
      layer->shape.d = 0;
    }
}

/**
 * lw6map_layer_clear
 *
 * @sys_context: global system context
 * @layer: the layer to init
 *
 * Clears a layer struct. This means freeing the pointer
 * if it's non NULL and setting everything to 0.
 *
 * Return value: none
 */
void
lw6map_layer_clear (lw6sys_context_t * sys_context, lw6map_layer_t * layer)
{
  if (layer->data)
    {
      LW6SYS_FREE (sys_context, layer->data);
    }

  memset (layer, 0, sizeof (lw6map_layer_t));
}
