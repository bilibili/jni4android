/*
 * copyright (c) 2015 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of jni4android.
 *
 * jni4android is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * jni4android is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with jni4android; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "j4a/j4a_internal.h"
#include "j4a/class/java/nio/ByteBuffer.h"
#include "j4a/class/java/util/ArrayList.h"
#include "j4a/class/android/os/Build.h"
#include "j4a/class/android/media/AudioTrack.h"
#include "j4a/class/android/media/MediaCodec.h"
#include "j4a/class/android/media/MediaFormat.h"
#include "j4a/class/android/media/PlaybackParams.h"
#include "j4a/class/android/os/Bundle.h"
#include "j4a/class/tv/danmaku/ijk/media/player/IjkMediaPlayer.h"
#include "j4a/class/tv/danmaku/ijk/media/player/misc/IMediaDataSource.h"

#define J4A_LOAD_CLASS(class__) \
    do { \
        ret = J4A_loadClass__J4AC_##class__(env); \
        if (ret) \
            goto fail; \
    } while (0)

int J4A_LoadAll__catchAll(JNIEnv *env)
{
    int ret = 0;

    J4A_LOAD_CLASS(ByteBuffer); // java_nio_ByteBuffer
    J4A_LOAD_CLASS(ArrayList);  // java_util_ArrayList

    // must load before all other android classes
    J4A_LOAD_CLASS(android_os_Build);

    J4A_LOAD_CLASS(AudioTrack);     // android_media_AudioTrack
    J4A_LOAD_CLASS(MediaCodec);     // android_media_MediaCodec
    J4A_LOAD_CLASS(MediaFormat);    // android_media_MediaFormat
    J4A_LOAD_CLASS(PlaybackParams); // android_media_PlaybackParams
    J4A_LOAD_CLASS(Bundle);         // android_os_Bundle

    J4A_LOAD_CLASS(IjkMediaPlayer);     // tv_danmaku_ijk_media_player_IjkMediaPlayer
    J4A_LOAD_CLASS(IMediaDataSource);   // tv_danmaku_ijk_media_player_misc_IMediaDataSource

fail:
    return ret;
}
