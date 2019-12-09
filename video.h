/* -*- mode: C -*- */
#ifndef RUBYSDL2_VIDEO_H
#define RUBYSDL2_VIDEO_H

#include "rubysdl2_internal.h"

static VALUE cWindow, cRenderer;

void elog(char* str, SDL_Surface* surf);
void make_screenshots_dir(VALUE dir);
void make_filename(char* dir, char* fn, VALUE filename, VALUE format);
void rubysdl2_init_screenshot();

#endif
