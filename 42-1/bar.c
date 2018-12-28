#include <dlfcn.h>
#include "tlpi_hdr.h"

extern void foo();

void *bar(void *arg)
{
	void *fooHandle;
	void (*foo)(void);
	const char *err;

	fooHandle = dlopen("libfoo.so", RTLD_LAZY);
	if (fooHandle == NULL)
		fatal("dlopen: %s", dlerror());

	(void) dlerror();
	*(void **) (&foo) = dlsym(fooHandle, "foo");
	err = dlerror();
	if (err != NULL)
		fatal("dlsym: %s", err);

	for (int i = 0; i >= 0; i++)
		if (0 == i % 100000000)
			(*foo)();

	return NULL;
}
