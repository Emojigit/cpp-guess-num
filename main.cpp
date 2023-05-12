#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <ctime>
#include <sys/time.h>
using namespace std;

int random_num(int lo,int hi) { // contributed by a_k_n, https://www.cplusplus.com/forum/general/107917/
	struct timeval time_now{};
	gettimeofday(&time_now, nullptr);
	srand(time_now.tv_usec);
	return rand()%(hi-lo) + lo;
}

int guess_attempt = 0;

void sigint_handler(int signum) {
   cout << endl << "Ctrl-C pressed, " << guess_attempt << " failed attempt." << endl;
   exit(0);
}

int main() {
	int rand_guess_int = random_num(10,99);
	cout << "Guess Number Game, Under GPLv3 License" << endl;
	cout << "Guess a 2 digit number!" << endl;
	signal(SIGINT, sigint_handler);
	while(1) {
		cout << guess_attempt+1 << " guess attempt: ";
		int x;
		cin >> x;
		++guess_attempt;
		if (cin.fail()) {
			cout << "INVALID NUMBER, NOT AN INT!" << endl;
			std::cin.clear();
        		std::cin.ignore(256,'\n');
        		--guess_attempt;
		} else if ( x < 10 ) {
			cout << "INVALID NUMBER! numbers should bigger then 9" << endl;
			--guess_attempt;
		} else if ( x > 99 ) {
			cout << "INVALID NUMBER! numbers should smaller then 100" << endl;
			--guess_attempt;
		} else if ( x == rand_guess_int ) {
			cout << "YAY! The secret number is " << rand_guess_int << ", you succeed within " << guess_attempt << " attempts!" << endl;
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

