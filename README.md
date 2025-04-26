# C program for MCMC simulations of the Ising model
C program for Markov-Chain Monte-Carlo simulations of the ferromagnetic (meaning J=1) Ising model in D-dimensions. The hamiltonian is
the nearest neighbours Ising model Hamiltonian with vanishing external field h: 
$E[\{s\}]=-\sum_{\langle \textbf{x} \textbf{y}\rangle}s_{\textbf{x}} s_{\textbf{y}}$

# How to use
The compilation is done as usual by make. Some macros can be manually modified in include/macro.h. 
Run the binary with ./Ising to display a helper message to start your simulations.

DIM $\rightarrow$ dimension of the problem 

UPDATER:

0 $\rightarrow$ Metropolis

1 $\rightarrow$ heatbath (not yet supported)

2 $\rightarrow$ single cluster (not yet supported)

OMP_MODE:

0 $\rightarrow$ inactive

1 $\rightarrow$ active with NTHREADS OpenMP threads
