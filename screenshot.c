/* -*- mode: C -*- */
#include <SDL_image.h>
#include <SDL_surface.h>
#include <time.h>
#include "video.h"

void elog(char* str, SDL_Surface* surf)
{
  if (SDL_GetError) {
    VALUE string = rb_str_new_cstr(str);
    rb_p( rb_str_plus( string, rb_str_new_cstr(SDL_GetError()) ) );
  }
  if (surf) SDL_FreeSurface(surf);
}

void make_screenshots_dir(VALUE dir)
{
  if (rb_funcall(rb_cDir, rb_intern("exist?"), 1, dir) == Qfalse)
    rb_funcall(rb_cDir, rb_intern("mkdir"), 1, dir);
}

void make_filename(char* dir, char* fn, VALUE filename, VALUE format)
{
  char* fname = StringValueCStr(filename);
  char* fmt = StringValueCStr(format);
  time_t rt = time(NULL);
  struct tm *tmp = localtime(&rt);
  sprintf(fn, "%s/%s_%d-%02d-%02d_%02d_%02d_%02d.%s", dir, fname, tmp->tm_year+1900,
          tmp->tm_mon+1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec, fmt);
}

/*
 * Document-class: SDL2::Screenshot
 *
 * This module represents the screenshot settings.
 * It handles file format and target directory.
 *
 * @!attribute [r] format
 *   Image file format : "jpg" or "png"
 *   @return [String]
 *
 * @!attribute [r] directory
 *   The name of the current Screenshots directory
 *   @return [String]
 *
 * @!attribute [r] filename
 *   The screenshot filename without the timestamp
 *   @return [String]
 *
 */

static VALUE SDL2_screenshot_format_get(VALUE self)
{
  return rb_iv_get(self, "format");
}

static VALUE SDL2_screenshot_format_set(VALUE self, VALUE fmt)
{
  return rb_iv_set(self, "format", fmt);
}

static VALUE SDL2_screenshot_directory_get(VALUE self)
{
  return rb_iv_get(self, "directory");
}

static VALUE SDL2_screenshot_directory_set(VALUE self, VALUE fmt)
{
  return rb_iv_set(self, "directory", fmt);
}

static VALUE SDL2_screenshot_filename_get(VALUE self)
{
  return rb_iv_get(self, "filename");
}

static VALUE SDL2_screenshot_filename_set(VALUE self, VALUE fmt)
{
  return rb_iv_set(self, "filename", fmt);
}

void rubysdl2_init_screenshot()
{
  VALUE shot = rb_define_module_under(mSDL2, "Screenshot");
  rb_iv_set(shot, "format", rb_str_new_cstr("jpg"));
  rb_iv_set(shot, "directory", rb_str_new_cstr("Screenshots"));
  rb_iv_set(shot, "filename", rb_str_new_cstr("shot"));
  rb_define_module_function(shot, "format", SDL2_screenshot_format_get, 0);
  rb_define_module_function(shot, "format=", SDL2_screenshot_format_set, 1);
  rb_define_module_function(shot, "directory", SDL2_screenshot_directory_get, 0);
  rb_define_module_function(shot, "directory=", SDL2_screenshot_directory_set, 1);
  rb_define_module_function(shot, "filename", SDL2_screenshot_filename_get, 0);
  rb_define_module_function(shot, "filename=", SDL2_screenshot_filename_set, 1);
}
