# C program for MCMC simulations of the Ising model
C program for Markov-Chain Monte-Carlo simulations of the ferromagnetic (meaning $J=1$) Ising model in $D$-dimensions. The hamiltonian is
the nearest neighbor Ising model Hamiltonian with vanishing external field $h$

$$
E[s]=-\sum_{\langle \textbf{x} \textbf{y}\rangle}s_{\textbf{x}} s_{\textbf{y}}
$$

# How to use
The compilation is done as usual by make.

Run the binary with `./Ising` to display a helper message and produce a `template_input.in` file to start your simulations.

the dimensionality `DIM` can be manually modified in `include/macro.h`. 
