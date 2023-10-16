/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 5 "nd-flow-expr.ypp"

// Netify Agent
// Copyright (C) 2015-2023 eGloo Incorporated <http://www.egloo.ca>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <radix/radix_tree.hpp>

#include "nd-flow-parser.hpp"
#include "nd-flow-expr.hpp"

extern "C" {
    #include "nd-flow-criteria.h"

    void yyerror(YYLTYPE *yyllocp, yyscan_t scanner, const char *message);
}

void yyerror(YYLTYPE *yyllocp, yyscan_t scanner, const char *message) {
    throw string(message);
}

static bool is_addr_equal(const ndAddr *flow_addr, const string &compr_addr) {
  typedef radix_tree<ndRadixNetworkEntry<_ND_ADDR_BITSv4>, bool> nd_rn4_addr;
  typedef radix_tree<ndRadixNetworkEntry<_ND_ADDR_BITSv6>, bool> nd_rn6_addr;

  ndAddr addr(compr_addr);
  if (! addr.IsValid() || ! addr.IsIP()) return false;
  if (! (flow_addr->IsIPv4() == addr.IsIPv4())) return false;
  if (! (flow_addr->IsIPv6() == addr.IsIPv6())) return false;

  addr.SetComparisonFlags(ndAddr::cfADDR);

  if (! addr.IsNetwork())
    return (addr == *flow_addr);

  try {
    if (addr.IsIPv4()) {
      nd_rn4_addr rn;
      ndRadixNetworkEntry<_ND_ADDR_BITSv4> entry;
      if (! ndRadixNetworkEntry<_ND_ADDR_BITSv4>::Create(entry, addr))
        return false;

      rn[entry] = true;

      nd_rn4_addr::iterator it;
      if (ndRadixNetworkEntry<_ND_ADDR_BITSv4>::CreateQuery(entry, *flow_addr)) {
        if ((it = rn.longest_match(entry)) != rn.end())
          return true;
      }
    }
    else {
      nd_rn6_addr rn;
      ndRadixNetworkEntry<_ND_ADDR_BITSv6> entry;
      if (! ndRadixNetworkEntry<_ND_ADDR_BITSv6>::Create(entry, addr))
        return false;

      rn[entry] = true;

      nd_rn6_addr::iterator it;
      if (ndRadixNetworkEntry<_ND_ADDR_BITSv6>::CreateQuery(entry, *flow_addr)) {
        if ((it = rn.longest_match(entry)) != rn.end())
          return true;
      }
    }
  }
  catch (runtime_error &e) {
      nd_dprintf("Error adding network: %s: %s\n",
        compr_addr.c_str(), e.what());
  }

  return false;
}


#line 158 "nd-flow-expr.cpp"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_ND_FLOW_EXPR_HPP_INCLUDED
# define YY_YY_ND_FLOW_EXPR_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 95 "nd-flow-expr.ypp"

typedef void* yyscan_t;

#line 200 "nd-flow-expr.cpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FLOW_IP_PROTO = 258,           /* FLOW_IP_PROTO  */
    FLOW_IP_VERSION = 259,         /* FLOW_IP_VERSION  */
    FLOW_IP_NAT = 260,             /* FLOW_IP_NAT  */
    FLOW_VLAN_ID = 261,            /* FLOW_VLAN_ID  */
    FLOW_OTHER_TYPE = 262,         /* FLOW_OTHER_TYPE  */
    FLOW_LOCAL_MAC = 263,          /* FLOW_LOCAL_MAC  */
    FLOW_OTHER_MAC = 264,          /* FLOW_OTHER_MAC  */
    FLOW_LOCAL_IP = 265,           /* FLOW_LOCAL_IP  */
    FLOW_OTHER_IP = 266,           /* FLOW_OTHER_IP  */
    FLOW_LOCAL_PORT = 267,         /* FLOW_LOCAL_PORT  */
    FLOW_OTHER_PORT = 268,         /* FLOW_OTHER_PORT  */
    FLOW_TUNNEL_TYPE = 269,        /* FLOW_TUNNEL_TYPE  */
    FLOW_DETECTION_GUESSED = 270,  /* FLOW_DETECTION_GUESSED  */
    FLOW_DETECTION_UPDATED = 271,  /* FLOW_DETECTION_UPDATED  */
    FLOW_CATEGORY = 272,           /* FLOW_CATEGORY  */
    FLOW_RISKS = 273,              /* FLOW_RISKS  */
    FLOW_NDPI_RISK_SCORE = 274,    /* FLOW_NDPI_RISK_SCORE  */
    FLOW_NDPI_RISK_SCORE_CLIENT = 275, /* FLOW_NDPI_RISK_SCORE_CLIENT  */
    FLOW_NDPI_RISK_SCORE_SERVER = 276, /* FLOW_NDPI_RISK_SCORE_SERVER  */
    FLOW_DOMAIN_CATEGORY = 277,    /* FLOW_DOMAIN_CATEGORY  */
    FLOW_APPLICATION = 278,        /* FLOW_APPLICATION  */
    FLOW_APPLICATION_CATEGORY = 279, /* FLOW_APPLICATION_CATEGORY  */
    FLOW_PROTOCOL = 280,           /* FLOW_PROTOCOL  */
    FLOW_PROTOCOL_CATEGORY = 281,  /* FLOW_PROTOCOL_CATEGORY  */
    FLOW_DETECTED_HOSTNAME = 282,  /* FLOW_DETECTED_HOSTNAME  */
    FLOW_SSL_VERSION = 283,        /* FLOW_SSL_VERSION  */
    FLOW_SSL_CIPHER = 284,         /* FLOW_SSL_CIPHER  */
    FLOW_ORIGIN = 285,             /* FLOW_ORIGIN  */
    FLOW_CT_MARK = 286,            /* FLOW_CT_MARK  */
    FLOW_OTHER_UNKNOWN = 287,      /* FLOW_OTHER_UNKNOWN  */
    FLOW_OTHER_UNSUPPORTED = 288,  /* FLOW_OTHER_UNSUPPORTED  */
    FLOW_OTHER_LOCAL = 289,        /* FLOW_OTHER_LOCAL  */
    FLOW_OTHER_MULTICAST = 290,    /* FLOW_OTHER_MULTICAST  */
    FLOW_OTHER_BROADCAST = 291,    /* FLOW_OTHER_BROADCAST  */
    FLOW_OTHER_REMOTE = 292,       /* FLOW_OTHER_REMOTE  */
    FLOW_OTHER_ERROR = 293,        /* FLOW_OTHER_ERROR  */
    FLOW_ORIGIN_LOCAL = 294,       /* FLOW_ORIGIN_LOCAL  */
    FLOW_ORIGIN_OTHER = 295,       /* FLOW_ORIGIN_OTHER  */
    FLOW_ORIGIN_UNKNOWN = 296,     /* FLOW_ORIGIN_UNKNOWN  */
    FLOW_TUNNEL_NONE = 297,        /* FLOW_TUNNEL_NONE  */
    FLOW_TUNNEL_GTP = 298,         /* FLOW_TUNNEL_GTP  */
    CMP_EQUAL = 299,               /* CMP_EQUAL  */
    CMP_NOTEQUAL = 300,            /* CMP_NOTEQUAL  */
    CMP_GTHANEQUAL = 301,          /* CMP_GTHANEQUAL  */
    CMP_LTHANEQUAL = 302,          /* CMP_LTHANEQUAL  */
    BOOL_AND = 303,                /* BOOL_AND  */
    BOOL_OR = 304,                 /* BOOL_OR  */
    VALUE_ADDR_IPMASK = 305,       /* VALUE_ADDR_IPMASK  */
    VALUE_TRUE = 306,              /* VALUE_TRUE  */
    VALUE_FALSE = 307,             /* VALUE_FALSE  */
    VALUE_ADDR_MAC = 308,          /* VALUE_ADDR_MAC  */
    VALUE_NAME = 309,              /* VALUE_NAME  */
    VALUE_REGEX = 310,             /* VALUE_REGEX  */
    VALUE_ADDR_IPV4 = 311,         /* VALUE_ADDR_IPV4  */
    VALUE_ADDR_IPV4_CIDR = 312,    /* VALUE_ADDR_IPV4_CIDR  */
    VALUE_ADDR_IPV6 = 313,         /* VALUE_ADDR_IPV6  */
    VALUE_ADDR_IPV6_CIDR = 314,    /* VALUE_ADDR_IPV6_CIDR  */
    VALUE_NUMBER = 315             /* VALUE_NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define FLOW_IP_PROTO 258
#define FLOW_IP_VERSION 259
#define FLOW_IP_NAT 260
#define FLOW_VLAN_ID 261
#define FLOW_OTHER_TYPE 262
#define FLOW_LOCAL_MAC 263
#define FLOW_OTHER_MAC 264
#define FLOW_LOCAL_IP 265
#define FLOW_OTHER_IP 266
#define FLOW_LOCAL_PORT 267
#define FLOW_OTHER_PORT 268
#define FLOW_TUNNEL_TYPE 269
#define FLOW_DETECTION_GUESSED 270
#define FLOW_DETECTION_UPDATED 271
#define FLOW_CATEGORY 272
#define FLOW_RISKS 273
#define FLOW_NDPI_RISK_SCORE 274
#define FLOW_NDPI_RISK_SCORE_CLIENT 275
#define FLOW_NDPI_RISK_SCORE_SERVER 276
#define FLOW_DOMAIN_CATEGORY 277
#define FLOW_APPLICATION 278
#define FLOW_APPLICATION_CATEGORY 279
#define FLOW_PROTOCOL 280
#define FLOW_PROTOCOL_CATEGORY 281
#define FLOW_DETECTED_HOSTNAME 282
#define FLOW_SSL_VERSION 283
#define FLOW_SSL_CIPHER 284
#define FLOW_ORIGIN 285
#define FLOW_CT_MARK 286
#define FLOW_OTHER_UNKNOWN 287
#define FLOW_OTHER_UNSUPPORTED 288
#define FLOW_OTHER_LOCAL 289
#define FLOW_OTHER_MULTICAST 290
#define FLOW_OTHER_BROADCAST 291
#define FLOW_OTHER_REMOTE 292
#define FLOW_OTHER_ERROR 293
#define FLOW_ORIGIN_LOCAL 294
#define FLOW_ORIGIN_OTHER 295
#define FLOW_ORIGIN_UNKNOWN 296
#define FLOW_TUNNEL_NONE 297
#define FLOW_TUNNEL_GTP 298
#define CMP_EQUAL 299
#define CMP_NOTEQUAL 300
#define CMP_GTHANEQUAL 301
#define CMP_LTHANEQUAL 302
#define BOOL_AND 303
#define BOOL_OR 304
#define VALUE_ADDR_IPMASK 305
#define VALUE_TRUE 306
#define VALUE_FALSE 307
#define VALUE_ADDR_MAC 308
#define VALUE_NAME 309
#define VALUE_REGEX 310
#define VALUE_ADDR_IPV4 311
#define VALUE_ADDR_IPV4_CIDR 312
#define VALUE_ADDR_IPV6 313
#define VALUE_ADDR_IPV6_CIDR 314
#define VALUE_NUMBER 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 102 "nd-flow-expr.ypp"

    char string[_NDFP_MAX_NAMELEN];

    bool bool_number;
    unsigned short us_number;
    unsigned long ul_number;

    bool bool_result;

#line 350 "nd-flow-expr.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (yyscan_t scanner);


#endif /* !YY_YY_ND_FLOW_EXPR_HPP_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FLOW_IP_PROTO = 3,              /* FLOW_IP_PROTO  */
  YYSYMBOL_FLOW_IP_VERSION = 4,            /* FLOW_IP_VERSION  */
  YYSYMBOL_FLOW_IP_NAT = 5,                /* FLOW_IP_NAT  */
  YYSYMBOL_FLOW_VLAN_ID = 6,               /* FLOW_VLAN_ID  */
  YYSYMBOL_FLOW_OTHER_TYPE = 7,            /* FLOW_OTHER_TYPE  */
  YYSYMBOL_FLOW_LOCAL_MAC = 8,             /* FLOW_LOCAL_MAC  */
  YYSYMBOL_FLOW_OTHER_MAC = 9,             /* FLOW_OTHER_MAC  */
  YYSYMBOL_FLOW_LOCAL_IP = 10,             /* FLOW_LOCAL_IP  */
  YYSYMBOL_FLOW_OTHER_IP = 11,             /* FLOW_OTHER_IP  */
  YYSYMBOL_FLOW_LOCAL_PORT = 12,           /* FLOW_LOCAL_PORT  */
  YYSYMBOL_FLOW_OTHER_PORT = 13,           /* FLOW_OTHER_PORT  */
  YYSYMBOL_FLOW_TUNNEL_TYPE = 14,          /* FLOW_TUNNEL_TYPE  */
  YYSYMBOL_FLOW_DETECTION_GUESSED = 15,    /* FLOW_DETECTION_GUESSED  */
  YYSYMBOL_FLOW_DETECTION_UPDATED = 16,    /* FLOW_DETECTION_UPDATED  */
  YYSYMBOL_FLOW_CATEGORY = 17,             /* FLOW_CATEGORY  */
  YYSYMBOL_FLOW_RISKS = 18,                /* FLOW_RISKS  */
  YYSYMBOL_FLOW_NDPI_RISK_SCORE = 19,      /* FLOW_NDPI_RISK_SCORE  */
  YYSYMBOL_FLOW_NDPI_RISK_SCORE_CLIENT = 20, /* FLOW_NDPI_RISK_SCORE_CLIENT  */
  YYSYMBOL_FLOW_NDPI_RISK_SCORE_SERVER = 21, /* FLOW_NDPI_RISK_SCORE_SERVER  */
  YYSYMBOL_FLOW_DOMAIN_CATEGORY = 22,      /* FLOW_DOMAIN_CATEGORY  */
  YYSYMBOL_FLOW_APPLICATION = 23,          /* FLOW_APPLICATION  */
  YYSYMBOL_FLOW_APPLICATION_CATEGORY = 24, /* FLOW_APPLICATION_CATEGORY  */
  YYSYMBOL_FLOW_PROTOCOL = 25,             /* FLOW_PROTOCOL  */
  YYSYMBOL_FLOW_PROTOCOL_CATEGORY = 26,    /* FLOW_PROTOCOL_CATEGORY  */
  YYSYMBOL_FLOW_DETECTED_HOSTNAME = 27,    /* FLOW_DETECTED_HOSTNAME  */
  YYSYMBOL_FLOW_SSL_VERSION = 28,          /* FLOW_SSL_VERSION  */
  YYSYMBOL_FLOW_SSL_CIPHER = 29,           /* FLOW_SSL_CIPHER  */
  YYSYMBOL_FLOW_ORIGIN = 30,               /* FLOW_ORIGIN  */
  YYSYMBOL_FLOW_CT_MARK = 31,              /* FLOW_CT_MARK  */
  YYSYMBOL_FLOW_OTHER_UNKNOWN = 32,        /* FLOW_OTHER_UNKNOWN  */
  YYSYMBOL_FLOW_OTHER_UNSUPPORTED = 33,    /* FLOW_OTHER_UNSUPPORTED  */
  YYSYMBOL_FLOW_OTHER_LOCAL = 34,          /* FLOW_OTHER_LOCAL  */
  YYSYMBOL_FLOW_OTHER_MULTICAST = 35,      /* FLOW_OTHER_MULTICAST  */
  YYSYMBOL_FLOW_OTHER_BROADCAST = 36,      /* FLOW_OTHER_BROADCAST  */
  YYSYMBOL_FLOW_OTHER_REMOTE = 37,         /* FLOW_OTHER_REMOTE  */
  YYSYMBOL_FLOW_OTHER_ERROR = 38,          /* FLOW_OTHER_ERROR  */
  YYSYMBOL_FLOW_ORIGIN_LOCAL = 39,         /* FLOW_ORIGIN_LOCAL  */
  YYSYMBOL_FLOW_ORIGIN_OTHER = 40,         /* FLOW_ORIGIN_OTHER  */
  YYSYMBOL_FLOW_ORIGIN_UNKNOWN = 41,       /* FLOW_ORIGIN_UNKNOWN  */
  YYSYMBOL_FLOW_TUNNEL_NONE = 42,          /* FLOW_TUNNEL_NONE  */
  YYSYMBOL_FLOW_TUNNEL_GTP = 43,           /* FLOW_TUNNEL_GTP  */
  YYSYMBOL_CMP_EQUAL = 44,                 /* CMP_EQUAL  */
  YYSYMBOL_CMP_NOTEQUAL = 45,              /* CMP_NOTEQUAL  */
  YYSYMBOL_CMP_GTHANEQUAL = 46,            /* CMP_GTHANEQUAL  */
  YYSYMBOL_CMP_LTHANEQUAL = 47,            /* CMP_LTHANEQUAL  */
  YYSYMBOL_BOOL_AND = 48,                  /* BOOL_AND  */
  YYSYMBOL_BOOL_OR = 49,                   /* BOOL_OR  */
  YYSYMBOL_VALUE_ADDR_IPMASK = 50,         /* VALUE_ADDR_IPMASK  */
  YYSYMBOL_VALUE_TRUE = 51,                /* VALUE_TRUE  */
  YYSYMBOL_VALUE_FALSE = 52,               /* VALUE_FALSE  */
  YYSYMBOL_VALUE_ADDR_MAC = 53,            /* VALUE_ADDR_MAC  */
  YYSYMBOL_VALUE_NAME = 54,                /* VALUE_NAME  */
  YYSYMBOL_VALUE_REGEX = 55,               /* VALUE_REGEX  */
  YYSYMBOL_VALUE_ADDR_IPV4 = 56,           /* VALUE_ADDR_IPV4  */
  YYSYMBOL_VALUE_ADDR_IPV4_CIDR = 57,      /* VALUE_ADDR_IPV4_CIDR  */
  YYSYMBOL_VALUE_ADDR_IPV6 = 58,           /* VALUE_ADDR_IPV6  */
  YYSYMBOL_VALUE_ADDR_IPV6_CIDR = 59,      /* VALUE_ADDR_IPV6_CIDR  */
  YYSYMBOL_VALUE_NUMBER = 60,              /* VALUE_NUMBER  */
  YYSYMBOL_61_ = 61,                       /* ';'  */
  YYSYMBOL_62_ = 62,                       /* '('  */
  YYSYMBOL_63_ = 63,                       /* ')'  */
  YYSYMBOL_64_ = 64,                       /* '!'  */
  YYSYMBOL_65_ = 65,                       /* '>'  */
  YYSYMBOL_66_ = 66,                       /* '<'  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_exprs = 68,                     /* exprs  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_expr_ip_proto = 70,             /* expr_ip_proto  */
  YYSYMBOL_expr_ip_version = 71,           /* expr_ip_version  */
  YYSYMBOL_expr_ip_nat = 72,               /* expr_ip_nat  */
  YYSYMBOL_expr_vlan_id = 73,              /* expr_vlan_id  */
  YYSYMBOL_expr_other_type = 74,           /* expr_other_type  */
  YYSYMBOL_value_other_type = 75,          /* value_other_type  */
  YYSYMBOL_expr_local_mac = 76,            /* expr_local_mac  */
  YYSYMBOL_expr_other_mac = 77,            /* expr_other_mac  */
  YYSYMBOL_expr_local_ip = 78,             /* expr_local_ip  */
  YYSYMBOL_expr_other_ip = 79,             /* expr_other_ip  */
  YYSYMBOL_value_addr_ip = 80,             /* value_addr_ip  */
  YYSYMBOL_expr_local_port = 81,           /* expr_local_port  */
  YYSYMBOL_expr_other_port = 82,           /* expr_other_port  */
  YYSYMBOL_expr_tunnel_type = 83,          /* expr_tunnel_type  */
  YYSYMBOL_value_tunnel_type = 84,         /* value_tunnel_type  */
  YYSYMBOL_expr_detection_guessed = 85,    /* expr_detection_guessed  */
  YYSYMBOL_expr_detection_updated = 86,    /* expr_detection_updated  */
  YYSYMBOL_expr_app = 87,                  /* expr_app  */
  YYSYMBOL_expr_app_id = 88,               /* expr_app_id  */
  YYSYMBOL_expr_app_name = 89,             /* expr_app_name  */
  YYSYMBOL_expr_category = 90,             /* expr_category  */
  YYSYMBOL_expr_risks = 91,                /* expr_risks  */
  YYSYMBOL_expr_ndpi_risk_score = 92,      /* expr_ndpi_risk_score  */
  YYSYMBOL_expr_ndpi_risk_score_client = 93, /* expr_ndpi_risk_score_client  */
  YYSYMBOL_expr_ndpi_risk_score_server = 94, /* expr_ndpi_risk_score_server  */
  YYSYMBOL_expr_app_category = 95,         /* expr_app_category  */
  YYSYMBOL_expr_domain_category = 96,      /* expr_domain_category  */
  YYSYMBOL_expr_proto = 97,                /* expr_proto  */
  YYSYMBOL_expr_proto_id = 98,             /* expr_proto_id  */
  YYSYMBOL_expr_proto_name = 99,           /* expr_proto_name  */
  YYSYMBOL_expr_proto_category = 100,      /* expr_proto_category  */
  YYSYMBOL_expr_detected_hostname = 101,   /* expr_detected_hostname  */
  YYSYMBOL_expr_fwmark = 102,              /* expr_fwmark  */
  YYSYMBOL_expr_ssl_version = 103,         /* expr_ssl_version  */
  YYSYMBOL_expr_ssl_cipher = 104,          /* expr_ssl_cipher  */
  YYSYMBOL_expr_origin = 105,              /* expr_origin  */
  YYSYMBOL_value_origin_type = 106         /* value_origin_type  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   323

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  319

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,     2,     2,     2,     2,     2,
      62,    63,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    61,
      66,     2,    65,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   161,   161,   163,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   200,   204,   208,   213,   217,   221,
     225,   229,   233,   237,   244,   248,   255,   259,   263,   267,
     271,   275,   282,   286,   290,   294,   298,   302,   306,   310,
     317,   323,   329,   373,   420,   421,   422,   423,   424,   425,
     426,   430,   436,   445,   451,   460,   466,   475,   481,   490,
     491,   492,   493,   497,   501,   505,   509,   513,   517,   521,
     525,   532,   536,   540,   544,   548,   552,   556,   560,   567,
     573,   579,   598,   620,   621,   624,   628,   634,   642,   650,
     658,   669,   673,   679,   687,   695,   703,   714,   720,   728,
     729,   732,   741,   753,   778,   806,   831,   859,   863,   867,
     885,   907,   911,   915,   919,   923,   927,   931,   935,   942,
     946,   950,   954,   958,   962,   966,   970,   977,   981,   985,
     989,   993,   997,  1001,  1005,  1012,  1028,  1047,  1063,  1082,
    1088,  1094,  1095,  1098,  1104,  1113,  1132,  1153,  1170,  1190,
    1197,  1204,  1222,  1240,  1277,  1286,  1294,  1302,  1310,  1318,
    1326,  1334,  1342,  1353,  1357,  1361,  1365,  1369,  1373,  1377,
    1381,  1388,  1392,  1396,  1400,  1404,  1408,  1412,  1416,  1423,
    1427,  1431,  1435,  1442,  1443,  1444
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FLOW_IP_PROTO",
  "FLOW_IP_VERSION", "FLOW_IP_NAT", "FLOW_VLAN_ID", "FLOW_OTHER_TYPE",
  "FLOW_LOCAL_MAC", "FLOW_OTHER_MAC", "FLOW_LOCAL_IP", "FLOW_OTHER_IP",
  "FLOW_LOCAL_PORT", "FLOW_OTHER_PORT", "FLOW_TUNNEL_TYPE",
  "FLOW_DETECTION_GUESSED", "FLOW_DETECTION_UPDATED", "FLOW_CATEGORY",
  "FLOW_RISKS", "FLOW_NDPI_RISK_SCORE", "FLOW_NDPI_RISK_SCORE_CLIENT",
  "FLOW_NDPI_RISK_SCORE_SERVER", "FLOW_DOMAIN_CATEGORY",
  "FLOW_APPLICATION", "FLOW_APPLICATION_CATEGORY", "FLOW_PROTOCOL",
  "FLOW_PROTOCOL_CATEGORY", "FLOW_DETECTED_HOSTNAME", "FLOW_SSL_VERSION",
  "FLOW_SSL_CIPHER", "FLOW_ORIGIN", "FLOW_CT_MARK", "FLOW_OTHER_UNKNOWN",
  "FLOW_OTHER_UNSUPPORTED", "FLOW_OTHER_LOCAL", "FLOW_OTHER_MULTICAST",
  "FLOW_OTHER_BROADCAST", "FLOW_OTHER_REMOTE", "FLOW_OTHER_ERROR",
  "FLOW_ORIGIN_LOCAL", "FLOW_ORIGIN_OTHER", "FLOW_ORIGIN_UNKNOWN",
  "FLOW_TUNNEL_NONE", "FLOW_TUNNEL_GTP", "CMP_EQUAL", "CMP_NOTEQUAL",
  "CMP_GTHANEQUAL", "CMP_LTHANEQUAL", "BOOL_AND", "BOOL_OR",
  "VALUE_ADDR_IPMASK", "VALUE_TRUE", "VALUE_FALSE", "VALUE_ADDR_MAC",
  "VALUE_NAME", "VALUE_REGEX", "VALUE_ADDR_IPV4", "VALUE_ADDR_IPV4_CIDR",
  "VALUE_ADDR_IPV6", "VALUE_ADDR_IPV6_CIDR", "VALUE_NUMBER", "';'", "'('",
  "')'", "'!'", "'>'", "'<'", "$accept", "exprs", "expr", "expr_ip_proto",
  "expr_ip_version", "expr_ip_nat", "expr_vlan_id", "expr_other_type",
  "value_other_type", "expr_local_mac", "expr_other_mac", "expr_local_ip",
  "expr_other_ip", "value_addr_ip", "expr_local_port", "expr_other_port",
  "expr_tunnel_type", "value_tunnel_type", "expr_detection_guessed",
  "expr_detection_updated", "expr_app", "expr_app_id", "expr_app_name",
  "expr_category", "expr_risks", "expr_ndpi_risk_score",
  "expr_ndpi_risk_score_client", "expr_ndpi_risk_score_server",
  "expr_app_category", "expr_domain_category", "expr_proto",
  "expr_proto_id", "expr_proto_name", "expr_proto_category",
  "expr_detected_hostname", "expr_fwmark", "expr_ssl_version",
  "expr_ssl_cipher", "expr_origin", "value_origin_type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -43,     1,   -43,    56,   -42,    79,    60,    83,    88,   119,
     145,   155,    64,    69,   157,   159,   161,   163,   165,    73,
      96,   100,   167,   169,   171,   173,   175,   177,   104,   113,
     179,   127,    30,    68,    18,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,     9,    12,
      25,    52,    76,    92,   107,   131,   174,   176,   181,   189,
     190,   191,   192,   193,   148,   148,   194,   195,   201,   202,
     139,   139,   139,   139,   197,   198,   199,   200,   203,   204,
     205,   206,   207,   208,   209,   210,   187,   187,   180,   182,
     184,   186,    36,   133,   217,   218,   213,   214,   215,   216,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   239,   240,     8,    10,   241,   242,
      77,   134,   243,   244,   185,   188,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,    37,    37,
     257,   258,   259,   260,   261,   262,   105,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,    30,    30,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   196,   196
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    36,     0,    46,    52,    60,     0,     0,
       0,     0,    83,    91,    99,   105,   111,     0,   127,   131,
     139,   147,     0,   117,     0,   159,     0,   169,   183,   191,
     199,   175,     0,     0,     0,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    23,
     119,   120,    18,    19,    20,    21,    22,    24,    25,    26,
     161,   162,    27,    28,    32,    29,    30,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    47,    53,
      61,    84,    92,   100,   106,   112,   128,   132,   140,   148,
     118,   160,   170,   184,   192,   200,   176,     0,     0,     3,
      38,    39,    40,    41,    42,    43,    44,    45,    48,    49,
      50,    51,    54,    55,    56,    57,    58,    59,    64,    65,
      66,    67,    68,    69,    70,    62,    63,    71,    72,    73,
      74,    79,    80,    81,    82,    75,    76,    77,    78,    85,
      86,    87,    88,    89,    90,    93,    94,    95,    96,    97,
      98,   103,   104,   101,   102,   107,   108,   109,   110,   113,
     114,   115,   116,   125,   126,   129,   130,   133,   134,   135,
     136,   137,   138,   141,   142,   143,   144,   145,   146,   149,
     150,   151,   152,   153,   154,   157,   158,   123,   121,   124,
     122,   155,   156,   165,   163,   166,   164,   167,   168,   171,
     173,   172,   174,   185,   186,   187,   188,   189,   190,   193,
     194,   195,   196,   197,   198,   203,   204,   205,   201,   202,
     177,   178,   179,   180,   181,   182,    35,    34,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -43,   -43,   -32,   -43,   -43,   -43,   -43,   -43,   238,   -43,
     -43,   -43,   -43,    84,   -43,   -43,   -43,   149,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,    87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    34,    35,    36,    37,    38,    39,   215,    40,
      41,    42,    43,   225,    44,    45,    46,   243,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,   308
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     166,     2,    74,    75,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,   277,    32,   279,    33,   187,   188,   278,   190,
     280,   167,   191,   168,   169,   170,   305,   306,   307,   189,
     171,   172,   173,   174,   175,   192,   176,   177,   178,   179,
     253,   180,    32,   181,    33,   182,   183,   184,   185,   186,
      68,    69,    70,    71,    78,    79,    80,    81,    94,    95,
      96,    97,   193,   100,   101,   102,   103,   116,   117,   118,
     119,    72,    73,    76,    77,    82,    83,    84,    85,    98,
      99,   283,    86,    87,   104,   105,   194,   284,   120,   121,
     122,   123,   124,   125,   128,   129,   130,   131,   146,   147,
     148,   149,   195,   187,   188,   317,   318,   152,   153,   154,
     155,   126,   127,    88,    89,   132,   133,   196,   316,   150,
     151,   160,   161,   162,   163,   226,   227,   228,   156,   157,
     208,   209,   210,   211,   212,   213,   214,   254,   285,    90,
      91,   197,   164,   165,   286,   221,   222,   223,   224,    92,
      93,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   158,   159,   198,   199,   200,   201,   241,
     242,   245,   246,   247,   248,   249,   250,   251,   252,   289,
     290,   202,   291,   292,   187,   188,   309,   217,   218,   203,
     204,   205,   206,   207,   219,   220,   244,   229,   230,   231,
     232,     0,     0,   233,   234,   235,   236,   237,   238,   239,
     240,   255,   256,   257,   258,   259,   260,     0,     0,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   281,   282,   287,   288,     0,
       0,     0,     0,     0,     0,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   310,   311,   312,
     313,   314,   315,   216
};

static const yytype_int16 yycheck[] =
{
      32,     0,    44,    45,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    54,    62,    54,    64,    48,    49,    60,    60,
      60,     3,    60,     5,     6,     7,    39,    40,    41,    61,
      12,    13,    14,    15,    16,    60,    18,    19,    20,    21,
      54,    23,    62,    25,    64,    27,    28,    29,    30,    31,
      44,    45,    46,    47,    44,    45,    46,    47,    44,    45,
      46,    47,    60,    44,    45,    46,    47,    44,    45,    46,
      47,    65,    66,    44,    45,    65,    66,    44,    45,    65,
      66,    54,    44,    45,    65,    66,    60,    60,    65,    66,
      44,    45,    46,    47,    44,    45,    46,    47,    44,    45,
      46,    47,    60,    48,    49,   187,   188,    44,    45,    46,
      47,    65,    66,    44,    45,    65,    66,    60,    63,    65,
      66,    44,    45,    46,    47,    91,    92,    93,    65,    66,
      32,    33,    34,    35,    36,    37,    38,    54,    54,    44,
      45,    60,    65,    66,    60,    56,    57,    58,    59,    44,
      45,    44,    45,    44,    45,    44,    45,    44,    45,    44,
      45,    44,    45,    44,    45,    44,    45,    44,    45,    44,
      45,    44,    45,    44,    45,    51,    52,    51,    52,    42,
      43,    51,    52,    51,    52,    51,    52,    51,    52,    54,
      55,    60,    54,    55,    48,    49,   159,    53,    53,    60,
      60,    60,    60,    60,    53,    53,   107,    60,    60,    60,
      60,    -1,    -1,    60,    60,    60,    60,    60,    60,    60,
      60,    54,    54,    60,    60,    60,    60,    -1,    -1,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    54,    54,    54,    54,    54,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    85
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    62,    64,    69,    70,    71,    72,    73,    74,
      76,    77,    78,    79,    81,    82,    83,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    44,    45,
      46,    47,    65,    66,    44,    45,    44,    45,    44,    45,
      46,    47,    65,    66,    44,    45,    44,    45,    44,    45,
      44,    45,    44,    45,    44,    45,    46,    47,    65,    66,
      44,    45,    46,    47,    65,    66,    44,    45,    44,    45,
      44,    45,    44,    45,    44,    45,    44,    45,    46,    47,
      65,    66,    44,    45,    46,    47,    65,    66,    44,    45,
      46,    47,    65,    66,    44,    45,    44,    45,    44,    45,
      44,    45,    44,    45,    44,    45,    44,    45,    46,    47,
      65,    66,    44,    45,    46,    47,    65,    66,    44,    45,
      44,    45,    46,    47,    65,    66,    69,     3,     5,     6,
       7,    12,    13,    14,    15,    16,    18,    19,    20,    21,
      23,    25,    27,    28,    29,    30,    31,    48,    49,    61,
      60,    60,    60,    60,    60,    60,    60,    60,    51,    52,
      51,    52,    60,    60,    60,    60,    60,    60,    32,    33,
      34,    35,    36,    37,    38,    75,    75,    53,    53,    53,
      53,    56,    57,    58,    59,    80,    80,    80,    80,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    42,    43,    84,    84,    51,    52,    51,    52,    51,
      52,    51,    52,    54,    54,    54,    54,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    54,    54,    54,    60,    54,
      60,    54,    54,    54,    60,    54,    60,    54,    54,    54,
      55,    54,    55,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    39,    40,    41,   106,   106,
      60,    60,    60,    60,    60,    60,    63,    69,    69
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    72,    72,    72,    72,
      72,    72,    73,    73,    73,    73,    73,    73,    73,    73,
      74,    74,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    76,    76,    77,    77,    78,    78,    79,    79,    80,
      80,    80,    80,    81,    81,    81,    81,    81,    81,    81,
      81,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      83,    83,    83,    84,    84,    85,    85,    85,    85,    85,
      85,    86,    86,    86,    86,    86,    86,    87,    87,    87,
      87,    88,    88,    89,    89,    90,    90,    91,    91,    91,
      91,    92,    92,    92,    92,    92,    92,    92,    92,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    94,    95,    95,    96,    96,    97,
      97,    97,    97,    98,    98,    99,    99,   100,   100,   101,
     101,   101,   101,   101,   101,   102,   102,   102,   102,   102,
     102,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   106,   106,   106
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     1,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     3,     3,
       3,     3,     1,     2,     3,     3,     3,     3,     3,     3,
       1,     2,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     2,     3,     3,     3,     3,     3,
       3,     1,     2,     3,     3,     3,     3,     3,     3,     1,
       2,     3,     3,     1,     1,     1,     2,     3,     3,     3,
       3,     1,     2,     3,     3,     3,     3,     1,     2,     1,
       1,     3,     3,     3,     3,     3,     3,     1,     2,     3,
       3,     1,     2,     3,     3,     3,     3,     3,     3,     1,
       2,     3,     3,     3,     3,     3,     3,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       2,     1,     1,     3,     3,     3,     3,     3,     3,     1,
       2,     3,     3,     3,     3,     1,     2,     3,     3,     3,
       3,     3,     3,     1,     2,     3,     3,     3,     3,     3,
       3,     1,     2,     3,     3,     3,     3,     3,     3,     1,
       2,     3,     3,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 33: /* expr: expr BOOL_OR expr  */
#line 196 "nd-flow-expr.ypp"
                        {
        _NDFP_result = ((yyval.bool_result) = ((yyvsp[-2].bool_result) || (yyvsp[0].bool_result)));
        _NDFP_debugf("OR (%d || %d == %d)\n", (yyvsp[-2].bool_result), (yyvsp[0].bool_result), (yyval.bool_result));
    }
#line 1820 "nd-flow-expr.cpp"
    break;

  case 34: /* expr: expr BOOL_AND expr  */
#line 200 "nd-flow-expr.ypp"
                         {
        _NDFP_result = ((yyval.bool_result) = ((yyvsp[-2].bool_result) && (yyvsp[0].bool_result)));
        _NDFP_debugf("AND (%d && %d == %d)\n", (yyvsp[-2].bool_result), (yyvsp[0].bool_result), (yyval.bool_result));
    }
#line 1829 "nd-flow-expr.cpp"
    break;

  case 35: /* expr: '(' expr ')'  */
#line 204 "nd-flow-expr.ypp"
                   { _NDFP_result = ((yyval.bool_result) = (yyvsp[-1].bool_result)); }
#line 1835 "nd-flow-expr.cpp"
    break;

  case 36: /* expr_ip_proto: FLOW_IP_PROTO  */
#line 208 "nd-flow-expr.ypp"
                    {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_protocol != 0));
        _NDFP_debugf(
            "IP Protocol is non-zero? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1845 "nd-flow-expr.cpp"
    break;

  case 37: /* expr_ip_proto: '!' FLOW_IP_PROTO  */
#line 213 "nd-flow-expr.ypp"
                        {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_protocol == 0));
        _NDFP_debugf("IP Protocol is zero? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1854 "nd-flow-expr.cpp"
    break;

  case 38: /* expr_ip_proto: FLOW_IP_PROTO CMP_EQUAL VALUE_NUMBER  */
#line 217 "nd-flow-expr.ypp"
                                           {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_protocol == (yyvsp[0].ul_number)));
        _NDFP_debugf("IP Protocol == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 1863 "nd-flow-expr.cpp"
    break;

  case 39: /* expr_ip_proto: FLOW_IP_PROTO CMP_NOTEQUAL VALUE_NUMBER  */
#line 221 "nd-flow-expr.ypp"
                                              {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_protocol != (yyvsp[0].ul_number)));
        _NDFP_debugf("IP Protocol != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 1872 "nd-flow-expr.cpp"
    break;

  case 40: /* expr_ip_proto: FLOW_IP_PROTO CMP_GTHANEQUAL VALUE_NUMBER  */
#line 225 "nd-flow-expr.ypp"
                                                {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_protocol >= (yyvsp[0].ul_number)));
        _NDFP_debugf("IP Protocol >= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 1881 "nd-flow-expr.cpp"
    break;

  case 41: /* expr_ip_proto: FLOW_IP_PROTO CMP_LTHANEQUAL VALUE_NUMBER  */
#line 229 "nd-flow-expr.ypp"
                                                {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_protocol <= (yyvsp[0].ul_number)));
        _NDFP_debugf("IP Protocol <= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 1890 "nd-flow-expr.cpp"
    break;

  case 42: /* expr_ip_proto: FLOW_IP_PROTO '>' VALUE_NUMBER  */
#line 233 "nd-flow-expr.ypp"
                                     {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_protocol > (yyvsp[0].ul_number)));
        _NDFP_debugf("IP Protocol > %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 1899 "nd-flow-expr.cpp"
    break;

  case 43: /* expr_ip_proto: FLOW_IP_PROTO '<' VALUE_NUMBER  */
#line 237 "nd-flow-expr.ypp"
                                     {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_protocol < (yyvsp[0].ul_number)));
        _NDFP_debugf("IP Protocol > %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 1908 "nd-flow-expr.cpp"
    break;

  case 44: /* expr_ip_version: FLOW_IP_VERSION CMP_EQUAL VALUE_NUMBER  */
#line 244 "nd-flow-expr.ypp"
                                             {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_version == (yyvsp[0].ul_number)));
        _NDFP_debugf("IP Version == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 1917 "nd-flow-expr.cpp"
    break;

  case 45: /* expr_ip_version: FLOW_IP_VERSION CMP_NOTEQUAL VALUE_NUMBER  */
#line 248 "nd-flow-expr.ypp"
                                                {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ip_version != (yyvsp[0].ul_number)));
        _NDFP_debugf("IP Version != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 1926 "nd-flow-expr.cpp"
    break;

  case 46: /* expr_ip_nat: FLOW_IP_NAT  */
#line 255 "nd-flow-expr.ypp"
                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->flags.ip_nat.load() == true));
        _NDFP_debugf("IP NAT is true? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1935 "nd-flow-expr.cpp"
    break;

  case 47: /* expr_ip_nat: '!' FLOW_IP_NAT  */
#line 259 "nd-flow-expr.ypp"
                      {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->flags.ip_nat.load() == false));
        _NDFP_debugf("IP NAT is false? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1944 "nd-flow-expr.cpp"
    break;

  case 48: /* expr_ip_nat: FLOW_IP_NAT CMP_EQUAL VALUE_TRUE  */
#line 263 "nd-flow-expr.ypp"
                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->flags.ip_nat.load() == true));
        _NDFP_debugf("IP NAT == true? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1953 "nd-flow-expr.cpp"
    break;

  case 49: /* expr_ip_nat: FLOW_IP_NAT CMP_EQUAL VALUE_FALSE  */
#line 267 "nd-flow-expr.ypp"
                                        {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->flags.ip_nat.load() == false));
        _NDFP_debugf("IP NAT == false? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1962 "nd-flow-expr.cpp"
    break;

  case 50: /* expr_ip_nat: FLOW_IP_NAT CMP_NOTEQUAL VALUE_TRUE  */
#line 271 "nd-flow-expr.ypp"
                                          {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->flags.ip_nat.load() != true));
        _NDFP_debugf("IP NAT != true? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1971 "nd-flow-expr.cpp"
    break;

  case 51: /* expr_ip_nat: FLOW_IP_NAT CMP_NOTEQUAL VALUE_FALSE  */
#line 275 "nd-flow-expr.ypp"
                                           {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->flags.ip_nat.load() != false));
        _NDFP_debugf("IP NAT != false? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1980 "nd-flow-expr.cpp"
    break;

  case 52: /* expr_vlan_id: FLOW_VLAN_ID  */
#line 282 "nd-flow-expr.ypp"
                   {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->vlan_id != 0));
        _NDFP_debugf("VLAN ID is non-zero? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1989 "nd-flow-expr.cpp"
    break;

  case 53: /* expr_vlan_id: '!' FLOW_VLAN_ID  */
#line 286 "nd-flow-expr.ypp"
                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->vlan_id == 0));
        _NDFP_debugf("VLAN ID is zero? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 1998 "nd-flow-expr.cpp"
    break;

  case 54: /* expr_vlan_id: FLOW_VLAN_ID CMP_EQUAL VALUE_NUMBER  */
#line 290 "nd-flow-expr.ypp"
                                          {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->vlan_id == (yyvsp[0].ul_number)));
        _NDFP_debugf("VLAN ID == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2007 "nd-flow-expr.cpp"
    break;

  case 55: /* expr_vlan_id: FLOW_VLAN_ID CMP_NOTEQUAL VALUE_NUMBER  */
#line 294 "nd-flow-expr.ypp"
                                             {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->vlan_id != (yyvsp[0].ul_number)));
        _NDFP_debugf("VLAN ID != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2016 "nd-flow-expr.cpp"
    break;

  case 56: /* expr_vlan_id: FLOW_VLAN_ID CMP_GTHANEQUAL VALUE_NUMBER  */
#line 298 "nd-flow-expr.ypp"
                                               {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->vlan_id >= (yyvsp[0].ul_number)));
        _NDFP_debugf("VLAN ID >= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2025 "nd-flow-expr.cpp"
    break;

  case 57: /* expr_vlan_id: FLOW_VLAN_ID CMP_LTHANEQUAL VALUE_NUMBER  */
#line 302 "nd-flow-expr.ypp"
                                               {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->vlan_id <= (yyvsp[0].ul_number)));
        _NDFP_debugf("VLAN ID <= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2034 "nd-flow-expr.cpp"
    break;

  case 58: /* expr_vlan_id: FLOW_VLAN_ID '>' VALUE_NUMBER  */
#line 306 "nd-flow-expr.ypp"
                                    {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->vlan_id > (yyvsp[0].ul_number)));
        _NDFP_debugf("VLAN ID > %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2043 "nd-flow-expr.cpp"
    break;

  case 59: /* expr_vlan_id: FLOW_VLAN_ID '<' VALUE_NUMBER  */
#line 310 "nd-flow-expr.ypp"
                                    {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->vlan_id < (yyvsp[0].ul_number)));
        _NDFP_debugf("VLAN ID < %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2052 "nd-flow-expr.cpp"
    break;

  case 60: /* expr_other_type: FLOW_OTHER_TYPE  */
#line 317 "nd-flow-expr.ypp"
                      {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->other_type != ndFlow::OTHER_UNKNOWN
        ));
        _NDFP_debugf("Other type known? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2063 "nd-flow-expr.cpp"
    break;

  case 61: /* expr_other_type: '!' FLOW_OTHER_TYPE  */
#line 323 "nd-flow-expr.ypp"
                          {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->other_type == ndFlow::OTHER_UNKNOWN
        ));
        _NDFP_debugf("Other type unknown? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2074 "nd-flow-expr.cpp"
    break;

  case 62: /* expr_other_type: FLOW_OTHER_TYPE CMP_EQUAL value_other_type  */
#line 329 "nd-flow-expr.ypp"
                                                 {
        switch ((yyvsp[0].us_number)) {
        case _NDFP_OTHER_UNKNOWN:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::OTHER_UNKNOWN
            );
            break;
        case _NDFP_OTHER_UNSUPPORTED:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::OTHER_UNSUPPORTED
            );
            break;
        case _NDFP_OTHER_LOCAL:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::OTHER_LOCAL
            );
            break;
        case _NDFP_OTHER_MULTICAST:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::OTHER_MULTICAST
            );
            break;
        case _NDFP_OTHER_BROADCAST:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::OTHER_BROADCAST
            );
            break;
        case _NDFP_OTHER_REMOTE:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::OTHER_REMOTE
            );
            break;
        case _NDFP_OTHER_ERROR:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::OTHER_ERROR
            );
            break;
        default:
            _NDFP_result = false;
        }

        (yyval.bool_result) = _NDFP_result;
        _NDFP_debugf("Other type == %hu? %s\n", (yyvsp[0].us_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2123 "nd-flow-expr.cpp"
    break;

  case 63: /* expr_other_type: FLOW_OTHER_TYPE CMP_NOTEQUAL value_other_type  */
#line 373 "nd-flow-expr.ypp"
                                                    {
        switch ((yyvsp[0].us_number)) {
        case _NDFP_OTHER_UNKNOWN:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::OTHER_UNKNOWN
            );
            break;
        case _NDFP_OTHER_UNSUPPORTED:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::OTHER_UNSUPPORTED
            );
            break;
        case _NDFP_OTHER_LOCAL:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::OTHER_LOCAL
            );
            break;
        case _NDFP_OTHER_MULTICAST:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::OTHER_MULTICAST
            );
            break;
        case _NDFP_OTHER_BROADCAST:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::OTHER_BROADCAST
            );
            break;
        case _NDFP_OTHER_REMOTE:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::OTHER_REMOTE
            );
            break;
        case _NDFP_OTHER_ERROR:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::OTHER_ERROR
            );
            break;
        default:
            _NDFP_result = false;
        }

        (yyval.bool_result) = _NDFP_result;
        _NDFP_debugf("Other type != %hu? %s\n", (yyvsp[0].us_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2172 "nd-flow-expr.cpp"
    break;

  case 64: /* value_other_type: FLOW_OTHER_UNKNOWN  */
#line 420 "nd-flow-expr.ypp"
                         { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2178 "nd-flow-expr.cpp"
    break;

  case 65: /* value_other_type: FLOW_OTHER_UNSUPPORTED  */
#line 421 "nd-flow-expr.ypp"
                             { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2184 "nd-flow-expr.cpp"
    break;

  case 66: /* value_other_type: FLOW_OTHER_LOCAL  */
#line 422 "nd-flow-expr.ypp"
                       { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2190 "nd-flow-expr.cpp"
    break;

  case 67: /* value_other_type: FLOW_OTHER_MULTICAST  */
#line 423 "nd-flow-expr.ypp"
                           { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2196 "nd-flow-expr.cpp"
    break;

  case 68: /* value_other_type: FLOW_OTHER_BROADCAST  */
#line 424 "nd-flow-expr.ypp"
                           { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2202 "nd-flow-expr.cpp"
    break;

  case 69: /* value_other_type: FLOW_OTHER_REMOTE  */
#line 425 "nd-flow-expr.ypp"
                        { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2208 "nd-flow-expr.cpp"
    break;

  case 70: /* value_other_type: FLOW_OTHER_ERROR  */
#line 426 "nd-flow-expr.ypp"
                       { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2214 "nd-flow-expr.cpp"
    break;

  case 71: /* expr_local_mac: FLOW_LOCAL_MAC CMP_EQUAL VALUE_ADDR_MAC  */
#line 430 "nd-flow-expr.ypp"
                                              {
        _NDFP_result = ((yyval.bool_result) = (
            strncasecmp(_NDFP_local_mac, (yyvsp[0].string), ND_STR_ETHALEN) == 0
        ));
        _NDFP_debugf("Local MAC == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2225 "nd-flow-expr.cpp"
    break;

  case 72: /* expr_local_mac: FLOW_LOCAL_MAC CMP_NOTEQUAL VALUE_ADDR_MAC  */
#line 436 "nd-flow-expr.ypp"
                                                 {
        _NDFP_result = ((yyval.bool_result) = (
            strncasecmp(_NDFP_local_mac, (yyvsp[0].string), ND_STR_ETHALEN) != 0
        ));
        _NDFP_debugf("Local MAC != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2236 "nd-flow-expr.cpp"
    break;

  case 73: /* expr_other_mac: FLOW_OTHER_MAC CMP_EQUAL VALUE_ADDR_MAC  */
#line 445 "nd-flow-expr.ypp"
                                              {
        _NDFP_result = ((yyval.bool_result) = (
            strncasecmp(_NDFP_other_mac, (yyvsp[0].string), ND_STR_ETHALEN) == 0
        ));
        _NDFP_debugf("Other MAC == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2247 "nd-flow-expr.cpp"
    break;

  case 74: /* expr_other_mac: FLOW_OTHER_MAC CMP_NOTEQUAL VALUE_ADDR_MAC  */
#line 451 "nd-flow-expr.ypp"
                                                 {
        _NDFP_result = ((yyval.bool_result) = (
            strncasecmp(_NDFP_other_mac, (yyvsp[0].string), ND_STR_ETHALEN) != 0
        ));
        _NDFP_debugf("Other MAC != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2258 "nd-flow-expr.cpp"
    break;

  case 75: /* expr_local_ip: FLOW_LOCAL_IP CMP_EQUAL value_addr_ip  */
#line 460 "nd-flow-expr.ypp"
                                            {
        _NDFP_result = ((yyval.bool_result) = (
            is_addr_equal(_NDFP_local_ip, (yyvsp[0].string)) == true
        ));
        _NDFP_debugf("Local IP == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2269 "nd-flow-expr.cpp"
    break;

  case 76: /* expr_local_ip: FLOW_LOCAL_IP CMP_NOTEQUAL value_addr_ip  */
#line 466 "nd-flow-expr.ypp"
                                               {
        _NDFP_result = ((yyval.bool_result) = (
            is_addr_equal(_NDFP_local_ip, (yyvsp[0].string)) == false
        ));
        _NDFP_debugf("Local IP != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2280 "nd-flow-expr.cpp"
    break;

  case 77: /* expr_other_ip: FLOW_OTHER_IP CMP_EQUAL value_addr_ip  */
#line 475 "nd-flow-expr.ypp"
                                            {
        _NDFP_result = ((yyval.bool_result) = (
            is_addr_equal(_NDFP_other_ip, (yyvsp[0].string)) == true
        ));
        _NDFP_debugf("Other IP == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2291 "nd-flow-expr.cpp"
    break;

  case 78: /* expr_other_ip: FLOW_OTHER_IP CMP_NOTEQUAL value_addr_ip  */
#line 481 "nd-flow-expr.ypp"
                                               {
        _NDFP_result = ((yyval.bool_result) = (
            is_addr_equal(_NDFP_other_ip, (yyvsp[0].string)) == false
        ));
        _NDFP_debugf("Other IP != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2302 "nd-flow-expr.cpp"
    break;

  case 79: /* value_addr_ip: VALUE_ADDR_IPV4  */
#line 490 "nd-flow-expr.ypp"
                      { strncpy((yyval.string), (yyvsp[0].string), _NDFP_MAX_NAMELEN); }
#line 2308 "nd-flow-expr.cpp"
    break;

  case 80: /* value_addr_ip: VALUE_ADDR_IPV4_CIDR  */
#line 491 "nd-flow-expr.ypp"
                           { strncpy((yyval.string), (yyvsp[0].string), _NDFP_MAX_NAMELEN); }
#line 2314 "nd-flow-expr.cpp"
    break;

  case 81: /* value_addr_ip: VALUE_ADDR_IPV6  */
#line 492 "nd-flow-expr.ypp"
                      { strncpy((yyval.string), (yyvsp[0].string), _NDFP_MAX_NAMELEN); }
#line 2320 "nd-flow-expr.cpp"
    break;

  case 82: /* value_addr_ip: VALUE_ADDR_IPV6_CIDR  */
#line 493 "nd-flow-expr.ypp"
                           { strncpy((yyval.string), (yyvsp[0].string), _NDFP_MAX_NAMELEN); }
#line 2326 "nd-flow-expr.cpp"
    break;

  case 83: /* expr_local_port: FLOW_LOCAL_PORT  */
#line 497 "nd-flow-expr.ypp"
                      {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_local_port != 0));
        _NDFP_debugf("Local port is true? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2335 "nd-flow-expr.cpp"
    break;

  case 84: /* expr_local_port: '!' FLOW_LOCAL_PORT  */
#line 501 "nd-flow-expr.ypp"
                          {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_local_port == 0));
        _NDFP_debugf("Local port is false? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2344 "nd-flow-expr.cpp"
    break;

  case 85: /* expr_local_port: FLOW_LOCAL_PORT CMP_EQUAL VALUE_NUMBER  */
#line 505 "nd-flow-expr.ypp"
                                             {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_local_port == (yyvsp[0].ul_number)));
        _NDFP_debugf("Local port == %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2353 "nd-flow-expr.cpp"
    break;

  case 86: /* expr_local_port: FLOW_LOCAL_PORT CMP_NOTEQUAL VALUE_NUMBER  */
#line 509 "nd-flow-expr.ypp"
                                                {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_local_port != (yyvsp[0].ul_number)));
        _NDFP_debugf("Local port != %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2362 "nd-flow-expr.cpp"
    break;

  case 87: /* expr_local_port: FLOW_LOCAL_PORT CMP_GTHANEQUAL VALUE_NUMBER  */
#line 513 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_local_port >= (yyvsp[0].ul_number)));
        _NDFP_debugf("Local port >= %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2371 "nd-flow-expr.cpp"
    break;

  case 88: /* expr_local_port: FLOW_LOCAL_PORT CMP_LTHANEQUAL VALUE_NUMBER  */
#line 517 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_local_port <= (yyvsp[0].ul_number)));
        _NDFP_debugf("Local port <= %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2380 "nd-flow-expr.cpp"
    break;

  case 89: /* expr_local_port: FLOW_LOCAL_PORT '>' VALUE_NUMBER  */
#line 521 "nd-flow-expr.ypp"
                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_local_port > (yyvsp[0].ul_number)));
        _NDFP_debugf("Local port > %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2389 "nd-flow-expr.cpp"
    break;

  case 90: /* expr_local_port: FLOW_LOCAL_PORT '<' VALUE_NUMBER  */
#line 525 "nd-flow-expr.ypp"
                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_local_port < (yyvsp[0].ul_number)));
        _NDFP_debugf("Local port > %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2398 "nd-flow-expr.cpp"
    break;

  case 91: /* expr_other_port: FLOW_OTHER_PORT  */
#line 532 "nd-flow-expr.ypp"
                      {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_other_port != 0));
        _NDFP_debugf("Other port is true? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2407 "nd-flow-expr.cpp"
    break;

  case 92: /* expr_other_port: '!' FLOW_OTHER_PORT  */
#line 536 "nd-flow-expr.ypp"
                          {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_other_port == 0));
        _NDFP_debugf("Other port is false? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2416 "nd-flow-expr.cpp"
    break;

  case 93: /* expr_other_port: FLOW_OTHER_PORT CMP_EQUAL VALUE_NUMBER  */
#line 540 "nd-flow-expr.ypp"
                                             {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_other_port == (yyvsp[0].ul_number)));
        _NDFP_debugf("Other port == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2425 "nd-flow-expr.cpp"
    break;

  case 94: /* expr_other_port: FLOW_OTHER_PORT CMP_NOTEQUAL VALUE_NUMBER  */
#line 544 "nd-flow-expr.ypp"
                                                {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_other_port != (yyvsp[0].ul_number)));
        _NDFP_debugf("Other port != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2434 "nd-flow-expr.cpp"
    break;

  case 95: /* expr_other_port: FLOW_OTHER_PORT CMP_GTHANEQUAL VALUE_NUMBER  */
#line 548 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_other_port >= (yyvsp[0].ul_number)));
        _NDFP_debugf("Other port >= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2443 "nd-flow-expr.cpp"
    break;

  case 96: /* expr_other_port: FLOW_OTHER_PORT CMP_LTHANEQUAL VALUE_NUMBER  */
#line 552 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_other_port <= (yyvsp[0].ul_number)));
        _NDFP_debugf("Other port <= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2452 "nd-flow-expr.cpp"
    break;

  case 97: /* expr_other_port: FLOW_OTHER_PORT '>' VALUE_NUMBER  */
#line 556 "nd-flow-expr.ypp"
                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_other_port > (yyvsp[0].ul_number)));
        _NDFP_debugf("Other port > %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2461 "nd-flow-expr.cpp"
    break;

  case 98: /* expr_other_port: FLOW_OTHER_PORT '<' VALUE_NUMBER  */
#line 560 "nd-flow-expr.ypp"
                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_other_port < (yyvsp[0].ul_number)));
        _NDFP_debugf("Other port > %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2470 "nd-flow-expr.cpp"
    break;

  case 99: /* expr_tunnel_type: FLOW_TUNNEL_TYPE  */
#line 567 "nd-flow-expr.ypp"
                       {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->tunnel_type != ndFlow::TUNNEL_NONE
        ));
        _NDFP_debugf("Tunnel type set? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2481 "nd-flow-expr.cpp"
    break;

  case 100: /* expr_tunnel_type: '!' FLOW_TUNNEL_TYPE  */
#line 573 "nd-flow-expr.ypp"
                           {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->tunnel_type == ndFlow::TUNNEL_NONE
        ));
        _NDFP_debugf("Tunnel type is none? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2492 "nd-flow-expr.cpp"
    break;

  case 101: /* expr_tunnel_type: FLOW_TUNNEL_TYPE CMP_EQUAL value_tunnel_type  */
#line 579 "nd-flow-expr.ypp"
                                                   {
        switch ((yyvsp[0].us_number)) {
        case _NDFP_TUNNEL_NONE:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::TUNNEL_NONE
            );
            break;
        case _NDFP_TUNNEL_GTP:
            _NDFP_result = (
                _NDFP_flow->other_type == ndFlow::TUNNEL_GTP
            );
            break;
        default:
            _NDFP_result = false;
        }

        (yyval.bool_result) = _NDFP_result;
        _NDFP_debugf("Tunnel type == %hu? %s\n", (yyvsp[0].us_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2516 "nd-flow-expr.cpp"
    break;

  case 102: /* expr_tunnel_type: FLOW_TUNNEL_TYPE CMP_NOTEQUAL value_tunnel_type  */
#line 598 "nd-flow-expr.ypp"
                                                      {
        switch ((yyvsp[0].us_number)) {
        case _NDFP_TUNNEL_NONE:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::TUNNEL_NONE
            );
            break;
        case _NDFP_TUNNEL_GTP:
            _NDFP_result = (
                _NDFP_flow->other_type != ndFlow::TUNNEL_GTP
            );
            break;
        default:
            _NDFP_result = false;
        }

        (yyval.bool_result) = _NDFP_result;
        _NDFP_debugf("Tunnel type != %hu? %s\n", (yyvsp[0].us_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2540 "nd-flow-expr.cpp"
    break;

  case 103: /* value_tunnel_type: FLOW_TUNNEL_NONE  */
#line 620 "nd-flow-expr.ypp"
                       { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2546 "nd-flow-expr.cpp"
    break;

  case 104: /* value_tunnel_type: FLOW_TUNNEL_GTP  */
#line 621 "nd-flow-expr.ypp"
                      { (yyval.us_number) = (yyvsp[0].us_number); }
#line 2552 "nd-flow-expr.cpp"
    break;

  case 105: /* expr_detection_guessed: FLOW_DETECTION_GUESSED  */
#line 624 "nd-flow-expr.ypp"
                             {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->flags.detection_guessed.load()));
        _NDFP_debugf("Detection was guessed? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2561 "nd-flow-expr.cpp"
    break;

  case 106: /* expr_detection_guessed: '!' FLOW_DETECTION_GUESSED  */
#line 628 "nd-flow-expr.ypp"
                                  {
        _NDFP_result = ((yyval.bool_result) = !(_NDFP_flow->flags.detection_guessed.load()));
        _NDFP_debugf(
            "Detection was not guessed? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2572 "nd-flow-expr.cpp"
    break;

  case 107: /* expr_detection_guessed: FLOW_DETECTION_GUESSED CMP_EQUAL VALUE_TRUE  */
#line 634 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->flags.detection_guessed.load() == true
        ));
        _NDFP_debugf(
            "Detection guessed == true? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2585 "nd-flow-expr.cpp"
    break;

  case 108: /* expr_detection_guessed: FLOW_DETECTION_GUESSED CMP_EQUAL VALUE_FALSE  */
#line 642 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->flags.detection_guessed.load() == false
        ));
        _NDFP_debugf(
            "Detection guessed == false? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2598 "nd-flow-expr.cpp"
    break;

  case 109: /* expr_detection_guessed: FLOW_DETECTION_GUESSED CMP_NOTEQUAL VALUE_TRUE  */
#line 650 "nd-flow-expr.ypp"
                                                     {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->flags.detection_guessed.load() != true
        ));
        _NDFP_debugf(
            "Detection guessed != true? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2611 "nd-flow-expr.cpp"
    break;

  case 110: /* expr_detection_guessed: FLOW_DETECTION_GUESSED CMP_NOTEQUAL VALUE_FALSE  */
#line 658 "nd-flow-expr.ypp"
                                                      {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->flags.detection_guessed.load() != false
        ));
        _NDFP_debugf(
            "Detection guessed != false? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2624 "nd-flow-expr.cpp"
    break;

  case 111: /* expr_detection_updated: FLOW_DETECTION_UPDATED  */
#line 669 "nd-flow-expr.ypp"
                             {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->flags.detection_updated.load()));
        _NDFP_debugf("Detection was updated? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2633 "nd-flow-expr.cpp"
    break;

  case 112: /* expr_detection_updated: '!' FLOW_DETECTION_UPDATED  */
#line 673 "nd-flow-expr.ypp"
                                  {
        _NDFP_result = ((yyval.bool_result) = !(_NDFP_flow->flags.detection_updated.load()));
        _NDFP_debugf(
            "Detection was not updated? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2644 "nd-flow-expr.cpp"
    break;

  case 113: /* expr_detection_updated: FLOW_DETECTION_UPDATED CMP_EQUAL VALUE_TRUE  */
#line 679 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->flags.detection_updated.load() == true
        ));
        _NDFP_debugf(
            "Detection updated == true? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2657 "nd-flow-expr.cpp"
    break;

  case 114: /* expr_detection_updated: FLOW_DETECTION_UPDATED CMP_EQUAL VALUE_FALSE  */
#line 687 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->flags.detection_updated.load() == false
        ));
        _NDFP_debugf(
            "Detection updated == false? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2670 "nd-flow-expr.cpp"
    break;

  case 115: /* expr_detection_updated: FLOW_DETECTION_UPDATED CMP_NOTEQUAL VALUE_TRUE  */
#line 695 "nd-flow-expr.ypp"
                                                     {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->flags.detection_updated.load() != true
        ));
        _NDFP_debugf(
            "Detection updated != true? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2683 "nd-flow-expr.cpp"
    break;

  case 116: /* expr_detection_updated: FLOW_DETECTION_UPDATED CMP_NOTEQUAL VALUE_FALSE  */
#line 703 "nd-flow-expr.ypp"
                                                      {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->flags.detection_updated.load() != false
        ));
        _NDFP_debugf(
            "Detection updated != false? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2696 "nd-flow-expr.cpp"
    break;

  case 117: /* expr_app: FLOW_APPLICATION  */
#line 714 "nd-flow-expr.ypp"
                       {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->detected_application != 0
        ));
        _NDFP_debugf("Application detected? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2707 "nd-flow-expr.cpp"
    break;

  case 118: /* expr_app: '!' FLOW_APPLICATION  */
#line 720 "nd-flow-expr.ypp"
                           {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->detected_application == 0
        ));
        _NDFP_debugf(
            "Application not detected? %s\n", (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2720 "nd-flow-expr.cpp"
    break;

  case 121: /* expr_app_id: FLOW_APPLICATION CMP_EQUAL VALUE_NUMBER  */
#line 732 "nd-flow-expr.ypp"
                                              {
        _NDFP_result = ((yyval.bool_result) = false);
        if ((yyvsp[0].ul_number) == _NDFP_flow->detected_application)
            _NDFP_result = ((yyval.bool_result) = true);

        _NDFP_debugf(
            "Application ID == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2734 "nd-flow-expr.cpp"
    break;

  case 122: /* expr_app_id: FLOW_APPLICATION CMP_NOTEQUAL VALUE_NUMBER  */
#line 741 "nd-flow-expr.ypp"
                                                 {
        _NDFP_result = ((yyval.bool_result) = true);
        if ((yyvsp[0].ul_number) == _NDFP_flow->detected_application)
            _NDFP_result = ((yyval.bool_result) = false);

        _NDFP_debugf(
            "Application ID != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2748 "nd-flow-expr.cpp"
    break;

  case 123: /* expr_app_name: FLOW_APPLICATION CMP_EQUAL VALUE_NAME  */
#line 753 "nd-flow-expr.ypp"
                                            {
        _NDFP_result = ((yyval.bool_result) = false);
        if (! _NDFP_flow->detected_application_name.empty()) {

            size_t p;
            string search((yyvsp[0].string));
            string app(_NDFP_flow->detected_application_name);

            while ((p = search.find_first_of("'")) != string::npos)
                search.erase(p, 1);

            if (strncasecmp(
                app.c_str(), search.c_str(), _NDFP_MAX_NAMELEN) == 0) {
                _NDFP_result = ((yyval.bool_result) = true);
            }
            else if ((p = app.find_first_of(".")) != string::npos && strncasecmp(
                app.substr(p + 1).c_str(), search.c_str(), _NDFP_MAX_NAMELEN) == 0) {
                _NDFP_result = ((yyval.bool_result) = true);
            }
        }

        _NDFP_debugf(
            "Application name == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2778 "nd-flow-expr.cpp"
    break;

  case 124: /* expr_app_name: FLOW_APPLICATION CMP_NOTEQUAL VALUE_NAME  */
#line 778 "nd-flow-expr.ypp"
                                               {
        _NDFP_result = ((yyval.bool_result) = true);
        if (! _NDFP_flow->detected_application_name.empty()) {

            size_t p;
            string search((yyvsp[0].string));
            string app(_NDFP_flow->detected_application_name);

            while ((p = search.find_first_of("'")) != string::npos)
                search.erase(p, 1);

            if (strncasecmp(
                app.c_str(), search.c_str(), _NDFP_MAX_NAMELEN) == 0) {
                _NDFP_result = ((yyval.bool_result) = false);
            }
            else if ((p = app.find_first_of(".")) != string::npos && strncasecmp(
                app.substr(p + 1).c_str(), search.c_str(), _NDFP_MAX_NAMELEN) == 0) {
                _NDFP_result = ((yyval.bool_result) = false);
            }
        }

        _NDFP_debugf(
            "Application name != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no"
        );
    }
#line 2808 "nd-flow-expr.cpp"
    break;

  case 125: /* expr_category: FLOW_CATEGORY CMP_EQUAL VALUE_NAME  */
#line 806 "nd-flow-expr.ypp"
                                         {
        size_t p;
        string category((yyvsp[0].string));

        while ((p = category.find_first_of("'")) != string::npos)
            category.erase(p, 1);

        _NDFP_result = (
            (yyval.bool_result) = (
                _NDFP_categories.LookupTag(
                    ndCAT_TYPE_APP, category) == _NDFP_flow->category.application
            )
        );

        if (! _NDFP_result) {
            _NDFP_result = (
                (yyval.bool_result) = (
                    _NDFP_categories.LookupTag(
                        ndCAT_TYPE_APP, category) == _NDFP_flow->category.domain
                )
            );
        }

        _NDFP_debugf("App/domain category == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2838 "nd-flow-expr.cpp"
    break;

  case 126: /* expr_category: FLOW_CATEGORY CMP_NOTEQUAL VALUE_NAME  */
#line 831 "nd-flow-expr.ypp"
                                            {
        size_t p;
        string category((yyvsp[0].string));

        while ((p = category.find_first_of("'")) != string::npos)
            category.erase(p, 1);

        _NDFP_result = (
            (yyval.bool_result) = (
                _NDFP_categories.LookupTag(
                    ndCAT_TYPE_APP, category) != _NDFP_flow->category.application
            )
        );

        if (! _NDFP_result) {
            _NDFP_result = (
                (yyval.bool_result) = (
                    _NDFP_categories.LookupTag(
                        ndCAT_TYPE_APP, category) != _NDFP_flow->category.domain
                )
            );
        }

        _NDFP_debugf("App/domain category != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 2868 "nd-flow-expr.cpp"
    break;

  case 127: /* expr_risks: FLOW_RISKS  */
#line 859 "nd-flow-expr.ypp"
                 {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->risks.size() != 0));
        _NDFP_debugf("Risks detected? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2877 "nd-flow-expr.cpp"
    break;

  case 128: /* expr_risks: '!' FLOW_RISKS  */
#line 863 "nd-flow-expr.ypp"
                     {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->risks.size() == 0));
        _NDFP_debugf("Risks not detected? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2886 "nd-flow-expr.cpp"
    break;

  case 129: /* expr_risks: FLOW_RISKS CMP_EQUAL VALUE_NAME  */
#line 867 "nd-flow-expr.ypp"
                                      {
        size_t p;
        string risk((yyvsp[0].string));

        while ((p = risk.find_first_of("'")) != string::npos)
            risk.erase(p, 1);

        nd_risk_id_t id = nd_risk_lookup(risk);

        _NDFP_result = false;
        for (auto &i : _NDFP_flow->risks) {
            if (i != id) continue;
            _NDFP_result = true;
            break;
        }

        _NDFP_debugf("Risks == %s %s\n", (yyvsp[0].string), risk.c_str(), (_NDFP_result) ? "yes" : "no");
    }
#line 2909 "nd-flow-expr.cpp"
    break;

  case 130: /* expr_risks: FLOW_RISKS CMP_NOTEQUAL VALUE_NAME  */
#line 885 "nd-flow-expr.ypp"
                                         {
        size_t p;
        string risk((yyvsp[0].string));

        while ((p = risk.find_first_of("'")) != string::npos)
            risk.erase(p, 1);

        nd_risk_id_t id = nd_risk_lookup(risk);

        _NDFP_result = false;
        for (auto &i : _NDFP_flow->risks) {
            if (i != id) continue;
            _NDFP_result = true;
            break;
        }

        _NDFP_result = !_NDFP_result;
        _NDFP_debugf("Risks != %s %s\n", (yyvsp[0].string), risk.c_str(), (_NDFP_result) ? "yes" : "no");
    }
#line 2933 "nd-flow-expr.cpp"
    break;

  case 131: /* expr_ndpi_risk_score: FLOW_NDPI_RISK_SCORE  */
#line 907 "nd-flow-expr.ypp"
                           {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score != 0));
        _NDFP_debugf("nDPI risk score is true? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2942 "nd-flow-expr.cpp"
    break;

  case 132: /* expr_ndpi_risk_score: '!' FLOW_NDPI_RISK_SCORE  */
#line 911 "nd-flow-expr.ypp"
                               {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score == 0));
        _NDFP_debugf("nDPI risk score is false? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 2951 "nd-flow-expr.cpp"
    break;

  case 133: /* expr_ndpi_risk_score: FLOW_NDPI_RISK_SCORE CMP_EQUAL VALUE_NUMBER  */
#line 915 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score == (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk score == %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2960 "nd-flow-expr.cpp"
    break;

  case 134: /* expr_ndpi_risk_score: FLOW_NDPI_RISK_SCORE CMP_NOTEQUAL VALUE_NUMBER  */
#line 919 "nd-flow-expr.ypp"
                                                     {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score != (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk score != %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2969 "nd-flow-expr.cpp"
    break;

  case 135: /* expr_ndpi_risk_score: FLOW_NDPI_RISK_SCORE CMP_GTHANEQUAL VALUE_NUMBER  */
#line 923 "nd-flow-expr.ypp"
                                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score >= (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk score >= %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2978 "nd-flow-expr.cpp"
    break;

  case 136: /* expr_ndpi_risk_score: FLOW_NDPI_RISK_SCORE CMP_LTHANEQUAL VALUE_NUMBER  */
#line 927 "nd-flow-expr.ypp"
                                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score <= (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk score <= %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2987 "nd-flow-expr.cpp"
    break;

  case 137: /* expr_ndpi_risk_score: FLOW_NDPI_RISK_SCORE '>' VALUE_NUMBER  */
#line 931 "nd-flow-expr.ypp"
                                            {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score > (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk score > %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 2996 "nd-flow-expr.cpp"
    break;

  case 138: /* expr_ndpi_risk_score: FLOW_NDPI_RISK_SCORE '<' VALUE_NUMBER  */
#line 935 "nd-flow-expr.ypp"
                                            {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score < (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk score > %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3005 "nd-flow-expr.cpp"
    break;

  case 139: /* expr_ndpi_risk_score_client: FLOW_NDPI_RISK_SCORE_CLIENT  */
#line 942 "nd-flow-expr.ypp"
                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_client != 0));
        _NDFP_debugf("nDPI risk client score is true? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3014 "nd-flow-expr.cpp"
    break;

  case 140: /* expr_ndpi_risk_score_client: '!' FLOW_NDPI_RISK_SCORE_CLIENT  */
#line 946 "nd-flow-expr.ypp"
                                      {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_client == 0));
        _NDFP_debugf("nDPI risk client score is false? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3023 "nd-flow-expr.cpp"
    break;

  case 141: /* expr_ndpi_risk_score_client: FLOW_NDPI_RISK_SCORE_CLIENT CMP_EQUAL VALUE_NUMBER  */
#line 950 "nd-flow-expr.ypp"
                                                         {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_client == (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk client score == %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3032 "nd-flow-expr.cpp"
    break;

  case 142: /* expr_ndpi_risk_score_client: FLOW_NDPI_RISK_SCORE_CLIENT CMP_NOTEQUAL VALUE_NUMBER  */
#line 954 "nd-flow-expr.ypp"
                                                            {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_client != (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk client score != %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3041 "nd-flow-expr.cpp"
    break;

  case 143: /* expr_ndpi_risk_score_client: FLOW_NDPI_RISK_SCORE_CLIENT CMP_GTHANEQUAL VALUE_NUMBER  */
#line 958 "nd-flow-expr.ypp"
                                                              {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_client >= (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk client score >= %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3050 "nd-flow-expr.cpp"
    break;

  case 144: /* expr_ndpi_risk_score_client: FLOW_NDPI_RISK_SCORE_CLIENT CMP_LTHANEQUAL VALUE_NUMBER  */
#line 962 "nd-flow-expr.ypp"
                                                              {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_client <= (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk client score <= %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3059 "nd-flow-expr.cpp"
    break;

  case 145: /* expr_ndpi_risk_score_client: FLOW_NDPI_RISK_SCORE_CLIENT '>' VALUE_NUMBER  */
#line 966 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_client > (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk client score > %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3068 "nd-flow-expr.cpp"
    break;

  case 146: /* expr_ndpi_risk_score_client: FLOW_NDPI_RISK_SCORE_CLIENT '<' VALUE_NUMBER  */
#line 970 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_client < (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk client score > %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3077 "nd-flow-expr.cpp"
    break;

  case 147: /* expr_ndpi_risk_score_server: FLOW_NDPI_RISK_SCORE_SERVER  */
#line 977 "nd-flow-expr.ypp"
                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_server != 0));
        _NDFP_debugf("nDPI risk server score is true? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3086 "nd-flow-expr.cpp"
    break;

  case 148: /* expr_ndpi_risk_score_server: '!' FLOW_NDPI_RISK_SCORE_SERVER  */
#line 981 "nd-flow-expr.ypp"
                                      {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_server == 0));
        _NDFP_debugf("nDPI risk server score is false? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3095 "nd-flow-expr.cpp"
    break;

  case 149: /* expr_ndpi_risk_score_server: FLOW_NDPI_RISK_SCORE_SERVER CMP_EQUAL VALUE_NUMBER  */
#line 985 "nd-flow-expr.ypp"
                                                         {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_server == (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk server score == %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3104 "nd-flow-expr.cpp"
    break;

  case 150: /* expr_ndpi_risk_score_server: FLOW_NDPI_RISK_SCORE_SERVER CMP_NOTEQUAL VALUE_NUMBER  */
#line 989 "nd-flow-expr.ypp"
                                                            {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_server != (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk server score != %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3113 "nd-flow-expr.cpp"
    break;

  case 151: /* expr_ndpi_risk_score_server: FLOW_NDPI_RISK_SCORE_SERVER CMP_GTHANEQUAL VALUE_NUMBER  */
#line 993 "nd-flow-expr.ypp"
                                                              {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_server >= (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk server score >= %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3122 "nd-flow-expr.cpp"
    break;

  case 152: /* expr_ndpi_risk_score_server: FLOW_NDPI_RISK_SCORE_SERVER CMP_LTHANEQUAL VALUE_NUMBER  */
#line 997 "nd-flow-expr.ypp"
                                                              {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_server <= (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk server score <= %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3131 "nd-flow-expr.cpp"
    break;

  case 153: /* expr_ndpi_risk_score_server: FLOW_NDPI_RISK_SCORE_SERVER '>' VALUE_NUMBER  */
#line 1001 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_server > (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk server score > %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3140 "nd-flow-expr.cpp"
    break;

  case 154: /* expr_ndpi_risk_score_server: FLOW_NDPI_RISK_SCORE_SERVER '<' VALUE_NUMBER  */
#line 1005 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ndpi_risk_score_server < (yyvsp[0].ul_number)));
        _NDFP_debugf("nDPI risk server score > %lu %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3149 "nd-flow-expr.cpp"
    break;

  case 155: /* expr_app_category: FLOW_APPLICATION_CATEGORY CMP_EQUAL VALUE_NAME  */
#line 1012 "nd-flow-expr.ypp"
                                                     {
        size_t p;
        string category((yyvsp[0].string));

        while ((p = category.find_first_of("'")) != string::npos)
            category.erase(p, 1);

        _NDFP_result = (
            (yyval.bool_result) = (
                _NDFP_categories.LookupTag(
                    ndCAT_TYPE_APP, category) == _NDFP_flow->category.application
            )
        );

        _NDFP_debugf("App category == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3170 "nd-flow-expr.cpp"
    break;

  case 156: /* expr_app_category: FLOW_APPLICATION_CATEGORY CMP_NOTEQUAL VALUE_NAME  */
#line 1028 "nd-flow-expr.ypp"
                                                        {
        size_t p;
        string category((yyvsp[0].string));

        while ((p = category.find_first_of("'")) != string::npos)
            category.erase(p, 1);

        _NDFP_result = (
            (yyval.bool_result) = (
                _NDFP_categories.LookupTag(
                    ndCAT_TYPE_APP, category) != _NDFP_flow->category.application
            )
        );

        _NDFP_debugf("App category != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3191 "nd-flow-expr.cpp"
    break;

  case 157: /* expr_domain_category: FLOW_DOMAIN_CATEGORY CMP_EQUAL VALUE_NAME  */
#line 1047 "nd-flow-expr.ypp"
                                                {
        size_t p;
        string category((yyvsp[0].string));

        while ((p = category.find_first_of("'")) != string::npos)
            category.erase(p, 1);

        _NDFP_result = (
            (yyval.bool_result) = (
                _NDFP_categories.LookupTag(
                    ndCAT_TYPE_APP, category) == _NDFP_flow->category.domain
            )
        );

        _NDFP_debugf("Domain category == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3212 "nd-flow-expr.cpp"
    break;

  case 158: /* expr_domain_category: FLOW_DOMAIN_CATEGORY CMP_NOTEQUAL VALUE_NAME  */
#line 1063 "nd-flow-expr.ypp"
                                                   {
        size_t p;
        string category((yyvsp[0].string));

        while ((p = category.find_first_of("'")) != string::npos)
            category.erase(p, 1);

        _NDFP_result = (
            (yyval.bool_result) = (
                _NDFP_categories.LookupTag(
                    ndCAT_TYPE_APP, category) != _NDFP_flow->category.domain
            )
        );

        _NDFP_debugf("Domain category != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3233 "nd-flow-expr.cpp"
    break;

  case 159: /* expr_proto: FLOW_PROTOCOL  */
#line 1082 "nd-flow-expr.ypp"
                    {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->detected_protocol != 0
        ));
        _NDFP_debugf("Protocol detected? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3244 "nd-flow-expr.cpp"
    break;

  case 160: /* expr_proto: '!' FLOW_PROTOCOL  */
#line 1088 "nd-flow-expr.ypp"
                        {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->detected_protocol == 0
        ));
        _NDFP_debugf("Protocol not detected? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3255 "nd-flow-expr.cpp"
    break;

  case 163: /* expr_proto_id: FLOW_PROTOCOL CMP_EQUAL VALUE_NUMBER  */
#line 1098 "nd-flow-expr.ypp"
                                           {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->detected_protocol == (yyvsp[0].ul_number)
        ));
        _NDFP_debugf("Protocol ID == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3266 "nd-flow-expr.cpp"
    break;

  case 164: /* expr_proto_id: FLOW_PROTOCOL CMP_NOTEQUAL VALUE_NUMBER  */
#line 1104 "nd-flow-expr.ypp"
                                              {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->detected_protocol != (yyvsp[0].ul_number)
        ));
        _NDFP_debugf("Protocol ID != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3277 "nd-flow-expr.cpp"
    break;

  case 165: /* expr_proto_name: FLOW_PROTOCOL CMP_EQUAL VALUE_NAME  */
#line 1113 "nd-flow-expr.ypp"
                                         {
        _NDFP_result = ((yyval.bool_result) = false);
        if (! _NDFP_flow->detected_protocol_name.empty()) {

            size_t p;
            string search((yyvsp[0].string));

            while ((p = search.find_first_of("'")) != string::npos)
                search.erase(p, 1);

            _NDFP_result = ((yyval.bool_result) = (strncasecmp(
                _NDFP_flow->detected_protocol_name.c_str(), search.c_str(), _NDFP_MAX_NAMELEN
            ) == 0));
        }

        _NDFP_debugf(
            "Protocol name == %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no"
        );
    }
#line 3301 "nd-flow-expr.cpp"
    break;

  case 166: /* expr_proto_name: FLOW_PROTOCOL CMP_NOTEQUAL VALUE_NAME  */
#line 1132 "nd-flow-expr.ypp"
                                            {
        _NDFP_result = ((yyval.bool_result) = true);
        if (! _NDFP_flow->detected_protocol_name.empty()) {

            size_t p;
            string search((yyvsp[0].string));

            while ((p = search.find_first_of("'")) != string::npos)
                search.erase(p, 1);

            _NDFP_result = ((yyval.bool_result) = (strncasecmp(
                _NDFP_flow->detected_protocol_name.c_str(), search.c_str(), _NDFP_MAX_NAMELEN
            )));
        }
        _NDFP_debugf(
            "Protocol name != %s? %s\n", (yyvsp[0].string), (_NDFP_result) ? "yes" : "no"
        );
    }
#line 3324 "nd-flow-expr.cpp"
    break;

  case 167: /* expr_proto_category: FLOW_PROTOCOL_CATEGORY CMP_EQUAL VALUE_NAME  */
#line 1153 "nd-flow-expr.ypp"
                                                  {
        size_t p;
        string category((yyvsp[0].string));

        while ((p = category.find_first_of("'")) != string::npos)
            category.erase(p, 1);

        _NDFP_result = (
            (yyval.bool_result) = (
                _NDFP_categories.LookupTag(
                    ndCAT_TYPE_PROTO, category) == _NDFP_flow->category.protocol
            )
        );

        _NDFP_debugf("Protocol category == %s? %s\n",
            (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3346 "nd-flow-expr.cpp"
    break;

  case 168: /* expr_proto_category: FLOW_PROTOCOL_CATEGORY CMP_NOTEQUAL VALUE_NAME  */
#line 1170 "nd-flow-expr.ypp"
                                                     {
        size_t p;
        string category((yyvsp[0].string));

        while ((p = category.find_first_of("'")) != string::npos)
            category.erase(p, 1);

        _NDFP_result = (
            (yyval.bool_result) = (
                _NDFP_categories.LookupTag(
                    ndCAT_TYPE_PROTO, category) != _NDFP_flow->category.protocol
            )
        );

        _NDFP_debugf("Protocol category != %s? %s\n",
            (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3368 "nd-flow-expr.cpp"
    break;

  case 169: /* expr_detected_hostname: FLOW_DETECTED_HOSTNAME  */
#line 1190 "nd-flow-expr.ypp"
                             {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->host_server_name[0] != '\0'
        ));
        _NDFP_debugf("Application hostname detected? %s\n",
            (_NDFP_result) ? "yes" : "no");
    }
#line 3380 "nd-flow-expr.cpp"
    break;

  case 170: /* expr_detected_hostname: '!' FLOW_DETECTED_HOSTNAME  */
#line 1197 "nd-flow-expr.ypp"
                                 {
        _NDFP_result = ((yyval.bool_result) = (
            _NDFP_flow->host_server_name[0] == '\0'
        ));
        _NDFP_debugf("Application hostname not detected? %s\n",
            (_NDFP_result) ? "yes" : "no");
    }
#line 3392 "nd-flow-expr.cpp"
    break;

  case 171: /* expr_detected_hostname: FLOW_DETECTED_HOSTNAME CMP_EQUAL VALUE_NAME  */
#line 1204 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = false);
        if (_NDFP_flow->host_server_name[0] != '\0') {
            size_t p;
            string search((yyvsp[0].string));

            while ((p = search.find_first_of("'")) != string::npos)
                search.erase(p, 1);

            if (strncasecmp(search.c_str(),
                _NDFP_flow->host_server_name.c_str(), _NDFP_MAX_NAMELEN) == 0) {
                _NDFP_result = ((yyval.bool_result) = true);
            }
        }

        _NDFP_debugf("Detected hostname == %s? %s\n",
            (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3415 "nd-flow-expr.cpp"
    break;

  case 172: /* expr_detected_hostname: FLOW_DETECTED_HOSTNAME CMP_NOTEQUAL VALUE_NAME  */
#line 1222 "nd-flow-expr.ypp"
                                                     {
        _NDFP_result = ((yyval.bool_result) = true);
        if (_NDFP_flow->host_server_name[0] != '\0') {
            size_t p;
            string search((yyvsp[0].string));

            while ((p = search.find_first_of("'")) != string::npos)
                search.erase(p, 1);

            if (strncasecmp(search.c_str(),
                _NDFP_flow->host_server_name.c_str(), _NDFP_MAX_NAMELEN) == 0) {
                _NDFP_result = ((yyval.bool_result) = false);
            }
        }

        _NDFP_debugf("Detected hostname != %s? %s\n",
            (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3438 "nd-flow-expr.cpp"
    break;

  case 173: /* expr_detected_hostname: FLOW_DETECTED_HOSTNAME CMP_EQUAL VALUE_REGEX  */
#line 1240 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = false);
#if HAVE_WORKING_REGEX
        if (_NDFP_flow->host_server_name[0] != '\0') {
            size_t p;
            string rx((yyvsp[0].string));

            while ((p = rx.find_first_of("'")) != string::npos)
                rx.erase(p, 1);
            while ((p = rx.find_first_of(":")) != string::npos)
                rx.erase(0, p);

            try {
                // XXX: Unfortunately we're going to compile this everytime...
                regex re(
                    rx,
                    regex_constants::icase |
                    regex_constants::optimize |
                    regex_constants::extended
                );

                cmatch match;
                _NDFP_result = ((yyval.bool_result) = regex_search(
                    _NDFP_flow->host_server_name.c_str(), match, re
                ));
            } catch (regex_error &e) {
                nd_printf("WARNING: Error compiling regex: %s: %d\n",
                    rx.c_str(), e.code());
            }
        }

        _NDFP_debugf("Detected hostname == %s? %s\n",
            (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_debugf("Detected hostname == %s? Broken regex support.\n", (yyvsp[0].string));
#endif
    }
#line 3480 "nd-flow-expr.cpp"
    break;

  case 174: /* expr_detected_hostname: FLOW_DETECTED_HOSTNAME CMP_NOTEQUAL VALUE_REGEX  */
#line 1277 "nd-flow-expr.ypp"
                                                      {
        _NDFP_result = ((yyval.bool_result) = true);

        _NDFP_debugf("Detected hostname != %s? %s\n",
            (yyvsp[0].string), (_NDFP_result) ? "yes" : "no");
    }
#line 3491 "nd-flow-expr.cpp"
    break;

  case 175: /* expr_fwmark: FLOW_CT_MARK  */
#line 1286 "nd-flow-expr.ypp"
                   {
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ct_mark != 0));
        _NDFP_debugf("FWMARK set? %s\n", (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_result = ((yyval.bool_result) = (false));
#endif
    }
#line 3504 "nd-flow-expr.cpp"
    break;

  case 176: /* expr_fwmark: '!' FLOW_CT_MARK  */
#line 1294 "nd-flow-expr.ypp"
                       {
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ct_mark == 0));
        _NDFP_debugf("FWMARK not set? %s\n", (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_result = ((yyval.bool_result) = (false));
#endif
    }
#line 3517 "nd-flow-expr.cpp"
    break;

  case 177: /* expr_fwmark: FLOW_CT_MARK CMP_EQUAL VALUE_NUMBER  */
#line 1302 "nd-flow-expr.ypp"
                                          {
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ct_mark == (yyvsp[0].ul_number)));
        _NDFP_debugf("FWMARK == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_result = ((yyval.bool_result) = (false));
#endif
    }
#line 3530 "nd-flow-expr.cpp"
    break;

  case 178: /* expr_fwmark: FLOW_CT_MARK CMP_NOTEQUAL VALUE_NUMBER  */
#line 1310 "nd-flow-expr.ypp"
                                             {
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ct_mark != (yyvsp[0].ul_number)));
        _NDFP_debugf("FWMARK != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_result = ((yyval.bool_result) = (false));
#endif
    }
#line 3543 "nd-flow-expr.cpp"
    break;

  case 179: /* expr_fwmark: FLOW_CT_MARK CMP_GTHANEQUAL VALUE_NUMBER  */
#line 1318 "nd-flow-expr.ypp"
                                               {
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ct_mark >= (yyvsp[0].ul_number)));
        _NDFP_debugf("FWMARK >= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_result = ((yyval.bool_result) = (false));
#endif
    }
#line 3556 "nd-flow-expr.cpp"
    break;

  case 180: /* expr_fwmark: FLOW_CT_MARK CMP_LTHANEQUAL VALUE_NUMBER  */
#line 1326 "nd-flow-expr.ypp"
                                               {
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ct_mark <= (yyvsp[0].ul_number)));
        _NDFP_debugf("FWMARK <= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_result = ((yyval.bool_result) = (false));
#endif
    }
#line 3569 "nd-flow-expr.cpp"
    break;

  case 181: /* expr_fwmark: FLOW_CT_MARK '>' VALUE_NUMBER  */
#line 1334 "nd-flow-expr.ypp"
                                    {
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ct_mark > (yyvsp[0].ul_number)));
        _NDFP_debugf("FWMARK > %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_result = ((yyval.bool_result) = (false));
#endif
    }
#line 3582 "nd-flow-expr.cpp"
    break;

  case 182: /* expr_fwmark: FLOW_CT_MARK '<' VALUE_NUMBER  */
#line 1342 "nd-flow-expr.ypp"
                                    {
#if defined(_ND_USE_CONNTRACK) && defined(_ND_WITH_CONNTRACK_MDATA)
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ct_mark < (yyvsp[0].ul_number)));
        _NDFP_debugf("FWMARK < %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
#else
        _NDFP_result = ((yyval.bool_result) = (false));
#endif
    }
#line 3595 "nd-flow-expr.cpp"
    break;

  case 183: /* expr_ssl_version: FLOW_SSL_VERSION  */
#line 1353 "nd-flow-expr.ypp"
                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.version != 0));
        _NDFP_debugf("SSL version set? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3604 "nd-flow-expr.cpp"
    break;

  case 184: /* expr_ssl_version: '!' FLOW_SSL_VERSION  */
#line 1357 "nd-flow-expr.ypp"
                           {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.version == 0));
        _NDFP_debugf("SSL version not set? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3613 "nd-flow-expr.cpp"
    break;

  case 185: /* expr_ssl_version: FLOW_SSL_VERSION CMP_EQUAL VALUE_NUMBER  */
#line 1361 "nd-flow-expr.ypp"
                                              {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.version == (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL version == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3622 "nd-flow-expr.cpp"
    break;

  case 186: /* expr_ssl_version: FLOW_SSL_VERSION CMP_NOTEQUAL VALUE_NUMBER  */
#line 1365 "nd-flow-expr.ypp"
                                                 {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.version != (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL version != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3631 "nd-flow-expr.cpp"
    break;

  case 187: /* expr_ssl_version: FLOW_SSL_VERSION CMP_GTHANEQUAL VALUE_NUMBER  */
#line 1369 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.version >= (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL version >= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3640 "nd-flow-expr.cpp"
    break;

  case 188: /* expr_ssl_version: FLOW_SSL_VERSION CMP_LTHANEQUAL VALUE_NUMBER  */
#line 1373 "nd-flow-expr.ypp"
                                                   {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.version <= (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL version <= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3649 "nd-flow-expr.cpp"
    break;

  case 189: /* expr_ssl_version: FLOW_SSL_VERSION '>' VALUE_NUMBER  */
#line 1377 "nd-flow-expr.ypp"
                                        {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.version > (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL version > %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3658 "nd-flow-expr.cpp"
    break;

  case 190: /* expr_ssl_version: FLOW_SSL_VERSION '<' VALUE_NUMBER  */
#line 1381 "nd-flow-expr.ypp"
                                        {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.version < (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL version < %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3667 "nd-flow-expr.cpp"
    break;

  case 191: /* expr_ssl_cipher: FLOW_SSL_CIPHER  */
#line 1388 "nd-flow-expr.ypp"
                      {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.cipher_suite != 0));
        _NDFP_debugf("SSL cipher suite set? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3676 "nd-flow-expr.cpp"
    break;

  case 192: /* expr_ssl_cipher: '!' FLOW_SSL_CIPHER  */
#line 1392 "nd-flow-expr.ypp"
                          {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.cipher_suite == 0));
        _NDFP_debugf("SSL cipher suite not set? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3685 "nd-flow-expr.cpp"
    break;

  case 193: /* expr_ssl_cipher: FLOW_SSL_CIPHER CMP_EQUAL VALUE_NUMBER  */
#line 1396 "nd-flow-expr.ypp"
                                             {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.cipher_suite == (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL cipher suite == %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3694 "nd-flow-expr.cpp"
    break;

  case 194: /* expr_ssl_cipher: FLOW_SSL_CIPHER CMP_NOTEQUAL VALUE_NUMBER  */
#line 1400 "nd-flow-expr.ypp"
                                                {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.cipher_suite != (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL cipher suite != %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3703 "nd-flow-expr.cpp"
    break;

  case 195: /* expr_ssl_cipher: FLOW_SSL_CIPHER CMP_GTHANEQUAL VALUE_NUMBER  */
#line 1404 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.cipher_suite >= (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL cipher suite >= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3712 "nd-flow-expr.cpp"
    break;

  case 196: /* expr_ssl_cipher: FLOW_SSL_CIPHER CMP_LTHANEQUAL VALUE_NUMBER  */
#line 1408 "nd-flow-expr.ypp"
                                                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.cipher_suite <= (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL cipher suite <= %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3721 "nd-flow-expr.cpp"
    break;

  case 197: /* expr_ssl_cipher: FLOW_SSL_CIPHER '>' VALUE_NUMBER  */
#line 1412 "nd-flow-expr.ypp"
                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.cipher_suite > (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL cipher suite > %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3730 "nd-flow-expr.cpp"
    break;

  case 198: /* expr_ssl_cipher: FLOW_SSL_CIPHER '<' VALUE_NUMBER  */
#line 1416 "nd-flow-expr.ypp"
                                       {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_flow->ssl.cipher_suite < (yyvsp[0].ul_number)));
        _NDFP_debugf("SSL cipher suite < %lu? %s\n", (yyvsp[0].ul_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3739 "nd-flow-expr.cpp"
    break;

  case 199: /* expr_origin: FLOW_ORIGIN  */
#line 1423 "nd-flow-expr.ypp"
                  {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_origin != _NDFP_ORIGIN_UNKNOWN));
        _NDFP_debugf("Flow origin known? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3748 "nd-flow-expr.cpp"
    break;

  case 200: /* expr_origin: '!' FLOW_ORIGIN  */
#line 1427 "nd-flow-expr.ypp"
                      {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_origin == _NDFP_ORIGIN_UNKNOWN));
        _NDFP_debugf("Flow origin unknown? %s\n", (_NDFP_result) ? "yes" : "no");
    }
#line 3757 "nd-flow-expr.cpp"
    break;

  case 201: /* expr_origin: FLOW_ORIGIN CMP_EQUAL value_origin_type  */
#line 1431 "nd-flow-expr.ypp"
                                              {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_origin == (yyvsp[0].us_number)));
        _NDFP_debugf("Flow origin == %hu? %s\n", (yyvsp[0].us_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3766 "nd-flow-expr.cpp"
    break;

  case 202: /* expr_origin: FLOW_ORIGIN CMP_NOTEQUAL value_origin_type  */
#line 1435 "nd-flow-expr.ypp"
                                                 {
        _NDFP_result = ((yyval.bool_result) = (_NDFP_origin != (yyvsp[0].us_number)));
        _NDFP_debugf("Flow origin != %hu? %s\n", (yyvsp[0].us_number), (_NDFP_result) ? "yes" : "no");
    }
#line 3775 "nd-flow-expr.cpp"
    break;

  case 203: /* value_origin_type: FLOW_ORIGIN_LOCAL  */
#line 1442 "nd-flow-expr.ypp"
                        { (yyval.us_number) = (yyvsp[0].us_number); }
#line 3781 "nd-flow-expr.cpp"
    break;

  case 204: /* value_origin_type: FLOW_ORIGIN_OTHER  */
#line 1443 "nd-flow-expr.ypp"
                        { (yyval.us_number) = (yyvsp[0].us_number); }
#line 3787 "nd-flow-expr.cpp"
    break;

  case 205: /* value_origin_type: FLOW_ORIGIN_UNKNOWN  */
#line 1444 "nd-flow-expr.ypp"
                          { (yyval.us_number) = (yyvsp[0].us_number); }
#line 3793 "nd-flow-expr.cpp"
    break;


#line 3797 "nd-flow-expr.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (&yylloc, scanner, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1446 "nd-flow-expr.ypp"


ndFlowParser::ndFlowParser()
    : flow(NULL), local_mac{}, other_mac{},
    local_ip(NULL), other_ip(NULL), local_port(0), other_port(0),
    origin(0), expr_result(false), scanner(NULL)
{
    yyscan_t scanner;
    yylex_init_extra((void *)this, &scanner);

    if (scanner == NULL)
        throw string("Error creating scanner context");

    this->scanner = (void *)scanner;
}

ndFlowParser::~ndFlowParser()
{
    yylex_destroy((yyscan_t)scanner);
}

bool ndFlowParser::Parse(nd_flow_ptr const& flow, const string &expr)
{
    this->flow = flow;
    expr_result = false;

    switch (flow->lower_map) {
    case ndFlow::LOWER_LOCAL:
        local_mac = flow->lower_mac.GetString().c_str();
        other_mac = flow->upper_mac.GetString().c_str();

        local_ip = &flow->lower_addr;
        other_ip = &flow->upper_addr;

        local_port = flow->lower_addr.GetPort();
        other_port = flow->upper_addr.GetPort();

        switch (flow->origin) {
        case ndFlow::ORIGIN_LOWER:
            origin = _NDFP_ORIGIN_LOCAL;
            break;
        case ndFlow::ORIGIN_UPPER:
            origin = _NDFP_ORIGIN_OTHER;
            break;
        default:
            origin = _NDFP_ORIGIN_UNKNOWN;
        }
        break;
    case ndFlow::LOWER_OTHER:
        local_mac = flow->upper_mac.GetString().c_str();
        other_mac = flow->lower_mac.GetString().c_str();

        local_ip = &flow->upper_addr;
        other_ip = &flow->lower_addr;

        local_port = flow->upper_addr.GetPort();
        other_port = flow->lower_addr.GetPort();

        switch (flow->origin) {
        case ndFlow::ORIGIN_LOWER:
            origin = _NDFP_ORIGIN_OTHER;
            break;
        case ndFlow::ORIGIN_UPPER:
            origin = _NDFP_ORIGIN_LOCAL;
            break;
        default:
            origin = _NDFP_ORIGIN_UNKNOWN;
        }
        break;
    default:
        //nd_dprintf("Bad lower map: %u\n", flow->lower_map);
        this->flow.reset();
        return false;
    }

    YY_BUFFER_STATE flow_expr_scan_buffer;
    flow_expr_scan_buffer = yy_scan_bytes(
        expr.c_str(), expr.size(), (yyscan_t)scanner
    );

    if (flow_expr_scan_buffer == NULL)
        throw string("Error allocating flow expression scan buffer");

    yy_switch_to_buffer(flow_expr_scan_buffer, (yyscan_t)scanner);

    int rc = 0;

    try {
        rc = yyparse((yyscan_t)scanner);
    } catch (...) {
        this->flow.reset();
        yy_delete_buffer(flow_expr_scan_buffer, scanner);
        throw;
    }

    yy_delete_buffer(flow_expr_scan_buffer, scanner);

    this->flow.reset();

    return (rc == 0) ? expr_result : false;
}
