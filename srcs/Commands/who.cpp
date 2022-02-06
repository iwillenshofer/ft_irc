/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:21 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/06 15:17:57 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.6.1 Who query
**	Command: WHO
**	Parameters: [ <mask> [ "o" ] ]
**	
**	The WHO command is used by a client to generate a query which returns
**	a list of information which 'matches' the <mask> parameter given by
**	the client.  In the absence of the <mask> parameter, all visible
**	(users who aren't invisible (user mode +i) and who don't have a
**	common channel with the requesting client) are listed.  The same
**	result can be achieved by using a <mask> of "0" or any wildcard which
**	will end up matching every visible user.
**	
**	The <mask> passed to WHO is matched against users' host, server, real
**	name and nickname if the channel <mask> cannot be found.
**	
**	If the "o" parameter is passed only operators are returned according
**	to the <mask> supplied.
**	
**	Numeric Replies:
**	
**			ERR_NOSUCHSERVER
**			RPL_WHOREPLY                  RPL_ENDOFWHO
**	
**	Examples:
**	
**	WHO *.fi                        ; Command to list all users who match
**									against "*.fi".
**	
**	WHO jto* o                      ; Command to list all users with a
**									match against "jto*" if they are an
**									operator.
**
** 352     RPL_WHOREPLY
**                        "<channel> <user> <host> <server> <nick> \
**                         <H|G>[*][@|+] :<hopcount> <real name>"
*/

void Commands::__perform_who(Client &client, std::map<std::string, std::string> &arguments, Channel *channel)
{
	arguments["channel"] = (channel ? channel->get_name() : "*");
	arguments["user"] = client.username;
	arguments["host"] = client.hostname;
	arguments["nick"] = client.nickname;
	arguments["real_name"] = client.realname;
	arguments["away"] = (client.is_away() ? "G" : "H");
	Debug("Operator: " + ft::to_string(_sender->is_operator()), DBG_ERROR);
	arguments["servop"] = (client.is_operator() ? "*" : "");
	arguments["chanop"] = "";
	if (channel && channel->is_operator(client))
		arguments["chanop"] = "@";
	else if (channel && channel->is_voice(client))
		arguments["chanop"] = "+";
	arguments["hops"] = "0";
	_message_user(_generate_reply(RPL_WHOREPLY, arguments), _sender);
}


void	Commands::_cmd_who(void)
{
	std::map<std::string, std::string> arguments;
	std::vector<Client *> shared_channel;
	Channel *channel;
	int include_invisible = false;

	if (!(_message.arguments().size()))
		_message.arguments().push_back("*");
	else if (_message.arguments(0) == "0")
		_message.arguments(0) = "*";
	arguments["name"] = _message.arguments(0);
	arguments["server"] = _server->servername();
	if (Message::is_bnf_channel(_message.arguments(0)))
	{
		channel = _get_channel_by_name(_message.arguments(0));
		if ((channel) && !(channel->is_secret()))
		{
			if (channel->is_user(*_sender))
				include_invisible = true;
			for (std::vector<Client *>::iterator it = channel->users.begin(); it != channel->users.end(); it++)
			{
				if ((include_invisible || (!((*it)->is_invisible()))))
					__perform_who(**it, arguments, channel);
			}
		}
	}
	else
	{
		for (channel_iterator it = _channels->begin(); it != _channels->end(); it++)
			if (it->second.is_user(*_sender))
				shared_channel.insert(shared_channel.end(), it->second.users.begin(), it->second.users.end());
		for (client_iterator it = ++(_clients->begin()); it != _clients->end(); it++)
		{
			if (!(it->second.is_invisible()) && std::find(shared_channel.begin(), shared_channel.end(), &(it->second)) == shared_channel.end()
			&& (Mask::match(it->second, _message.arguments(0)) || Mask::match_raw(it->second.nickname, _message.arguments(0)) || 
			Mask::match_raw(it->second.hostname, _message.arguments(0)) || Mask::match_raw(it->second.realname, _message.arguments(0)) || 
			Mask::match_raw(_server->servername(), _message.arguments(0))))
			{
				if (_message.arguments().size() <= 1 || _message.arguments(1) != "o" || it->second.is_operator())
				__perform_who(it->second, arguments);
			}
		}
	}
	_message_user(_generate_reply(RPL_ENDOFWHO, arguments), _sender);
}




/*
	!!! You left #magirc

15:47		>>> StatServ (StatServ@services.teranova.net Statistical Service) services.teranova.net (0 hops) #magirc H&@
15:47		>>> Tiger (sid296629@teranova-kpef4t.helmsley.irccloud.com mai arrendersi) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> Simos (simos@teranova-3gq.njo.4.46.IP Filippo Cortigiani) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> DG (DG@teranova-ofovjn.bnc.cakeforce.uk DG) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> Az (Az@teranova-urb.m29.173.107.IP Az) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> Jyzee-zZ (Jyzee@Master.Of.The.Machines Jyzee) sigsegv.teranova.net (0 hops) #magirc G@
15:47		>>> GTAXL (gtaxlnetwor@gtaxl.net Victor Coss [GBNC]) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> j0rd (j0rd@teranova-kgq5m4.ninja J0rd) sigsegv.teranova.net (0 hops) #magirc G
15:47		>>> meepmeep (meepmeep@teranova-e4crkg.of.cylind.re meepmeep) sigsegv.teranova.net (0 hops) #magirc G




15:47		>>> StatServ (StatServ@services.teranova.net Statistical Service) services.teranova.net (0 hops) #magirc H&@
15:47		>>> Tiger (sid296629@teranova-kpef4t.helmsley.irccloud.com mai arrendersi) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> Simos (simos@teranova-3gq.njo.4.46.IP Filippo Cortigiani) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> DG (DG@teranova-ofovjn.bnc.cakeforce.uk DG) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> Az (Az@teranova-urb.m29.173.107.IP Az) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> Han` (Han@Millenium.Falcon Han) sigsegv.teranova.net (0 hops) #magirc H@
15:47		>>> Jyzee-zZ (Jyzee@Master.Of.The.Machines Jyzee) sigsegv.teranova.net (0 hops) #magirc G@
15:47		>>> GTAXL (gtaxlnetwor@gtaxl.net Victor Coss [GBNC]) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> bigua (bigua@teranova-ba9iof.org Yaákov, bar Yosef, akhui di Yeshua) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> Enopa (Enopa@teranova-lu34s2.hjlq.aaok.b0c0.2a03.IP Enopa Bot) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> Syloq (Syloq@teranova-75h.a4q.152.204.IP Syloq) sigsegv.teranova.net (0 hops) #magirc G
15:47		>>> genius3000 (g3k@teranova-ree1qr.solutions Matt <genius3000@g3k.solutions>) sigsegv.teranova.net (0 hops) #magirc G
15:47		>>> j0rd (j0rd@teranova-kgq5m4.ninja J0rd) sigsegv.teranova.net (0 hops) #magirc G
15:47		>>> meepmeep (meepmeep@teranova-e4crkg.of.cylind.re meepmeep) sigsegv.teranova.net (0 hops) #magirc G
15:47		>>> Jobe (jobe@catastrophic.failure Jobe) sigsegv.teranova.net (0 hops) #magirc H@
15:47		>>> PlasmaStar (plasma@IPv6.PlasmaStar.Net Jamie) sigsegv.teranova.net (0 hops) #magirc G
15:47		>>> KindOne (KindOne@cops.ate.all.my.donuts ...) sigsegv.teranova.net (0 hops) #magirc H
15:47		>>> iwillens (Mibbit@teranova-nts8jq.conab.gov.br http://www.mibbit.com) sigsegv.teranova.net (0 hops) #magirc H




15:48		>>> Moonspell (moon@teranova-sjp.n39.238.140.IP Look me in the eyes... and drown!) sigsegv.teranova.net (0 hops) * H
15:48		>>> anope (anope@teranova-e5dq2b.tomaw.net Tom Wesley <tom@tomaw.net>) sigsegv.teranova.net (0 hops) * H
15:48		>>> mom (mom@teranova-9vabru.de mommy) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> DG (DG@teranova-ofovjn.bnc.cakeforce.uk DG) sigsegv.teranova.net (0 hops) #help H
15:48		>>> DarthGandalf (Vetinari@teranova-truaft.7aqa.15pm.0278.2a02.IP Welstiel Massing) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> MemoServ (services@services.teranova.net Memo Service) services.teranova.net (0 hops) * H
15:48		>>> Az (Az@teranova-urb.m29.173.107.IP Az) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> gothicserpent (gothicserpe@teranova-g03.01j.126.144.IP gothicserpent) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> DM (the@dungeon.master DarkBot) services.teranova.net (0 hops) * H
15:48		>>> donk (donk@teranova-0ofqhu.virginmediabusiness.co.uk donk) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> GHF (EviL@teranova-500suo.sisrv.net no reason to get excited) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> lord-znc (lord@0-0-0.localhost.mil -=[ Warriors Crew ]=-) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Belgie (Belgie@Belgie.Bot België) services.teranova.net (0 hops) * H
15:48		>>> GIG (MYOB@teranova-0ht.c5v.98.172.IP J) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> GTAXL (gtaxlnetwor@gtaxl.net Victor Coss [GBNC]) sigsegv.teranova.net (0 hops) #help H
15:48		>>> NickServ (services@services.teranova.net Nickname Registration Service) services.teranova.net (0 hops) * H
15:48		>>> FatJesus (F@t.Jesus FatJesus) services.teranova.net (0 hops) * H
15:48		>>> Syloq (Syloq@teranova-75h.a4q.152.204.IP Syloq) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> bigua (bigua@teranova-ba9iof.org Yaákov, bar Yosef, akhui di Yeshua) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> cowgirl3 (mara@teranova-u45juq.rob.in.net Mara) volcano.teranova.net (0 hops) #anope H
15:48		>>> ChanServ (services@services.teranova.net Channel Registration Service) services.teranova.net (0 hops) * H
15:48		>>> peer (connect@reset.by peer) services.teranova.net (0 hops) * H
15:48		>>> aidan (aidan@teranova-o21.gu1.185.205.IP aidan) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> JellyTots (JellyTots@Wobbly.E.World JellyTots) services.teranova.net (0 hops) * H
15:48		>>> Simos (simos@teranova-3gq.njo.4.46.IP Filippo Cortigiani) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Services (services@teranova.net services) services.teranova.net (0 hops) * H
15:48		>>> HostServ (services@services.teranova.net vHost Service) services.teranova.net (0 hops) * H
15:48		>>> ACL (ACL@AChemicalLanguage.org ACL) services.teranova.net (0 hops) * H
15:48		>>> Arnie (niels@teranova-ebtrct.okkernoot.net niels) sigsegv.teranova.net (0 hops) * H
15:48		>>> Waser (waser@teranova-occf0n.mc.videotron.ca waser) volcano.teranova.net (0 hops) #anope H
15:48		>>> Wollino (weareone@teranova-8esgn6.ircforever.org Wollino) volcano.teranova.net (0 hops) #anope H
15:48		>>> lemming (lemming@broken.pipe lemmings are cool) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> OUTsider (outsider@scarynet.org The RTFM Enforcer) sigsegv.teranova.net (0 hops) #anope.de G@
15:48		>>> Shillos (sid16461@teranova-ief078.irccloud.com Woofy) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Nikos (url@teranova-89rtbt.0x1.gr Nikos-UrL) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> iwillens (Mibbit@teranova-nts8jq.conab.gov.br http://www.mibbit.com) sigsegv.teranova.net (0 hops) #magirc H
15:48		>>> Penix (penix@maximus.com Penix) services.teranova.net (0 hops) * H
15:48		>>> jwheare__ (sid2@teranova-a97tth.hampstead.irccloud.com James Wheare) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> mattf (mattf@teranova-q5tgq1.members.linode.com mattf) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> Nando (nando@teranova-04ukfm.ninja Keep calm and let Nando handle it) volcano.teranova.net (0 hops) #anope H
15:48		>>> henk (henk@teranova-jl96ud.netwichtig.de henk) volcano.teranova.net (0 hops) #help H
15:48		>>> Tiger (sid296629@teranova-kpef4t.helmsley.irccloud.com mai arrendersi) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> LocalGhost (sid116151@teranova-n53i33.irccloud.com PeGaSuS <pegasuspt@yandex.com>) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Ben (Ben@mrbenc.net Ben C.) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> PeGaSuS (Ubuntu@teranova-js5gin.t9at.iu0m.0470.2001.IP Ubuntu <pegasuspt@yandex.com>) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> Apocalypse (Apocalypse@teranova-3tfapp.us.darkvoltage.net The End of the Universe) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> PlasmaStar (plasma@IPv6.PlasmaStar.Net Jamie) sigsegv.teranova.net (0 hops) #help G
15:48		>>> po||ux (alex@teranova-28hdms.barton.de Alex Barton) sigsegv.teranova.net (0 hops) #anope.de G@
15:48		>>> VitaoDoidao (vd@Cannabiss.Ativa VD Priv8 Brasil) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> meepmeep (meepmeep@teranova-e4crkg.of.cylind.re meepmeep) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> Botox (Botox@services.anope.org Botox) services.teranova.net (0 hops) * H
15:48		>>> Jobe (jobe@catastrophic.failure Jobe) sigsegv.teranova.net (0 hops) #anope H%
15:48		>>> BotServ (services@services.teranova.net Bot Service) services.teranova.net (0 hops) * H
15:48		>>> Duck (Duck@teranova-urvtb5.duckspike.net .bang) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> sabet (sabet@teranova-ntd.v0n.27.198.IP sabet) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Enopa (Enopa@teranova-lu34s2.hjlq.aaok.b0c0.2a03.IP Enopa Bot) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> brachamh (brachamh@teranova-cdp.bt3.11.69.IP brachamh) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Cookie (cookie@everyone.likes.it Cookie) services.teranova.net (0 hops) * H
15:48		>>> StatServ (StatServ@services.teranova.net Statistical Service) services.teranova.net (0 hops) #magirc H&@
15:48		>>> X (X@number.of.chans Teranova.net) services.teranova.net (0 hops) * H
15:48		>>> CBX-AWAY (cyberbotx@cbx.anope.org Naram Qashat) sigsegv.teranova.net (0 hops) #anope G@
15:48		>>> Global (services@services.teranova.net Global Noticer) services.teranova.net (0 hops) * H
15:48		>>> OperServ (services@services.teranova.net Operator Service) services.teranova.net (0 hops) * H
15:48		>>> Digerati_ (sid11177@teranova-8ci2l0.helmsley.irccloud.com ryan-goldstein.com) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> ThatOneRoadie (ThatOneRoad@teranova-qfl1iv.snoonet.org Dwayne Elizondo Mountain Dew Herbert Camacho) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> TGS (theghostsh@teranova-vtdkod.theghostbox.com Brian Gilliford) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Cronus (Cronus@yum.yum.buttercup Taylor) volcano.teranova.net (0 hops) #moocows H*@
15:48		>>> kamel (identhere@teranova-ka2go0.16c1.4uc1.19f0.2001.IP ...) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> Han` (Han@Millenium.Falcon Han) sigsegv.teranova.net (0 hops) #anope H%
15:48		>>> KindOne (KindOne@cops.ate.all.my.donuts ...) sigsegv.teranova.net (0 hops) #magirc H
15:48		>>> Chris[A] (lol@teranova-nufl5u.afdp.slsp.04f8.2a01.IP coke is yummy!) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Jyzee-zZ (Jyzee@Master.Of.The.Machines Jyzee) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> Obi_Wan (Obi_Wan@teranova-2vfpeo.rz.st-city.net Obi_Wan) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Koragg (sid268081@teranova-mqcsb5.lymington.irccloud.com IRCCloud) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> val (val@teranova-d67gag.abo.wanadoo.fr Val Lorentz) volcano.teranova.net (0 hops) #anope H
15:48		>>> Sadie (sadie@teranova-vetans.kk6q.apl1.41d0.2001.IP ｡･ﾟﾟ･ 𝔖𝔞𝔡𝔦𝔢 💖 ･ﾟﾟ･｡) sigsegv.teranova.net (0 hops) #anope H@
15:48		>>> Teranova (Teranova@teranova.net Teranova) services.teranova.net (0 hops) * H
15:48		>>> Alef_Burzmali (burzmali@teranova-pke49p.burzmali.com Thomas Fargeix) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> jsoref (sid4015@teranova-n9p3ja.ilkley.irccloud.com jsoref) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> NiKaN (sid385034@teranova-9qdluq.helmsley.irccloud.com NiKaN) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Emmanuel_Chanel (emmanuel@teranova-n6mdna.dion.ne.jp realname) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> genius3000 (g3k@teranova-ree1qr.solutions Matt <genius3000@g3k.solutions>) sigsegv.teranova.net (0 hops) #magirc G
15:48		>>> xylite (anonymous@teranova-ikgjde.10100111001.de Got ZNC?) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> Randy (randy@teranova-tvh0bs.ph Randy R.) sigsegv.teranova.net (0 hops) #anope G
15:48		>>> neo (sid485950@teranova-7hog40.irccloud.com neo) sigsegv.teranova.net (0 hops) * H
15:48		>>> no_name (nnm@teranova-32tghp.bmn4.4hvk.6400.2605.IP nnm) sigsegv.teranova.net (0 hops) * H
15:48		>>> DarkBot (DarkBot@sbsgaming.com DarkBot) services.teranova.net (0 hops) * H
15:48		>>> OCD (Services@OCD.TeraNova.Net OCD) services.teranova.net (0 hops) * H
15:48		>>> siniStar (sinistar@teranova-hd0bv3.irc4fun.net siniStar @ IRC4Fun.net) volcano.teranova.net (0 hops) #anope H
15:48		>>> [R] (rs@teranova-u4rrd1.org RMS) sigsegv.teranova.net (0 hops) #anope H
15:48		>>> j0rd (j0rd@teranova-kgq5m4.ninja J0rd) sigsegv.teranova.net (0 hops) #anope G
*/
