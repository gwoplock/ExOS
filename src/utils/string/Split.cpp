#include "Split.h"

//This looks like it works but it might not
char **strSplit(char *to_split, char delim)
{
	int spl_ind = -1;
	for (int i = 0; i < strlen(to_split); i++) {
		if (to_split[i] == delim) {
			spl_ind = i;
			break;
		}
	}
	if (spl_ind == -1) {
		return nullptr;
	}
	char **ret = (char**) malloc(2* sizeof(char *));
	ret[0] = to_split;
	ret[0][spl_ind] = '\0';
	ret[1] = to_split + spl_ind + 1;
	return ret;
}