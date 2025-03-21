// Copyright (c) the JPEG XL Project Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "tools/codec_config.h"

#include <hwy/targets.h>

#include "lib/jxl/base/status.h"

namespace jpegxl {
namespace tools {

std::string CodecConfigString(uint32_t lib_version) {
  std::string config;

  if (lib_version != 0) {
    char version_str[20];
    snprintf(version_str, sizeof(version_str), "v%d.%d.%d ",
             lib_version / 1000000, (lib_version / 1000) % 1000,
             lib_version % 1000);
    config += version_str;
  }

  std::string version = JPEGXL_VERSION;
  if (version != "(unknown)") {
    config += version + ' ';
  }

#if defined(ADDRESS_SANITIZER)
  config += " asan ";
#elif defined(MEMORY_SANITIZER)
  config += " msan ";
#elif defined(THREAD_SANITIZER)
  config += " tsan ";
#else
#endif

  bool saw_target = false;
  config += "| SIMD supported: ";
  for (const uint32_t target : hwy::SupportedAndGeneratedTargets()) {
    config += hwy::TargetName(target);
    config += ',';
    saw_target = true;
  }
  JXL_ASSERT(saw_target);
  (void)saw_target;
  config.resize(config.size() - 1);  // remove trailing comma

  return config;
}

}  // namespace tools
}  // namespace jpegxl
