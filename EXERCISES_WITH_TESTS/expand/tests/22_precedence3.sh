#!/bin/bash
exec "$1" tests/same_prefix_rules.txt tests/anima_rules.txt <<EOF
Algoritms are great. They are the essence of programming.  Except that
I misspelled the word "Algorithm". Anyway, I just love Algorithmic
thinking.  A good Algorithm is worth 1000 Allegories.  Well, that
doesn't make sense, I know, but I needed to somehow use the word Allegory.
EOF
