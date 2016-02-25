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

#include "audio.h"

#include "../error/error.h"
#include "../platform/resourceLoader.h"

void Audio::playMusic(FilePath *musicFile)
{
	playMusic(musicFile, 0);
}

void Audio::playMusic(FilePath *musicFile, U16 loops)
{
	if(Mix_PlayingMusic() || Mix_PausedMusic()) return;

	Mix_Music *music = ResourceLoader::loadMusic(musicFile);

	Mix_PlayMusic(music, loops);
}

void Audio::pauseMusic()
{
	if(Mix_PlayingMusic()) Mix_PauseMusic();
}

void Audio::resumeMusic()
{
	if(Mix_PausedMusic()) Mix_ResumeMusic();
}

void Audio::stopMusic()
{
	if(!Mix_PlayingMusic()) return;

	Mix_HaltMusic();
}

void Audio::setMusicVolume(U16 volume)
{
	if(!Mix_PlayingMusic()) return;

	Mix_VolumeMusic(volume);
}

bool Audio::isMusicPlaying()
{
	if(Mix_PlayingMusic()) return true;

	return false;
}

void Audio::playSoundEffect(FilePath *soundFile, U16 channel)
{
	playSoundEffect(soundFile, channel, 0);
}

void Audio::playSoundEffect(FilePath *soundFile, U16 channel, U16 loops)
{
	if(Mix_Playing(channel)) return;

	Mix_Chunk *soundEffect = ResourceLoader::loadSound(soundFile);

	Mix_PlayChannel(channel, soundEffect, loops);
}

void Audio::stopSoundEffect(U16 channel)
{
	if(!Mix_Playing(channel)) return;

	Mix_HaltChannel(channel);
}

void Audio::setChannelVolume(U16 channel, U16 volume)
{
	if(!Mix_Playing(channel)) return;

	Mix_Volume(channel, volume);
}

bool Audio::isSoundEffectPlaying(U16 channel)
{
	if(Mix_Playing(channel)) return true;

	return false;
}
