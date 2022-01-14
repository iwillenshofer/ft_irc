001    RPL_WELCOME
"Welcome to the Internet Relay Network <nick>!<user>@<host>"

002    RPL_YOURHOST
"Your host is <servername>, running version <ver>"

003    RPL_CREATED
"This server was created <date>"

004    RPL_MYINFO
"<servername> <version> <available user modes> <available channel modes>"

005    RPL_BOUNCE
"Try server <server name>, port <port number>"

302    RPL_USERHOST
":*1<reply> *( " " <reply> )"

303    RPL_ISON
":*1<nick> *( " " <nick> )"

301    RPL_AWAY
"<nick> :<away message>"

305    RPL_UNAWAY
":You are no longer marked as being away"

306    RPL_NOWAWAY
":You have been marked as being away"

311    RPL_WHOISUSER
"<nick> <user> <host> * :<real name>"

312    RPL_WHOISSERVER
"<nick> <server> :<server info>"

313    RPL_WHOISOPERATOR
"<nick> :is an IRC operator"

317    RPL_WHOISIDLE
"<nick> <integer> :seconds idle"

318    RPL_ENDOFWHOIS
"<nick> :End of WHOIS list"

319    RPL_WHOISCHANNELS
"<nick> :*( ( "@" / "+" ) <channel> " " )"

314    RPL_WHOWASUSER
"<nick> <user> <host> * :<real name>"

369    RPL_ENDOFWHOWAS
"<nick> :End of WHOWAS"

322    RPL_LIST
"<channel> <# visible> :<topic>"

323    RPL_LISTEND
":End of LIST"

325    RPL_UNIQOPIS
"<channel> <nickname>"

324    RPL_CHANNELMODEIS
"<channel> <mode> <mode params>"

331    RPL_NOTOPIC
"<channel> :No topic is set"

332    RPL_TOPIC
"<channel> :<topic>"

341    RPL_INVITING
"<channel> <nick>"

342    RPL_SUMMONING
"<user> :Summoning user to IRC"

346    RPL_INVITELIST
"<channel> <invitemask>"

347    RPL_ENDOFINVITELIST
"<channel> :End of channel invite list"

348    RPL_EXCEPTLIST
"<channel> <exceptionmask>"

349    RPL_ENDOFEXCEPTLIST
"<channel> :End of channel exception list"

351    RPL_VERSION
"<version>.<debuglevel> <server> :<comments>"

352    RPL_WHOREPLY
"<channel> <user> <host> <server> <nick>( "H" / "G" > ["*"] [ ( "@" / "+" ) ]:<hopcount> <real name>"

315    RPL_ENDOFWHO
"<name> :End of WHO list"

353    RPL_NAMREPLY
"( "=" / "*" / "@" ) <channel>:[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )"

366    RPL_ENDOFNAMES
"<channel> :End of NAMES list"

364    RPL_LINKS
"<mask> <server> :<hopcount> <server info>"

365    RPL_ENDOFLINKS
"<mask> :End of LINKS list"

367    RPL_BANLIST
"<channel> <banmask>"

368    RPL_ENDOFBANLIST
"<channel> :End of channel ban list"

371    RPL_INFO
":<string>"

374    RPL_ENDOFINFO
":End of INFO list"

375    RPL_MOTDSTART
":- <server> Message of the day - "
372    RPL_MOTD
":- <text>"
376    RPL_ENDOFMOTD
":End of MOTD command"

381    RPL_YOUREOPER
":You are now an IRC operator"

382    RPL_REHASHING
"<config file> :Rehashing"

383    RPL_YOURESERVICE
"You are service <servicename>"

391    RPL_TIME
"<server> :<string showing server's local time>"

392    RPL_USERSSTART
":UserID   Terminal  Host"

393    RPL_USERS
":<username> <ttyline> <hostname>"

394    RPL_ENDOFUSERS
":End of users"

395    RPL_NOUSERS
":Nobody logged in"

200    RPL_TRACELINK
"Link <version & debug level> <destination> <next server> V<protocol version> <link uptime in seconds> <backstream sendq> <upstream sendq>"

201    RPL_TRACECONNECTING
"Try. <class> <server>"

202    RPL_TRACEHANDSHAKE
"H.S. <class> <server>"

203    RPL_TRACEUNKNOWN
"???? <class> [<client IP address in dot form>]"

204    RPL_TRACEOPERATOR
"Oper <class> <nick>"

205    RPL_TRACEUSER
"User <class> <nick>"

206    RPL_TRACESERVER
"Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> V<protocol version>"

207    RPL_TRACESERVICE
"Service <class> <name> <type> <active type>"

208    RPL_TRACENEWTYPE
"<newtype> 0 <client name>"

209    RPL_TRACECLASS
"Class <class> <count>"

210    RPL_TRACERECONNECT
""

261    RPL_TRACELOG
"File <logfile> <debug level>"

262    RPL_TRACEEND
"<server name> <version & debug level> :End of TRACE"

211    RPL_STATSLINKINFO
"<linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>"

212    RPL_STATSCOMMANDS
"<command> <count> <byte count> <remote count>"

219    RPL_ENDOFSTATS
"<stats letter> :End of STATS report"

242    RPL_STATSUPTIME
":Server Up %d days %d:%02d:%02d"

243    RPL_STATSOLINE
"O <hostmask> * <name>"

221    RPL_UMODEIS
"<user mode string>"

234    RPL_SERVLIST
"<name> <server> <mask> <type> <hopcount> <info>"

235    RPL_SERVLISTEND
"<mask> <type> :End of service listing"

251    RPL_LUSERCLIENT
":There are <integer> users and <integer> services on <integer> servers"

252    RPL_LUSEROP
"<integer> :operator(s) online"

253    RPL_LUSERUNKNOWN
"<integer> :unknown connection(s)"

254    RPL_LUSERCHANNELS
"<integer> :channels formed"

255    RPL_LUSERME
":I have <integer> clients and <integer> servers"

256    RPL_ADMINME
"<server> :Administrative info"

257    RPL_ADMINLOC1
":<admin info>"

258    RPL_ADMINLOC2
":<admin info>"

259    RPL_ADMINEMAIL
":<admin info>"

263    RPL_TRYAGAIN
"<command> :Please wait a while and try again."

401    ERR_NOSUCHNICK
"<nickname> :No such nick/channel"

402    ERR_NOSUCHSERVER
"<server name> :No such server"

403    ERR_NOSUCHCHANNEL
"<channel name> :No such channel"

404    ERR_CANNOTSENDTOCHAN
"<channel name> :Cannot send to channel"

405    ERR_TOOMANYCHANNELS
"<channel name> :You have joined too many channels"

406    ERR_WASNOSUCHNICK
"<nickname> :There was no such nickname"

407    ERR_TOOMANYTARGETS
"<target> :<error code> recipients. <abort message>"

408    ERR_NOSUCHSERVICE
"<service name> :No such service"

409    ERR_NOORIGIN
":No origin specified"

411    ERR_NORECIPIENT
":No recipient given (<command>)"

412    ERR_NOTEXTTOSEND
":No text to send"

413    ERR_NOTOPLEVEL
"<mask> :No toplevel domain specified"

414    ERR_WILDTOPLEVEL
"<mask> :Wildcard in toplevel domain"

415    ERR_BADMASK
"<mask> :Bad Server/host mask"

421    ERR_UNKNOWNCOMMAND
"<command> :Unknown command"

422    ERR_NOMOTD
":MOTD File is missing"

423    ERR_NOADMININFO
"<server> :No administrative info available"

424    ERR_FILEERROR
":File error doing <file op> on <file>"

431    ERR_NONICKNAMEGIVEN
":No nickname given"

432    ERR_ERRONEUSNICKNAME
"<nick> :Erroneous nickname"

433    ERR_NICKNAMEINUSE
"<nick> :Nickname is already in use"

436    ERR_NICKCOLLISION
"<nick> :Nickname collision KILL from <user>@<host>"

437    ERR_UNAVAILRESOURCE
"<nick/channel> :Nick/channel is temporarily unavailable"

441    ERR_USERNOTINCHANNEL
"<nick> <channel> :They aren't on that channel"

442    ERR_NOTONCHANNEL
"<channel> :You're not on that channel"

443    ERR_USERONCHANNEL
"<user> <channel> :is already on channel"

444    ERR_NOLOGIN
"<user> :User not logged in"

445    ERR_SUMMONDISABLED
":SUMMON has been disabled"

446    ERR_USERSDISABLED
":USERS has been disabled"

451    ERR_NOTREGISTERED
":You have not registered"

461    ERR_NEEDMOREPARAMS
"<command> :Not enough parameters"

462    ERR_ALREADYREGISTRED
":Unauthorized command (already registered)"

463    ERR_NOPERMFORHOST
":Your host isn't among the privileged"

464    ERR_PASSWDMISMATCH
":Password incorrect"

465    ERR_YOUREBANNEDCREEP
":You are banned from this server"

466    ERR_YOUWILLBEBANNED
""

467    ERR_KEYSET
"<channel> :Channel key already set"

471    ERR_CHANNELISFULL
"<channel> :Cannot join channel (+l)"

472    ERR_UNKNOWNMODE
"<char> :is unknown mode char to me for <channel>"

473    ERR_INVITEONLYCHAN
"<channel> :Cannot join channel (+i)"

474    ERR_BANNEDFROMCHAN
"<channel> :Cannot join channel (+b)"

475    ERR_BADCHANNELKEY
"<channel> :Cannot join channel (+k)"

476    ERR_BADCHANMASK
"<channel> :Bad Channel Mask"

477    ERR_NOCHANMODES
"<channel> :Channel doesn't support modes"

478    ERR_BANLISTFULL
"<channel> <char> :Channel list is full"

481    ERR_NOPRIVILEGES
":Permission Denied- You're not an IRC operator"

482    ERR_CHANOPRIVSNEEDED
"<channel> :You're not channel operator"

483    ERR_CANTKILLSERVER
":You can't kill a server!"

484    ERR_RESTRICTED
":Your connection is restricted!"

485    ERR_UNIQOPPRIVSNEEDED
":You're not the original channel operator"

491    ERR_NOOPERHOST
":No O-lines for your host"

501    ERR_UMODEUNKNOWNFLAG
":Unknown MODE flag"

502    ERR_USERSDONTMATCH
":Cannot change mode for other users"



001    RPL_WELCOME
002    RPL_YOURHOST
003    RPL_CREATED
004    RPL_MYINFO
005    RPL_BOUNCE
302    RPL_USERHOST
303    RPL_ISON
301    RPL_AWAY
305    RPL_UNAWAY
306    RPL_NOWAWAY
311    RPL_WHOISUSER
312    RPL_WHOISSERVER
313    RPL_WHOISOPERATOR
317    RPL_WHOISIDLE
318    RPL_ENDOFWHOIS
319    RPL_WHOISCHANNELS
314    RPL_WHOWASUSER
369    RPL_ENDOFWHOWAS
322    RPL_LIST
323    RPL_LISTEND
325    RPL_UNIQOPIS
324    RPL_CHANNELMODEIS
331    RPL_NOTOPIC
332    RPL_TOPIC
341    RPL_INVITING
342    RPL_SUMMONING
346    RPL_INVITELIST
347    RPL_ENDOFINVITELIST
348    RPL_EXCEPTLIST
349    RPL_ENDOFEXCEPTLIST
351    RPL_VERSION
352    RPL_WHOREPLY
315    RPL_ENDOFWHO
353    RPL_NAMREPLY
366    RPL_ENDOFNAMES
364    RPL_LINKS
365    RPL_ENDOFLINKS
367    RPL_BANLIST
368    RPL_ENDOFBANLIST
371    RPL_INFO
374    RPL_ENDOFINFO
375    RPL_MOTDSTART
372    RPL_MOTD
376    RPL_ENDOFMOTD
381    RPL_YOUREOPER
382    RPL_REHASHING
383    RPL_YOURESERVICE
391    RPL_TIME
392    RPL_USERSSTART
393    RPL_USERS
394    RPL_ENDOFUSERS
395    RPL_NOUSERS
200    RPL_TRACELINK
201    RPL_TRACECONNECTING
202    RPL_TRACEHANDSHAKE
203    RPL_TRACEUNKNOWN
204    RPL_TRACEOPERATOR
205    RPL_TRACEUSER
206    RPL_TRACESERVER
207    RPL_TRACESERVICE
208    RPL_TRACENEWTYPE
209    RPL_TRACECLASS
210    RPL_TRACERECONNECT
261    RPL_TRACELOG
262    RPL_TRACEEND
211    RPL_STATSLINKINFO
212    RPL_STATSCOMMANDS
219    RPL_ENDOFSTATS
242    RPL_STATSUPTIME
243    RPL_STATSOLINE
221    RPL_UMODEIS
234    RPL_SERVLIST
235    RPL_SERVLISTEND
251    RPL_LUSERCLIENT
252    RPL_LUSEROP
253    RPL_LUSERUNKNOWN
254    RPL_LUSERCHANNELS
255    RPL_LUSERME
256    RPL_ADMINME
257    RPL_ADMINLOC1
258    RPL_ADMINLOC2
259    RPL_ADMINEMAIL
263    RPL_TRYAGAIN
401    ERR_NOSUCHNICK
402    ERR_NOSUCHSERVER
403    ERR_NOSUCHCHANNEL
404    ERR_CANNOTSENDTOCHAN
405    ERR_TOOMANYCHANNELS
406    ERR_WASNOSUCHNICK
407    ERR_TOOMANYTARGETS
408    ERR_NOSUCHSERVICE
409    ERR_NOORIGIN
411    ERR_NORECIPIENT
412    ERR_NOTEXTTOSEND
413    ERR_NOTOPLEVEL
414    ERR_WILDTOPLEVEL
415    ERR_BADMASK
421    ERR_UNKNOWNCOMMAND
422    ERR_NOMOTD
423    ERR_NOADMININFO
424    ERR_FILEERROR
431    ERR_NONICKNAMEGIVEN
432    ERR_ERRONEUSNICKNAME
433    ERR_NICKNAMEINUSE
436    ERR_NICKCOLLISION
437    ERR_UNAVAILRESOURCE
441    ERR_USERNOTINCHANNEL
442    ERR_NOTONCHANNEL
443    ERR_USERONCHANNEL
444    ERR_NOLOGIN
445    ERR_SUMMONDISABLED
446    ERR_USERSDISABLED
451    ERR_NOTREGISTERED
461    ERR_NEEDMOREPARAMS
462    ERR_ALREADYREGISTRED
463    ERR_NOPERMFORHOST
464    ERR_PASSWDMISMATCH
465    ERR_YOUREBANNEDCREEP
466    ERR_YOUWILLBEBANNED
467    ERR_KEYSET
471    ERR_CHANNELISFULL
472    ERR_UNKNOWNMODE
473    ERR_INVITEONLYCHAN
474    ERR_BANNEDFROMCHAN
475    ERR_BADCHANNELKEY
476    ERR_BADCHANMASK
477    ERR_NOCHANMODES
478    ERR_BANLISTFULL
481    ERR_NOPRIVILEGES
482    ERR_CHANOPRIVSNEEDED
483    ERR_CANTKILLSERVER
484    ERR_RESTRICTED
485    ERR_UNIQOPPRIVSNEEDED
491    ERR_NOOPERHOST
501    ERR_UMODEUNKNOWNFLAG
502    ERR_USERSDONTMATCH
