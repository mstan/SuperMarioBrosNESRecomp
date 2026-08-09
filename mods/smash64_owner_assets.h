#pragma once

#include <stddef.h>

/* Prepare the immutable owner-derived Falcon cache and return its UTF-8 root. */
int smash64_owner_assets_prepare(const char *owner_rom_path,
                                 char *cache_root, size_t cache_root_size);
