FROM alpine:3.9


# used if we need to recompile ircu2
RUN apk add build-base vim bash binutils libc-dev byacc git autoconf
WORKDIR /home
RUN git clone https://github.com/UndernetIRC/ircu2.git
WORKDIR /home/ircu2
RUN cd /home/ircu2 && \
	./configure --prefix=/ircu  --enable-debug --with-maxcon=10000 --with-cpath=/ircu/lib/ircd.conf --with-lpath=/ircu/ircd.debug 
RUN make install

#ADD ./ircu.tar.gz /
RUN adduser -D -g '' ircd
RUN chown -R ircd /ircu
RUN chgrp -R ircd /ircu
