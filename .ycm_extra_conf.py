import os

C_CURRENT_DIR = os.path.dirname(__file__)


def FlagsForFile(filename, **kwargs):
    return {
        'flags': [
            '-I', '/usr/include',
            '-Wall',
            '-Wextra',
            '-Werror',
            '-x', 'c++',
            '-std=c++20',
        ]
    }
