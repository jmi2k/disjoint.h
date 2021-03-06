# disjoint - disjoint types (aka sum types) for C

- `typedef`-friendly
- Tiny implementation (<10 SLOC) which blends nicely with C syntax.

```c
#include <assert.h>
#include <stdio.h>
#include "disjoint.h"

disjoint Machine {
	variants(EMPTY, IDLE, BROKEN) {
		unsigned int bottles;
		char *error;
	};
};

#define Empty emptyvariant(disjoint Machine, EMPTY)
#define Idle(B) variant(disjoint Machine, IDLE, .bottles = B)
#define Broken(E) variant(disjoint Machine, BROKEN, .error = E)

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

void
refill(disjoint Machine *m, unsigned int bottles)
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

# Installation using [clib](http://clibs.org)

```sh
clib install jmi2k/disjoint.h
```

# Known bugs

- Under clang, `emptyvariant` causes "warning: missing field '' initializer".
