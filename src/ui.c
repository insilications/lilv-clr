/*
  Copyright 2007-2011 David Robillard <http://drobilla.net>

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

#define _XOPEN_SOURCE 500

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "lilv_internal.h"

LilvUI*
lilv_ui_new(LilvWorld* world,
            LilvValue* uri,
            LilvValue* type_uri,
            LilvValue* binary_uri)
{
	assert(uri);
	assert(type_uri);
	assert(binary_uri);

	LilvUI* ui = malloc(sizeof(struct LilvUIImpl));
	ui->world      = world;
	ui->uri        = uri;
	ui->binary_uri = binary_uri;

	// FIXME: kludge
	char* bundle     = lilv_strdup(lilv_value_as_string(ui->binary_uri));
	char* last_slash = strrchr(bundle, '/') + 1;
	*last_slash = '\0';
	ui->bundle_uri = lilv_new_uri(world, bundle);
	free(bundle);

	ui->classes = lilv_values_new();
	lilv_array_append(ui->classes, type_uri);

	return ui;
}

void
lilv_ui_free(LilvUI* ui)
{
	lilv_value_free(ui->uri);
	ui->uri = NULL;

	lilv_value_free(ui->bundle_uri);
	ui->bundle_uri = NULL;

	lilv_value_free(ui->binary_uri);
	ui->binary_uri = NULL;

	lilv_values_free(ui->classes);

	free(ui);
}

LILV_API
const LilvValue*
lilv_ui_get_uri(const LilvUI* ui)
{
	assert(ui);
	assert(ui->uri);
	return ui->uri;
}

LILV_API
unsigned
lilv_ui_is_supported(const LilvUI*       ui,
                     LilvUISupportedFunc supported_func,
                     const LilvValue*    container_type,
                     const LilvValue**   ui_type)
{
#ifdef HAVE_SUIL
	const LilvValues* classes = lilv_ui_get_classes(ui);
	LILV_FOREACH(values, c, classes) {
		const LilvValue* type = lilv_values_get(classes, c);
		const unsigned   q    = supported_func(lilv_value_as_uri(container_type),
		                                       lilv_value_as_uri(type));
		if (q) {
			if (ui_type) {
				*ui_type = lilv_value_duplicate(type);
			}
			return q;
		}
	}
#endif
	return 0;
}

LILV_API
const LilvValues*
lilv_ui_get_classes(const LilvUI* ui)
{
	return ui->classes;
}

LILV_API
bool
lilv_ui_is_a(const LilvUI* ui, const LilvValue* ui_class_uri)
{
	return lilv_values_contains(ui->classes, ui_class_uri);
}

LILV_API
const LilvValue*
lilv_ui_get_bundle_uri(const LilvUI* ui)
{
	assert(ui);
	assert(ui->bundle_uri);
	return ui->bundle_uri;
}

LILV_API
const LilvValue*
lilv_ui_get_binary_uri(const LilvUI* ui)
{
	assert(ui);
	assert(ui->binary_uri);
	return ui->binary_uri;
}