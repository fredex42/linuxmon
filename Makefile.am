CFLAGS=-O2 -pipe
AM_LDFLAGS=
LIBS=-lpqxx

bin_PROGRAMS=linuxmon
linuxmon_SOURCES=procloadavg.cpp main.cpp procstat.cpp base.cpp metrixdb.cpp dbpostgres.cpp serverparams.cpp  procfile.cpp procmeminfo.cpp \
	procmeminfo.h serverparams.h procfile.h procstat.h base.h metrixdb.h dbpostgres.h procloadavg.h config.h

linuxmonconfdir=$(sysconfdir)
linuxmonconf_DATA=linuxconf.cfg
