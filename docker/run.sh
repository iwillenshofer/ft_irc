
docker build --build-arg http_proxy=$http_proxy -t irc-image .
docker run --rm -t -a stdout -p4443:4443 --name my-irc -v $PWD/ircd.conf:/ircu/lib/ircd.conf:ro irc-image /tmp/run.sh
