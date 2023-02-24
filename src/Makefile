FLAGS:=-Wall -Werror -Wextra
SRCs:=main.cc game_src/pong.cc

build: clear
	g++ $(SRCs) -o pong_ex

run: build
	./pong_ex

clear:
	rm -rf pong_ex