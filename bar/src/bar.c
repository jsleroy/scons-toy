#include "bar/bar.h"

#include <foo/foo.h>

int bar(void)
{
  return foo() + 1;
}
