/* Judging program for the task Treasure hunt
 * Author: Jakub Radoszewski
 * Date: 9.06.2011
 */

#include <cstdio>
using namespace std;

#include "treinc.h"
#include "tre.cpp"

int main()
{
  const int MAGIC = 358429321;
  const int MAGIC3 = 898469027; /* the last number in a test case */
  freopen("tests/tre10.in","r",stdin);
  freopen("myoutput.out","w",stdout);
  init();
  int num_calls, magic;
  scanf("%d%d", &num_calls, &magic);
  magic ^= MAGIC;
  num_calls ^= magic;
  for (int i = 1; i <= num_calls; i++)
  {
    int call, a, b;
    scanf("%d%d%d", &call, &a, &b);
    call ^= magic ^ (i + 1);
    a ^= magic;
    b ^= magic;
    if (call == 0)
      path(a, b);
    else
      printf("%d\n", dig(a, b) ^ magic);
  }
  scanf("%d", &magic);
  if (magic != MAGIC3)
  {
    printf("WRONG: the solution tampered with reading the input\n");
    return 1;
  }
  return 0;
}
