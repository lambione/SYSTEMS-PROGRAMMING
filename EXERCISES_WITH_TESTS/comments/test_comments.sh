#!/bin/sh

#
# test 1
#
cat > test1.in <<EOF
non comment line // even though it contains a comment string
// comment line number one
non comment line n. 2 // even though it contains a comment string
     // comment line number two
ciao
EOF
./comments < test1.in > test1.out
cat > test1.expected <<EOF
(stdin)	2	5
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.in test1.out test1.expected
else
    echo "Test 1 FAILED"
    diff test1.out test1.expected
    exit 1
fi
#
# test 2
#
cat > test1.in <<EOF
non comment line // even though it contains a comment string
// comment line number one
non comment line n. 2 // even though it contains a comment string
     // comment line number two
ciao
EOF
./comments test1.in > test1.out
cat > test1.expected <<EOF
test1.in	2	5
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.in test1.out test1.expected
else
    echo Test 2 FAILED
    diff test1.out test1.expected
    exit 1
fi
#
# test 3
#
cat > test1.in <<EOF
non comment line // even though it contains a comment string
// comment line number one
non comment line n. 2 // even though it contains a comment string
     // comment line number two
ciao
EOF
./comments comment=// test1.in > test1.out
cat > test1.expected <<EOF
test1.in	2	5
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.in test1.out test1.expected
else
    echo "Test 3 FAILED"
    diff test1.out test1.expected
    exit 1
fi
#
# test 4
#
cat > test1.in <<EOF
non comment line # even though it contains a comment string
# comment line number one
non comment line n. 2 # even though it contains a comment string
     # comment line number two
ciao
EOF
cat > test2.in <<EOF
   ### comment line
   # comment line
	# comment line
	# comment line, this is full of comment lines
EOF
./comments comment='#' test1.in test2.in > test1.out
cat > test1.expected <<EOF
test1.in	2	5
test2.in	4	4
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.in test2.in test1.out test1.expected
else
    echo "Test 4 FAILED"
    diff test1.out test1.expected
    exit 1
fi
#
# test 5
#
cat > test1.in <<EOF
non comment line # even though it contains a comment string
# comment line number one
non comment line n. 2 # even though it contains a comment string
     # comment line number two
ciao
EOF
cat > test2.in <<EOF
   ### comment line
   # comment line
	# comment line
	# comment line, this is full of comment lines
EOF
./comments comment='##' test1.in test2.in > test1.out
cat > test1.expected <<EOF
test1.in	0	5
test2.in	1	4
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.in test2.in test1.out test1.expected
else
    echo "Test 5 FAILED"
    diff test1.out test1.expected
    exit 1
fi
echo PASSED
