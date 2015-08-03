#include <stdio.h>
#include <math.h>

main() {
	unsigned long int p = 24, q = 24; // Arbitrary, non-prime numbers
	unsigned long int n, t, e, d;

	printf("RSA Encryptor/Decryptor\n\n");

	// Take in two prime numbers
	while(!prime(p)) {
		printf("Enter a prime number(p): ");
		scanf("%d", &p);
	}
	while(!prime(q)) {
		printf("Enter a prime number(q): ");
		scanf("%d", &q);
	}

	// Calculate n
	n = p * q;
	printf("n: %d\n", n);

	// Calculate the totient of n
	t = n - (p + q - 1);
	printf("t(n): %d\n", t);

	// Print possible values of e
	printf("Some possible values for e:\n");
	unsigned long int x, y = 0;
	for(x = t-1; x > 0; x--) {
		// e must be coprime to t and should not be equal to p or q
		if (t % x == 0 || !prime(x) || x == p || x == q) continue;
		
		printf("%d (", x);
		print_bin(x);
		printf(")\n");

		y++;
		if (y > 25) break; // limit the number of options printed to the screen
	}
	printf("\n");
	
	// Allow the user to select one
	e = 24; // Arbitrary, non-prime number
	while(t % e == 0 || !prime(e) || e == p || e == q) {
		printf("Please select a value for e: ");
		scanf("%d", &e);
	}

	// Calculate a value for d
	d = 1;
	while(1) { d += t; if (d % e == 0) { d /= e; break; } }
	printf("d: %d\n", d);

	printf("\nPublic Key: e=%d,n=%d\n", e, n);
	printf("\bPrivate Key: d=%d\n", d);

	// MOD TESTING
	//printf("%d\n", mod(8363, 11787, 137*131, 137, 131));

	return 0;
}

prime(unsigned long int num) {
	unsigned long int x;
	for(x = 2; x < sqrt(num) + 1; x++) 
		if (num % x == 0) return 0;
	return 1;
}

print_bin(unsigned long int num) {
	while(num) {
		num & 1 ? printf("1"): printf("0");
		num >>= 1;
	}
}

mod(int m, int exp, int n, int p, int q) {
	// CRT optimized modular exponentiation
	int dp = exp % (p - 1);
	int dq = exp % (q - 1);
	int q_inv = (1 / q) % p;
	int m_1 = (int)pow(m, dp) % p;
	int m_2 = (int)pow(m, dq) % q;
	int h = q_inv * (m_1 - m_2 + p) % p;
	
	return m_2 + h * q;
}
