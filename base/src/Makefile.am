#
# Makefile.am for core/base/src
#

ybin_PROGRAMS = y2base

y2base_SOURCES = y2base.cc

YAST2CORE =					\
	../../wfm/src/libpy2wfm.la		\
        ../../scr/src/libpy2scr.la              \
	../../liby2/src/liby2.la		\
	../../libscr/src/libscr.la		\
	../../libycp/src/libycpvalues.la	\
	../../libycp/src/libycp.la


y2base_DEPENDENCIES = $(YAST2CORE)

#
# do not add any libraries needed by a plugin.
# link the plugin against any special library.
#

y2base_LDADD = ${Y2UTIL_LIBS}

# -ljemalloc: workaround for error when jemalloc is dlopened in ruby in old testsuite (bsc#1068883)
y2base_LDFLAGS =			\
	-Xlinker --whole-archive	\
	-ljemalloc              	\
	$(PERL_LDFLAGS)			\
	$(YAST2CORE)			\
	-Xlinker --no-whole-archive

TESTS = y2base-smoke-test
EXTRA_DIST = $(TESTS)
