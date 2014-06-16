# Copyright 2013 Endless Mobile, Inc.

eosmetrics_public_installed_headers = eosmetrics/eosmetrics.h

eosmetrics_private_installed_headers = \
	eosmetrics/emtr-connection.h \
	eosmetrics/emtr-enums.h \
	eosmetrics/emtr-event-recorder.h \
	eosmetrics/emtr-event-types.h \
	eosmetrics/emtr-macros.h \
	eosmetrics/emtr-sender.h \
	eosmetrics/emtr-types.h \
	eosmetrics/emtr-util.h \
	eosmetrics/emtr-version.h \
	$(NULL)

eosmetrics_library_sources = \
	emer-event-recorder-server.c emer-event-recorder-server.h \
	eosmetrics/emtr-connection.c \
	eosmetrics/emtr-event-recorder.c \
	eosmetrics/emtr-mac.c eosmetrics/emtr-mac-private.h \
	eosmetrics/emtr-osversion.c eosmetrics/emtr-osversion-private.h \
	eosmetrics/emtr-sender.c \
	eosmetrics/emtr-util.c eosmetrics/emtr-util-private.h \
	eosmetrics/emtr-uuid.c eosmetrics/emtr-uuid-private.h \
	eosmetrics/emtr-web.c eosmetrics/emtr-web-private.h \
	shared/metrics-util.c shared/metrics-util.h \
	$(NULL)

lib_LTLIBRARIES = libeosmetrics-@EMTR_API_VERSION@.la
libeosmetrics_@EMTR_API_VERSION@_la_SOURCES = \
	$(eosmetrics_public_installed_headers) \
	$(eosmetrics_private_installed_headers) \
	$(eosmetrics_library_sources) \
	$(NULL)
# Defining G_LOG_DOMAIN allows you to run any program with
# G_MESSAGES_DEBUG=EosMetrics ./myprogram
# and turn on debug messages
libeosmetrics_@EMTR_API_VERSION@_la_CPPFLAGS = \
	@EOSMETRICS_CFLAGS@ \
	-DG_LOG_DOMAIN=\"EosMetrics\" \
	-DCOMPILING_EOS_METRICS \
	-DDATADIR=\""$(datadir)"\" \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-D_POSIX_C_SOURCE=200112L \
	$(NULL)
libeosmetrics_@EMTR_API_VERSION@_la_CFLAGS = $(AM_CFLAGS)
libeosmetrics_@EMTR_API_VERSION@_la_LIBADD = @EOSMETRICS_LIBS@
libeosmetrics_@EMTR_API_VERSION@_la_LDFLAGS = \
	-version-info @EMTR_LT_VERSION_INFO@ \
	-export-symbols-regex "^emtr_" \
	$(NULL)