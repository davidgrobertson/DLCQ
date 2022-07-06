#include <stdio.h>
#include <stdlib.h>

#define MAXSTATES 100

/* Global variable: */
int *state[MAXSTATES];

/* ======================================================================== */

int parts (int n)
{
  int nparts, i, j, k, len;

  /* Base case for recursion: */
  if (n == 1) {
    state[0][0] = 1;
    nparts = 1;
  }
  else {
    nparts = parts(n - 1);

    /* Build the new partitions for the current n: */
    i = 0;
    while (state[i][0] != 0) {

      /* Find length of this partition: */
      len = 0;
      while (state[i][++len] != 0 && len < n-1)
	;

      /* Here is one of thes partitions of n: */
      state[i][len] = 1;
      i++;

      /* Here is the other, potentially: */
      if (len == 1 || state[i-1][len-2] > state[i-1][len-1]) {

	/* Shift later perms up to make room: */
	for (j = nparts-1; j>=i-1; j--)
	  for (k=0; k<n; k++)
	    state[j+1][k] = state[j][k];
	state[i][len] = 0;
	state[i][len-1] += 1;
	i++;
	nparts++;
      }
    }
  }
  return nparts;
}

/* ======================================================================== */

int main(int argc, char *argv[])
{
  int k, i, j;

  /* Get the algorithm working, then switch to dynamical allocation
     using realloc... */
  k = atoi(argv[1]);

  /* Setup */
  for (i=0; i<MAXSTATES; i++) {
    state[i] = (int *) calloc(k, sizeof(int));
    for (j=0; j<k; j++)
      state[i][j] = 0;
  }

  printf("There are %d partitions:\n", parts(k));

  for (i=0; i<MAXSTATES; i++) {
    if (state[i][0] != 0) {
      for (j=0; j<k; j++)
	if (state[i][j] != 0)
	  printf("%d ", state[i][j]);
      printf("\n");
    }
  }
  exit(0);
}
