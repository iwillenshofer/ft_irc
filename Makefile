# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 13:47:20 by iwillens          #+#    #+#              #
#    Updated: 2022/01/23 20:28:56 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = clang++
CCFLAGS = -Wall -Werror -Wextra -g -std=c++98 -pedantic -fsanitize=address

SRC_DIR = ./srcs
OBJ_DIR = ./build

INC_DIR = ./${SRC_DIR}

SRCS = 	${SRC_DIR}/main.cpp \
			${SRC_DIR}/Debug.cpp \
			${SRC_DIR}/Socket.cpp \
			${SRC_DIR}/FileDescriptors.cpp \
			${SRC_DIR}/utilities.cpp \
			${SRC_DIR}/WebServer.cpp \
			${SRC_DIR}/Client.cpp \
			${SRC_DIR}/Commands.cpp \
			${SRC_DIR}/Commands/pass.cpp \
			${SRC_DIR}/Commands/nick.cpp \
			${SRC_DIR}/Commands/user.cpp \
			${SRC_DIR}/Commands/oper.cpp \
			${SRC_DIR}/Commands/mode.cpp \
			${SRC_DIR}/Commands/quit.cpp \
			${SRC_DIR}/Commands/join.cpp \
			${SRC_DIR}/Commands/part.cpp \
			${SRC_DIR}/Commands/mode_channel.cpp \
			${SRC_DIR}/Commands/topic.cpp \
			${SRC_DIR}/Commands/names.cpp \
			${SRC_DIR}/Commands/list.cpp \
			${SRC_DIR}/Commands/invite.cpp \
			${SRC_DIR}/Commands/kick.cpp \
			${SRC_DIR}/Commands/privmsg.cpp \
			${SRC_DIR}/Commands/notice.cpp \
			${SRC_DIR}/Commands/motd.cpp \
			${SRC_DIR}/Commands/lusers.cpp \
			${SRC_DIR}/Commands/version.cpp \
			${SRC_DIR}/Commands/stats.cpp \
			${SRC_DIR}/Commands/links.cpp \
			${SRC_DIR}/Commands/time.cpp \
			${SRC_DIR}/Commands/trace.cpp \
			${SRC_DIR}/Commands/admin.cpp \
			${SRC_DIR}/Commands/info.cpp \
			${SRC_DIR}/Commands/who.cpp \
			${SRC_DIR}/Commands/whois.cpp \
			${SRC_DIR}/Commands/whowas.cpp \
			${SRC_DIR}/Commands/kill.cpp \
			${SRC_DIR}/Commands/ping.cpp \
			${SRC_DIR}/Commands/pong.cpp \
			${SRC_DIR}/Commands/error.cpp \
			${SRC_DIR}/Channel.cpp \
			${SRC_DIR}/Mask.cpp



OBJECTS = $(patsubst ${SRC_DIR}/%.cpp, ${OBJ_DIR}/%.o, ${SRCS})
DEPENDENCIES = $(patsubst %.o, %.d, ${OBJECTS})

all: ${NAME}

${NAME}: ${OBJECTS}
	@${CC} ${CCFLAGS} ${OBJECTS} -I. -I ${INC_DIR} -o ${NAME}
	@echo "\033[92m./${NAME} is built. \033[0m"

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	@mkdir -p $(dir $@)
	@echo -n "."
	@${CC} ${CCFLAGS} -MMD -c  $< -I. -I ${INC_DIR} -o $@

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -rf ./${NAME}

re: fclean all

-include $(DEPENDENCIES)
