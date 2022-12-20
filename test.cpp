#include "pch.h"
#include <chrono>

using namespace std;

int summevonbisfor(int von, int bis){
	int summe = 0;
	for (int i = von; i <= bis; i++) {
		summe += i;
	}
	return summe;
}

int summevonbiswhile(int von, int bis) {
	int i = von;
	int summe = 0;
	while (i <= bis) {
		summe += i;
		i++;
	}
	return summe;
}

TEST(TestCaseName, forschleife) {
	EXPECT_EQ(summevonbisfor(1, 10), 55);
	EXPECT_EQ(summevonbisfor(1, 4), 10);
}

TEST(TestCaseName, whileschleife) {
	EXPECT_EQ(summevonbiswhile(1, 10), summevonbisfor(1,10));
	EXPECT_EQ(summevonbiswhile(1, 4), summevonbisfor(1,4));
}

bool teilbar(int a, int b){
	return (a % b == 0);
}



TEST(Primes, teilbarkeit) {
	EXPECT_EQ(teilbar(4, 2), true);
	EXPECT_EQ(teilbar(4, 3), false);
	EXPECT_EQ(teilbar(2, 4), false);
}
bool isPrime(int zahl){	
	if (teilbar(zahl, 2)) { 
		return false; 
	}
	for (int i = 3; i <= std::sqrt(zahl); i += 2) {
		if (teilbar(zahl, i)){
			return false;
		}		
	}
	return true;
}



bool isPrimeclever(int zahl) {

	vector<int> allezahlen = {};
	for (int i = 2; i <= std::sqrt(zahl); i++) {
		allezahlen.push_back(i);
	}

	std::vector<int>::iterator iterator;
	
	for(int i : allezahlen){
		if (teilbar(zahl, i)) {
			return false;
		}
		else {
			for(int zuloeschendezahl = i+i; zuloeschendezahl < zahl; zuloeschendezahl += i) { 
				iterator = find(allezahlen.begin(), allezahlen.end(), zuloeschendezahl);
				if (iterator != allezahlen.end()) {
					allezahlen.erase(iterator);
				}
			}
		}

	}
	
    return true;
}

TEST(Primzahltest, testoverrange) {
	EXPECT_EQ(isPrimeclever(7), true);
	EXPECT_EQ(isPrimeclever(4), false);
	EXPECT_EQ(isPrimeclever(101), true);
	auto start = chrono::high_resolution_clock::now();
	cout << isPrimeclever(999999999989) << endl;
	auto stop = chrono::high_resolution_clock::now();
	auto diff = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "Schlau: " << diff.count() << endl;
}

TEST(Primzahltest, isPrime) {
	EXPECT_EQ(isPrime(7), true);
	EXPECT_EQ(isPrime(4), false);
	auto start = chrono::high_resolution_clock::now();
	cout << isPrime(999999999989) << endl;
	auto stop = chrono::high_resolution_clock::now();
	auto diff = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "Dumm: " << diff.count() << endl;
}

bool SieveOfEratosthenes(long long int n)
{
	// Create a boolean array "prime[0..n]" and initialize
	// all entries it as true. A value in prime[i] will
	// finally be false if i is Not a prime, else true.
	std::vector<bool> prime(n+1,true);

	for (int p = 2; p * p <= n; p++) {
		// If prime[p] is not changed, then it is a prime
		if (prime[p] == true) {
			// Update all multiples of p greater than or
			// equal to the square of it numbers which are
			// multiple of p and are less than p^2 are
			// already been marked.
			for (int i = p * p; i <= n; i += p)
				prime[i] = false;
		}
	}
	return prime[n];
}


TEST(Primzahltest, eras) {
	auto start = chrono::high_resolution_clock::now();
	cout << SieveOfEratosthenes(999999999) << endl;
	auto stop = chrono::high_resolution_clock::now();
	auto diff = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "gekauft: " << diff.count() << endl;
}
