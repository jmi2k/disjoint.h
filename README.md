# disjoint - disjoint types (aka sum types) for C

```c
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
		printf("ERROR %p!\n", (void *) m);
		break;
	}
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

# Known bugs

- For variants with no data, empty braces are generated. In theory it is not
  allowed by the spec, but in practice it works well enough across compilers.
