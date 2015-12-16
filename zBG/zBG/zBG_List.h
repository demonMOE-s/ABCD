#ifndef ___$zBG__LIST_
#define ___$zBG__LIST_

#include "zBG_dlmalloc.h"
#include "zBG_Marco.h"
#include <windows.h>

typedef struct _zBG_List {
	void* data;
	struct _zBG_List* next;
} zBG_List;

void FORCEINLINE insert_list(zBG_List* pList, void* data) {

	zBG_List* zBG_Poll_List;
	zBG_List* zBG_Mal_List = dlmalloc(sizeof(zBG_List));
	zBG_Mal_List->next = NULL;
	zBG_Mal_List->data = data;
	if (pList->next == NULL
	&&  pList->data == NULL) {
		pList->data = data;
		pList->next = NULL;
		return;
	}
	while(TRUE) {
		if (pList->next == NULL) {
			pList->next = zBG_Mal_List;
			return;
		}	
		pList = pList->next;
	}
}

BOOL create_list(zBG_List** ppList);
void delete_list(zBG_List* pList);

#endif