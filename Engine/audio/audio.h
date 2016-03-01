//Imagine Engine
//Copyright (c) 2016 Szymon 'skprime' Krygier
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef _IE_AUDIO_H_
#define _IE_AUDIO_H_

#include "../platform/file.h"
#include "../platform/types.h"

class Game;

class Audio
{
	friend class Game;

public:
	static void playMusic(FilePath *musicFile);
	static void playMusic(FilePath *musicFile, U16 loops);
	static void pauseMusic();
	static void resumeMusic();
	static void stopMusic();
	static void setMusicVolume(U16 volume);
	static bool isMusicPlaying();
	static void playSoundEffect(FilePath *soundFile, U16 channel);
	static void playSoundEffect(FilePath *soundFile, U16 channel, U16 loops);
	static void stopSoundEffect(U16 channel);
	static void setChannelVolume(U16 channel, U16 volume);
	static bool isSoundEffectPlaying(U16 channel);

private:
	static void destroy();
};

#endif
