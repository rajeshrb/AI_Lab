
/*
 * File name : perceptron.c
 *
 * This program is an implementation of the "Perceptron" - a classic neural
 * network structure. It's used as a helper program read from a Tk shell.
 * It reads points from a file and prints to the standard output a set of 2
 * x:y pairs, that correspond to a line that seperates the plain into two
 * regions, a region where the perceptron's output will be true, and a region
 * where the perceptron's output will be false.
 *
 */

#include <stdio.h>

#define NUM 2         /* Number of input nodes */
#define LIMIT 100     /* Maximum number of inputs the system can handle */
#define SESSIONS 3000 /* Number of training sessions that we'll put the system through */

typedef struct
{
  float p[NUM];
} vector;

vector w, test[LIMIT];
int hits[LIMIT], total;

float bias = 0.5;

print_vector( v ) vector v;
{
  int i;
  for ( i = 0 ; i < NUM ; i++ ) printf("  %.4f ", v.p[i] );
  printf("\n");
}

float sum( x ) vector x;
{
  int i;
  float s = 0.0;
  for ( i = 0 ; i < NUM ; i++ )  s += x.p[i];
  return s;
}

float scalar_mult( x, y ) vector x, y;
{
  int i;
  float s = 0.0;
  for ( i = 0 ; i < NUM ; i++ )  s += ( x.p[i] * y.p[i] );
  return s;
}

/*-----------------------------------------------------------------------*\
|                                                                         |
|  This function computes the NN's output for a certain input vector      |
|                                                                         |
\*-----------------------------------------------------------------------*/
int net( x ) vector x;
{
  return( (scalar_mult( x, w ) + bias > 0.0));
}

/*-----------------------------------------------------------------------*\
|                                                                         |
|  Educate the NN with all training inputs                                |
|                                                                         |
\*-----------------------------------------------------------------------*/
educate_net()
{
  vector x;
  int i, j, correct_result;

  for ( i = 0 ; i < total ; i++ )
    {
      x = test[i];
      correct_result = hits[i];

      if ( net(x) != correct_result )
        if ( correct_result == 0 )
          {
            /* False alarm */
            for (j=0;j<NUM;j++) w.p[j] -= x.p[j];
            bias -= 1.0;
          }
        else
          {
            /* Miss */
            for (j=0;j<NUM;j++) w.p[j] += x.p[j];
            bias += 1.0;
          }
    }
}

/*-----------------------------------------------------------------------*\
|                                                                         |
|  Return the number of cases for which the NN returns the correct value  |
|                                                                         |
\*-----------------------------------------------------------------------*/
check_performance()
{
  vector x;
  int j, count=0;
  for ( j = 0 ; j < total ; j++ )
    {
      x = test[j];
      if ( net(x) == hits[j] )
        count++;
    }
  return count;
}

/*-----------------------------------------------------------------------*\
|                                                                         |
|  Get data (read input file)                                             |
|                                                                         |
\*-----------------------------------------------------------------------*/
int get_data()
{
  char* FileName = "input";
  FILE *fd;
  int i, posnum, negnum;
  float x,y;

  /* opens the file  */
  if ( (fd = fopen(FileName,"r")) == NULL )
    {
      printf ("no-input-file is provided");
      exit(10);
    }

  /* Total number of input values */
  total = 0;

  /* read the positive examples */
  fscanf( fd, "%d", &posnum);
  printf("value of posnum %d\n", posnum);
  if (posnum > LIMIT)
    {
      printf("Error 1");
      exit(20);
    }
  for ( i = 0 ; i < posnum ; i++ )
    {
      fscanf( fd, "%f %f", &x, &y);
      test[ total ].p[0] = x / 1000;
      test[ total ].p[1] = y / 1000;
      hits[ total++ ] = 1;  /* 1 for positive examples */
    }

  /* read the negative examples */
  fscanf( fd, "%d", &negnum);
  printf("value of negnum %d\n", negnum);
  if ((negnum+total) > LIMIT)
    {
      printf("Error 2");
      exit(21);
    }
  for ( i = 0 ; i < negnum ; i++ )
    {
      fscanf( fd, "%f %f", &x, &y);
      test[ total ].p[0] = x / 1000;
      test[ total ].p[1] = y / 1000;
      hits[ total++ ] = 0; /* 0 for negative example */
    }
    printf("value of total %d\n", total);
  return (0) ;
}

/*-----------------------------------------------------------------------*\
|                                                                         |
|  Main                                                                   |
|                                                                         |
\*-----------------------------------------------------------------------*/
main()
{
  int i=0, test = 0;
  int speed, dist, road;
  vector x;
  float px, py, px1, py1;

  for ( i = 0 ; i < NUM ; i++ ) w.p[i] = 0.0;

  get_data();  /* Read input from file */

  /* educate the net */
  while ( ((test=check_performance()) != total ) && ( i++ < SESSIONS ) )
      educate_net();

  if ( check_performance() != total)
    {
      printf("fail");
      exit(1);
    }

  /* We'll calculate the intersection with the visible box [0..350, 0..350] */
  px = -1000 * bias / w.p[0];
  py = -1000 * bias / w.p[1];

  px1 = ((py-350)/py) * px ;
  py1 = py - 350*py/px ;

  if ( (px  >= 0) && (px  <= 350))  printf("%d %d ", (int)px, 0 );
  if ( (py  >= 0) && (py  <= 350))  printf("%d %d ", 0, (int)py );
  if ( (px1 >= 0) && (px1 <= 350))  printf("%d %d ", (int)px1, 350 );
  if ( (py1 >= 0) && (py1 <= 350))  printf("%d %d ", 350, (int)py1 );
}