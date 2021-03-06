/*         ______   ___    ___
 *        /\  _  \ /\_ \  /\_ \
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      A builtin bitmap font using no external data.
 *
 *      By Dennis Busch.
 *
 *      See LICENSE.txt for copyright information.
 */

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"


ALLEGRO_DEBUG_CHANNEL("font")


/* Adapted from Allegro4 "font.c" (removed unnecessary height and width
 * information and packed them all into a single continuous array).
 * Contains the following ranges
 *
 *        ASCII          (0x0020 to 0x007F)
 *        Latin-1        (0x00A1 to 0x00FF)
 *        Extended-A     (0x0100 to 0x017F)
 *        Euro           (0x20AC)
 */
static const unsigned char builtin_rom_font_8x8[] = {
   /* standard ASCII characters (0x20 to 0x7F) */
   /* 0x20 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   /* 0x21 */ 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00,
   /* 0x22 */ 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00,
   /* 0x23 */ 0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00,
   /* 0x24 */ 0x18, 0x7E, 0xC0, 0x7C, 0x06, 0xFC, 0x18, 0x00,
   /* 0x25 */ 0x00, 0xC6, 0xCC, 0x18, 0x30, 0x66, 0xC6, 0x00,
   /* 0x26 */ 0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00,
   /* 0x27 */ 0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
   /* 0x28 */ 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00,
   /* 0x29 */ 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00,
   /* 0x2A */ 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00,
   /* 0x2B */ 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00,
   /* 0x2C */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30,
   /* 0x2D */ 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
   /* 0x2E */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
   /* 0x2F */ 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00,
   /* 0x30 */ 0x7C, 0xCE, 0xDE, 0xF6, 0xE6, 0xC6, 0x7C, 0x00,
   /* 0x31 */ 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00,
   /* 0x32 */ 0x78, 0xCC, 0x0C, 0x38, 0x60, 0xCC, 0xFC, 0x00,
   /* 0x33 */ 0x78, 0xCC, 0x0C, 0x38, 0x0C, 0xCC, 0x78, 0x00,
   /* 0x34 */ 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x1E, 0x00,
   /* 0x35 */ 0xFC, 0xC0, 0xF8, 0x0C, 0x0C, 0xCC, 0x78, 0x00,
   /* 0x36 */ 0x38, 0x60, 0xC0, 0xF8, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x37 */ 0xFC, 0xCC, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00,
   /* 0x38 */ 0x78, 0xCC, 0xCC, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x39 */ 0x78, 0xCC, 0xCC, 0x7C, 0x0C, 0x18, 0x70, 0x00,
   /* 0x3A */ 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00,
   /* 0x3B */ 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30,
   /* 0x3C */ 0x18, 0x30, 0x60, 0xC0, 0x60, 0x30, 0x18, 0x00,
   /* 0x3D */ 0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00,
   /* 0x3E */ 0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00,
   /* 0x3F */ 0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00,
   /* 0x40 */ 0x7C, 0xC6, 0xDE, 0xDE, 0xDC, 0xC0, 0x7C, 0x00,
   /* 0x41 */ 0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00,
   /* 0x42 */ 0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00,
   /* 0x43 */ 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00,
   /* 0x44 */ 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00,
   /* 0x45 */ 0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00,
   /* 0x46 */ 0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00,
   /* 0x47 */ 0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3A, 0x00,
   /* 0x48 */ 0xCC, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00,
   /* 0x49 */ 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x4A */ 0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x4B */ 0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00,
   /* 0x4C */ 0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00,
   /* 0x4D */ 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00,
   /* 0x4E */ 0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00,
   /* 0x4F */ 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00,
   /* 0x50 */ 0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00,
   /* 0x51 */ 0x7C, 0xC6, 0xC6, 0xC6, 0xD6, 0x7C, 0x0E, 0x00,
   /* 0x52 */ 0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00,
   /* 0x53 */ 0x7C, 0xC6, 0xE0, 0x78, 0x0E, 0xC6, 0x7C, 0x00,
   /* 0x54 */ 0xFC, 0xB4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x55 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0x00,
   /* 0x56 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00,
   /* 0x57 */ 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00,
   /* 0x58 */ 0xC6, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0xC6, 0x00,
   /* 0x59 */ 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x78, 0x00,
   /* 0x5A */ 0xFE, 0xC6, 0x8C, 0x18, 0x32, 0x66, 0xFE, 0x00,
   /* 0x5B */ 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00,
   /* 0x5C */ 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00,
   /* 0x5D */ 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00,
   /* 0x5E */ 0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00,
   /* 0x5F */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
   /* 0x60 */ 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
   /* 0x61 */ 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
   /* 0x62 */ 0xE0, 0x60, 0x60, 0x7C, 0x66, 0x66, 0xDC, 0x00,
   /* 0x63 */ 0x00, 0x00, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00,
   /* 0x64 */ 0x1C, 0x0C, 0x0C, 0x7C, 0xCC, 0xCC, 0x76, 0x00,
   /* 0x65 */ 0x00, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
   /* 0x66 */ 0x38, 0x6C, 0x64, 0xF0, 0x60, 0x60, 0xF0, 0x00,
   /* 0x67 */ 0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
   /* 0x68 */ 0xE0, 0x60, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00,
   /* 0x69 */ 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x6A */ 0x0C, 0x00, 0x1C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78,
   /* 0x6B */ 0xE0, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x00,
   /* 0x6C */ 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x6D */ 0x00, 0x00, 0xCC, 0xFE, 0xFE, 0xD6, 0xD6, 0x00,
   /* 0x6E */ 0x00, 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0x00,
   /* 0x6F */ 0x00, 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x70 */ 0x00, 0x00, 0xDC, 0x66, 0x66, 0x7C, 0x60, 0xF0,
   /* 0x71 */ 0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0x1E,
   /* 0x72 */ 0x00, 0x00, 0xDC, 0x76, 0x62, 0x60, 0xF0, 0x00,
   /* 0x73 */ 0x00, 0x00, 0x7C, 0xC0, 0x70, 0x1C, 0xF8, 0x00,
   /* 0x74 */ 0x10, 0x30, 0xFC, 0x30, 0x30, 0x34, 0x18, 0x00,
   /* 0x75 */ 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00,
   /* 0x76 */ 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00,
   /* 0x77 */ 0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00,
   /* 0x78 */ 0x00, 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00,
   /* 0x79 */ 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
   /* 0x7A */ 0x00, 0x00, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00,
   /* 0x7B */ 0x1C, 0x30, 0x30, 0xE0, 0x30, 0x30, 0x1C, 0x00,
   /* 0x7C */ 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00,
   /* 0x7D */ 0xE0, 0x30, 0x30, 0x1C, 0x30, 0x30, 0xE0, 0x00,
   /* 0x7E */ 0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   /* 0x7F */ 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0x00,
   /* ANSI Latin-1 characters (0xA1 to 0xFF) */
   /* 0xA1 */ 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00,
   /* 0xA2 */ 0x18, 0x18, 0x7E, 0xC0, 0xC0, 0x7E, 0x18, 0x18,
   /* 0xA3 */ 0x38, 0x6C, 0x64, 0xF0, 0x60, 0xE6, 0xFC, 0x00,
   /* 0xA4 */ 0x00, 0xC6, 0x7C, 0xC6, 0xC6, 0x7C, 0xC6, 0x00,
   /* 0xA5 */ 0xCC, 0xCC, 0x78, 0xFC, 0x30, 0xFC, 0x30, 0x30,
   /* 0xA6 */ 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00,
   /* 0xA7 */ 0x3E, 0x61, 0x3C, 0x66, 0x66, 0x3C, 0x86, 0x7C,
   /* 0xA8 */ 0x00, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   /* 0xA9 */ 0x7E, 0x81, 0x9D, 0xA1, 0xA1, 0x9D, 0x81, 0x7E,
   /* 0xAA */ 0x3C, 0x6C, 0x6C, 0x3E, 0x00, 0x7E, 0x00, 0x00,
   /* 0xAB */ 0x00, 0x33, 0x66, 0xCC, 0x66, 0x33, 0x00, 0x00,
   /* 0xAC */ 0x00, 0x00, 0x00, 0xFC, 0x0C, 0x0C, 0x00, 0x00,
   /* 0xAD */ 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
   /* 0xAE */ 0x7E, 0x81, 0xB9, 0xA5, 0xB9, 0xA5, 0x81, 0x7E,
   /* 0xAF */ 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   /* 0xB0 */ 0x38, 0x6C, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00,
   /* 0xB1 */ 0x30, 0x30, 0xFC, 0x30, 0x30, 0x00, 0xFC, 0x00,
   /* 0xB2 */ 0x70, 0x18, 0x30, 0x60, 0x78, 0x00, 0x00, 0x00,
   /* 0xB3 */ 0x78, 0x0C, 0x38, 0x0C, 0x78, 0x00, 0x00, 0x00,
   /* 0xB4 */ 0x0C, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
   /* 0xB5 */ 0x00, 0x00, 0x33, 0x33, 0x66, 0x7E, 0xC0, 0x80,
   /* 0xB6 */ 0x7F, 0xDB, 0xDB, 0x7B, 0x1B, 0x1B, 0x1B, 0x00,
   /* 0xB7 */ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
   /* 0xB8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0C, 0x38,
   /* 0xB9 */ 0x18, 0x38, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00,
   /* 0xBA */ 0x38, 0x6C, 0x6C, 0x38, 0x00, 0x7C, 0x00, 0x00,
   /* 0xBB */ 0x00, 0xCC, 0x66, 0x33, 0x66, 0xCC, 0x00, 0x00,
   /* 0xBC */ 0xC3, 0xC6, 0xCC, 0xDB, 0x37, 0x6F, 0xCF, 0x03,
   /* 0xBD */ 0xC3, 0xC6, 0xCC, 0xDE, 0x33, 0x66, 0xCC, 0x0F,
   /* 0xBE */ 0xE1, 0x32, 0xE4, 0x3A, 0xF6, 0x2A, 0x5F, 0x86,
   /* 0xBF */ 0x30, 0x00, 0x30, 0x60, 0xC0, 0xCC, 0x78, 0x00,
   /* 0xC0 */ 0x18, 0x0C, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x00,
   /* 0xC1 */ 0x30, 0x60, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x00,
   /* 0xC2 */ 0x7C, 0x82, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x00,
   /* 0xC3 */ 0x76, 0xDC, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x00,
   /* 0xC4 */ 0xC6, 0x00, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x00,
   /* 0xC5 */ 0x10, 0x28, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x00,
   /* 0xC6 */ 0x3E, 0x6C, 0xCC, 0xFE, 0xCC, 0xCC, 0xCE, 0x00,
   /* 0xC7 */ 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x18, 0x0C, 0x78,
   /* 0xC8 */ 0x30, 0x18, 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x00,
   /* 0xC9 */ 0x0C, 0x18, 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x00,
   /* 0xCA */ 0x7C, 0x82, 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x00,
   /* 0xCB */ 0xC6, 0x00, 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x00,
   /* 0xCC */ 0x30, 0x18, 0x3C, 0x18, 0x18, 0x18, 0x3C, 0x00,
   /* 0xCD */ 0x0C, 0x18, 0x3C, 0x18, 0x18, 0x18, 0x3C, 0x00,
   /* 0xCE */ 0x3C, 0x42, 0x3C, 0x18, 0x18, 0x18, 0x3C, 0x00,
   /* 0xCF */ 0x66, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x3C, 0x00,
   /* 0xD0 */ 0xF8, 0x6C, 0x66, 0xF6, 0x66, 0x6C, 0xF8, 0x00,
   /* 0xD1 */ 0xFC, 0x00, 0xCC, 0xEC, 0xFC, 0xDC, 0xCC, 0x00,
   /* 0xD2 */ 0x30, 0x18, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xD3 */ 0x18, 0x30, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xD4 */ 0x7C, 0x82, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xD5 */ 0x76, 0xDC, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xD6 */ 0xC6, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xD7 */ 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00, 0x00,
   /* 0xD8 */ 0x3A, 0x6C, 0xCE, 0xD6, 0xE6, 0x6C, 0xB8, 0x00,
   /* 0xD9 */ 0x60, 0x30, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xDA */ 0x18, 0x30, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xDB */ 0x7C, 0x82, 0x00, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xDC */ 0xC6, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0xDD */ 0x0C, 0x18, 0x66, 0x66, 0x3C, 0x18, 0x3C, 0x00,
   /* 0xDE */ 0xE0, 0x60, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0xF0,
   /* 0xDF */ 0x78, 0xCC, 0xCC, 0xD8, 0xCC, 0xC6, 0xCC, 0x00,
   /* 0xE0 */ 0xE0, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x7E, 0x00,
   /* 0xE1 */ 0x1C, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x7E, 0x00,
   /* 0xE2 */ 0x7E, 0xC3, 0x3C, 0x06, 0x3E, 0x66, 0x3F, 0x00,
   /* 0xE3 */ 0x76, 0xDC, 0x78, 0x0C, 0x7C, 0xCC, 0x7E, 0x00,
   /* 0xE4 */ 0xCC, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x7E, 0x00,
   /* 0xE5 */ 0x30, 0x30, 0x78, 0x0C, 0x7C, 0xCC, 0x7E, 0x00,
   /* 0xE6 */ 0x00, 0x00, 0x7F, 0x0C, 0x7F, 0xCC, 0x7F, 0x00,
   /* 0xE7 */ 0x00, 0x00, 0x78, 0xC0, 0xC0, 0x78, 0x0C, 0x38,
   /* 0xE8 */ 0xE0, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
   /* 0xE9 */ 0x1C, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
   /* 0xEA */ 0x7E, 0xC3, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00,
   /* 0xEB */ 0xCC, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
   /* 0xEC */ 0xE0, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0xED */ 0x38, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0xEE */ 0x7C, 0xC6, 0x38, 0x18, 0x18, 0x18, 0x3C, 0x00,
   /* 0xEF */ 0xCC, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0xF0 */ 0x08, 0x3C, 0x08, 0x7C, 0xCC, 0xCC, 0x78, 0x00,
   /* 0xF1 */ 0x00, 0xF8, 0x00, 0xF8, 0xCC, 0xCC, 0xCC, 0x00,
   /* 0xF2 */ 0x00, 0xE0, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0xF3 */ 0x00, 0x1C, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0xF4 */ 0x78, 0xCC, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0xF5 */ 0x76, 0xDC, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0xF6 */ 0x00, 0xCC, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0xF7 */ 0x30, 0x30, 0x00, 0xFC, 0x00, 0x30, 0x30, 0x00,
   /* 0xF8 */ 0x00, 0x02, 0x7C, 0xCE, 0xD6, 0xE6, 0x7C, 0x80,
   /* 0xF9 */ 0x00, 0xE0, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0xFA */ 0x00, 0x1C, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0xFB */ 0x78, 0xCC, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0xFC */ 0x00, 0xCC, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0xFD */ 0x18, 0x30, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
   /* 0xFE */ 0xF0, 0x60, 0x7C, 0x66, 0x7C, 0x60, 0xF0, 0x00,
   /* 0xFF */ 0x00, 0xCC, 0x00, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
   /* Extended-A characters (0x100 to 0x17F) */
   /* 0x100 */ 0xFE, 0x00, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x00,
   /* 0x101 */ 0xFC, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x7E, 0x00,
   /* 0x102 */ 0x82, 0x7C, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x00,
   /* 0x103 */ 0xC3, 0x7E, 0x78, 0x0C, 0x7C, 0xCC, 0x7E, 0x00,
   /* 0x104 */ 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x1C, 0x30, 0x1E,
   /* 0x105 */ 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x7E, 0x30, 0x1C,
   /* 0x106 */ 0x0C, 0x18, 0x7C, 0xC6, 0xC0, 0xC6, 0x7C, 0x00,
   /* 0x107 */ 0x1C, 0x00, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00,
   /* 0x108 */ 0x7C, 0x82, 0x7C, 0xC6, 0xC0, 0xC6, 0x7C, 0x00,
   /* 0x109 */ 0x7E, 0xC3, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00,
   /* 0x10A */ 0x10, 0x00, 0x7C, 0xC6, 0xC0, 0xC6, 0x7C, 0x00,
   /* 0x10B */ 0x10, 0x00, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00,
   /* 0x10C */ 0x6C, 0x38, 0x7C, 0xC6, 0xC0, 0xC6, 0x7C, 0x00,
   /* 0x10D */ 0x6C, 0x38, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00,
   /* 0x10E */ 0x6C, 0x38, 0xF8, 0x66, 0x66, 0x66, 0xF8, 0x00,
   /* 0x10F */ 0xBC, 0x4C, 0x0C, 0x7C, 0xCC, 0xCC, 0x76, 0x00,
   /* 0x110 */ 0xF8, 0x6C, 0x66, 0xF6, 0x66, 0x6C, 0xF8, 0x00,
   /* 0x111 */ 0x08, 0x3C, 0x08, 0x7C, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x112 */ 0xFE, 0x00, 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x00,
   /* 0x113 */ 0xFC, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
   /* 0x114 */ 0x6C, 0x38, 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x00,
   /* 0x115 */ 0x6C, 0x38, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
   /* 0x116 */ 0x10, 0x00, 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x00,
   /* 0x117 */ 0x10, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
   /* 0x118 */ 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x18, 0x30, 0x1C,
   /* 0x119 */ 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x38, 0x0C,
   /* 0x11A */ 0x6C, 0x38, 0xFE, 0xC0, 0xFC, 0xC0, 0xFE, 0x00,
   /* 0x11B */ 0x6C, 0x38, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
   /* 0x11C */ 0x7C, 0x82, 0x7C, 0xC6, 0xC0, 0xCE, 0x7E, 0x00,
   /* 0x11D */ 0x7E, 0xC3, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
   /* 0x11E */ 0x82, 0x7C, 0x7C, 0xC6, 0xC0, 0xCE, 0x7E, 0x00,
   /* 0x11F */ 0xC3, 0x7E, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
   /* 0x120 */ 0x10, 0x00, 0x7C, 0xC6, 0xC0, 0xCE, 0x7E, 0x00,
   /* 0x121 */ 0x10, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
   /* 0x122 */ 0x7C, 0xC6, 0xC0, 0xCE, 0x7E, 0x18, 0x0C, 0x78,
   /* 0x123 */ 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8, 0x0C, 0x38,
   /* 0x124 */ 0x78, 0x84, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00,
   /* 0x125 */ 0xEE, 0x7B, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00,
   /* 0x126 */ 0xCC, 0xFE, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00,
   /* 0x127 */ 0xE0, 0xFE, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00,
   /* 0x128 */ 0x76, 0xDC, 0x78, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x129 */ 0x76, 0xDC, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x12A */ 0x78, 0x00, 0x78, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x12B */ 0x78, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x12C */ 0x84, 0x78, 0x78, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x12D */ 0xC6, 0x7C, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x12E */ 0x78, 0x30, 0x30, 0x30, 0x78, 0x18, 0x30, 0x1E,
   /* 0x12F */ 0x30, 0x00, 0x70, 0x30, 0x30, 0x78, 0x30, 0x1C,
   /* 0x130 */ 0x10, 0x00, 0x78, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x131 */ 0x00, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x132 */ 0xEE, 0x42, 0x42, 0x42, 0x52, 0x52, 0xEC, 0x00,
   /* 0x133 */ 0x42, 0x00, 0xC6, 0x42, 0x42, 0x42, 0xE2, 0x0C,
   /* 0x134 */ 0x7C, 0x82, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x135 */ 0x7C, 0xC6, 0x1C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78,
   /* 0x136 */ 0xE6, 0x6C, 0x78, 0x6C, 0xE6, 0x30, 0x18, 0xF0,
   /* 0x137 */ 0xE0, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x30, 0xE0,
   /* 0x138 */ 0x00, 0x00, 0xE6, 0x6C, 0x78, 0x6C, 0xE6, 0x00,
   /* 0x139 */ 0xF3, 0x66, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00,
   /* 0x13A */ 0x73, 0x36, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x13B */ 0xF0, 0x60, 0x62, 0x66, 0xFE, 0x18, 0x0C, 0x78,
   /* 0x13C */ 0x70, 0x30, 0x30, 0x30, 0x30, 0x78, 0x0C, 0x38,
   /* 0x13D */ 0xF5, 0x66, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00,
   /* 0x13E */ 0x75, 0x36, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x13F */ 0xF0, 0x60, 0x64, 0x60, 0x62, 0x66, 0xFE, 0x00,
   /* 0x140 */ 0x70, 0x30, 0x30, 0x32, 0x30, 0x30, 0x78, 0x00,
   /* 0x141 */ 0xF0, 0x60, 0x70, 0x60, 0xE2, 0x66, 0xFE, 0x00,
   /* 0x142 */ 0x70, 0x30, 0x38, 0x30, 0x70, 0x30, 0x78, 0x00,
   /* 0x143 */ 0x0C, 0x18, 0xCC, 0xEC, 0xFC, 0xDC, 0xCC, 0x00,
   /* 0x144 */ 0x1C, 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0x00,
   /* 0x145 */ 0xCC, 0xEC, 0xFC, 0xDC, 0xCC, 0x30, 0x18, 0xF0,
   /* 0x146 */ 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0x30, 0xE0,
   /* 0x147 */ 0x6C, 0x38, 0xCC, 0xEC, 0xFC, 0xDC, 0xCC, 0x00,
   /* 0x148 */ 0x6C, 0x38, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0x00,
   /* 0x149 */ 0xC0, 0x80, 0x5C, 0x66, 0x66, 0x66, 0x66, 0x00,
   /* 0x14A */ 0x00, 0xCC, 0xEC, 0xFC, 0xDC, 0xCC, 0x0C, 0x38,
   /* 0x14B */ 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0x0C, 0x38,
   /* 0x14C */ 0xFE, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0x14D */ 0x00, 0xFC, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x14E */ 0x6C, 0x38, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0x14F */ 0x6C, 0x38, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x150 */ 0x36, 0x6C, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0x151 */ 0x36, 0x6C, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
   /* 0x152 */ 0x7E, 0xDA, 0x88, 0x8C, 0x88, 0xDA, 0x7E, 0x00,
   /* 0x153 */ 0x00, 0x00, 0x6C, 0x92, 0x9E, 0x90, 0x6C, 0x00,
   /* 0x154 */ 0x0C, 0x18, 0xFC, 0x66, 0x7C, 0x6C, 0xE6, 0x00,
   /* 0x155 */ 0x0C, 0x18, 0xDC, 0x76, 0x62, 0x60, 0xF0, 0x00,
   /* 0x156 */ 0xFC, 0x66, 0x7C, 0x6C, 0xE6, 0x30, 0x18, 0xF0,
   /* 0x157 */ 0x00, 0xDC, 0x76, 0x62, 0x60, 0xF0, 0x30, 0xE0,
   /* 0x158 */ 0x6C, 0x38, 0xFC, 0x66, 0x7C, 0x6C, 0xE6, 0x00,
   /* 0x159 */ 0x6C, 0x38, 0xDC, 0x76, 0x62, 0x60, 0xF0, 0x00,
   /* 0x15A */ 0x0C, 0x18, 0x7C, 0xE0, 0x78, 0x0E, 0x7C, 0x00,
   /* 0x15B */ 0x0C, 0x18, 0x7C, 0xC0, 0x70, 0x1C, 0xF8, 0x00,
   /* 0x15C */ 0x7C, 0x82, 0x7C, 0xE0, 0x78, 0x0E, 0x7C, 0x00,
   /* 0x15D */ 0x7C, 0xC6, 0x7C, 0xC0, 0x70, 0x1C, 0xF8, 0x00,
   /* 0x15E */ 0x7C, 0xE0, 0x78, 0x0E, 0x7C, 0x18, 0x0C, 0x78,
   /* 0x15F */ 0x00, 0x7C, 0xC0, 0x70, 0x1C, 0xF8, 0x0C, 0x38,
   /* 0x160 */ 0x6C, 0x38, 0x7C, 0xE0, 0x78, 0x0E, 0x7C, 0x00,
   /* 0x161 */ 0x6C, 0x38, 0x7C, 0xC0, 0x70, 0x1C, 0xF8, 0x00,
   /* 0x162 */ 0xFC, 0x30, 0x30, 0x30, 0x78, 0x18, 0x0C, 0x38,
   /* 0x163 */ 0x10, 0x30, 0xFC, 0x30, 0x34, 0x18, 0x0C, 0x38,
   /* 0x164 */ 0x6C, 0x38, 0xFC, 0x30, 0x30, 0x30, 0x78, 0x00,
   /* 0x165 */ 0x12, 0x3A, 0xFC, 0x30, 0x30, 0x34, 0x18, 0x00,
   /* 0x166 */ 0xFC, 0xB4, 0x30, 0x30, 0xFC, 0x30, 0x78, 0x00,
   /* 0x167 */ 0x10, 0x30, 0xFC, 0x30, 0xFC, 0x34, 0x18, 0x00,
   /* 0x168 */ 0x76, 0xDC, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0x169 */ 0x76, 0xDC, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0x16A */ 0xFE, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0x16B */ 0x00, 0xFE, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0x16C */ 0x6C, 0x38, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0x16D */ 0x6C, 0x38, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0x16E */ 0x38, 0x6C, 0xFE, 0xD6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0x16F */ 0x38, 0x6C, 0x38, 0xDC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0x170 */ 0x36, 0x6C, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00,
   /* 0x171 */ 0x36, 0x6C, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x00,
   /* 0x172 */ 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x30, 0x60, 0x3C,
   /* 0x173 */ 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x7E, 0x18, 0x0E,
   /* 0x174 */ 0x7C, 0x82, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00,
   /* 0x175 */ 0x7C, 0xC6, 0x00, 0xC6, 0xD6, 0xFE, 0x6C, 0x00,
   /* 0x176 */ 0x7C, 0x82, 0xCC, 0xCC, 0x78, 0x30, 0x78, 0x00,
   /* 0x177 */ 0x7C, 0xC6, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
   /* 0x178 */ 0xCC, 0x00, 0xCC, 0xCC, 0x78, 0x30, 0x78, 0x00,
   /* 0x179 */ 0x0C, 0x18, 0xFE, 0x8C, 0x18, 0x32, 0xFE, 0x00,
   /* 0x17A */ 0x0C, 0x18, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00,
   /* 0x17B */ 0x10, 0x00, 0xFE, 0x8C, 0x18, 0x32, 0xFE, 0x00,
   /* 0x17C */ 0x10, 0x00, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00,
   /* 0x17D */ 0x6C, 0x38, 0xFE, 0x8C, 0x18, 0x32, 0xFE, 0x00,
   /* 0x17E */ 0x6C, 0x38, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00,
   /* 0x17F */ 0x38, 0x6C, 0x64, 0xE0, 0x60, 0x60, 0xE0, 0x00,
   /* euro character (0x20AC) */
   /* 0x20AC*/ 0x3C, 0x62, 0xF8, 0x60, 0xF8, 0x62, 0x3C, 0x00
};



/* range definitions for the above binary data */
static const int builtin_rom_font_8x8_ranges[] = {
   0x00000020, 0x0000007F,
   0x000000A1, 0x000000FF,
   0x00000100, 0x0000017F,
   0x000020AC, 0x000020AC
};

static const int builtin_rom_font_8x8_ranges_count =
   (sizeof(builtin_rom_font_8x8_ranges) / sizeof(int)) / 2;



static void put_pixel_abgr8888_le(ALLEGRO_LOCKED_REGION *region,
   int x, int y, uint32_t pixel)
{
   uint32_t *target = (uint32_t *) ((uint8_t *)region->data
                                    + y * region->pitch
                                    + x * region->pixel_size);
   *target = pixel;
}



/* decodes the binary data and creates a bitmap containing the glyps from it */
static ALLEGRO_BITMAP *create_builtin_font_sheet(void)
{
   const int glyph_count = sizeof(builtin_rom_font_8x8) / 8;
   const int glyphs_per_row = 32;
   const int alloc_rows = (glyph_count + glyphs_per_row - 1) / glyphs_per_row;

   ALLEGRO_STATE state;
   ALLEGRO_BITMAP *bmp;
   ALLEGRO_LOCKED_REGION *lr;
   int i, j, k;

   al_store_state(&state,
      ALLEGRO_STATE_NEW_BITMAP_PARAMETERS |
      ALLEGRO_STATE_TARGET_BITMAP);

   /* putting pixels is much faster on a memory bitmap */
   al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
   al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_WITH_ALPHA);

   /* create bitmap onto which to render the glyphs */
   bmp = al_create_bitmap(glyphs_per_row * 8 + glyphs_per_row + 1,
                          alloc_rows * 8 + alloc_rows + 1);
   if (bmp) {
      al_set_target_bitmap(bmp);
      al_clear_to_color(al_map_rgba(255, 255, 0, 255));
      lr = al_lock_bitmap(bmp,
         ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_READWRITE);

      /* decode and render glyph pixels */
      for (i = 0; i < glyph_count; i++) {
         /* for each of the 8 lines per character */
         for (j = 0; j < 8; j++) {
            /* decode and draw each of the 8 pixels of the current line */
            for (k = 0; k < 8; k++) {
               bool set = (builtin_rom_font_8x8[i * 8 + j] >> (7 - k)) & 0x01;

               put_pixel_abgr8888_le(lr,
                  (i % glyphs_per_row) * 9 + 1 + k,
                  (i / glyphs_per_row) * 9 + 1 + j,
                  set ? 0xFFFFFFFF : 0x00000000);
            }
         }
      }

      al_unlock_bitmap(bmp);
   }
   else {
      ALLEGRO_ERROR("Unable to create bitmap.\n");
   }

   al_restore_state(&state);

   return bmp;
}



/* Function: al_create_builtin_font
 */
ALLEGRO_FONT *al_create_builtin_font(void)
{
   ALLEGRO_BITMAP *bmp;
   ALLEGRO_FONT *font;

   bmp = create_builtin_font_sheet();
   if (!bmp)
      return NULL;

   font = al_grab_font_from_bitmap(bmp, builtin_rom_font_8x8_ranges_count,
      builtin_rom_font_8x8_ranges);

   al_destroy_bitmap(bmp);

   return font;
}


/* vim: set sts=3 sw=3 et: */
