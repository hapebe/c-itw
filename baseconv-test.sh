#!/bin/bash
if [ "$(./baseconv ff 16 10)" -ne "255" ] ; then echo "assumption failed in line #${LINENO}..." 1>&2 ; fi
if [ "$(./baseconv -0 16 10)" -ne "0" ] ; then echo "assumption failed in line #${LINENO}..." 1>&2 ; fi
if [ "$(./baseconv -z 36 10)" -ne "-35" ] ; then echo "assumption failed in line #${LINENO}..." 1>&2 ; fi
# 63 binary digits:
if [ "$(./baseconv 111111111111111111111111111111111111111111111111111111111111111 2 16)" != "7fffffffffffffff" ] ; then echo "assumption failed in line #${LINENO}..." 1>&2 ; fi
# 64(!) binary digits, I expect no output (plus an error message)
if [ "$(./baseconv 1111111111111111111111111111111111111111111111111111111111111111 2 16)" != "" ] ; then echo "assumption failed in line #${LINENO}..." 1>&2 ; fi
