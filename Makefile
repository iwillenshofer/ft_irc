# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 13:47:20 by iwillens          #+#    #+#              #
#    Updated: 2022/01/13 13:05:26 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = clang++
CCFLAGS = -Wall -Werror -Wextra -g -std=c++98 -pedantic -fsanitize=address

SRC_DIR = ./srcs
OBJ_DIR = ./build

INC_DIR = .

SRCS = 	${SRC_DIR}/main.cpp \
			${SRC_DIR}/Debug.cpp \
			${SRC_DIR}/Socket.cpp \
			${SRC_DIR}/FileDescriptors.cpp \
			${SRC_DIR}/utilities.cpp \
			${SRC_DIR}/WebServer.cpp \
			${SRC_DIR}/Commands.cpp

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