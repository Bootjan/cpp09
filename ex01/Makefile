SRC_DIR = src
SRCS			:=$(wildcard $(SRC_DIR)/*.cpp) \
				main.cpp
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
NAME = RPN
VPATH = . src/

I_DIRS := $(shell find . -type f -name "*.hpp" -exec dirname {} + | uniq)
INCLUDE = $(I_DIRS:%=-I%)

CC = c++
CFLAGS := -Wall -Werror -Wextra -Wpedantic -std=c++11
OBJS_DIR = ./objs

ifdef LOG
	CFLAGS	+=-D LOG=0
endif

ifdef SAN
	CFLAGS	+=-fsanitize=address
endif

ifdef BUG
	CFLAGS	+=-g
endif

RM = rm -f

all:	$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)
	@echo "./$(NAME) made!"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "./objs made!"

$(OBJS_DIR)/%.o:	%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean:	
	@$(RM) -r $(OBJS_DIR)
	@echo "$(NAME) objects removed!"

fclean: clean
	@$(RM) $(NAME)
	@echo "./$(NAME) removed!"
	@rm -rf $(OBJS_DIR)
	@echo "./objs removed!"

re: fclean all

nolog:
	@$(MAKE) LOG=1
.PHONY: nolog

relog: fclean nolog
.PHONY: relog

fsan:
	@$(MAKE) SAN=1 BUG=1
.PHONY: fsan

resan: fclean fsan
.PHONY: resan

debug:
	@$(MAKE) BUG=1
.PHONY: debug

rebug: fclean debug
.PHONY: rebug

.PHONY: all clean re fclean fsan desan
