plugin_name = xrandr

icondir = $(datadir)/icons/hicolor
context = apps

ICON_FILES = 			\
	gsd-xrandr-16.png	\
	gsd-xrandr-22.png	\
	gsd-xrandr-24.png	\
	gsd-xrandr-32.png	\
	gsd-xrandr.svg

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(icondir)/16x16/$(context)
	$(mkinstalldirs) $(DESTDIR)$(icondir)/22x22/$(context)
	$(mkinstalldirs) $(DESTDIR)$(icondir)/24x24/$(context)
	$(mkinstalldirs) $(DESTDIR)$(icondir)/32x32/$(context)
	$(mkinstalldirs) $(DESTDIR)$(icondir)/scalable/$(context)
	$(INSTALL_DATA) $(srcdir)/gsd-xrandr-16.png $(DESTDIR)$(icondir)/16x16/$(context)/gsd-xrandr.png
	$(INSTALL_DATA) $(srcdir)/gsd-xrandr-22.png $(DESTDIR)$(icondir)/22x22/$(context)/gsd-xrandr.png
	$(INSTALL_DATA) $(srcdir)/gsd-xrandr-24.png $(DESTDIR)$(icondir)/24x24/$(context)/gsd-xrandr.png
	$(INSTALL_DATA) $(srcdir)/gsd-xrandr-32.png $(DESTDIR)$(icondir)/32x32/$(context)/gsd-xrandr.png
	$(INSTALL_DATA) $(srcdir)/gsd-xrandr.svg $(DESTDIR)$(icondir)/scalable/$(context)/gsd-xrandr.svg

uninstall-local:
	rm -f $(DESTDIR)$(icondir)/16x16/$(context)/gsd-xrandr.png
	rm -f $(DESTDIR)$(icondir)/22x22/$(context)/gsd-xrandr.png
	rm -f $(DESTDIR)$(icondir)/24x24/$(context)/gsd-xrandr.png
	rm -f $(DESTDIR)$(icondir)/32x32/$(context)/gsd-xrandr.png
	rm -f $(DESTDIR)$(icondir)/scalable/$(context)/gsd-xrandr.svg

libexec_PROGRAMS = gsd-xrandr

gsd_xrandr_SOURCES =		\
	main.c				\
	gsd-xrandr-manager.c		\
	gsd-xrandr-manager.h

gsd_xrandr_CPPFLAGS =					\
	-I$(top_srcdir)/data/					\
	-I$(top_srcdir)/gnome-settings-daemon			\
	-I$(top_builddir)/gnome-settings-daemon			\
	-I$(top_srcdir)/plugins/common				\
	-DGNOME_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\"	\
	-DLIBEXECDIR=\""$(libexecdir)"\"			\
	$(AM_CPPFLAGS)

gsd_xrandr_CFLAGS =			\
	$(PLUGIN_CFLAGS)		\
	$(XRANDR_CFLAGS)

gsd_xrandr_LDADD =						\
	$(top_builddir)/gnome-settings-daemon/libgsd.la		\
	$(top_builddir)/plugins/common/libcommon.la		\
	$(XRANDR_LIBS)

desktopdir = $(sysconfdir)/xdg/autostart
desktop_in_files = org.gnome.SettingsDaemon.XRANDR.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

org.gnome.SettingsDaemon.XRANDR.desktop: $(desktop_in_files) Makefile
	$(AM_V_GEN) sed -e "s|\@libexecdir\@|$(libexecdir)|" $< > $@

EXTRA_DIST = $(desktop_in_files) $(ICON_FILES)
CLEANFILES = $(desktop_DATA)
DISTCLEANFILES = $(desktop_DATA)
