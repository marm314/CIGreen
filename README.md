# CIGreen
Build Green's function (for the spin up -- spin up channel) from Slater Determinants for spin-compensated systems. 

Works by reading the output of the P. J. Knowles and N. C. Handy full configuration interaction (FCI) code

1) Knowles, P. J. & Handy, N. C. (1984) - A new determinant-based full configuration interaction method, Chemical Physics Letters, 111, 315–321. DOI: 10.1016/0009-2614(84)85513-X.

2) Knowles, P. J. & Handy, N. C. (1989) - A determinant based full configuration interaction program, Computer Physics Communications, 54, 75–83. DOI: 10.1016/0010-4655(89)90033-7

for the N, N-1, and N+1 systems (users must run these calculations in advance by themselves) and the CI vectors stored in different files. [Feel free to ask me for help to get the FCI code]

Some utilities are provided to adecuate the N+1 and N-1 files for computing the overlaps < N-1 | a_p | N > and < N+1 | a^dagger_p | N> (see the example is test for more details). 

The code builds G as a matrix for G(w_k) and G(tau_k) values; including the imaginary times and frequencies case. Also, the spectral function can be computed if requested (using the retarded Green's function).

Some details:
.............

The code only stores the CI vector for the N system. The rest of CI vectors (for the N-1 and N+1 systems) are read on-the-fly when computing the overlaps to reduce the storage requirements (at expenses of reducing the performance of the code).
