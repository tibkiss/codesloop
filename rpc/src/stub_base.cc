/*
Copyright (c) 2008,2009, David Beck, Tamas Foldi

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials_ provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "stub_base.hh"
#include "common.h"
#include "ustr.hh"
#include "csrparser.hh"
#include "logger.hh"

#include <iostream>
#include <fstream>

using csl::common::ustr;
using std::endl;

/**
  @file csl_rpc/src/stub_base.cc
  @brief implementation of codesloop interface descriptor
 */

namespace csl
{
  namespace rpc
  {
    stub_base::stub_base(const iface * i) : csl::common::obj()
    {
      ENTER_FUNCTION();

      ifc_    = i;
      ifname_ = ifc_->get_name().c_str();
      ls_     = "";

      output_.open( (ifname_+".hh").c_str(), std::ios_base::out );

      output_ 
        << "/* THIS FILE IS AUTOMATICALLY GENERATED BY CSRGEN */" << endl          
        << "/*          DO NOT EDIT IT MANUALLY               */" << endl
        << endl;

      LEAVE_FUNCTION();
    }

    stub_base::~stub_base()
    {
      ENTER_FUNCTION();

      output_.close();

      LEAVE_FUNCTION();
    }


    void stub_base::generate_ns_open()
    {
      ENTER_FUNCTION();

      char * pch = strtok(const_cast<char*>(ifc_->get_namespc().c_str()) ,":");

      while (pch != NULL)
      {
        output_ 
          << ls_ << "namespace " << pch << endl
          << ls_ << "{" 
          << endl
        ;

        ls_ += "  ";

        pch = strtok (NULL, ":");
      }

      LEAVE_FUNCTION();
    }

    void stub_base::generate_ns_close()
    {
      ENTER_FUNCTION();

      for ( size_t i = ls_.size() ; i > 0 ; i -= 2 )
      {
        output_ 
          << ls_.substr(0,i-2) 
          << "}"
          << endl
        ;
      }

      ls_ = "";
      LEAVE_FUNCTION();
    }


    void stub_base::generate_func_params(std::string function, bool is_async)
    {   
      ENTER_FUNCTION();

      /*---------------------------------------------------------\
      |  Generate function specs                                 |
      \---------------------------------------------------------*/
      iface::function_iterator func_it = ifc_->get_functions()->begin();
      iface::func::param_iterator param_it;

      for ( ; func_it != ifc_->get_functions()->end(); func_it++ )
      {
        if ( (*func_it).name != function )
          continue;

        param_it = (*func_it).params.begin();

        // fix parameter for
        output_ << ls_ << "\t/* inout */\tcsl::rpc::conn &\t__rpc_conn," << endl;

        if ( is_async == true )
          output_ << ls_ << "\t/* inout */\tcsl::rpc::handle &\t__handle," << endl;

        // parameters
        while( param_it != (*func_it).params.end() ) 
        {
          if( (*param_it).kind==MD_EXCEPTION) 
          {
            output_
              << ls_ << "\t"
              << "/* throws "
              << (*param_it).type << " */" 
              ;

          } else { 
            output_ 
              << ls_ << "\t" 
              << "/* " 
              << param_kind_name[ (*param_it).kind ] << " */"
              << "\t"
              << ((*param_it).kind==MD_INPUT ? "const " : "")
              ;


            if (  (*param_it).is_array ) {
              output_ << "vec<" << (*param_it).type << ">";
            } else {
              output_ << (*param_it).type;
            }

            if ( (*param_it).kind==MD_INPUT )
              output_ << " &"; 
            else if ( (*param_it).kind==MD_OUTPUT )
              output_ << " *";
            else if ( (*param_it).kind==MD_INOUT )
              output_ << " &";

            output_
              << "\t" << (*param_it).name  
              ;
          }

          param_it++;
          
          // TODO: now it works only, if exceptions are defined last
          if ( (*param_it).kind!=MD_EXCEPTION && param_it != (*func_it).params.end() )
            output_ << ",";
          output_ << endl;
        }

        output_ << ls_ << ")";

        LEAVE_FUNCTION();
      }
    }
  };
};

/* EOF */
