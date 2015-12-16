#ifndef ___$zBG__SOUND_
#define ___$zBG__SOUND_

#include <d3d9.h>
#include <d3dx9.h>
#include <XAudio2.h>
#include <dinput.h>
#include "zBG_Marco.h"
#include "zBG_List.h"
#include "zBG_Background_Buffer_m.h"


typedef struct _sound_slot {
	
	char* FileName; /* wave index */ 
	void* ActulWaveData; /* dlmalloc malloc's mem (align 16) */
	DWORD WaveSize;		
	DWORD Sound_Status;
	XAUDIO2_BUFFER SND_Tools; /* play tools */
	WAVEFORMATEX SND_Infos; /* wave Info */ 
	IXAudio2SourceVoice* SNDs; /* sound track */
} sound_slot;

void _destroy_wave_slot(void);

#endif 