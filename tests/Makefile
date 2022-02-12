# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 13:47:20 by iwillens          #+#    #+#              #
#    Updated: 2022/02/12 00:23:53 by iwillens         ###   ########.fr        #
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
						${CLIENT_DIR}/srcs/test_whois.cpp

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
