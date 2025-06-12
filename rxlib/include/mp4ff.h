/*
** FAAD2 - Freeware Advanced Audio (AAC) Decoder including SBR decoding
** Copyright (C) 2003-2005 M. Bakker, Nero AG, http://www.nero.com
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** Any non-GPL usage of this software or parts of this software is strictly
** forbidden.
**
** The "appropriate copyright message" mentioned in section 2c of the GPLv2
** must read: "Code from FAAD2 is copyright (c) Nero AG, www.nero.com"
**
** Commercial non-GPL licensing of this software is possible.
** For more info contact Nero AG through Mpeg4AAClicense@nero.com.
**
** $Id: mp4ff.h,v 1.27 2009/01/29 00:41:08 menno Exp $
**/

#ifndef MP4FF_H
#define MP4FF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

/* file callback structure */
typedef struct
{
    uint32_t (*read)(void *user_data, void *buffer, uint32_t length);
    uint32_t (*write)(void *udata, void *buffer, uint32_t length);
    uint32_t (*seek)(void *user_data, uint64_t position);
    uint32_t (*truncate)(void *user_data);
    void *user_data;
    uint32_t read_error;
} mp4ff_callback_t;

#ifdef USE_TAGGING

/* metadata tag structure */
typedef struct
{
    char *item;
    char *value;
    uint32_t len;
    uint32_t top;
} mp4ff_tag_t;

/* metadata list structure */
typedef struct
{
    mp4ff_tag_t *tags;
    uint32_t count;
} mp4ff_metadata_t;

int32_t mp4ff_meta_update(mp4ff_callback_t *f,const mp4ff_metadata_t * data);

#endif


#ifndef MP4FF_INTERNAL_H
/* mp4 main file structure */
typedef void* mp4ff_t;
#else
typedef struct
{
    int32_t type;
    int32_t channelCount;
    int32_t sampleSize;
    uint16_t sampleRate;
    int32_t audioType;

    /* stsd */
    int32_t stsd_entry_count;

    /* stsz */
    int32_t stsz_sample_size;
    int32_t stsz_sample_count;
    int32_t *stsz_table;

    /* stts */
    int32_t stts_entry_count;
    int32_t *stts_sample_count;
    int32_t *stts_sample_delta;

    /* stsc */
    int32_t stsc_entry_count;
    int32_t *stsc_first_chunk;
    int32_t *stsc_samples_per_chunk;
    int32_t *stsc_sample_desc_index;

    /* stsc */
    int32_t stco_entry_count;
    int32_t *stco_chunk_offset;

    /* ctts */
    int32_t ctts_entry_count;
    int32_t *ctts_sample_count;
    int32_t *ctts_sample_offset;

    /* esde */
    uint8_t *decoderConfig;
    int32_t decoderConfigLen;

    uint32_t maxBitrate;
    uint32_t avgBitrate;

    uint32_t timeScale;
    uint64_t duration;

} mp4ff_track_t;

/* mp4 main file structure */
typedef struct
{
    /* stream to read from */
    mp4ff_callback_t *stream;
    int64_t current_position;

    int32_t moov_read;
    uint64_t moov_offset;
    uint64_t moov_size;
    uint8_t last_atom;
    uint64_t file_size;
    uint32_t error;

    /* mvhd */
    int32_t time_scale;
    int32_t duration;

    /* incremental track index while reading the file */
    int32_t total_tracks;

    /* track data */
    mp4ff_track_t *track[MAX_TRACKS];

    /* metadata */
    mp4ff_metadata_t tags;
} mp4ff_t;
#endif


/* API */

mp4ff_t *mp4ff_open_read(mp4ff_callback_t *f);
mp4ff_t *mp4ff_open_read_metaonly(mp4ff_callback_t *f);
void mp4ff_close(mp4ff_t *f);
int32_t mp4ff_get_sample_duration(const mp4ff_t *f, const int32_t track, const int32_t sample);
int32_t mp4ff_get_sample_duration_use_offsets(const mp4ff_t *f, const int32_t track, const int32_t sample);
int64_t mp4ff_get_sample_position(const mp4ff_t *f, const int32_t track, const int32_t sample);
int32_t mp4ff_get_sample_offset(const mp4ff_t *f, const int32_t track, const int32_t sample);
int32_t mp4ff_find_sample(const mp4ff_t *f, const int32_t track, const int64_t offset,int32_t * toskip);
int32_t mp4ff_find_sample_use_offsets(const mp4ff_t *f, const int32_t track, const int64_t offset,int32_t * toskip);

int32_t mp4ff_read_sample(mp4ff_t *f, const int32_t track, const int32_t sample,
                          unsigned char **audio_buffer,  uint32_t *bytes);

int32_t mp4ff_read_sample_v2(mp4ff_t *f, const int track, const int sample,unsigned char *buffer);//returns 0 on error, number of bytes read on success, use mp4ff_read_sample_getsize() to check buffer size needed
int32_t mp4ff_read_sample_getsize(mp4ff_t *f, const int track, const int sample);//returns 0 on error, buffer size needed for mp4ff_read_sample_v2() on success



int32_t mp4ff_get_decoder_config(const mp4ff_t *f, const int32_t track,
                             unsigned char** ppBuf, uint32_t* pBufSize);
int32_t mp4ff_get_track_type(const mp4ff_t *f, const int track);
int32_t mp4ff_total_tracks(const mp4ff_t *f);
int32_t mp4ff_num_samples(const mp4ff_t *f, const int32_t track);
int32_t mp4ff_time_scale(const mp4ff_t *f, const int32_t track);

uint32_t mp4ff_get_avg_bitrate(const mp4ff_t *f, const int32_t track);
uint32_t mp4ff_get_max_bitrate(const mp4ff_t *f, const int32_t track);
int64_t mp4ff_get_track_duration(const mp4ff_t *f, const int32_t track); //returns (-1) if unknown
int64_t mp4ff_get_track_duration_use_offsets(const mp4ff_t *f, const int32_t track); //returns (-1) if unknown
uint32_t mp4ff_get_sample_rate(const mp4ff_t *f, const int32_t track);
uint32_t mp4ff_get_channel_count(const mp4ff_t * f,const int32_t track);
uint32_t mp4ff_get_audio_type(const mp4ff_t * f,const int32_t track);


/* metadata */
int32_t mp4ff_meta_get_num_items(const mp4ff_t *f);
int32_t mp4ff_meta_get_by_index(const mp4ff_t *f, uint32_t index,
                            char **item, char **value);
int32_t mp4ff_meta_get_title(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_artist(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_writer(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_album(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_date(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_tool(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_comment(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_genre(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_track(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_disc(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_totaltracks(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_totaldiscs(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_compilation(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_tempo(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_coverart(const mp4ff_t *f, char **value);
int32_t mp4ff_meta_get_coverart2(const mp4ff_t *f, int32_t *top, int32_t *len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
