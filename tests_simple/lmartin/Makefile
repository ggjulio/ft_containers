# https://misc.flogisoft.com/bash/tip_colors_and_formatting
_BOLD      =\e[1m
_DIM       =\e[2m
_UNDERLINE =\e[4m
_BLINK     =\e[5m
_REVERSE   =\e[7m
_HIDDEN    =\e[8m

# RESET list
_R          =\e[0m
_RBOLD      =\e[21m
_RDIM       =\e[22m
_RUNDERLINE =\e[24m
_RBLINK     =\e[25m
_RREVERSE   =\e[27m
_RHIDDEN    =\e[28m

# Colors
_RED      =\e[91m
_GREEN    =\e[92m
_YELLOW   =\e[93m
_BLUE     =\e[94m
_MAGENTA  =\e[35m
_CYAN     =\e[96m
_WHITE    =\e[97m

# Inverted, i.e. colored backgrounds
_IRED     =\e[101m
_IGREEN   =\e[102m
_IYELLOW  =\e[103m
_IBLUE    =\e[104m
_IMAGENTA =\e[45m
_ICYAN    =\e[106m
_IWHITE   =\e[107m

#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/20 12:43:01 by juligonz          #+#    #+#              #
#    Updated: 2020/08/24 16:37:55 by juligonz         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

UNAME := $(shell uname)

NAME = a.out

SRC_DIR = ./ ../../src 
INC_DIR = $(shell find . -type d -name "includes")
INC_DIR+= $(shell find ../../includes -type d)

OBJ_DIR = obj

SRCS_DIR = $(shell find $(SRC_DIR) -type d)

vpath %.hpp $(INC_DIR)

SRC = main.cpp rb_tree.cpp

SRC+= test_map.cpp
SRC+= test_stack.cpp
SRC+= test_vector.cpp



OBJ = $(addprefix  $(OBJ_DIR)/,$(SRC:%.cpp=%.o))
vpath %.cpp $(SRCS_DIR)

DEP = $(addprefix  $(OBJ_DIR)/,$(SRC:%.cpp=%.d))


LDFLAGS = $(foreach lib, $(LIB_DIR),-L$(lib))  $(foreach lib, $(LIB),-l$(lib))

CXX = clang++
CXXFLAGS  = -Wall -Wextra -Werror -std=c++98 -MMD -MP #-g -fstandalone-debug #-fsanitize=address  -fsanitize=undefined -fstack-protector  
IFLAGS  = $(foreach inc, $(INC_DIR),-I$(inc))

all:  $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -o $@ $(OBJ) $(LDFLAGS)
	@printf "$(_GREEN)Compiled : $(_MAGENTA)$(NAME)$(_R)\n"
	@printf "\nDo $(_CYAN)$(_BOLD)make show$(_R) to debug the Makefile\n"
	@printf "Do $(_RED)$(_BOLD)make debug$(_R) to run tests with lldb\n"
	@printf "Do $(_YELLOW)$(_BOLD)make valgrind$(_R) to run valgrind $(_MAGENTA)(May have falses positives under OSX)$(_R)\n"

run: $(NAME)
	@./$(NAME)

debug:	CXXFLAGS += -g
debug: $(NAME)
	@lldb $(NAME)

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes --log-file=output_valgrind ./$(NAME)
	@printf "$(_BOLD)$(_RED)################################################################$(_R)\n"
	@printf "$(_BOLD)$(_RED)##########################  $(_GREEN)Valgrind$(_RED)  ##########################$(_R)\n"
	@printf "$(_BOLD)$(_RED)################################################################$(_R)\n\n"
	@cat output_valgrind

show:
	@printf "$(_MAGENTA)UNAME  :$(_GREEN)  $(UNAME)$(_END)\n"
	@printf "$(_MAGENTA)ARCH   :$(_GREEN)  $(shell uname -p)$(_END)\n\n"
	@printf "$(_CYAN)NAME   :$(_RED)  $(NAME)$(_END)\n"
	@printf "$(_CYAN)NS_NAME:$(_RED)  $(NS_NAME)$(_END)\n\n"
	@printf "$(_CYAN)CXX    :$(_RED)  $(CXX)$(_END)\n"
	@printf "$(_CYAN)CXXFLAGS :$(_RED)  $(CXXFLAGS)$(_END)\n"
	@printf "$(_CYAN)IFLAGS :$(_RED)  $(IFLAGS)$(_END)\n"
	@printf "$(_CYAN)LDFLAGS :$(_RED)  $(LDFLAGS)$(_END)\n\n"
	@printf "$(_CYAN)SRC_DIR:$(_RED)  $(SRC_DIR)$(_END)\n"
	@printf "$(_CYAN)INC_DIR:$(_RED)  $(INC_DIR)$(_END)\n"
	@printf "$(_CYAN)LIB_DIR:$(_RED)  $(LIB_DIR)$(_END)\n\n"
	@printf "$(_CYAN)SRC    :$(_RED)  $(SRC)$(_END)\n"
	@printf "$(_CYAN)OBJ    :$(_RED)  $(OBJ)$(_END)\n"
	@printf "$(_CYAN)DEP     :$(_RED)  $(DEP)$(_END)\n"

clean:
	@rm -rf $(OBJ_DIR) output_valgrind
	@printf "$(_RED)Removed :$(_MAGENTA) $(OBJ_DIR)/$(_MAGENTA)\n"

fclean: clean
	@rm -fr $(NAME) $(NAME).dSYM/
	@printf "$(_RED)Removed : $(_MAGENTA)./$(NAME), $(NAME).dSYM/$(_R)\n"

re: fclean all

-include $(DEP)

.PHONY: all run debug valgrind show clean fclean re
