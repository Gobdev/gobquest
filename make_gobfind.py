import re, os
from pathlib import Path

paths = {}

for path in Path('games/').glob('**/*.gob'):
    parent = str(path.parts[1])
    if parent not in paths:
        paths[parent] = []
    path = Path("/".join(path.parts[2:]))
    paths[parent].append(str(path))

for game in paths:
    with open('games/%s/gob.find' % game, 'w') as fw:
        for filename in paths.get(game):
            lines = []
            with open('games/%s/%s' % (game, filename), 'r') as f:
                pointer_pos = 0;
                for line in iter(f.readline, ''):
                    mgrp = re.match('(\w+)\s*:', line)
                    if mgrp:
                        lines.append((mgrp.group(1), filename, pointer_pos))
                    pointer_pos = f.tell()
            for line in lines:
                fw.write("%s %s %d\n" % line)
