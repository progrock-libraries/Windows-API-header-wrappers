#pragma once

#ifdef MessageBox
#   error "<windows.h> has already been included, possibly with undesired options."
#endif

#include <assert.h>
#ifdef _MSC_VER
#   include <iso646.h>                  // Standard `and` etc. also with MSVC.
#endif

#ifndef _WIN32_WINNT
#   define _WIN32_WINNT     0x0600      // Windows Vista as earliest supported OS.
#endif
#undef WINVER
#define WINVER _WIN32_WINNT

// UTF8_WINAPI is a custom macro for this file. UNICODE, _UNICODE and _MBCS are MS macros.
#if defined( UTF8_WINAPI ) and defined( UNICODE )
#   error "Inconsistent, both UNICODE (UTF-16) and UTF8_WINAPI (UTF-8) are defined."
#endif

#if defined( _MBCS ) and defined( UNICODE )
#   error "Inconsistent, both UNICODE (UTF-16) and _MBCS (Windows multibyte) are defined."
#endif

#if not( defined( UTF8_WINAPI ) or defined( UNICODE ) )
#   error "Define either UTF8_WINAPI or UNICODE, for respectively UTF-8 and UTF-16."
#endif

#undef UNICODE
#undef _UNICODE
#ifdef UTF8_WINAPI
#   undef _MBCS
#   define _MBCS        // Mainly for 3rd party code that uses it for platform detection.
#else
#   define UNICODE
#   define _UNICODE     // Mainly for 3rd party code that uses it for platform detection.
#endif
#undef NOMINMAX
#define NOMINMAX
#undef STRICT
#define STRICT
#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
// After this an `#include <winsock2.h>` will actually include that header.


/////////////////////////////////////////////////////////////////////
#include <windows.h>                                                //
/////////////////////////////////////////////////////////////////////


#define IS_NARROW_WINAPI() \
    ("Define UTF8_WINAPI please.", sizeof(*GetCommandLine()) == 1)

#define IS_WIDE_WINAPI() \
    ("Define UNICODE please.", sizeof(*GetCommandLine()) > 1)

inline auto winapi_h_assert_utf8_codepage()
    -> bool
{
    #ifdef __GNUC__
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wunused-value"
    #endif
    assert(( "The process codepage isn't UTF-8 (old Windows?).", GetACP() == 65001 ));
    #ifdef __GNUC__
        #pragma GCC diagnostic pop
    #endif
    return true;
}
