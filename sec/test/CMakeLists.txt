# Copyright (c) 2008,2009, David Beck, Tamas Foldi
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# SET(CMAKE_VERBOSE_MAKEFILE ON)

IF(WIN32)

  IF(MSYS)
  
    LINK_LIBRARIES(
                    csl_sec
                    csl_common
                    eay32
                    z
                    wsock32
                  )

    INCLUDE_DIRECTORIES(
                         ../src
                         ../../common/src 
                         c:/OpenSSL/include
                         $ENV{OPENSSL_DEV_ENV}/include
                         ../../../3rdparty/OpenSSL/include
                       )

    LINK_DIRECTORIES( ../src
                      ../../common/src
                      c:/OpenSSL/lib/MinGW
                      $ENV{OPENSSL_DEV_ENV}/lib/MinGW
                      ../../../3rdparty/OpenSSL/lib/MinGW
                      )
                      
    ADD_DEFINITIONS(
                     -Wall
                     -Wwrite-strings
                     -Wcast-qual
                     -Wpointer-arith
                     -Wold-style-cast
                     -Wconversion
                     -Wcomment
                     -Wcast-align
                     -Wshadow
                     -Wredundant-decls
                     -g3
                   )

  ELSE(MSYS)

    LINK_LIBRARIES(
                    csl_sec
                    csl_common
                    ssleay32MT
                    libeay32MT
                    zlib
                    wsock32
                  )

    INCLUDE_DIRECTORIES(
                         ../src
                         ../../common/src 
                         c:/OpenSSL/include
                         $ENV{OPENSSL_DEV_ENV}/include
                         ../../../3rdparty/OpenSSL/include
                         $ENV{ZLIB_DEV_ENV}/include
                         ../../../3rdparty/zlib/GnuWin32/include
                       )

    LINK_DIRECTORIES( ../src
                      ../../common/src
                      c:/OpenSSL/lib/VC/static
                      $ENV{OPENSSL_DEV_ENV}/lib/VC/static
                      ../../../3rdparty/OpenSSL/lib/VC/static
                      $ENV{ZLIB_DEV_ENV}/lib
                      ../../../3rdparty/zlib/GnuWin32/lib
                      )
  ENDIF(MSYS)

ELSE(WIN32)

  find_library(DLOPEN_FOUND NAMES dl PATH /usr/lib /lib /usr/local/lib)
  set(LIBDL)

  if (DLOPEN_FOUND)
    set(LIBDL dl)
    set(HAVE_LIBDL TRUE)
  endif (DLOPEN_FOUND)

  ADD_DEFINITIONS(
                   -Wall
                   -Wwrite-strings
                   -Wcast-qual
                   -Wpointer-arith
                   -Wold-style-cast
                   -Wconversion
                   -Wcomment
                   -Wcast-align
                   -Wshadow
                   -Wredundant-decls
                   -g3
                 )

  INCLUDE_DIRECTORIES(
      ../src
      ../../common/src
      /usr/local/ssl/include )

  LINK_LIBRARIES(
      csl_sec
      csl_common
      ssl
      crypto
      z
      stdc++
      ${LIBDL} )

  LINK_DIRECTORIES(
      ../src
      ../../common/src
       /usr/local/ssl/lib )

ENDIF(WIN32)

ADD_EXECUTABLE(t__umac               t__umac.cc)
ADD_EXECUTABLE(t__crypt_buf          t__crypt_buf.cc)
ADD_EXECUTABLE(t__crypt_pkt          t__crypt_pkt.cc)
ADD_EXECUTABLE(t__derive_ec_params   t__derive_ec_params.c)
ADD_EXECUTABLE(t__sha1               t__sha1.c)
ADD_EXECUTABLE(t__bignum             t__bignum.cc)
ADD_EXECUTABLE(t__ecdh_key           t__ecdh_key.cc)

# -- EOF --
