/*
*Developer: Ezra Gordon
*Reviewer: Tom Goldberg
*Status: A
*/

#include <stdio.h> /* printf */
#include <stdlib.h>	/* malloc */

int Flavius(int num_of_soldiers);

int main ()
{
    Flavius(100);
	printf("\n------------------------\n");
	Flavius(50);
	printf("\n------------------------\n");
	Flavius(6);
    return (0);
}

/* Finds the last living soldier after each one takes his turn, in order, to 
to stab and kill the soldier to his right using a "sword". If the soldier whose 
turn it is to kill is dead, the sword passes to the next soldier. Once there is 
one soldier left, he is deemed the lucky soldier */
 
int Flavius(int num_of_soldiers)
{
    int *soldiers = NULL;
    int i = 0;
    int *sword = NULL;
    int *up_next = NULL;
    int up_next_counter = 0;

	soldiers = (int *)malloc(sizeof(int) * num_of_soldiers);

	if (NULL == soldiers)
	{
		return (0);
	}

    sword = soldiers;           	  	  /* Sword starts with first soldier. */
    up_next = soldiers + 1;       				    	   /* soldier to die. */

    while (i < num_of_soldiers)                        /* Summon the soldiers */
    {
        soldiers[i] = 1;
        ++i;
    }

    while (sword != up_next)                   /* While more than one is left */
    {
        *up_next = 0;                      					  /* Soldier dies */

        do
        {
            ++sword;                                     /* Pass on the sword */

			/* Woa there, too far. Go back to first soldier */
            if (sword >= (soldiers + num_of_soldiers))

            {
                sword = soldiers;
            }
        }
        while (0 == *sword);            	/* He's dead... Pass the sword on */

		/* When it's 2, we've reached the next one to get killed */
        while (2 != up_next_counter)
        {
            ++up_next;

            if (up_next >= (soldiers + num_of_soldiers))
            {
                up_next = soldiers;
            }

            if (1 == *up_next)                 /* Next soldier to go is found */
            {
                ++up_next_counter;
            }
        }
        up_next_counter = 0;
    }

    i = 0;
    while (i < num_of_soldiers)
    {
        if (1 == soldiers[i])
        {
            printf("Of %d soldiers, soldier #%d was the lucky one\n",
														  num_of_soldiers, i+1);
        }
/*        else
        {
            printf("Soldier #%d: DEAD\n", i+1);
        }
*/
        ++i;
    }

	free(soldiers); soldiers = NULL;

	return (0);
}
