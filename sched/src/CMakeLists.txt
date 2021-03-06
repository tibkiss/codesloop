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

LINK_DIRECTORIES(
                  ../../nthread/src
                  ../../common/src
                  ../../sec/src
                  ../../slt3/src
                )

INCLUDE_DIRECTORIES(
                     ../../nthread/src
                     ../../common/src
                     ../../sec/src
                     ../../slt3/src
                    )

IF(WIN32)

  IF(MSYS)

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

  ENDIF(MSYS)

ELSE(WIN32)

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

  ENDIF(WIN32)

ADD_LIBRARY( csl_sched STATIC
             schedule.cc      schedule.hh
             exc.cc           exc.hh
             item.cc          item.hh
             peer.cc          peer.hh
             route.cc         route.hh
             remote_peer.cc   remote_peer.hh
             head.cc          head.hh
             data.cc          data.hh
             cfg.cc           cfg.hh
             item_state.cc    item_state.hh
             synchr.cc        synchr.hh
           )

# -- EOF --

