TEMPLATE = subdirs

SUBDIRS += \
    Telescope_Control \
    libStellarium

Telescope_Control.depends = libStellarium
