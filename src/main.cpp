#include <bn_core.h>
#include <bn_dmg_music.h>
#include <bn_dmg_music_item.h>
#include <bn_format.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_vector.h>

#include "SongInfo.hpp"
#include "SongKind.hpp"
#include "SramSave.hpp"

#include "common_variable_8x16_sprite_font.h"

static constexpr int SELECT_TEXT_SPR_CNT = 20;
static constexpr int PLAYING_TEXT_SPR_CNT = 40;

void select_song(int song_index, bn::vector<bn::sprite_ptr, SELECT_TEXT_SPR_CNT>& text_select,
                 bn::sprite_text_generator&);
void play_song(int song_index, bn::vector<bn::sprite_ptr, PLAYING_TEXT_SPR_CNT>& text_playing, cr::SramSave&,
               bn::sprite_text_generator&);

int main()
{
    bn::core::init();

    bn::sprite_text_generator text_gen(common::variable_8x16_sprite_font);
    text_gen.set_center_alignment();

    bn::vector<bn::sprite_ptr, 64> text_static;
    bn::vector<bn::sprite_ptr, PLAYING_TEXT_SPR_CNT> text_playing;
    bn::vector<bn::sprite_ptr, SELECT_TEXT_SPR_CNT> text_select;
    bn::vector<bn::sprite_ptr, 20> text_desc;

    cr::SramSave sram_save;
    int song_index = sram_save.read_song_index();

    text_gen.generate(0, -60, "copyrat90's GB songs", text_static);
    play_song(song_index, text_playing, sram_save, text_gen);
    select_song(song_index, text_select, text_gen);
    text_gen.generate(0, 45, "A: Play", text_static);
    text_gen.generate(0, 60, "B: Pause/Resume", text_static);

    while (true)
    {
        if (bn::keypad::a_pressed())
            play_song(song_index, text_playing, sram_save, text_gen);
        else if (bn::keypad::b_pressed())
        {
            if (bn::dmg_music::paused())
                bn::dmg_music::resume();
            else
                bn::dmg_music::pause();
        }
        else if (bn::keypad::left_pressed())
        {
            song_index = (song_index - 1 + (int)cr::SongKind::TOTAL_COUNT) % (int)cr::SongKind::TOTAL_COUNT;
            select_song(song_index, text_select, text_gen);
        }
        else if (bn::keypad::right_pressed())
        {
            song_index = (song_index + 1) % (int)cr::SongKind::TOTAL_COUNT;
            select_song(song_index, text_select, text_gen);
        }

        bn::core::update();
    }
}

void select_song(int song_index, bn::vector<bn::sprite_ptr, SELECT_TEXT_SPR_CNT>& text_select,
                 bn::sprite_text_generator& text_gen)
{
    const auto& song_info = cr::SongInfo::get((cr::SongKind)song_index);

    text_select.clear();
    text_gen.generate(0, 20,
                      bn::format<90>("< {} ({}/{}) >", song_info.title, song_index + 1, (int)cr::SongKind::TOTAL_COUNT),
                      text_select);
}

void play_song(int song_index, bn::vector<bn::sprite_ptr, PLAYING_TEXT_SPR_CNT>& text_playing, cr::SramSave& sram_save,
               bn::sprite_text_generator& text_gen)
{
    const auto& song_info = cr::SongInfo::get((cr::SongKind)song_index);

    text_playing.clear();
    text_gen.generate(0, -35, bn::format<25>("Now playing #{}", song_index + 1), text_playing);
    text_gen.generate(0, -20, song_info.title, text_playing);
    text_gen.generate(0, -5, song_info.license_str, text_playing);

    sram_save.write_song_index(song_index);

    song_info.song.play();
}
