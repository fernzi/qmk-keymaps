# Fern's Keyboard Layouts

My personal QMK keymaps. Only one for the KPRepublic XD75 for now.

Keeping QMK keymaps out of the main repo is kind of a pain.
For some reason, QMK has always preferred mantaining
random people's personal layouts in the project repo,
so out-of-tree builds are not really supported at all.

To get around that, I use OverlayFS to combine the `qmk_firmware`
repo and the directory with my keymaps into a single tree,
run the build, and then get the compiled firmware by itself.

Also, I miss when building QMK didn't require Python.
But can't get rid of it, so I might as well use it.

## Installation

Building requires the PDM package manager for Python,
and `fuse-overlayfs`, which you can install with the commands

``` shell
# On Debian, Ubuntu, and derivatives:
apt install python3-pdm fuse-overlayfs

# On Arch, Manjaro, and probably others:
pacman -S python-pdm fuse-overlayfs

# Might support MacOS using MacFUSE at some point.

# PDM can also be installed with Pip on any OS,
# but you'd still need to get `fuse-overlayfs`.
pip install --user pdm
```

so you can then install the rest of the Python dependencies by running

``` shell
pdm install
```

inside the project's directory.

QMK has its own dependencies which have to be installed as well.
Can probably do it by running the command `pdm run qmk setup` or
in any way the [QMK documentation][qmk-doc] says you should.
In any case, you can run any command from the QMK CLI tool by
preceding it with `pdm run` if necessary.

Wish they didn't try to be so "user friendly" and just listed them
in their docs instead of being buried in some automatic install script.

[qmk-doc]: https://docs.qmk.fm

## Usage

By default, the scripts will build the firmware for all the keyboards
within the `src` directory, which is structured in the same way as in
the main `qmk_firmware` repo, i.e. a folder per keymap of the form
`src/keyboards/${BRAND}/${KEYBOARD}/keymaps/${KEYMAP}`, containing
`config.h`, `keymap.c`, `rules.mk`, etc.

Note that the `src` directory gets overlaid over QMK's source,
so could technically override or add any file into it,
but I've yet to try anything other than adding keymaps.

Can then start the build with the shorthand command

``` shell
pdm run build
```

which will mount the overlay, build all the available firmware,
and unmount the overlay when it's done.

Can also build only one keymap by running a command like
`pdm run doit build:${BRAND}:${KEYBOARD}:${KEYMAP}`, e.g.
`pdm run doit build:xiudi:xd75:fernzi` would build my personal
layout for the XD75 keyboard.

Flashing can also be done the same way, but I recommend that
you use the `pdm run doit flash:${BRAND}:${KEYBOARD}:${KEYMAP}`
form of the command to flash a single keyboard, rather than
`pdm run flash`, unless you actually want to flash every single
keyboard you own, for whatever reason.
