# Fern's Keyboard Layouts

My personal QMK keymap for the KPRepublic XD75.

Keeping QMK keymaps outside of the main repo is kind of a pain.
For some reason, QMK has always preferred mantaining
random people's personal layouts in the project repo,
so out-of-tree builds are not really supported at all.

To get around that, I use OverlayFS to combine the `qmk_firmware`
repo and the directory with my keymap into a single tree,
run the build, and then get the compiled firmware by itself.

Also, I miss when building QMK didn't require Python.
