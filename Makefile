NAME = Matt_daemon

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

CXXFLAGS += -I $(INC_DIR)

INC_DIR = ./include

SRC_DIR = ./src

SRC_FILES = main.cpp TintinReporter.cpp FileHandler.cpp

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

docker:
	docker-compose up --build

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
