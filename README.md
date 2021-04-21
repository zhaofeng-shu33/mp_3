Mathematical Programming Code implemented in C++ when I am 
in third year of undergraduate.

## Simplex Algorithm

Simplex algorithms solves the primal form of linear programming:
$$
\begin{align}
\min \, & c^T x \\
s.t.\,& Ax=b, x\geq 0
\end{align}
$$
where $A$ is an $m\times n$ matrix, $b$ is an $m$ dimensional vector, and $x,c$ are $n$ dimensional vectors.

## Input data format

a txt file containing the following:
```
-1 -2 0 0 0 0
1 0 1 0 0 1
0 1 0 1 0 1
1 1 0 0 1 1.5
```
Omitting the upper right element 0,
the first line gives the vector $c$. The last column gives $b$.
The remaining block is the matrix $A$.
If $A$ has shape $m\times n$, we require that the input block has shape
$(m+1) \times (n+1)$.
Therefore, the above input file describes a LP problem in the following sense:

![](shape.png)