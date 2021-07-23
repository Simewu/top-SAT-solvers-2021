#!/bin/sh
binary=`basename $0`
die () {
  echo "$binary: error: $*" 1>&2
  exit 1
}
[ -f makefile ] || die "no 'makefile' (run './configure' first)"
CC="`sed -e '/^CC/!d' -e 's,^CC=,,' makefile`"
[ "$CC" = "" ] && die "could not get 'CC' from makefile"
CFLAGS="`sed -e '/^CFLAGS/!d' -e 's,^CFLAGS=,,' makefile`"
[ "$CFLAGS" = "" ] && die "could not get 'CFLAGS' from makefile"
case "$CC" in
  gcc*|clang*) CC="`$CC --version 2>/dev/null|head -1`";;
esac
COMPILER="$CC $CFLAGS"
VERSION="`cat ../VERSION 2>/dev/null`"
[ "$VERSION" = "" ] && die "could not get 'VERSION'"
cat <<EOF
#define VERSION "$VERSION"
#define COMPILER "$COMPILER"
EOF
#START-CUT-OUT-ID
if [ -d .git -o -d ../.git ]
then
  ID="`git show 2>/dev/null|awk '{print $2; exit}'`"
  [ "$ID" = "" ] && die "could not get git id with 'git show'"
else
  ID=79d8d8f20465e71fd2b0f193b468898cd803a59a
fi
#END-CUT-OUT-ID
cat <<EOF
#define ID "$ID"
EOF
LC_TIME="en_US"
export LC_TIME
DATE="`date 2>/dev/null|sed -e 's,  *, ,g'`"
OS="`uname -srmn 2>/dev/null`"
BUILD="`echo $DATE $OS|sed -e 's,^ *,,' -e 's, *$,,'`"
cat << EOF
#define BUILD "$BUILD"
EOF
DIR="`pwd`"
cat <<EOF
#define DIR "$DIR"
EOF
