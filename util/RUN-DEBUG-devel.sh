#!/usr/bin/env bash

set -euo pipefail

: ${NETIFYD_PREFIX:=/tmp/netify-agent}
: ${NETIFYD_OPTIONS:=-d --run-without-sources}
: ${NETIFYD_CONF:=netifyd.conf}

if [ -z "${NETIFYD_CONF}" -a -f netifyd.conf ]; then
  NETIFYD_CONF="$(pwd)/netifyd.conf"
fi

echo "Options:"
echo " NETIFYD_PREFIX: ${NETIFYD_PREFIX}"
echo " NETIFYD_OPTIONS: ${NETIFYD_OPTIONS}"

if [ ! -d "${NETIFYD_PREFIX}" ]; then
  echo "ERROR: The Netify Agent prefix path does not exist."
  exit 1
fi

echo " NETIFYD_CONF: ${NETIFYD_CONF}"

if [ ! -f "${NETIFYD_CONF}" ]; then
  echo "ERROR: The Netify Agent configuration file was not found."
  exit 1
fi

NETIFYD_SO=$(find ${NETIFYD_PREFIX} -name 'libnetifyd.so')

if [ -z "${NETIFYD_SO}" -o ! -x "${NETIFYD_PREFIX}/usr/sbin/netifyd" ]; then
  echo "ERROR: The Netify Agent is not installed under: ${NETIFYD_PREFIX}"
  exit 1
fi

export LD_LIBRARY_PATH=$(dirname ${NETIFYD_SO})
echo " LD_LIBRARY_PATH: ${LD_LIBRARY_PATH}"

SUDO=$(which sudo)

if [ -z "${SUDO}" ]; then
  echo "WARNING: sudo not found, running as current user."
  exec ${NETIFYD_PREFIX}/usr/sbin/netifyd -c ${NETIFYD_CONF} ${NETIFYD_OPTIONS} $@
else
  exec ${SUDO} LD_LIBRARY_PATH=${LD_LIBRARY_PATH} ${NETIFYD_PREFIX}/usr/sbin/netifyd -c ${NETIFYD_CONF} ${NETIFYD_OPTIONS} $@
fi

exit 0
