all: probing chaining AlexCoin


probing:
	g++ -std=c++17 -O3 -o probing runner_probing.cpp Hash.cpp ProbingHashTable.cpp
chaining:
	g++ -std=c++17 -o chaining runner_chaining.cpp Hash.cpp ChainingHashTable.cpp
AlexCoin:
	g++ -std=c++17 -o AlexCoin AlexCoin.cpp	Hash.cpp
clean:
	rm probing chaining AlexCoin
	