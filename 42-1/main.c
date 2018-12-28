#include <dlfcn.h>
#include <pthread.h>
#include "tlpi_hdr.h"

int main()
{
	void *fooHandle, *barHandle;
	void (*foo)(void);
	void *(*bar)(void *);
	const char *err;

	fooHandle = dlopen("libfoo.so", RTLD_LAZY);
	if (fooHandle == NULL)
		fatal("dlopen: %s", dlerror());

	barHandle = dlopen("libbar.so", RTLD_LAZY);
	if (fooHandle == NULL)
		fatal("dlopen: %s", dlerror());

	(void) dlerror();
	*(void **) (&foo) = dlsym(fooHandle, "foo");
	err = dlerror();
	if (err != NULL)
		fatal("dlsym: %s", err);

	(void) dlerror();
	*(void **) (&bar) = dlsym(barHandle, "bar");
	err = dlerror();
	if (err != NULL)
		fatal("dlsym: %s", err);

	printf("Calling foo of libfoo.so from main\n");
	(*foo)();

	pthread_t t;
	void *res;
	int s;

	printf("Creating a thread that calls bar of libbar.so from main\n");
	s = pthread_create(&t, NULL, *bar, NULL);
	if (s != 0)
		errExitEN(s, "pthread_create");

	sleep(2);

	printf("Closing libfoo.so with dlclose()\n");
	dlclose(fooHandle);

	s = pthread_join(t, &res);
	if (s != 0)
		errExitEN(s, "pthread_join");

	exit(EXIT_SUCCESS);
}
