#!/bin/bash
mode="${1:-partition}"
cd cmake-build-release || exit 1
./countword ../WarAndPeace.txt freqstd || exit 1
for n in 1 4 8 16; do
  for essai in 1 2 3; do
    printf '\nMode=%s threads=%s essai=%s\n' "$mode" "$n" "$essai"
    ./countword ../WarAndPeace.txt "$mode" "$n" &&
      ../check.sh freqstd.freq "$mode.freq" || exit 1
  done
done