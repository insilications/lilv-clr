/*
  Copyright 2007-2020 David Robillard <http://drobilla.net>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THIS SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <stdbool.h>
#include <stdio.h>

/// Return true iff `path` is an absolute path
bool
lilv_path_is_absolute(const char* path);

/// Return true iff `path` is a child of `dir`
bool
lilv_path_is_child(const char* path, const char* dir);

/**
   Return `path` as an absolute path.

   If `path` is absolute, an identical copy of it is returned.  Otherwise, the
   returned path is relative to the current working directory.
*/
char*
lilv_path_absolute(const char* path);

/**
   Return `path` relative to `base` if possible.

   If `path` is not within `base`, a copy is returned.  Otherwise, an
   equivalent path relative to `base` is returned (which may contain
   up-references).
*/
char*
lilv_path_relative_to(const char* path, const char* base);

/**
   Return the path to the directory that contains `path`.

   Returns the root path if `path` is the root path.
*/
char*
lilv_dirname(const char* path);

/// Join path `a` and path `b` with a single directory separator between them
char*
lilv_path_join(const char* a, const char* b);

/// Return `path` normalized to have a trailing directory separator
char*
lilv_dir_path(const char* path);

/**
   Return `path` as a canonicalized absolute path.

   This expands all symbolic links, relative references, and removes extra
   directory separators.
*/
char*
lilv_realpath(const char* path);

/// Return true iff `path` points to an existing file system entry
bool
lilv_path_exists(const char* path);

/**
   Copy the file at path `src` to path `dst`.

   @return Zero on success, or a standard `errno` error code.
*/
int
lilv_copy_file(const char* src, const char* dst);

/**
   Create a symlink at `newpath` that points to `oldpath`.

   @return Zero on success, otherwise non-zero and `errno` is set.
*/
int
lilv_symlink(const char* oldpath, const char* newpath);

/**
   Set or remove an advisory exclusive lock on `file`.

   If the `lock` is true and the file is already locked, then this will not
   succeed and non-zero will be returned.

   @return Zero on success.
*/
int
lilv_flock(FILE* file, bool lock);

/**
   Visit every file in the directory at `path`.

   @param path A path to a directory.

   @param data Opaque user data that is passed to `f`.

   @param f A function called on every entry in the directory.  The `path`
   parameter is always the directory path passed to this function, the `name`
   parameter is the name of the directory entry (not its full path).
*/
void
lilv_dir_for_each(const char* path,
                  void*       data,
                  void (*f)(const char* path, const char* name, void* data));

/**
   Create the directory `dir_path` and any parent directories if necessary.

   @return Zero on success, or an `errno` error code.
*/
int
lilv_mkdir_p(const char* dir_path);

/// Return true iff the given paths point to files with identical contents
bool
lilv_file_equals(const char* a_path, const char* b_path);