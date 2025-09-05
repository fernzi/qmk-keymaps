# Fern's Keyboard Layouts

My personal QMK keymaps. Only one for the KPRepublic XD75 for now.

Keeping QMK keymaps out of the main repo is kind of a pain.
For some reason, QMK had always preferred mantaining
random people's personal layouts in the project repo,
so out-of-tree builds weren't really supported for a long time.

Luckily, at some point which I failed to notice in time,
QMK started supporting something it calls "external userspaces,"
standalone repositories that mirror the main project's layout,
but contain your and only your keymaps without going thru
the hassle of mantaining a fork or having to make PRs
just to have them hosted somewhere in a way that still builds.
