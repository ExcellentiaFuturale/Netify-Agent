#!/bin/bash

: ${COMPILER:=gcc}
: ${VARIANT:=generic}
: ${OPTION_CONNTRACK:=enable}
: ${OPTION_NETLINK:=enable}
: ${OPTION_PLUGINS:=enable}
: ${OPTION_LIBTCMALLOC:=enable}
: ${OPTION_NFQUEUE:=enable}
: ${ENABLE_SANITIZER:=false}
: ${ENABLE_STACK_PROTECTION:=false}

: ${prefix:=/usr}
: ${exec_prefix:=${prefix}}
: ${bindir:=${prefix}/bin}
: ${sbindir:=${prefix}/sbin}
: ${sysconfdir:=/etc}
: ${datadir:=${prefix}/share}
: ${includedir:=${prefix}/include}
: ${libdir:=${prefix}/lib64}
: ${libexecdir:=${prefix}/libexec}
: ${localstatedir:=/var}
: ${sharedstatedir:=/var/lib}
: ${mandir:=${prefix}/share/man}
: ${infodir:=${prefix}/share/info}

export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig

CPPFLAGS_COMMON="-pipe -g -O1 -fexceptions -Wall"

case "x${ENABLE_SANITIZER}" in
xaddress)
  ;;
xthread)
  ;;
xfalse)
  ;;
*)
  echo "ERROR: Unsupported SANITIZER: ${ENABLE_SANITIZER}"
  exit 1
  ;;
esac

if [ "x${ENABLE_SANITIZER}" != "xfalse" ]; then
  if [ "x${COMPILER}" == "xgcc" ]; then
    echo "Overriding COMPILER to clang, sanitzer enabled."
    COMPILER=clang
  fi
  if [ "x${OPTION_LIBTCMALLOC}" == "xenable" ]; then
    echo "Disabling OPTION_LIBTCMALLOC, sanitizer enabled."
    OPTION_LIBTCMALLOC=disable
  fi
fi

if [ "x${COMPILER}" == "xgcc" ]; then
  export CC=gcc
  export CXX=g++
  CPPFLAGS_COMMON="${CPPFLAGS_COMMON} -grecord-gcc-switches"
elif [ "x${COMPILER}" == "xclang" ]; then
  export CC=clang
  export CXX=clang++
  if [ "x${ENABLE_SANITIZER}" != "xfalse" ]; then
    export LDFLAGS="-fsanitize=${ENABLE_SANITIZER}"
    CPPFLAGS_COMMON="${CPPFLAGS_COMMON} -fsanitize=${ENABLE_SANITIZER} -fno-omit-frame-pointer"
  fi
else
  echo "ERROR: Unsupported COMPILER: ${COMPILER}"
  exit 1
fi

if [ "x${ENABLE_STACK_PROTECTION}" == "xtrue" ]; then
  CPPFLAGS_COMMON="${CPPFLAGS_COMMON} -fstack-clash-protection \
    -fstack-protector-strong -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2"
fi

export CPPFLAGS="${CPPFLAGS_COMMON}"

echo "Options:"
echo " COMPILER: ${COMPILER}"
echo " VARIANT: ${VARIANT}"
echo " OPTION_CONNTRACK: ${OPTION_CONNTRACK}"
echo " OPTION_NETLINK: ${OPTION_NETLINK}"
echo " OPTION_PLUGINS: ${OPTION_PLUGINS}"
echo " OPTION_LIBTCMALLOC: ${OPTION_LIBTCMALLOC}"
echo " OPTION_NFQUEUE: ${OPTION_NFQUEUE}"
echo " ENABLE_SANITIZER: ${ENABLE_SANITIZER}"
echo " ENABLE_STACK_PROTECTION: ${ENABLE_STACK_PROTECTION}"
echo " CPPFLAGS: ${CPPFLAGS}"
echo " LDFLAGS: ${LDFLAGS}"

if [ $# -gt 0 -a "x$1" == "xhelp" ]; then exit 0; fi

case "x${VARIANT}" in
xgeneric)
  ;;
xcentos7x)
  ;;
xubuntu20x)
  ;;
*)
  echo "ERROR: Unsupported VARIANT: ${VARIANT}"
  exit 1
  ;;
esac

./configure \
    --program-prefix= \
    --prefix=${prefix} \
    --exec-prefix=${exec_prefix} \
    --bindir=${bindir} \
    --sbindir=${sbindir} \
    --sysconfdir=${sysconfdir} \
    --datadir=${datadir} \
    --includedir=${includedir} \
    --libdir=${libdir} \
    --libexecdir=${libexecdir} \
    --localstatedir=${localstatedir} \
    --sharedstatedir=${sharedstatedir} \
    --mandir=${mandir} \
    --infodir=${infodir} \
    --${OPTION_CONNTRACK}-conntrack \
    --${OPTION_NETLINK}-netlink \
    --${OPTION_PLUGINS}-plugins \
    --${OPTION_LIBTCMALLOC}-libtcmalloc \
    --${OPTION_NFQUEUE}-nfqueue \
    $@ || exit $?

cat << EOF > compile_flags.txt
-std=gnu++11
-DHAVE_CONFIG_H
-I./
-I../include/
-I./include/
-I./libs/inih/cpp/
-I./libs/ndpi/src/include/
-I./libs/gperftools/src/
EOF

exit 0
