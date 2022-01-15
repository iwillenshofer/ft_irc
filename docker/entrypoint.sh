#!/bin/sh
RED='\033[1;31m'
GREEN='\033[1;32m'
BLUE='\033[1;34m'
NC='\033[0m' 

DIR='ircu'

cd /${DIR}
touch /${DIR}/ircd.log
touch /${DIR}/ircd.debug
# run!
su ircd -c "/${DIR}/bin/ircd -n" &
echo "HELLO WORLD"
touch a
tail -f /${DIR}/ircd.log

killall ircd
tail -f /dev/null