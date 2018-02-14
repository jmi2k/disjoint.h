# disjoint - disjoint types (aka sum types) for C

- _Almost_ C99 compliant (except anonymous structs, available as an extension
  in almost all compilers)
- `typedef`-friendly
- Tiny implementation (5 SLOC) which blends with C syntax.

```c
#include <assert.h>
#include <stdio.h>
#include "disjoint.h"

disjoint Machine { variants(EMPTY, IDLE, BROKEN) {
	#define Empty variant(disjoint Machine, EMPTY)

	#define Idle(B) variant(disjoint Machine, IDLE, .bottles = B)
	unsigned int bottles;

	#define Broken(E) variant(disjoint Machine, BROKEN, .error = E)
	char *error;
	};
};

void
takebottle(disjoint Machine *m)
{
	match (*m) {
	case EMPTY:
		printf("No bottles left.\n");
		break;
	case IDLE:
		printf("Take it! Bottles left: %u\n", --m->bottles);
		if (!m->bottles)
			*m = Empty;
		break;
	case BROKEN:
		printf("ERROR %p: %s\n", (void *) m, m->error);
		break;
	}
}

void refill(disjoint Machine *m, unsigned int bottles)
{
	assert(variantof(*m) == EMPTY);
	*m = Idle(bottles);
}

int
main(void)
{
	disjoint Machine m = Idle(4);

	while (variantof(m) != EMPTY)
		takebottle(&m);

	return 0;
}
```
