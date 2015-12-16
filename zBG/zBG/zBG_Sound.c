#include "zBG_Sound.h"
#include "zBG_dlmalloc.h"
#include "zBG_Global.h"
#include <stdlib.h>
#include <string.h>

#define Zl_PLAY_ALONE_IN_BEG_POS	1
#define Zl_PLAY_ALONE_IN_CUR_POS	2
#define Zl_PLAY_ALONE_IN_DES_POS	4
#define Zl_PLAY_LOOP_IN_BEG_POS		8
#define Zl_PLAY_LOOP_IN_CUR_POS		16
#define Zl_PLAY_LOOP_IN_DES_POS		32
#define Zl_PLAY_PAUSE				64
#define Zl_PLAY_FLUSH_STREAM		128
#define Zl_PLAY_MORE				256 
#define Zl_PLAY_RESUME				512

#define Zl_SOUND_BUFFER_UPDATE		4 
#define Zl_SOUND_BUFFER_READY		2
#define Zl_SOUND_BUFFER_STOP		1 
#define Zl_SOUND_BUFFER_CLEAR		0


/* most code from $MS's DirectX SDK Doc */ 

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, PDWORD dwChunkSize /* org - DWORD & dwChunkSize */, PDWORD dwChunkDataPosition /* org - DWORD & dwChunkDataPosition */ )
{
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0; /* val seq hack for c89 */ 

	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	/* == 
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
					== */
	while (hr == S_OK)
	{
		DWORD dwRead;
		if( 0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );

		if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );

		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if( 0 == ReadFile( hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL ) )
				hr = HRESULT_FROM_WIN32( GetLastError() );
			break;

		default:
			if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT ) )
				return HRESULT_FROM_WIN32( GetLastError() );            
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			*dwChunkSize = dwChunkDataSize;
			*dwChunkDataPosition = dwOffset; /* hack add delete ref */ 
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;

	}


	return S_OK;

}

HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	DWORD dwRead;// hack val seq for c89
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, bufferoffset, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	// DWORD dwRead;
	if( 0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL ) )
		hr = HRESULT_FROM_WIN32( GetLastError() );
	return hr;
}

ZBG_API u32 STDWIN32_CALL ZlGetSoundId(const char* name) {

	int	index;               // looping variable
	// step one: are there any open id's ?
	for (index=0; index != 64; index++) {
		if (!strcmp(name,wave_slot[index].FileName)) return index;
	}
	return -1;
}

ZBG_API void STDWIN32_CALL ZlSetSoundLoops(const char* name, DWORD num) {

	int	sound_id = -1,       // id of sound to be loaded
		index;               // looping variable

	// step one: are there any open id's ?
	for (index=0; index != 64; index++)
	{	
		// make sure this sound is unused
		if (wave_slot[index].FileName != 0)
		{
			if (0 == strcmp(name,wave_slot[index].FileName)) 
			{
				wave_slot[index].SND_Tools.LoopCount=num&255;
				break;
			} // end if

		} // end for index
	}
}

ZBG_API void STDWIN32_CALL ZlPlaySound(const char* name, DWORD control_type) {

	int	sound_id = -1,       // id of sound to be loaded
		index;               // looping variable

	// step one: are there any open id's ?
	for (index=0; index != 64; index++)
	{	
		// make sure this sound is unused
		if (wave_slot[index].FileName != 0)
		{
			if (0 == strcmp(name,wave_slot[index].FileName)) 
			{
				sound_id = index;
				break;
			} // end if

		} // end for index
	}
	// did we get a free id?
	if (sound_id==-1)
		return;

	switch(control_type) {

	case Zl_PLAY_MORE:
		{
			if (wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_READY
			||  wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_CLEAR) {

				wave_slot[sound_id].SNDs->lpVtbl->SubmitSourceBuffer( wave_slot[sound_id].SNDs, &wave_slot[sound_id].SND_Tools, NULL );

			} else if (wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_STOP) {

				wave_slot[sound_id].SNDs->lpVtbl->FlushSourceBuffers(wave_slot[sound_id].SNDs);
				wave_slot[sound_id].SNDs->lpVtbl->Start(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
				wave_slot[sound_id].SNDs->lpVtbl->SubmitSourceBuffer( wave_slot[sound_id].SNDs, &wave_slot[sound_id].SND_Tools, NULL );
			} else if (wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_UPDATE) {

				wave_slot[sound_id].SNDs->lpVtbl->Stop(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
				wave_slot[sound_id].SNDs->lpVtbl->FlushSourceBuffers(wave_slot[sound_id].SNDs);
				wave_slot[sound_id].SNDs->lpVtbl->Start(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
				wave_slot[sound_id].SNDs->lpVtbl->SubmitSourceBuffer( wave_slot[sound_id].SNDs, &wave_slot[sound_id].SND_Tools, NULL );
			}
			wave_slot[sound_id].Sound_Status = Zl_SOUND_BUFFER_UPDATE;
		}
		break;

	case Zl_PLAY_PAUSE:
		{
			if (wave_slot[sound_id].Sound_Status != Zl_SOUND_BUFFER_STOP) {

				wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_STOP;
				wave_slot[sound_id].SNDs->lpVtbl->Stop(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
				wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_STOP;
			}
		}
		break;
	case Zl_PLAY_RESUME:
		{
			if ( wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_STOP ) {
			
				wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_READY;
				wave_slot[sound_id].SNDs->lpVtbl->Start(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);

			}
		}
		break;

	case Zl_PLAY_FLUSH_STREAM:
		{
			wave_slot[sound_id].Sound_Status == Zl_SOUND_BUFFER_CLEAR;
			wave_slot[sound_id].SNDs->lpVtbl->Stop(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
			wave_slot[sound_id].SNDs->lpVtbl->FlushSourceBuffers(wave_slot[sound_id].SNDs);
			wave_slot[sound_id].SNDs->lpVtbl->Start(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
			wave_slot[sound_id].SNDs->lpVtbl->SubmitSourceBuffer( wave_slot[sound_id].SNDs, &wave_slot[sound_id].SND_Tools, NULL );
		}
		break;
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////
//		source code from:Windows游戏编程大师技巧(第二版)\T3DCHAP10\demo10_3.cpp [AndreLamothe]
/////////////////////////////////////////////////////////////////////////////////////////////
ZBG_API int STDWIN32_CALL ZlLoadWindowsWave(char *filename)
{
	// this function loads a .wav file, sets up the directsound 
	// buffer and loads the data into memory, the function returns 
	// the id number of the sound

	HMMIO 			hwav;    // handle to wave file
	MMCKINFO		parent,  // parent chunk
					child;   // child chunk
	int	sound_id = -1,       // id of sound to be loaded
		index;               // looping variable
	char* name = NULL;		 // file name 

	// step one: are there any open id's ?
	for (index=0; index != 64; index++)
	{	
		// make sure this sound is unused
		if (wave_slot[index].FileName == 0)
		{
			sound_id = index;
			break;
		} // end if

	} // end for index

	// did we get a free id?
	if (sound_id==-1)
		return(-1);

	// set up chunk info structure
	parent.ckid 	    = (FOURCC)0;
	parent.cksize 	    = 0;
	parent.fccType	    = (FOURCC)0;
	parent.dwDataOffset = 0;
	parent.dwFlags		= 0;

	// copy data
	child = parent;

	// open the WAV file
	if ((hwav = mmioOpenA(filename, NULL, MMIO_READ | MMIO_ALLOCBUF))==NULL)
		return(-1);

	// descend into the RIFF 
	parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');

	if (mmioDescend(hwav, &parent, NULL, MMIO_FINDRIFF))
	{
		// close the file
		mmioClose(hwav, 0);

		// return error, no wave section
		return(-1); 	
	} // end if

	// descend to the WAVEfmt 
	child.ckid = mmioFOURCC('f', 'm', 't', ' ');

	if (mmioDescend(hwav, &child, &parent, 0))
	{
		// close the file
		mmioClose(hwav, 0);

		// return error, no format section
		return(-1); 	
	} // end if

	// now read the wave format information from file
	if (mmioRead(hwav, (char *)&wave_slot[sound_id].SND_Infos, sizeof(wave_slot[sound_id].SND_Infos)) != sizeof(wave_slot[sound_id].SND_Infos))
	{
		// close file
		mmioClose(hwav, 0);

		// return error, no wave format data
		return(-1);
	} // end if

	// make sure that the data format is PCM
	if (wave_slot[sound_id].SND_Infos.wFormatTag != WAVE_FORMAT_PCM)
	{
		// close the file
		mmioClose(hwav, 0);

		// return error, not the right data format
		return(-1); 
	} // end if

	// now ascend up one level, so we can access data chunk
	if (mmioAscend(hwav, &child, 0))
	{
		// close file
		mmioClose(hwav, 0);

		// return error, couldn't ascend
		return(-1); 	
	} // end if

	// descend to the data chunk 
	child.ckid = mmioFOURCC('d', 'a', 't', 'a');

	if (mmioDescend(hwav, &child, &parent, MMIO_FINDCHUNK))
	{
		// close file
		mmioClose(hwav, 0);

		// return error, no data
		return(-1); 	
	} // end if

	// finally!!!! now all we have to do is read the data in and
	// set up the directsound buffer

	// allocate the memory to load sound data
	wave_slot[sound_id].WaveSize = child.cksize;
	wave_slot[sound_id].ActulWaveData = dlmemalign(16,child.cksize);
	// read the wave data 
	mmioRead(hwav, (char *)wave_slot[sound_id].ActulWaveData, child.cksize);

	// close the file
	mmioClose(hwav, 0);

	if( FAILED(IBaseAudio->lpVtbl->CreateSourceVoice( IBaseAudio, &wave_slot[sound_id].SNDs, 
												(WAVEFORMATEX*)&wave_slot[sound_id].SND_Infos,
												0, XAUDIO2_DEFAULT_FREQ_RATIO, 
												NULL, NULL, NULL ) ) ) return FALSE;

	wave_slot[sound_id].SND_Tools.pAudioData = wave_slot[sound_id].ActulWaveData;
	wave_slot[sound_id].SND_Tools.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
	wave_slot[sound_id].Sound_Status = Zl_SOUND_BUFFER_READY;
	wave_slot[sound_id].SND_Tools.AudioBytes = child.cksize;
	wave_slot[sound_id].SND_Tools.LoopCount = 0;
	wave_slot[sound_id].SNDs->lpVtbl->Start(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
	name = strrchr(filename,'\\');
	wave_slot[sound_id].FileName = dlmemalign(16,(strlen(filename)+1));
	strcpy(wave_slot[sound_id].FileName,name != NULL ? name + 1 : filename);


	//wave_slot[sound_id].SNDs->lpVtbl->SubmitSourceBuffer( wave_slot[sound_id].SNDs, &wave_slot[sound_id].SND_Tools, NULL );
	//wave_slot[sound_id].SNDs->lpVtbl->FlushSourceBuffers(wave_slot[sound_id].SNDs);
	//wave_slot[sound_id].SNDs->lpVtbl->Stop(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
	//wave_slot[sound_id].SNDs->lpVtbl->Start(wave_slot[sound_id].SNDs,0,XAUDIO2_COMMIT_NOW);
	return(sound_id);

} // end DSound_Load_WAV

void _destroy_wave_slot(void) {

	int index;               // looping variable

	// step one: are there any open id's ?
	for (index=0; index != 64; index++)
	{	
		// make sure this sound is unused
		if (wave_slot[index].FileName != 0)
		{
			dlfree(wave_slot[index].FileName);
			dlfree(wave_slot[index].ActulWaveData);
			wave_slot[index].SNDs->lpVtbl->Stop(wave_slot[index].SNDs,0,XAUDIO2_COMMIT_NOW);
			wave_slot[index].SNDs->lpVtbl->FlushSourceBuffers(wave_slot[index].SNDs);
			wave_slot[index].SNDs->lpVtbl->DestroyVoice(wave_slot[index].SNDs);

		} // end if

	} // end for index
}

BOOL STDWIN32_CALL FSetchWave(const char* FileName) {

	DWORD nINX;
	HANDLE hFile;
	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	DWORD filetype;

	FOR (nINX=0; nINX != 64; nINX++) {

		if ( wave_slot[nINX].FileName == 0 ) {

			goto __Out;
		}
	}
	return FALSE;

__Out:
	hFile = CreateFileA( FileName,
						GENERIC_READ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING,
						0,
						NULL );

	if( INVALID_HANDLE_VALUE == hFile )
		return FALSE;

	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return FALSE;


	FindChunk(hFile,fourccRIFF,&dwChunkSize, &dwChunkPosition );	
	ReadChunkData(hFile,&filetype,sizeof(DWORD),dwChunkPosition);
	if (filetype != fourccWAVE)
		return FALSE;


	FindChunk(hFile,fourccFMT,&dwChunkSize, &dwChunkPosition );
	ReadChunkData(hFile, &wave_slot[nINX].SND_Infos, dwChunkSize, dwChunkPosition );

	FindChunk(hFile,fourccDATA,&dwChunkSize, &dwChunkPosition );
	wave_slot[nINX].ActulWaveData = dlmemalign(16,dwChunkSize);

	// BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, wave_slot[nINX].ActulWaveData, dwChunkSize, dwChunkPosition);

	if( FAILED(IBaseAudio->lpVtbl->CreateSourceVoice( IBaseAudio, &wave_slot[nINX].SNDs, 
												(WAVEFORMATEX*)&wave_slot[nINX].SND_Infos,
												0, XAUDIO2_DEFAULT_FREQ_RATIO, 
												NULL, NULL, NULL ) ) ) return FALSE;

	wave_slot[nINX].SND_Tools.pAudioData = wave_slot[nINX].ActulWaveData;
	wave_slot[nINX].SND_Tools.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
	wave_slot[nINX].SND_Tools.AudioBytes = dwChunkSize;
	wave_slot[nINX].SND_Tools.LoopCount = 0;

	wave_slot[nINX].SNDs->lpVtbl->SubmitSourceBuffer( wave_slot[nINX].SNDs, &wave_slot[nINX].SND_Tools, NULL );
}