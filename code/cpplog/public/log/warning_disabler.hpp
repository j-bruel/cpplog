#pragma once

#if defined(_MSC_VER)
  #define DISABLE_WARNING_PUSH __pragma(warning(push))
  #define DISABLE_WARNING_POP __pragma(warning(pop))
  #define DISABLE_WARNING(warningNumber) __pragma(warning(disable : warningNumber))

  #define DISABLE_WARNING_EXPORTED_DATA_MISMATCH DISABLE_WARNING(4251)
#elif defined(__GNUC__) || defined(__clang__)
  #define DO_PRAGMA(X) _Pragma(#X)
  #define DISABLE_WARNING_PUSH DO_PRAGMA(GCC diagnostic push)
  #define DISABLE_WARNING_POP DO_PRAGMA(GCC diagnostic pop)
  #define DISABLE_WARNING(warningName) DO_PRAGMA(GCC diagnostic ignored #warningName)

  #define DISABLE_WARNING_EXPORTED_DATA_MISMATCH
#else
  #define DISABLE_WARNING_PUSH
  #define DISABLE_WARNING_POP

  #define DISABLE_WARNING_EXPORTED_DATA_MISMATCH
#endif
