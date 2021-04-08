#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <ctime>
using namespace std;

int random_num(int lo,int hi) { // contributed by a_k_n, https://www.cplusplus.com/forum/general/107917/
	srand(time(NULL));
	return rand()%(hi-lo) + lo;
}

int guess_attempt = 0;

void sigint_handler(int signum) {
   cout << "Ctrl-C pressed, " << guess_attempt << " failed attempt." << endl;
   exit(0);
}

int main() {
	int rand_guess_int = random_num(10,99);
	cout << "Guess Number Game, Under GPLv3 License" << endl;
	cout << "Guess a 2 digit number!" << endl;
	signal(SIGINT, sigint_handler);
	while(1) {
		cout << guess_attempt++ << " guess attempt: ";
		int x;
		cin >> x;
		++guess_attempt;
		if ( x == rand_guess_int ) {
			cout << "YAY! The secret number is " << rand_guess_int << ", you success within " << guess_attempt << " attempts!" << endl;
			return 0;
		} else if ( x < rand_guess_int ) {
			cout << "Your guess is too small!" << endl;
		} else if ( x > rand_guess_int ) {
			cout << "Your guess is too big!" << endl;
		} else {
			cout << "ERROR!" << endl;
			return 1;
		}
	}
}

