CXX = c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
LDFLAGS = 

ifdef FSAN
	CXXFLAGS +=-fsantitize=address
endif

ifdef BUG
	CXXFLAGS +=-g
endif

NAME = webserv

SRC = main.cpp
OBJ = $(SRC:%.cpp=%.o)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

fsan:
	$(MAKE) FSAN=1 BUG=1
.PHONY: fsan

resan:	fclean fsan
.PHONY: resan

debug:
	$(MAKE) BUG=1
.PHONY: debug

rebug:	fclean debug
.PHONY: rebug