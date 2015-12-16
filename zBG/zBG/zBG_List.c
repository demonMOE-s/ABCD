#include "zBG_List.h"
#include <windows.h>

BOOL create_list(zBG_List** ppList) {

	*ppList = dlmalloc(sizeof(zBG_List));
	if (*ppList == NULL)	return FALSE;
	(*ppList)->data = NULL;
	(*ppList)->next = NULL;
	return TRUE;
}

void delete_list(zBG_List* pList) {

	zBG_List* pORG_List = pList->next;	
	while(TRUE) {
		if (pORG_List == NULL) {
			if (pList != NULL) dlfree(pList); return;
		} else {
			dlfree(pList); pList = pORG_List; pORG_List = pList->next;
		}
	}
}

