all: clean example1
run:
	@echo "Running example1"
	@./example1

example1:
	@echo "Compiling example1"
	@g++ -Wall Secex.cpp PackCommunication.cpp example1.cpp -o example1

clean:
	@echo "Removing binaries"
	@rm -f example1