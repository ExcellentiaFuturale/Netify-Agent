# Netify Agent Debian Package Automake File
# Copyright (C) 2016-2022 eGloo Incorporated
#
# This is free software, licensed under the GNU General Public License v3.

DEBFILES = changelog conffiles control debian.init debian.postinst netifyd-dev.install netifyd.dsc netifyd.install rules
DEBFILES_IN = changelog.in conffiles.in control.in debian.init.in debian.postinst.in netifyd-dev.install.in netifyd.dsc.in netifyd.install.in rules.in

BUILT_SOURCES = $(DEBFILES)
CLEANFILES = $(DEBFILES)
EXTRA_DIST = $(DEBFILES_IN)

%: %.in
	$(SED) \
		-e 's|[@]bindir@|$(bindir)|g' \
		-e 's|[@]datadir@|$(datadir)/$(PACKAGE_TARNAME)|g' \
		-e 's|[@]includedir@|$(includedir)|g' \
		-e 's|[@]libdir@|$(libdir)|g' \
		-e 's|[@]PACKAGE_BUGREPORT@|$(PACKAGE_BUGREPORT)|g' \
		-e 's|[@]PACKAGE_NAME@|$(PACKAGE_NAME)|g' \
		-e 's|[@]PACKAGE_TARNAME@|$(PACKAGE_TARNAME)|g' \
		-e 's|[@]PACKAGE_VERSION@|$(PACKAGE_VERSION)|g' \
		-e 's|[@]sbindir@|$(sbindir)|g' \
		-e 's|[@]sysconfdir@|$(sysconfdir)|g' \
		-e 's|[@]volatilestatedir@|$(volatilestatedir)|g' \
		< "$<" > "$@"
