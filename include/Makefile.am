AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = nd-json-response-code.txt.in

netifyincludedir = $(includedir)/netifyd
netifyinclude_HEADERS = nd-base64.h nd-conntrack.h nd-detection.h nd-flow.h \
	nd-inotify.h nd-json.h nd-json-response-code.h nd-ndpi.h nd-netlink.h \
	nd-plugin.h nd-sha1.h nd-sink.h nd-socket.h nd-thread.h nd-util.h netifyd.h

BUILT_SOURCES = nd-json-response-code.h
CLEANFILES = nd-json-response-code.h

nd-json-response-code.h: nd-json-response-code.txt.in
	../util/generate-json-include.sh c-response-code >$@