#!/usr/bin/env python
# Copyright © 2021-2023 Fern Zapata
# This program is subject to the terms of the GNU GPL, version 3
# or, at your option, any later version. If a copy of it was not
# included with this file, see https://www.gnu.org/licenses/.

from pathlib import Path
from shutil import rmtree
from doit.action import CmdAction


DOIT_CONFIG = {
    'default_tasks': ['build'],
    'verbosity': 2,
}

OUTPUT = Path('build')
OUTDRS = [OUTPUT / x for x in ('mnt', 'out', 'tmp')]
SOURCE = Path('src')
QMKSRC = Path('lib', 'qmk_firmware')


## Utilities ##########################################################


def parts2keebs(parts: [str]) -> (str, str, str):
    return parts[2], parts[3], parts[-1]


## Tasks ##############################################################


def task_outdirs():
    """Create output directories."""
    for d in OUTDRS:
        tgt = [d]
        yield {
            'name': d.name,
            'actions': [
                (lambda p: p.mkdir(parents=True, exist_ok=True), tgt),
            ],
            'targets': tgt,
        }


def task_mount():
    """Mount overlay directory."""
    opts = 'lowerdir={}:{},upperdir={},workdir={}'.format(
        QMKSRC, SOURCE, OUTPUT / 'out', OUTPUT / 'tmp')
    return {
        'actions': [['fuse-overlayfs', '-o', opts, OUTPUT / 'mnt']],
        'teardown': [['umount', '--', OUTPUT / 'mnt']],
        'task_dep': ['outdirs'],
        'uptodate': [(Path.is_mount, [OUTPUT / 'mnt'])],
    }


def task_umount():
    """Unmount overlay directory."""
    return {
        'actions': [['fusermount', '-uz', OUTPUT / 'mnt']],
        'uptodate': [(lambda x: not x.is_mount(), [OUTPUT / 'mnt'])],
    }


def task_build():
    """Build available keyboards' firmware."""
    for keymap in SOURCE.glob('keyboards/*/*/keymaps/*'):
        mf, kb, km = parts2keebs(keymap.parts)
        cmd = ['qmk', 'compile', '-kb', f'{mf}/{kb}', '-km', km]

        yield {
            'name': f'{mf}:{kb}:{km}',
            'actions': [
                CmdAction(cmd, cwd=OUTPUT / 'mnt', shell=False),
            ],
            'setup': ['mount'],
            'file_dep': list(keymap.glob('*')),
            'targets': [OUTPUT / 'out' / f'{mf}_{kb}_{km}.hex'],
        }


def task_flash():
    """Flash keyboard firmware."""
    for keymap in SOURCE.glob('keyboards/*/*/keymaps/*'):
        mf, kb, km = parts2keebs(keymap.parts)
        cmd = ['qmk', 'flash', '-kb', f'{mf}/{kb}', '-km', km]

        yield {
            'name': f'{mf}:{kb}:{km}',
            'actions': [
                CmdAction(cmd, cwd=OUTPUT / 'mnt', shell=False),
            ],
            'setup': ['mount'],
            'file_dep': [OUTPUT / 'out' / f'{mf}_{kb}_{km}.hex']
        }
