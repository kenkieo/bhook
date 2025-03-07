// Copyright (c) 2020-2024 ByteDance, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

// Created by Kelun Cai (caikelun@bytedance.com) on 2020-06-02.

#pragma once

#include <pthread.h>
#include <stdbool.h>

// linker's __dl__ZL10dlopen_extPKciPK17android_dlextinfoPv for Android 7.0, 7.1
typedef void *(*bh_linker_dlopen_ext_t)(const char *, int, const void *, void *);
extern bh_linker_dlopen_ext_t bh_linker_dlopen_ext;

// linker's __dl__Z9do_dlopenPKciPK17android_dlextinfoPv for Android 7.0, 7.1
typedef void *(*bh_linker_do_dlopen_t)(const char *, int, const void *, void *);
extern bh_linker_do_dlopen_t bh_linker_do_dlopen;

// linker's __dl__Z23linker_get_error_bufferv for Android 7.0, 7.1
typedef char *(*bh_linker_get_error_buffer_t)(void);
extern bh_linker_get_error_buffer_t bh_linker_get_error_buffer;

// linker's __dl__ZL23__bionic_format_dlerrorPKcS0_ for Android 7.0, 7.1
typedef void (*bh_linker_bionic_format_dlerror_t)(const char *, const char *);
extern bh_linker_bionic_format_dlerror_t bh_linker_bionic_format_dlerror;

int bh_linker_init(void);

void bh_linker_lock(void);
void bh_linker_unlock(void);
bool bh_linker_is_in_lock(void);

bool bh_linker_is_use_basename(void);
bool bh_linker_elf_is_match(const char *linker_elf_name, const char *external_elf_name);

// used to check maybe-support for dl-init-fini-monitor at compile time
#if defined(__aarch64__) || defined(__arm__)
#define BH_LINKER_MAYBE_SUPPORT_DL_INIT_FINI_MONITOR 1
#else
#define BH_LINKER_MAYBE_SUPPORT_DL_INIT_FINI_MONITOR 0
#endif

// used to check maybe-NOT-support for dl-init-fini-monitor at compile time
#if defined(__aarch64__) || (defined(__arm__) && __ANDROID_API__ >= __ANDROID_API_L__)
#define BH_LINKER_MAYBE_NOT_SUPPORT_DL_INIT_FINI_MONITOR 0
#else
#define BH_LINKER_MAYBE_NOT_SUPPORT_DL_INIT_FINI_MONITOR 1
#endif

// used to check confirmed-support for dl-init-fini-monitor at runtime
bool bh_linker_is_support_dl_init_fini_monitor(void);
