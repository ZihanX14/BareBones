/* strcpy.c - strcpy */

/*
 * strcpy - Copy the string given by the second argument into the first
 */
int	strcpy(char	*tar, char *src){
	while ( (*tar++ = *src++) != '\0') {
		;
	}
	return 0;
}
