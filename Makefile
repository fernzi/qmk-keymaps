# Copyright © 2021-2023 Fern Zapata
# This program is subject to the terms of the GNU GPL, version 3
# or, at your option, any later version. If a copy of it was not
# included with this file, see https://www.gnu.org/licenses/.

OBJDIR := build

QMK    := pipenv run qmk
QMKDIR := qmk_firmware
KBDDIR := src
KBDSRC = $(wildcard $(KBDDIR)/keyboards/xiudi/xd75/keymaps/fernzi/*)

export PIPENV_PIPFILE=$(CURDIR)/Pipfile

## Rules ##

all: $(OBJDIR)/out/xiudi_xd75_fernzi.hex

clean:
	test -d $(OBJDIR) && $(RM) -r $(OBJDIR)

init:
	git submodule update --init --recursive
	pipenv install

flash: $(OBJDIR)/out/xiudi_xd75_fernzi.hex
	fuse-overlayfs -o \
		lowerdir=$(QMKDIR):$(KBDDIR),upperdir=$(OBJDIR)/out,workdir=$(OBJDIR)/work \
		$(OBJDIR)/mnt
	cd $(OBJDIR)/mnt && pipenv run qmk flash -kb xiudi/xd75 -km fernzi
	sleep 1
	umount $(OBJDIR)/mnt

$(OBJDIR)/out/xiudi_xd75_fernzi.hex: $(KBDSRC)
	mkdir -p $(OBJDIR)/out $(OBJDIR)/work $(OBJDIR)/mnt
	fuse-overlayfs -o \
		lowerdir=$(QMKDIR):$(KBDDIR),upperdir=$(OBJDIR)/out,workdir=$(OBJDIR)/work \
		$(OBJDIR)/mnt
	cd $(OBJDIR)/mnt && pipenv run qmk compile -kb xiudi/xd75 -km fernzi
	sleep 1
	umount $(OBJDIR)/mnt

## Other ##

.PHONY: all clean init flash
