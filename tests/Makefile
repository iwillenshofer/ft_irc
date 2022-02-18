# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roman <roman@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 13:47:20 by iwillens          #+#    #+#              #
#    Updated: 2022/02/17 21:16:15 by roman            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = irctest

CC = clang++
CCFLAGS = -Wall -Werror -Wextra -g -std=c++11 -pedantic -fsanitize=address

SRC_DIR = ../srcs
OBJ_DIR = ./build

CLIENT_DIR = ./
CLIENT_OBJ_DIR = ./build/client

INC_DIR = ${SRC_DIR} -I../srcs/


SRCS =					${SRC_DIR}/Debug.cpp \
						${SRC_DIR}/utilities.cpp \
						${SRC_DIR}/Message.cpp \
						${SRC_DIR}/Mask.cpp

CLIENT_SRCS =			${CLIENT_DIR}/IrcClient.cpp \
						${CLIENT_DIR}/Tester.cpp \
						${CLIENT_DIR}/main.cpp \
						${CLIENT_DIR}/srcs/test_registration.cpp \
						$(CLIENT_DIR)/srcs/test_admin.cpp \
						$(CLIENT_DIR)/srcs/test_away.cpp \
						$(CLIENT_DIR)/srcs/test_connect.cpp \
						$(CLIENT_DIR)/srcs/test_error.cpp \
						$(CLIENT_DIR)/srcs/test_info.cpp \
						$(CLIENT_DIR)/srcs/test_invite.cpp \
						$(CLIENT_DIR)/srcs/test_join.cpp \
						$(CLIENT_DIR)/srcs/test_kick.cpp \
						$(CLIENT_DIR)/srcs/test_kill.cpp \
						$(CLIENT_DIR)/srcs/test_links.cpp \
						$(CLIENT_DIR)/srcs/test_list.cpp \
						$(CLIENT_DIR)/srcs/test_lusers.cpp \
						$(CLIENT_DIR)/srcs/test_mode_channel.cpp \
						$(CLIENT_DIR)/srcs/test_mode_user.cpp \
						$(CLIENT_DIR)/srcs/test_motd.cpp \
						$(CLIENT_DIR)/srcs/test_names.cpp \
						$(CLIENT_DIR)/srcs/test_nick.cpp \
						$(CLIENT_DIR)/srcs/test_notice.cpp \
						$(CLIENT_DIR)/srcs/test_oper.cpp \
						$(CLIENT_DIR)/srcs/test_part.cpp \
						$(CLIENT_DIR)/srcs/test_pass.cpp \
						$(CLIENT_DIR)/srcs/test_ping.cpp \
						$(CLIENT_DIR)/srcs/test_pong.cpp \
						$(CLIENT_DIR)/srcs/test_privmsg.cpp \
						$(CLIENT_DIR)/srcs/test_quit.cpp \
						$(CLIENT_DIR)/srcs/test_server.cpp \
						$(CLIENT_DIR)/srcs/test_squit.cpp \
						$(CLIENT_DIR)/srcs/test_stats.cpp \
						$(CLIENT_DIR)/srcs/test_time.cpp \
						$(CLIENT_DIR)/srcs/test_topic.cpp \
						$(CLIENT_DIR)/srcs/test_trace.cpp \
						$(CLIENT_DIR)/srcs/test_user.cpp \
						$(CLIENT_DIR)/srcs/test_version.cpp \
						${CLIENT_DIR}/srcs/test_whois.cpp \
						${CLIENT_DIR}/srcs/test_whowas.cpp \
						${CLIENT_DIR}/srcs/test_who.cpp

OBJECTS = $(patsubst ${SRC_DIR}/%.cpp, ${OBJ_DIR}/%.o, ${SRCS})
CLIENT_OBJECTS = $(patsubst ${CLIENT_DIR}/%.cpp, ${CLIENT_OBJ_DIR}/%.o, ${CLIENT_SRCS})
DEPENDENCIES = $(patsubst %.o, %.d, ${OBJECTS})
CLIENT_DEPENDENCIES = $(patsubst %.o, %.d, ${CLIENT_OBJECTS})

all: ${NAME}

${NAME}: ${OBJECTS} ${CLIENT_OBJECTS}
	@${CC} ${CCFLAGS} ${OBJECTS} ${CLIENT_OBJECTS} -I. -I ${INC_DIR} -o ${NAME}
	@echo "\033[92m./${NAME} is built. \033[0m"

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	@mkdir -p $(dir $@)
	@echo -n "."
	@${CC} ${CCFLAGS} -MMD -c  $< -I. -I ${INC_DIR} -o $@

${CLIENT_OBJ_DIR}/%.o: ${CLIENT_DIR}/%.cpp
	@mkdir -p $(dir $@)
	@echo -n "."
	@${CC} ${CCFLAGS} -MMD -c  $< -I. -I ${INC_DIR} -o $@

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -rf ./${NAME}

re: fclean all

-include $(DEPENDENCIES)
-include $(CLIENT_DEPENDENCIES)
